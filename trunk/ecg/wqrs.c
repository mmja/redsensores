#include <math.h>
#include "wqrs.h"
//VARIABLES

//Para el Paso 1
int16_t *f0;//Fo= se�al original
//int16_t *f;//F= se�al despu�s del preprocesado
int16_t *Bo,*Bc;//B, Bo (apertura) y Bc (cierre) = se seleccionan bas�ndose en las propiedades de las ondas caracter�sticas de ECG (elementos estructurales)
int16_t *B1,*B2;
int16_t from=0,count=0, init=0;  //readed values number

//para el paso 1
int16_t *signal1; //filtering for noise reduction and baseline correction signal

//para el paso 2
int16_t *mf; //multiscale morphological transformed signal


//TODOS SON ARRAYS DE 2 POSICIONES EN LA POS.0 SE GUARDA LA POSICION DE INCIO DE f y en la POS.1 la posicion final respecto de f
int16_t Rpeak;//Paso 3 Rpeak= Local minimo entre Thf y Thr. 
int16_t *Rwave;//Paso 4 (entre el primer max local a la izq y a la derecha de Rpeak)X CADA RPEAK????
int16_t Qwave;//Paso 5 (puede que no se detecte)1� minimo local a la izq de Rwave
int16_t Swave;//Paso 6 (puede que no se detecte)1�minimo local desde la drecha de la parte positiva de Rwave

//Paso 7: Onset y Offset de Pwave y Twave (puede que no se detecte)
int16_t *Pwave;// los 2 primeros maximos locales desde la izq de Pwave
int16_t *Twave;// los 2 primeros maximos locales desde la dcha de Twave

//CONSTANTES (DESPUES HABRA QUE PONERLO COMO #define ... N�)
int16_t s; //window length of (2s+1) samples, s<W*Fs, para el Paso 2 (mmt)
//int8_t /*thf=150,*/ thr; //threshold para el Paso 3 (detectar los Rpeaks) 
int32_t detecinterval; // detection interval= 0,12 segundos, se usa en el Paso 5 y 6 (Qwave y Swave)

//int16_t* results0,*results1,*results2,*results3,*results4,*results5,*results6,*results7,*results8,*results9,*results10,*results11; 

//*************************************************************************************
//This function return the value (in raw adus) of sample number current in open signal s,
//if successful, or the value of the previous successfully read sample.
int16_t getsample( int16_t dat,int16_t *f){
 	static int16_t v;
    /* If the caller specified a negative sample number, prepare to return
       sample 0.  This behavior differs from the convention that only the
       absolute value of the sample number matters. */
    if (dat < 0L) dat = 0L;
    //if (dat+from>to) dat = to-from; 
    /* The requested sample is in the buffer.  Set sample_vflag and
       return the requested sample. */
    if ((v = (f[(dat)&(BUFLN-1)] /*+ s*/)) == WFDB_INVALID_SAMPLE || v==0 )
        sample_vflag = -1;
    else
        sample_vflag = 1;
    return (v);
}
//********************************************************************************************
// step1: morphological filtering for noise reduction and baseline correction
//********************************************************************************************

//************************************************************************************

int16_t* erosion(int16_t *f, int16_t *B,int16_t lon){
	
	int16_t i;
	int16_t j;
	int16_t min;
	int16_t *result;
	//if (result[(from+(lon-1)/2)&(BUFLN-1)]==0){
	
		
		
		result =(int16_t *)malloc(BUFLN*sizeof(int16_t));
	if(result!=NULL){
		for(i=0;i<(lon-1)/2;i++){
			result[(init+i)&(BUFLN-1)]=f[(init+i)&(BUFLN-1)];	
		}
		for(i=(lon-1)/2;i<(BUFLN-(lon+1)/2);i++){
			min=f[(init+i-(lon-1)/2)&(BUFLN-1)]-B[0];
			for(j=1;j<lon;j++){
				if(min > (f[(init+i-((lon-1)/2)+j)&(BUFLN-1)] - B[j])) min= f[(init+i-(lon-1)/2+j)&(BUFLN-1)] - B[j];
			
			}
			result[(init+i)&(BUFLN-1)]=min;	
		}
		for(i=(BUFLN-(lon+1)/2);i<BUFLN;i++){
			result[(init+i)&(BUFLN-1)]=f[(init+i)&(BUFLN-1)];	
		}
		return result;			
	}	else {dbg(DBG_USR1, "Erosion: No hay espacio\n"); return NULL;	}
	
	
	
}

int16_t* dilation(int16_t *f, int16_t *B, int16_t lon){
	
	int16_t i,j;
	int16_t max;
	int16_t *result;
	//if (result[(from+(lon-1)/2)&(BUFLN-1)]==0){
	
	result =(int16_t *)malloc(BUFLN*sizeof(int16_t));
	if(result!=NULL){	
		for(i=0;i<(lon-1)/2;i++){
			result[(init+i)&(BUFLN-1)]=f[(init+i)&(BUFLN-1)];	
		}
		for(i=(lon-1)/2;i<BUFLN-(lon+1)/2;i++){
			max=f[(init+i-(lon-1)/2)&(BUFLN-1)]+ B[0];
			for(j=1;j<lon;j++){
				if(max < (f[(init+i-((lon-1)/2)+j)&(BUFLN-1)] + B[j])) max=f[(init+i-((lon-1)/2)+j)&(BUFLN-1)] + B[j];
		
			}
			result[(init+i)&(BUFLN-1)]=max;
		}
		for(i=(BUFLN-(lon+1)/2);i<BUFLN;i++){
			result[(init+i)&(BUFLN-1)]=f[(init+i)&(BUFLN-1)];	
		}
		return result;
	}else {
		
		dbg(DBG_USR1, "Dilation: No hay espacio\n");
		return NULL;	
	}
	
}

int16_t* opening(int16_t *f, int16_t *B, int16_t lon){
	int16_t *aux,*sol;
	aux=erosion(f,B, lon);
	sol= dilation(aux,B, lon);
	(void)free(aux);
	return sol;	
}

int16_t* closing(int16_t *f, int16_t *B, int16_t lon){
	int16_t *aux,*sol;
	aux=dilation(f,B,lon);
	sol= erosion(aux,B,lon);
	(void)free(aux);
	return sol;	
		
}

//**************************************************************************************
int16_t* mmf(int16_t *f){
	int16_t i;
	int16_t *fb;//Fb=se�al de correcci�n de l�nea
	int16_t *res=(int16_t *)malloc(BUFLN*sizeof(int16_t)),*sol=(int16_t *)malloc(BUFLN*sizeof(int16_t));
	int16_t *first,*second;
    int16_t *aux,*aux1;
	//static int16_t** results;
	
	
	//iniciacion de las matrices
	int16_t lo=LQRS*FS;
	int16_t lc=1.5*lo;
	int16_t l1=5;
	Bo=(int16_t*)malloc(lo*sizeof(int16_t));
	Bc=(int16_t*)malloc(lc*sizeof(int16_t));
	for(i=0;i<lc;i++){
		Bc[i]=0;	
	}
	for(i=0;i<lo;i++){
		Bo[i]=0;	
	}
	//The structuring element used for noise suppression has length 5 and values of (0, 1, 5, 1, 0).
	B1=(int16_t*)malloc(l1*sizeof(int16_t));
	B1[0]=0;  B1[1]=1;   B1[2]=5;   B1[3]=1;   B1[4]=0;
	B2=(int16_t*)malloc(l1*sizeof(int16_t));
	for(i=0;i<l1;i++){
		B2[i]=0;	
	}
	
	//int16_t B1[]={0,1,5,1,0};
	/*if(results==NULL){
		
		results=(int16_t **)malloc(12*sizeof(int16_t*));
		
	}*/
	
	aux=opening(f,Bo,lo );
	fb=closing(aux,Bc,lc);
	(void)free(aux);
	
	//noise suppresion
	for(i=0;i<BUFLN;i++){
		res[i]=f[i]-fb[i];	
	}
	//formula 2
	aux=dilation(res,B1,l1);
	first=erosion(aux,B2,l1);
	(void)free(aux);
	
	aux=erosion(res,B1,l1);
	second=dilation(aux,B2,l1);
	(void)free(aux);
	
	//formula 1
	/*aux=opening(res,B1,l1);
	first=closing(aux,B1,l1);
	(void)free(aux);
	
	aux=closing(res,B1,l1);
	second=opening(aux,B1,l1);
	(void)free(aux);
	*/
	//first=closing(opening(res,B1,l1),B1,l1);
	//second=opening(closing(res,B1,l1),B1,l1);
	
	
	for(i=0;i<BUFLN;i++){
		sol[i]=(first[i]+second[i])/2;	
	}
	aux=dilation(f,Bo,lo );
	aux1=erosion(aux,Bo,lo);
	//dbg(DBG_USR1, "\%d --> MMF:   %d   fb:  %d  %d  %d  value:   \%d\n", from, f[(from)&(BUFLN-1)],aux[(from)&(BUFLN-1)],fb[(from)&(BUFLN-1)],
	//res[(from)&(BUFLN-1)],sol[(from)&(BUFLN-1)]);
	
	(void)free(fb);
	(void)free(first);
	(void)free(second);
	(void)free(Bo);
	(void)free(Bc); 
	(void)free(B1);
	(void)free(res);
	
	return sol;
	
}

//********************************************************************************************
// step2: multiscale morphological transform 
//********************************************************************************************
int16_t mmt(int16_t current,int16_t *f){
	int16_t i;
	static int16_t tt=0;
	if (mf == NULL) {
		mf = (int16_t *)malloc(BUFLN*sizeof(int16_t));		
		for(i=0;i<s;i++){
			mf[i&(BUFLN-1)]=0;	
			
		}
		tt=s;
    }
    
    if ((current < from) && (current > count - s) ) {
		
	    return -1;
    }
	
    
    while(tt<current){
		int16_t max=0;
		int16_t min=0;
		int16_t t;
		int16_t aux;
		for (t = tt-s; t <= tt+s; t++){ //find the maximum and minimum local values 
			if((aux=getsample(t,f))!= WFDB_INVALID_SAMPLE){
				if (aux > max) max = aux;
				if (aux < min) min = aux;
			}
		}
		mf[tt&(BUFLN-1)]=((max+min-2*getsample(tt,f)) / s);
		//dbg(DBG_USR1, "\%d --> MMF:   %d   fb:  %d  %d  %d  value:   \%d\n", from, f[(from)&(BUFLN-1)],tt);
		tt++;
    }	
    return mf[current&(BUFLN-1)];
	
	
}	
	
//********************************************************************************************
// step3: Rpeaks detection, the local maxima and minima
// return 1 if there aren't any rpeaks detected
//********************************************************************************************
int8_t rpeak_detection(int16_t *f){
// Se calcula Rpeak de tipo int16_t.
// Se van buscando las locales minimas entre Thf y Thr.
// devuelve 0 si todo fue OK y 1 si fallo algo.
    int16_t r, ab; //posicion del minimo
    int16_t  mt, thr;
 
    
    int16_t right_local_min;
    right_local_min=mmt(from,f);
   
    // buscamos el 1� minimo hacia la izqda:
	r=(from+1);
	thr=160; 
    while(mf!=NULL && r<(count-s)){
	    mt=mmt(r,f);
	    if(right_local_min>=mt)
	    	right_local_min=mt;
    
	    else {
		    
		    ab=abs(right_local_min);
	    	if(ab>thr){Rpeak=r-1;return 0;}
    	}
	    	
	    r++;    
    }
	return 1;
	
}

//********************************************************************************************
// step4: Rwave detection
// return 1 if there aren't any rwave detected
//********************************************************************************************
int8_t rwave(int16_t *f){
	
	int16_t right_local_max;
	int16_t left_local_max;
	int16_t r,l;//posiciones right y left
	//For the Rpeak:   	
    	right_local_max= mmt(Rpeak,f);
    	left_local_max= mmt(Rpeak,f);
    //busca 1� maximo local a la derecha:	    
    for(r=(Rpeak+1);r<count-s && right_local_max<mmt(r,f);r++){
	    right_local_max=mmt(r,f);	    
	}
    r--;
    
    //busca 1� maximo local a la izquierda:    
     for(l=(Rpeak-1);l>=from && left_local_max<mmt(l,f);l--){    
	    left_local_max=mmt(l,f);	    
	}
    l++;
  
    // si los ha encontrado, crea Rwave y devuelve 0, sino devuelve 1
    if(r< count-s && l>=from )
    {		
		Rwave[0]=l;
		Rwave[1]=r;
		return 0;	
	}
    else return 1;
  
}

//********************************************************************************************
// step5: Qwave detection
//********************************************************************************************
int8_t qwave(int16_t *f){
	
	//Calculamos el 1� minimo local a la izq de Rwave (del intervalo de Rwave no??)
	int16_t left_local_min= mmt(Rwave[0],f);//partimos de la izq de Rwave.
	int16_t l; //posicion del minimo
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	
	
	t1 = detecinterval;
		
	// buscamos el 1� minimo hacia la izqda:
	 for(l=(Rwave[0]-1);l>=from && left_local_min>mmt(l,f)&&(t1!=0);l--,t1--){    
	    left_local_min=mmt(l,f);	    
	}
    l++;
	
	
	// si los ha encontrado, crea Qwave y devuelve 0, sino devuelve 1
    	if(l>=from && (t1!=0)) 
		{
			Qwave=l;			
		//Qwave[1]=Rwave[0];
			return 0;
		}
    	else return 1;
}
//********************************************************************************************
// step6: Swave detection
//********************************************************************************************
int8_t swave(int16_t *f){
	
	//Calculamos el 1� minimo local a la DCHA de Rwave
	
	// OJO !!!!!!!!!!!!!!!FALTA VER CUAL ES LA PARTE POSITIVA


	int16_t right_local_min= mmt(Rwave[1],f);//partimos de la izq de Rwave.
	int16_t r; //posicion del minimo
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	
	t1 = detecinterval;
		
	// buscamos el 1� minimo hacia la izqda:
	 for(r=(Rwave[1]+1);r<count-s && right_local_min>mmt(r,f)&&(t1!=0);r++,t1--){    
	    right_local_min=mmt(r,f);	    
	}
    r--;

	// si los ha encontrado, crea Qwave y devuelve 0, sino devuelve 1
    	if(r<count-s && (t1!=0)) 
		{
			Swave=r;			
			return 0;
		}
    	else return 1;
}
//*******************************************************************************************
//***************************  METODOS AUXILIARES ********************************************
//**********************************************************************************************
int8_t pwave(int16_t *f){

	
	//Pwave=Buscamos 2 maximos locales desde Qwave hacia la izq:
	int8_t offsetP;
	
	int8_t left1;	//posicion 1� max (onset)
	int8_t left2;	//posicion 2� max(offset)
	
	//Buscamos el onset de Pwave (1� maximo local) y el offset (2� maximo local)
	int8_t onsetP=mmt(Qwave,f);

	//busca 1� maximo local a la izquierda (onset Pwave):   
	for(left1=(Qwave-1);left1>=from && onsetP<mmt(left1,f);left1--){    
	    onsetP=mmt(left1,f);	    
	}
    left1++;
	//busca 2� maximo local a la izquierda(offset Pwave):   
	offsetP=mmt(left1-1,f);
	
	 for(left2=(left1-1);left2>=from && offsetP<mmt(left2,f);left2--){    
	    offsetP=mmt(left2,f);	    
	}
    left2++;
	
	 // si los ha encontrado, crea Rwave y devuelve 0, sino devuelve 1
    if(left1>=from && left2>=from )
    {		
		Pwave[0]=left1;//onset
		Pwave[1]=left2;//offset
		return 0;	
	}
    else return 1; 
}	
//********************************************************
int8_t twave(int16_t *f){
	
	//Twave=Buscamos 2 maximos locales desde Swave hacia la dcha:
	int8_t offsetT;
	
	int8_t right1;	//posiciion 1� max (onset)
	int8_t right2;	//posicion 2� max(offset)
	
	//Buscamos el onset de Twave (1� maximo local) y el offset (2� maximo local)
	int8_t onsetT=mmt(Swave,f);

	
	//busca 1� maximo local a la derecha (onset Twave):   
	for(right1=(Swave+1);right1<count-s && onsetT<mmt(right1,f);right1++){
	    onsetT=mmt(right1,f);	    
	}
    right1--;
	//busca 2� maximo local a la derecha (offset Twave):   
	offsetT=mmt(right1+1,f);
	
	 for(right2=(right1+1);right2<count-s  && offsetT<mmt(right2,f);right2++){    
	    offsetT=mmt(right2,f);	    
	}
    right2--;
	
	 // si los ha encontrado, crea Rwave y devuelve 0, sino devuelve 1
    if(right1< count-s && right2< count-s )
    {		
		Twave[0]=right1;//onset
		Twave[1]=right2;//offset
		return 0;	
	}
    else return 1; 
}	

//********************************************************************************************
// step7: onset and offset, Pwave and Twave detection
//********************************************************************************************
int8_t TandPwave(int16_t *f){
	
int8_t ok;
	
	ok=pwave(f);
	ok = ok || twave(f);
	
return ok;	
	 
	 
}



//*******************************************************************************************
//***************************  METODO PRINCIPAL ********************************************
//**********************************************************************************************

int32_t wqrs(int16_t datum, int16_t *buffer)
{ 
	int8_t correct=0,correct1=-1; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)
	int16_t *fp;//F= se�al despu�s del preprocesado
	detecinterval=(int16_t)(0.12*FS + 0.5);
    s=FS*W-1;
	
	buffer[count&(BUFLN-1)]=datum; //metemos el dato en el buffer
	count++;
	init=count-BUFLN;  
	from=init+NOPS*(1.5*LQRS*FS-1)/2;
	
		
	//llenado inicial del bucle
	if(count<BUFLN){
		
		return 0;
	}
	//tiempo inicial para fijar los umbrales thr y thf

	
	// Step 1: morphological filtering for noise reduction and baseline correction
	fp=mmf(buffer);
	
	//dbg(DBG_USR1, "\%d --> MMF: \%d  value: \%d\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)]);
	// Step 2: multiscale morphological transform 
	mmt(from,fp);
	dbg(DBG_USR1, "\%d --> f: \%d   MMF:   \%d  value:  \%d\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)],mf[(from)&(BUFLN-1)]);
	// Step 3: Rpeaks detection, the local maxima and minima
	correct1=rpeak_detection(fp);
	/*if (correct1==0){
		dbg(DBG_USR1, "\%d --> MMF:\%d  value: \%d  Rpeak:\%d\n",from,fp[(from)&(BUFLN-1)],mmt(from,fp),Rpeak);
		correct =-1;
	}else{ dbg(DBG_USR1, "\%d --> MMF:\%d  value: \%d\n",from,fp[(from)&(BUFLN-1)],mmt(from,fp));}
	*/// Step 4: Rwave detection
	
	/*if (correct==0)
		correct=rwave(fp);
	
	if (correct==0){
		// Step 5: Qwave detection
		qwave(fp);
		// Step 6: Swave detection
		correct=swave(fp);
		// Step 7: onset and offset, Pwave and Twave detection
		if (correct==0) 
			correct=TandPwave(fp);
	}
	(void)free(fp);
	//if(correct==0)//todo ha sido detectado
		return 0;
	*/
	//(void)free(fp);
	return 1;
}
void freeBuffers(){
	(void)free(f0);
    (void)free(mf);

}

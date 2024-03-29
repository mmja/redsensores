/**********************************************************************************************************
/ VERSION 0.1 - Monica Jimenez, Laura Gutierrez
/ Con Punteros. Sin ninguna optimizacion.
/ No soportada por el Nodo (por usar punteros).                    
/***********************************************************************************************************/

#include <math.h>
#include "wqrs.h"

//Para el Paso 1
int16_t *f0;//Fo= se�al original
int16_t *Bo,*Bc;//B, Bo (apertura) y Bc (cierre) = se seleccionan bas�ndose en las propiedades de las ondas caracter�sticas de ECG (elementos estructurales)
int16_t *B1,*B2;
int16_t from=0,count=0, init=0,to=0;  //readed values number
int16_t notnoise;
int16_t thr,thf; //threshold
int8_t initialize=1;
int16_t distance;
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
int32_t detecinterval,detecinterval2; // detection interval= 0,12 segundos, se usa en el Paso 5 y 6 (Qwave y Swave)

//*************************************************************************************
//This function return the value (in raw adus) of sample number current in open signal s,
//if successful, or the value of the previous successfully read sample.
int16_t getsample( int16_t dat,int16_t *f){
 	static int16_t v;
    /* If the caller specified a negative sample number, prepare to return
       sample 0.  This behavior differs from the convention that only the
       absolute value of the sample number matters. */
    if (dat < 0L) dat = 0L;
  
    /* The requested sample is in the buffer.  Set sample_vflag and
       return the requested sample. */
    if ((v = (f[(dat)&(BUFLN-1)])) == WFDB_INVALID_SAMPLE)
        sample_vflag = -1;
    else
        sample_vflag = 1;
    return (v);
}
//********************************************************************************************
// step1: morphological filtering for noise reduction and baseline correction
//********************************************************************************************

int16_t* erosion(int16_t *f, int16_t *B,int16_t lon){
	
	int16_t i;
	int16_t j;
	int16_t min;
	int16_t *result;
		
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
	
	//baseline correction
	
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
    
    if ((current < from) && (current > to) ) {
		
	    return -1;
    }
	
    
    while(tt<=current){
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
		mf[tt&(BUFLN-1)]=((max+min-2*getsample(tt,f))*10 / s);
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
    int16_t r; //posicion del minimo
    int16_t  mt;
 	int16_t igual;//primera posicion de minimo en caso de que haya varios segudios iguales
    
   
    // buscamos el 1� minimo hacia la izqda:
	r=(from+1);
	
    while(mf!=NULL && r<to){
	    mt=mmt(r,f);
	 
	  //SI ES UN MINIMO UNICO
	  	if(mmt(r-1,f)>mt && mt<mmt(r+1,f)){
	    	
			
		    //ab=abs(mt);
	    	if(mt<(-1*thr)){
		    	//dbg(DBG_USR1, "ab: \%d ,thr:%d",ab,thr);
		    	Rpeak=r;return 1;}
    	
		}
		//PARTE NUEVA QUE BUSCA EL MINIMO LOCAL, DEVUELVE EL PRIMERO SI ES LLANURA  \___/
		//----------------------------------------------------------------
		//SI ES EL 1� DE UNA LLANURA
		if(mmt(r-1,f)>mt && mt==mmt(r+1,f))igual=r;
		//SI ES EL ULTIMO DE LA LLANURA Y EL SIGUIENTE ES MAYOR
		if(mmt(r-1,f)==mt && mt<mmt(r+1,f)){
			if(mt<(-1*thr)){
		    	Rpeak=igual; return 1;}
		}
	    	
	    r++;    
    }
	return 0;
	
}

//********************************************************************************************
// step4: Rwave detection
// return 1 if there aren't any rwave detected
//********************************************************************************************
int8_t rwave(int16_t *f){
	
	int16_t right_local_max;
	int16_t left_local_max;
	int16_t r,l;//posiciones right y left
	int16_t right,left;//verdadera posicion del maximo hacia la dcha
	if(Rwave==NULL) Rwave=(int16_t *)malloc(2*sizeof(int16_t));		
	right=-1;
	left=-1;
	//For the Rpeak:   	
    	right_local_max= mmt(Rpeak,f);
    	left_local_max= mmt(Rpeak,f);
    //busca 1� maximo local a la derecha:	
           
    for(r=(Rpeak+1);r<to && !(right_local_max<= mmt(r,f) && mmt(r,f)>mmt(r+1,f) && abs(mmt(r,f) )>thf);r++){
	    //el primero igual lo guardamos   
	     if(right_local_max< mmt(r,f)&& mmt(r,f)==mmt(r+1,f)){right=r;}		    
	    right_local_max=mmt(r,f);
	}
	    
    //busca 1� maximo local a la izquierda:   
       
     for(l=(Rpeak-1);l>=from && !(left_local_max<=mmt(l,f) && mmt(l,f)>mmt(l-1,f) && abs(mmt(l,f) )>thf);l--){ 
	     //el primero igual lo guardamos   
	     if(left_local_max< mmt(l,f)&& mmt(l,f)==mmt(l-1,f)){left=l;}	
	    left_local_max=mmt(l,f);	    
	}  
    // si los ha encontrado, crea Rwave y devuelve 0, sino devuelve 1
    if(r< to && l>=from )
    {		//comprobamos si habia algun valor guardado antes
		if(left != -1)Rwave[0]=left;else Rwave[0]=l;
		if(right != -1)Rwave[1]=right;else Rwave[1]=r;
		return 1;	
	}
    else return 0;
  
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
	 for(l=(Rwave[0]-1);l>=from && !(left_local_min>mmt(l,f) && mmt(l,f)<=mmt(l-1,f) && abs(mmt(l,f))>thf)&&(t1!=0);l--,t1--){  
		 
		//el primero igual lo guardamos   
		 
	    left_local_min=mmt(l,f);	    
	}
	Qwave=l;	
	// si los ha encontrado, crea Qwave y devuelve 0, sino devuelve 1
    	if(l>=from && (t1!=0)) 
		{
			return 1;
		}
    	else{ 
	    	
	    	return 0;
    	}
}
//********************************************************************************************
// step6: Swave detection
//********************************************************************************************
int8_t swave(int16_t *f){
	
	//Calculamos el 1� minimo local a la DCHA de Rwave
	int16_t right_local_min= mmt(Rwave[1],f);//partimos de la izq de Rwave.
	int16_t r; //posicion del minimo
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	
	t1 = detecinterval;
		
	// buscamos el 1� minimo hacia la izqda:
	 for(r=(Rwave[1]+1);r<to && !(right_local_min>mmt(r,f) && mmt(r,f)<=mmt(r+1,f) && abs(mmt(r,f))>thf)&&(t1!=0);r++,t1--){    
		 
		//if(right_local_min> mmt(r,f)&& mmt(r,f)==mmt(r+1,f)){right=r;}	
		 
	    right_local_min=mmt(r,f);	    
	}
   		Swave=r;	
	// si los ha encontrado, crea Qwave y devuelve 0, sino devuelve 1
    	if(r<to && (t1!=0))  
		{	
			
			return 1;
		}
    	else return 0;
}


//********************************************************************************************
// step7: onset and offset, Pwave and Twave detection
//********************************************************************************************
	 
	 
int8_t pwave(int16_t *f){

	
	//Pwave=Buscamos 2 maximos locales desde Qwave hacia la izq:
	int16_t offsetP;
	
	int16_t left1=0;	//posicion 1� max (onset)
	int16_t left2=0;	//posicion 2� max(offset)
	int16_t onsetP;
	int16_t l;
	int8_t encontrado=0;
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
		
	t1 = detecinterval2;
	//Buscamos el onset de Pwave (1� maximo local) y el offset (2� maximo local)
	
	
	if(Pwave==NULL) Pwave=(int16_t *)malloc(3*sizeof(int16_t));		
	//busca 1� maximo local a la izquierda (onset Pwave):   
	l=Rwave[0];
	while(!encontrado){
		onsetP==mmt(l,f);
		
		for(left1=(l-1);left1>=from && !(onsetP<=mmt(left1,f) && mmt(left1,f)>mmt(left1-1,f)&& mmt(left1,f)>0 /*&& abs(mmt(left1,f))>thf*/ ) &&(t1!=0);left1--,t1--){ 
		    
			//if(onsetP< mmt(left1,f)&& mmt(left1,f)==mmt(left1-1,f)){l1=left1;}
			onsetP=mmt(left1,f);	    
		}
		//busca minimo intermedio que supere thf
		for(l=left1;l>=from && !(mmt(l+1,f)>=mmt(l,f) && mmt(l,f)<mmt(l-1,f) ) &&(t1!=0) ;l--,t1--);
		//l=left1;
		if(l<from || (t1==0))return 0;
		if (abs(mmt(l,f))>thf && mmt(l,f)<thf){
			Pwave[2]=l;
			encontrado=1;}
	}
	//busca 2� maximo local a la izquierda(offset Pwave):   
	offsetP=mmt(l,f);
	
	for(left2=l;left2>=from && !(offsetP<=mmt(left2,f) &&mmt(left2,f)>mmt(left2-1,f) && mmt(left2,f)>0/*&& abs(mmt(left2,f))>thf*/) &&(t1!=0);left2--,t1--){ 
	    
		//if(offsetP< mmt(left2,f)&& mmt(left2,f)==mmt(left2-1,f)){l2=left2;}
		offsetP=mmt(left2,f);	    
	}

	 // si los ha encontrado, crea Rwave y devuelve 0, sino devuelve 1
    if(left1>=from && left2>=from  &&(t1!=0))
    {		
		  Pwave[0]=left2;//onset
		 Pwave[1]=left1;//offset
		return 1;	
	}
    else return 0; 
}	
//********************************************************
int8_t twave(int16_t *f){
	
	//Twave=Buscamos 2 maximos locales desde Swave hacia la dcha:
	int16_t offsetT;
	
	int16_t right1;	//posiciion 1� max (onset)
	int16_t right2;	//posicion 2� max(offset)
	int16_t onsetT;
	int16_t r;
	int8_t encontrado=0;
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
		
	t1 = detecinterval2;
	//Buscamos el onset de Twave (1� maximo local) y el offset (2� maximo local)
	
	
	if(Twave==NULL) Twave=(int16_t *)malloc(3*sizeof(int16_t));	
	r=Rwave[1];	
	//busca 1� maximo local a la derecha (onset Twave):   
	while(!encontrado){
		onsetT=mmt(r,f);
		
		for(right1=r+1;right1<to && !(onsetT<=mmt(right1,f) &&mmt(right1,f)>mmt(right1+1,f) && mmt(right1,f)>0/*&& abs(mmt(right1,f))>thf*/) &&(t1!=0);right1++,t1--){
	    
			onsetT=mmt(right1,f);	    
		}
		//busca minimo intermedio 
		for(r=right1;r<to && !(mmt(r-1,f)>=mmt(r,f) && mmt(r,f)<mmt(r+1,f))&&(t1!=0);r++ ,t1--);
		
		//si no ha encontrado ningun minimo y se ha salido
		if(r>=to || (t1==0))return 0;
		//vemos si supera thf
		if (abs(mmt(r,f))>thf && mmt(r,f)<thf ){
			Twave[2]=r;
			encontrado=1;}
	
	}
	
	//busca 2� maximo local a la derecha (offset Twave):   
	offsetT=mmt(r,f);
	 for(right2=(r+1);right2<to && !(offsetT<=mmt(right2,f) && mmt(right2,f)>mmt(right2+1,f) && mmt(right2,f)>0/* && abs(mmt(right2,f))>thf*/)&&(t1!=0);right2++,t1--){    
	    
		 //if(offsetT< mmt(right2,f)&& mmt(right2,f)==mmt(right2+1,f)){r2=right2;}
		 offsetT=mmt(right2,f);	    
	}
	
	 // si los ha encontrado, crea Rwave y devuelve 0, sino devuelve 1
    if(right1< to && right2< to  &&(t1!=0))
    {		
		 Twave[0]=right1;//onset
		 Twave[1]=right2;//offset
		return 1;	
	}
    else return 0; 
}	
//*******************************************************************************************
//adaptive thresholding
//******************************************************************************************
void quicksort(int16_t *lista,int16_t inf,int16_t sup){
	
	int16_t pivote = lista[sup];
    int16_t i = inf;
    int16_t j = sup - 1;
    int8_t cont = 1;
 	int16_t temp;
    // Verificamos que no se crucen los l�mites
    if (inf >= sup)
          return;
 
    //  Clasificamos la sublista
    while (cont){
         while (i<sup &&lista[i] < pivote) { ++i; }
         while (j>inf && lista[j] > pivote ) { --j; }
         if (i<j/*lista[i] > lista[j]*/){
              temp = lista[i];
              lista[i] = lista[j];
              lista[j] = temp;
              ++i;--j;
     	}else
              cont = 0;
	}
 
   // Copiamos el pivote en su posici�n final
    temp = lista[i];
    lista[i] = lista[sup];
    lista[sup] = temp;
 
   // Aplicamos el procedimiento recursivamente a cada sublista
    quicksort (lista, inf, i - 1);
    quicksort (lista, i + 1, sup);

}
void thresholding(int16_t* f){
	
	int16_t *lista=(int16_t *)malloc((to-from)*sizeof(int16_t));
	int16_t *valores;
	int16_t *cantidad;
	int16_t n,i,j,min=abs(f[from&(BUFLN-1)]),max=abs(f[from&(BUFLN-1)]), processedVal=0;
	int8_t groups=5;
	thr=0;thf=0;
	
	for(i=0;i<to-from;i++){
		
		lista[i]=abs(f[(i+from)&(BUFLN-1)]);
	}
	quicksort(lista,0,to-from);
	

	max=lista[to-from-1];
	min=lista[0];
	
	n=max-min+1;
	valores=(int16_t *)malloc(((n/groups)+1)*sizeof(int16_t));
	cantidad=(int16_t *)malloc(((n/groups)+1)*sizeof(int16_t));
	valores[0]=min;//lista[0];
	cantidad[0]=1;
	
	for(i=0,j=0;i<to-from;i++){
		if(valores[j]+groups<=lista[i]){
			
			j++;
			//cont++; 
			valores[j]=valores[j-1]+groups;//lista[i];
			cantidad[j]=0;
			i--	;
		}else{
			cantidad[j]++;
		}
	}
	
	
	for(i=0;i<(n/groups)+1;i++){
		dbg(DBG_USR1, "%d  val: \%d    \%d\n",i,valores[i],cantidad[i]);
	}
	min=cantidad[(n/groups)];
	processedVal=cantidad[(n/groups)];
	for(i=(n/groups)-1;i>0 && !(min>=cantidad[i] && cantidad[i]<cantidad[i-1] &&processedVal>50);i--){
		processedVal+=cantidad[i];
		min=cantidad[i]; 		
	}
	thr=valores[i];
	min=cantidad[0];
	processedVal=cantidad[0];
	
	for(i=1;i<(n/groups)+1 && !(min>=cantidad[i] && cantidad[i]<cantidad[i+1]  &&processedVal>450);i++){
		processedVal+=cantidad[i];
		min=cantidad[i]; 		
	}
	thf=valores[i];
	
	free(valores);
	free(cantidad);
	free(lista);
	 
}
//*******************************************************************************************
//***************************  METODO PRINCIPAL ********************************************
//**********************************************************************************************

int32_t wqrs(int16_t datum, int16_t *buffer,int16_t *out)
{ 
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)
	int16_t *fp;//F= se�al despu�s del preprocesado
	int8_t *combine=(int8_t *)malloc(4*sizeof(int8_t));	
	
	detecinterval=(int16_t)(0.12*FS + 0.5);
	detecinterval2=(int16_t)(0.40*FS + 0.5);
    s=FS*W-1;
	buffer[count&(BUFLN-1)]=datum; //metemos el dato en el buffer
	count=(count+1)&(BUFLN-1);
	init=(count+1)&(BUFLN-1);  
	from=init+NOPS*(1.5*LQRS*FS-1)/2;
	//to=count-NOPS*(1.5*LQRS*FS-1)/2;
	to=from+distance;
	if(out==NULL) out=(int16_t *)malloc(12*sizeof(int16_t));	
		
	//llenado inicial del bucle
	if(initialize && count==0){
		
			initialize=0;
			to=BUFLN-NOPS*(1.5*LQRS*FS-1)/2;
			distance=to-from;
		
	}

	if(initialize){
		
		return 0;
	}
	// Step 1: morphological filtering for noise reduction and baseline correction
	fp=mmf(buffer);
	
	//dbg(DBG_USR1, "\%d --> MMF: \%d  value: \%d\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)]);
	// Step 2: multiscale morphological transform 
	
	mmt(to,fp); //fijamos thr
	if(count==0){
		notnoise=0;
		thresholding(mf);
		
		                                    
	}             
	
	
	//------------------------------------------------------------
	
	if(notnoise>=from){
		dbg(DBG_USR1, "\%d --> MMF: \%d \%d \%d\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)], mf[(from)&(BUFLN-1)]);
		return 0;	
	}
	
	// Step 3: Rpeaks detection, the local maxima and minima
	correct=rpeak_detection(fp);
	// Step 4: Rwave detection
	
	if (correct==1){		
		correct =-1;
      	correct=rwave(fp);	
      	if (correct==1){
	      	
			// Step 5: Qwave detection
		
			notnoise=Rwave[1]; 
			combine[3]=qwave(fp);
			// Step 6: Swave detection
			combine[2]= swave(fp);
			// Step 7: onset and offset, Pwave and Twave detection
			combine[1]=pwave(fp);
			combine[0]=twave(fp);
					
			//tenemos que tocarlo en funcion de combine
		
		out[0]=Rpeak;out[1]=fp[Rpeak];out[2]=Rwave[0];out[3]=Rwave[1];
		
			if(combine[3]==1)out[4]=Qwave; else out[4]=-1;
			if(combine[2]==1)out[5]=Swave; else out[5]=-1;
			if(combine[1]==1){  out[6]= Pwave[0];out[7]= fp[Pwave[2]];out[8]= Pwave[1];}else {out[6]= -1;out[7]=-1;out[8]=-1;}
			if(combine[0]==1){out[9]=Twave[0];out[10]= fp[Twave[2]];out[11]= Twave[1];}else {out[9]=-1;out[10]= -1;out[11]= -1;}
			dbg(DBG_USR1, "\%d --> MMF: \%d \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)], mf[(from)&(BUFLN-1)],out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);	
				
		}else{ dbg(DBG_USR1, "\%d --> MMF: \%d  \%d   \%d  Rwave not detected\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)],mf[(from)&(BUFLN-1)]);
				}
	
	}else{ 
		dbg(DBG_USR1, "\%d --> MMF: \%d \%d   \%d  Rpeak not detected\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)],mf[(from)&(BUFLN-1)]);
	}
	(void)free(fp);
	return 0;
}
void freeBuffers(){
	(void)free(f0);
    (void)free(mf);
	(void)free(Rwave);
	(void)free(Pwave);
	(void)free(Twave);
}

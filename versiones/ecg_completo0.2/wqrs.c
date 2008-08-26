/**********************************************************************************************************
/ VERSION 0.2 - Monica Jimenez, Laura Gutierrez
/ Con Arrays. Reduccion del numero de variables.
/ No soportada por el Nodo (no entra en memoria).                    
/***********************************************************************************************************/

#include <math.h>
#include "wqrs.h"


int16_t count=0, init=0,  from=0;//,to=0,,;  //readed values number
int16_t notnoise=0;
int16_t thr=0,thf=0; //threshold
int8_t initialize=1;
int16_t aux1[BUFLN],aux2[BUFLN];

int16_t Rpeak=0;//Paso 3 Rpeak= Local minimo entre Thf y Thr. 
int16_t Rwave[2];//Paso 4 (entre el primer max local a la izq y a la derecha de Rpeak)
int16_t Qwave=0;//Paso 5 (puede que no se detecte)1º minimo local a la izq de Rwave
int16_t Swave=0;//Paso 6 (puede que no se detecte)1ºminimo local desde la drecha de la parte positiva de Rwave
//Paso 7: Onset y Offset de Pwave y Twave (puede que no se detecte)
int16_t Pwave[3];// los 2 primeros maximos locales desde la izq de Pwave
int16_t Twave[3];// los 2 primeros maximos locales desde la dcha de Twave

int16_t fp[BUFLN];//F= señal después del preprocesado


//********************************************************************************************
// step1: morphological filtering for noise reduction and baseline correction
//********************************************************************************************

void erosion(int16_t f[BUFLN], int16_t lon,int16_t B[lon],int16_t result[BUFLN]){
	
	int16_t i=0;
	int16_t j=0;
	int16_t min=0;

		for(i=0;i<(lon-1)/2;i++){
			result[(init+i+BUFLN)%(BUFLN)]=f[(init+i+BUFLN)%(BUFLN)];	
		}
		for(i=(lon-1)/2;i<(BUFLN-(lon+1)/2);i++){
			min=f[(init+i-(lon-1)/2 +BUFLN)%(BUFLN)]-B[0];
			for(j=1;j<lon;j++){
				if(min > (f[(init+i-((lon-1)/2)+j+BUFLN)%(BUFLN)] - B[j])) min= f[(init+i-(lon-1)/2+j+BUFLN)%(BUFLN)] - B[j];
			
			}
			result[(init+i+BUFLN)%(BUFLN)]=min;	
		}
		for(i=(BUFLN-(lon+1)/2);i<BUFLN;i++){
			result[(init+i+BUFLN)%(BUFLN)]=f[(init+i+BUFLN)%(BUFLN)];	
		}

	
	
}

void dilation(int16_t f[BUFLN], int16_t lon,int16_t B[lon],int16_t result[BUFLN]){
	int16_t i=0,j=0;
	int16_t max=0;
	for(i=0;i<(lon-1)/2;i++){
			result[(init+i+BUFLN)%(BUFLN)]=f[(init+i+BUFLN)%(BUFLN)];	
		}
		for(i=(lon-1)/2;i<BUFLN-(lon+1)/2;i++){
			max=f[(init+i-(lon-1)/2+BUFLN)%(BUFLN)]+ B[0];
			for(j=1;j<lon;j++){
				if(max < (f[(init+i-((lon-1)/2)+j+BUFLN)%(BUFLN)] + B[j])) max=f[(init+i-((lon-1)/2)+j+BUFLN)%(BUFLN)] + B[j];
			}
			result[(init+i+BUFLN)%(BUFLN)]=max;
		}
		for(i=(BUFLN-(lon+1)/2);i<BUFLN;i++){
			result[(init+i+BUFLN)%(BUFLN)]=f[(init+i+BUFLN)%(BUFLN)];	
		}

	
}

void opening(int16_t f[BUFLN], int16_t lon,int16_t B[lon],int16_t sol[BUFLN]){

	erosion(f,lon,B, aux1);
	dilation(aux1,lon,B,sol);

}

void closing(int16_t f[BUFLN], int16_t lon,int16_t B[lon],int16_t sol[BUFLN]){

	dilation(f,lon,B,aux1);
	erosion(aux1,lon,B,sol);

		
}

//**************************************************************************************
void mmf(int16_t f[BUFLN],int16_t sol[BUFLN]){
	int16_t i=0,b2,b3;

	//matrix initialization
	static int16_t Bo[lo],Bc[lc];
	//B, Bo (apertura) y Bc (cierre) = se seleccionan basándose en las propiedades de las ondas características de ECG (elementos estructurales)
	static int16_t B1[l1];//,B2[l1];

	for(i=0;i<lc;i++){
		Bc[i]=0;	
	}
	for(i=0;i<lo;i++){
		Bo[i]=0;	
	}

		
	//baseline correction
	opening(f,lo,Bo,aux2);
	closing(aux2,lc,Bc,aux2);

	//noise suppresion
	for(i=0;i<BUFLN;i++){		
		aux2[i]=f[i]-aux2[i];	
	
	}
	
	
		B1[0]=0;  B1[1]=1;   B1[2]=5;   B1[3]=1;   B1[4]=0;
	//formula 2
	dilation(aux2,l1,B1,aux1);

	for(i=0;i<l1;i++){
		B1[i]=0;	
	}
	erosion(aux1,l1,B1,sol); //first

		B1[0]=0;  B1[1]=1;   B1[2]=5;   B1[3]=1;   B1[4]=0;
	erosion(aux2,l1,B1,aux1);
	for(i=0;i<l1;i++){
		B1[i]=0;	
	}

	dilation(aux1,l1,B1,aux2); //second

	b2=sol[from%BUFLN];
	
	for(i=0;i<BUFLN;i++){
		sol[i]=(sol[i]+aux2[i])/2;	
	}
	

	
}

//********************************************************************************************
// step2: multiscale morphological transform 
//*******************************************************************************************
int16_t mmt(int16_t current,int16_t f[BUFLN]){
	
	int16_t max=0;
		int16_t min=0;
		int16_t t;
    
    if ((current < (from)) && (current > (from)+distance) ) {
		
	    return -1;
    }
		
		for (t = current-s; t <= current+s; t++){ //find the maximum and minimum local values 

				if (f[(t+BUFLN)%(BUFLN)] > max) max = f[(t+BUFLN)%(BUFLN)]; 
				if (f[(t+BUFLN)%(BUFLN)] < min) min = f[(t+BUFLN)%(BUFLN)];			
		}
		
    return ((max+min-2*f[(current+BUFLN)%(BUFLN)])*10 / s);
	

	
}	
	
//********************************************************************************************
// step3: Rpeaks detection, the local maxima and minima
// return 0 if there aren't any rpeaks detected
//********************************************************************************************
int8_t rpeak_detection(){

    int16_t r; 
    int16_t  mt;
 	int16_t igual=0;
    
    // Looking for the first local minimun 
	r=((from)+1);
	
    while( r<(from)+distance){
	    mt=mmt(r,fp);

	  	if(mmt(r-1,fp)>mt && mt<mmt(r+1,fp)){
	    	if(mt<(-1*thr)){Rpeak=r;return 1;}
		}
		
		//Special case: several equal values, get the first one
		if(mmt(r-1,fp)>mt && mt==mmt(r+1,fp))igual=r;
		if(mmt(r-1,fp)==mt && mt<mmt(r+1,fp)){
			if(mt<(-1*thr)){Rpeak=igual; return 1;}
		} 	
	    r++;    
    }
	return 0;
	
}

//********************************************************************************************
// step4: Rwave detection
// return 0 if there aren't any rwave detected
//********************************************************************************************
int8_t rwave(int16_t f[BUFLN]){
	
	int16_t right_local_max;
	int16_t left_local_max;
	int16_t r,l;//posiciones right y left
	int16_t right,left;//verdadera posicion del maximo hacia la dcha
	right=-1;
	left=-1;
	//From Rpeak:   	
    	right_local_max= mmt(Rpeak,f);
    	left_local_max= mmt(Rpeak,f);
    //Looking for the first local maximun to right	
          
    for(r=(Rpeak+1);r<((from)+distance) && !(right_local_max<= mmt(r,f) && mmt(r,f)>mmt(r+1,f) && abs(mmt(r,f) )>thf);r++){
	     if(right_local_max< mmt(r,f)&& mmt(r,f)==mmt(r+1,f)){right=r;}		    
	    right_local_max=mmt(r,f);
	}
    //Looking for the first local maximun to left	     
     for(l=(Rpeak-1);l>=(from) && !(left_local_max<=mmt(l,f) && mmt(l,f)>mmt(l-1,f) && abs(mmt(l,f) )>thf);l--){  
	     if(left_local_max< mmt(l,f)&& mmt(l,f)==mmt(l-1,f)){left=l;}	
	    left_local_max=mmt(l,f);	    
	}

    if(r< ((from)+distance) && l>=(from) )
    {	
		if(left != -1)Rwave[0]=left;else Rwave[0]=l;
		if(right != -1)Rwave[1]=right;else Rwave[1]=r;
		return 1;	
	}
    else return 0;
  
}

//********************************************************************************************
// step5: Qwave detection
//********************************************************************************************
int8_t qwave(int16_t f[BUFLN]){

	int16_t left_local_min= mmt(Rwave[0],f);
	int16_t l; 
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval;
		
	// Looking for the first local minumun to left
	 for(l=(Rwave[0]-1);l>=(from) && !(left_local_min>mmt(l,f) && mmt(l,f)<=mmt(l-1,f) && abs(mmt(l,f))>thf)&&(t1!=0);l--,t1--){  
		left_local_min=mmt(l,f);	    
		}

	Qwave=l;	

    	if(l>=(from) && (t1!=0)) {return 1;}else{return 0;}
}
//********************************************************************************************
// step6: Swave detection
//********************************************************************************************
int8_t swave(int16_t f[BUFLN]){

	int16_t right_local_min= mmt(Rwave[1],f);
	int16_t r; 
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval;
		
	// Looking for the first local minumun to right
	 for(r=(Rwave[1]+1);r<((from)+distance) && !(right_local_min>mmt(r,f) && mmt(r,f)<=mmt(r+1,f) && abs(mmt(r,f))>thf)&&(t1!=0);r++,t1--){    
		 right_local_min=mmt(r,f);	    
		}
   		Swave=r;	
    	if(r<((from)+distance) && (t1!=0))  {return 1;}else return 0;
}


//********************************************************************************************
// step7: onset and offset, Pwave and Twave detection
//********************************************************************************************
int8_t pwave(int16_t f[BUFLN]){
	
	//Pwave=Buscamos 2 maximos locales desde Qwave hacia la izq:
	int16_t offsetP;
	
	int16_t left1=0;	//posicion 1º max (onset)
	int16_t left2=0;	//posicion 2º max(offset)
	int16_t onsetP=0;
	int16_t l;
	int8_t encontrado=0;
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval2;
	
	//busca 1º maximo local a la izquierda (onset Pwave):   
	l=Rwave[0];
	while(!encontrado){
		onsetP==mmt(l,f);
		
		for(left1=(l-1);left1>=(from) && !(onsetP<=mmt(left1,f) && mmt(left1,f)>mmt(left1-1,f)&& mmt(left1,f)>0 /*&& abs(mmt(left1,f))>thf*/ ) &&(t1!=0);left1--,t1--){ 
			onsetP=mmt(left1,f);	    
		}
		//busca minimo intermedio que supere thf
		for(l=left1;l>=(from) && !(mmt(l+1,f)>=mmt(l,f) && mmt(l,f)<mmt(l-1,f) ) &&(t1!=0) ;l--,t1--);
		if(l<(from) || (t1==0))return 0;
		if (abs(mmt(l,f))>thf && mmt(l,f)<thf){
			Pwave[2]=l;
			encontrado=1;}
	}
	//busca 2º maximo local a la izquierda(offset Pwave):   
	offsetP=mmt(l,f);
	
	for(left2=l;left2>=(from) && !(offsetP<=mmt(left2,f) &&mmt(left2,f)>mmt(left2-1,f) && mmt(left2,f)>0/*&& abs(mmt(left2,f))>thf*/) &&(t1!=0);left2--,t1--){ 
		offsetP=mmt(left2,f);	    
	}

    if(left1>=(from) && left2>=(from)  &&(t1!=0))
    {		
		  Pwave[0]=left2;//onset
		 Pwave[1]=left1;//offset
		return 1;	
	}
    else return 0; 
}	
//********************************************************
int8_t twave(int16_t f[BUFLN]){
	
	//Twave=Buscamos 2 maximos locales desde Swave hacia la dcha:
	int16_t offsetT;
	int16_t right1=0;	//posiciion 1º max (onset)
	int16_t right2=0;	//posicion 2º max(offset)
	int16_t onsetT=0;
	int16_t r;
	int8_t encontrado=0;
	int32_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval2;
	
	r=Rwave[1];	
	//busca 1º maximo local a la derecha (onset Twave):   
	while(!encontrado){
		onsetT=mmt(r,f);
		
		for(right1=r+1;right1<((from)+distance) && !(onsetT<=mmt(right1,f) &&mmt(right1,f)>mmt(right1+1,f) && mmt(right1,f)>0/*&& abs(mmt(right1,f))>thf*/) &&(t1!=0);right1++,t1--){
			onsetT=mmt(right1,f);	    
		}
		//busca minimo intermedio 
		for(r=right1;r<((from)+distance) && !(mmt(r-1,f)>=mmt(r,f) && mmt(r,f)<mmt(r+1,f))&&(t1!=0);r++ ,t1--);
		
		//si no ha encontrado ningun minimo y se ha salido
		if(r>=((from)+distance) || (t1==0))return 0;
		if (abs(mmt(r,f))>thf && mmt(r,f)<thf ){
			Twave[2]=r;
			encontrado=1;			
			}
	}
	
	//busca 2º maximo local a la derecha (offset Twave):   
	offsetT=mmt(r,f);
	 for(right2=(r+1);right2<((from)+distance) && !(offsetT<=mmt(right2,f) && mmt(right2,f)>mmt(right2+1,f) && mmt(right2,f)>0/* && abs(mmt(right2,f))>thf*/)&&(t1!=0);right2++,t1--){    
	   offsetT=mmt(right2,f);	    
		}
		
    if(right1< ((from)+distance) && right2< ((from)+distance)  &&(t1!=0))
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
void quicksort(int16_t lista[distance],int16_t inf,int16_t sup){
	
	int16_t pivote = lista[sup];
    int16_t i = inf;
    int16_t j = sup - 1;
    int8_t cont = 1;
 	int16_t temp;
    // Verificamos que no se crucen los límites
    if (inf >= sup)
          return;
 
    //  Clasificamos la sublista
    while (cont){
         while (i<sup &&lista[i] < pivote) { ++i; }
         while (j>inf && lista[j] > pivote ) { --j; }
         if (i<j){
              temp = lista[i];
              lista[i] = lista[j];
              lista[j] = temp;
              ++i;--j;
     	}else
              cont = 0;
	}
 
   // Copiamos el pivote en su posición final
    temp = lista[i];
    lista[i] = lista[sup];
    lista[sup] = temp;
 
   // Aplicamos el procedimiento recursivamente a cada sublista
    quicksort (lista, inf, i - 1);
    quicksort (lista, i + 1, sup);

}
void thresholding(int16_t lista[distance],int16_t min, int16_t max){
	
	
	int16_t n=max-min+1,i,j, processedVal=0,aux;
	int8_t groups=5;
	int16_t valores[((n/groups)+1)];
	int16_t cantidad[((n/groups)+1)];
	thr=0;thf=0;
	
	valores[0]=min;//lista[0];
	cantidad[0]=1;
	
	for(i=0,j=0;i<distance;i++){
		if(valores[j]+groups<=lista[i]){
			j++; 
			valores[j]=valores[j-1]+groups;
			cantidad[j]=0;
			i--	;
		}else{
			cantidad[j]++;
		}
	}
	
	aux=cantidad[(n/groups)];
	processedVal=cantidad[(n/groups)];
	for(i=(n/groups)-1;i>0 && !(aux>=cantidad[i] && cantidad[i]<cantidad[i-1] &&processedVal>10/*50*/);i--){
		processedVal+=cantidad[i];
		aux=cantidad[i]; 		
	}
	thr=valores[i];
	aux=cantidad[0];
	processedVal=cantidad[0];
	
	for(i=1;i<(n/groups)+1 && !(aux>=cantidad[i] && cantidad[i]<cantidad[i+1]  &&processedVal>100);i++){
		processedVal+=cantidad[i];
		aux=cantidad[i]; 		
	}
	thf=65;//valores[i];
	
}





//*******************************************************************************************
//***************************  METODO PRINCIPAL ********************************************
//**********************************************************************************************

int8_t wqrs(int16_t datum, int16_t buffer[BUFLN],int16_t out[12])
{ 
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)
	
	int8_t combine[4];//=(int8_t *)malloc(4*sizeof(int8_t));	
	int16_t lista[distance]; //para calcular thresholding
	int16_t min,  max,i; //para el thresholding

    //Buffer initialization
	buffer[(count+BUFLN)%(BUFLN)]=datum; 
	count=(count+1+BUFLN)%(BUFLN);
	

	init=((count+1)+BUFLN)%(BUFLN);  
	from=init+margin;

		
	//Learning...
	if(initialize && count==0){
			initialize=0;
	}
	if(initialize){return 0;}
	
	// Step 1: morphological filtering for noise reduction and baseline correction
	mmf(buffer,fp);
 	if(from>102 && from < 304)
    dbg(DBG_USR1, "\%d, ", fp[(from+BUFLN)%(BUFLN)]);
	// Step 2: multiscale morphological transform 
	mmt((from+distance),fp); 
	
	//Thresholding calculation
	if(count==0){
		
		notnoise=(notnoise+BUFLN)%(BUFLN);
		for(i=0;i<distance;i++){
		
			lista[i]=abs(mmt(((i+from)+BUFLN)%(BUFLN),fp));
		}
		quicksort(lista,0,distance);
		
	
		max=lista[distance-1];
		min=lista[0];
		thresholding(lista,min,max);                               
	}             
	
	
	if(notnoise>=from){
		dbg(DBG_USR1, "\%d --> MMF: \%d \%d \%d\n",from%BUFLN,buffer[(from+BUFLN)%(BUFLN)],fp[(from+BUFLN)%(BUFLN)], mmt((from+BUFLN)%(BUFLN),fp));
		return 0;	
	}
	
	// Step 3: Rpeaks detection, the local maxima and minima
	correct=rpeak_detection();
	
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
	
			out[0]=(Rpeak+BUFLN)%(BUFLN);out[1]=fp[(Rpeak+BUFLN)%(BUFLN)];out[2]=(Rwave[0]+BUFLN)%(BUFLN);out[3]=(Rwave[1]+BUFLN)%(BUFLN);
		
			if(combine[3]==1)out[4]=(Qwave+BUFLN)%(BUFLN); else out[4]=0;
			if(combine[2]==1)out[5]=(Swave+BUFLN)%(BUFLN); else out[5]=0;
			if(combine[1]==1){  out[6]= (Pwave[0]+BUFLN)%(BUFLN);out[7]= fp[(Pwave[2]+BUFLN)%(BUFLN)];out[8]=(Pwave[1]+BUFLN)%(BUFLN);}
				else {out[6]= 0;out[7]=0;out[8]=0;}
			if(combine[0]==1){out[9]=(Twave[0]+BUFLN)%(BUFLN);out[10]= fp[(Twave[2]+BUFLN)%(BUFLN)];out[11]= (Twave[1]+BUFLN)%(BUFLN);}
				else {out[9]=0;out[10]= 0;out[11]= 0; notnoise=(from+10); }
				
			dbg(DBG_USR1, "\%d --> MMF: \%d \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",from%BUFLN,buffer[(from+BUFLN)%(BUFLN)],fp[(from+BUFLN)%(BUFLN)], mmt((from+BUFLN)%(BUFLN),fp),out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);	
			
			}else{
				dbg(DBG_USR1, "\%d --> MMF: \%d \%d \%d Rwave not detected\n",from%BUFLN,buffer[(from+BUFLN)%(BUFLN)],fp[(from+BUFLN)%(BUFLN)], mmt((from+BUFLN)%(BUFLN),fp)); 
				}
	}else{
		dbg(DBG_USR1, "\%d --> MMF: \%d \%d \%d Rpeak not detected\n",from%BUFLN,buffer[(from+BUFLN)%(BUFLN)],fp[(from+BUFLN)%(BUFLN)], mmt((from+BUFLN)%(BUFLN),fp)); 
		}
	
	return 0;
}


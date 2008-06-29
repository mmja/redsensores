#include <math.h>
#include "ecg_detection.h"
//VARIABLES
int16_t count=0, init=0,  from=0;//,to=0,,;  //readed values number
int16_t notnoise=0;
int16_t thr=0,thf=0; //threshold
int8_t initialize=1;
int8_t aux1[BUFLNZIP];


//**********************************************************************************************************
void comprime(int8_t f[BUFLNZIP],int16_t p,int16_t data){
	//int8_t comp[(BUFLN*1.5)+1];

	int8_t data_mod;
	int16_t inter;
	
	if(p%2==0){
		data_mod=data>>4;
		f[p+p/2]=data_mod;
		data_mod=data<<4;
		f[p+p/2+1]= f[p+p/2+1]& 0x0f;	
		f[p+p/2+1]= f[p+p/2+1]|data_mod;
	}else{
		inter=(data>>8)&0x000f;
		data_mod=inter;
		f[p+p/2]= f[p+p/2]& 0xf0;	
		f[p+p/2]= f[p+p/2]|data_mod;
		f[p+p/2+1]=data;

	}
	
}
int16_t descomprime(int8_t f[BUFLNZIP],int16_t p,int8_t isBuffer){
	int16_t out,aux;
	int8_t inter;
	if(isBuffer==0){
		if(p%2==0){
			out=f[p+p/2];
			out=out<<4;
			inter=(f[p+p/2+1]>>4)&0x0f;
			out=out|inter;
			
		}else{
			inter=f[p+p/2]<<4;
			out=inter<<4;
			//if((f[p+p/2]&0x08)!=8){	
			//	aux=f[p+p/2+1]&0x00ff;}
			//else{ 
			//	aux=f[p+p/2+1];}
			aux=f[p+p/2+1]&0x00ff;
			out=out|aux;
	
		}
	}else {
		if(p%2==0){
			out=f[p+p/2]&0x00ff;
			out=out<<4;
			inter=(f[p+p/2+1]>>4)&0x0f;
			out=out|inter;
			
		}else{
			out=(f[p+p/2]&0x000f);
			out=out<<8;
			out=out|(f[p+p/2+1]&0x00ff);
	
		}
	}
	   //dbg(DBG_USR1, "\%d val: %d %d \n",p,fp[p],out);   
	return out;
}



//**************************************************************************************


//********************************************************************************************
// step2: multiscale morphological transform 
//*******************************************************************************************
int16_t mmt(int16_t current,int8_t f[BUFLNZIP]){
	
	//int16_t i;
	int16_t max=0;
		int16_t min=0;
		int16_t t;
		
	//static int16_t tt=0;
	/*if (mf == NULL) {
		//mf = (int16_t *)malloc(BUFLN*sizeof(int16_t));		
		for(i=0;i<s;i++){
			mf[(i+BUFLN)%(BUFLN)]=0;	
			
		}
		tt=s;
    }*/
    
    if ((current < (from)) && (current > (from)+distance) ) {
		
	    return -1;
    }
	
    
    //while(tt<=current){
		
		for (t = current-s; t <= current+s; t++){ //find the maximum and minimum local values 
				
			//if((aux=getsample(t,f))!= WFDB_INVALID_SAMPLE){
				//if (f[(t+BUFLN)%(BUFLN)] > max) max = f[(t+BUFLN)%(BUFLN)]; 
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) > max) max = descomprime(f,(t+BUFLN)%(BUFLN),0);
				//if (f[(t+BUFLN)%(BUFLN)] < min) min = f[(t+BUFLN)%(BUFLN)];
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) < min) min = descomprime(f,(t+BUFLN)%(BUFLN),0);
			//}
			
		}
		

    //return ((max+min-2*f[(current+BUFLN)%(BUFLN)])*10 / s);
	return ((max+min-2*descomprime(f,(current+BUFLN)%(BUFLN),0) )*10 / s);

	
}	
	
//********************************************************************************************
// step3: Rpeaks detection, the local maxima and minima
// return 0 if there aren't any rpeaks detected
//********************************************************************************************
int8_t rpeak_detection(int8_t f[BUFLNZIP], int16_t outecg[12]){

    int16_t r; 
    int16_t  mt;
 	int16_t igual=0;
    
    // Looking for the first local minimun 
	r=((from)+1);
	
    while( r<(from)+distance){
	    mt=mmt(r,f);

	  	if(mmt(r-1,f)>mt && mt<mmt(r+1,f)){
	    	if(mt<(-1*thr)){outecg[0]=r;return 1;}
		}
		
		//Special case: several equal values, get the first one
		if(mmt(r-1,f)>mt && mt==mmt(r+1,f))igual=r;
		if(mmt(r-1,f)==mt && mt<mmt(r+1,f)){
			if(mt<(-1*thr)){outecg[0]=igual; return 1;}
		} 	
	    r++;    
    }
	return 0;
	
}

//********************************************************************************************
// step4: Rwave detection
// return 0 if there aren't any rwave detected
//********************************************************************************************
int8_t rwave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	
	int16_t right_local_max;
	int16_t left_local_max;
	int16_t r,l;//posiciones right y left
	int16_t right,left;//verdadera posicion del maximo hacia la dcha
	//if(Rwave==NULL) Rwave=(int16_t *)malloc(2*sizeof(int16_t));		
	right=-1;
	left=-1;
	//From Rpeak:   	
    	right_local_max= mmt(outecg[0],f);
    	left_local_max= mmt(outecg[0],f);
    //Looking for the first local maximun to right	
           
    for(r=(outecg[0]+1);r<((from)+distance) && !(right_local_max<= mmt(r,f) && mmt(r,f)>mmt(r+1,f) && abs(mmt(r,f) )>thf);r++){
	     if(right_local_max< mmt(r,f)&& mmt(r,f)==mmt(r+1,f)){right=r;}		    
	    right_local_max=mmt(r,f);
	}
    //Looking for the first local maximun to left	     
     for(l=(outecg[0]-1);l>=(from) && !(left_local_max<=mmt(l,f) && mmt(l,f)>mmt(l-1,f) && abs(mmt(l,f) )>thf);l--){  
	     if(left_local_max< mmt(l,f)&& mmt(l,f)==mmt(l-1,f)){left=l;}	
	    left_local_max=mmt(l,f);	    
	}

    if(r< ((from)+distance) && l>=(from) )
    {	
		if(left != -1)outecg[2]=left;else outecg[2]=l;
		if(right != -1)outecg[3]=right;else outecg[3]=r;
		return 1;	
	}
    else return 0;
  
}

//********************************************************************************************
// step5: Qwave detection
//********************************************************************************************
int8_t qwave(int8_t f[BUFLNZIP], int16_t outecg[12]){

	int16_t left_local_min= mmt(outecg[2],f);
	int16_t l; 
	int8_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval;
		
	// Looking for the first local minumun to left
	 for(l=(outecg[2]-1);l>=(from) && !(left_local_min>mmt(l,f) && mmt(l,f)<=mmt(l-1,f) && abs(mmt(l,f))>thf)&&(t1!=0);l--,t1--){  
		left_local_min=mmt(l,f);	    
		}

	outecg[4]=l;	

    	if(l>=(from) && (t1!=0)) {return 1;}else{return 0;}
}
//********************************************************************************************
// step6: Swave detection
//********************************************************************************************
int8_t swave(int8_t f[BUFLNZIP], int16_t outecg[12]){

	int16_t right_local_min= mmt(outecg[3],f);
	int16_t r; 
	int8_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval;
		
	// Looking for the first local minumun to right
	 for(r=(outecg[3]+1);r<((from)+distance) && !(right_local_min>mmt(r,f) && mmt(r,f)<=mmt(r+1,f) && abs(mmt(r,f))>thf)&&(t1!=0);r++,t1--){    
		 right_local_min=mmt(r,f);	    
		}
   		outecg[5]=r;	
    	if(r<((from)+distance) && (t1!=0))  {return 1;}else return 0;
}


//********************************************************************************************
// step7: onset and offset, Pwave and Twave detection
//********************************************************************************************
int8_t pwave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	
	//Pwave=Buscamos 2 maximos locales desde Qwave hacia la izq:
	int16_t offsetP;
	
	int16_t left1=0;	//posicion 1º max (onset)
	int16_t left2=0;	//posicion 2º max(offset)
	int16_t onsetP=0;
	int16_t l;
	int8_t encontrado=0;
	int8_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval2;
	
	
	//if(Pwave==NULL) Pwave=(int16_t *)malloc(3*sizeof(int16_t));		
	//busca 1º maximo local a la izquierda (onset Pwave):   
	l=outecg[2];
	while(!encontrado){
		onsetP==mmt(l,f);
		
		for(left1=(l-1);left1>=(from) && !(onsetP<=mmt(left1,f) && mmt(left1,f)>mmt(left1-1,f)&& mmt(left1,f)>0 /*&& abs(mmt(left1,f))>thf*/ ) &&(t1!=0);left1--,t1--){ 
			onsetP=mmt(left1,f);	    
		}
		//busca minimo intermedio que supere thf
		for(l=left1;l>=(from) && !(mmt(l+1,f)>=mmt(l,f) && mmt(l,f)<mmt(l-1,f) ) &&(t1!=0) ;l--,t1--);
		//l=left1;
		if(l<(from) || (t1==0))return 0;
		if (abs(mmt(l,f))>thf && mmt(l,f)<thf){
			outecg[7]=l;
			encontrado=1;}
	}
	//busca 2º maximo local a la izquierda(offset Pwave):   
	offsetP=mmt(l,f);
	
	for(left2=l;left2>=(from) && !(offsetP<=mmt(left2,f) &&mmt(left2,f)>mmt(left2-1,f) && mmt(left2,f)>0/*&& abs(mmt(left2,f))>thf*/) &&(t1!=0);left2--,t1--){ 
		offsetP=mmt(left2,f);	    
	}

    if(left1>=(from) && left2>=(from)  &&(t1!=0))
    {		
		  outecg[6]=left2;//onset
		 outecg[8]=left1;//offset
		return 1;	
	}
    else return 0; 
}	
//********************************************************
int8_t twave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	
	//Twave=Buscamos 2 maximos locales desde Swave hacia la dcha:
	int16_t offsetT;
	int16_t right1=0;	//posiciion 1º max (onset)
	int16_t right2=0;	//posicion 2º max(offset)
	int16_t onsetT=0;
	int16_t r;
	int8_t encontrado=0;
	int8_t	t1;// tienen que tradar menos de 0,12 seg en encontrar el minimo
	t1 = detecinterval2;
	
	//if(Twave==NULL) Twave=(int16_t *)malloc(3*sizeof(int16_t));	
	r=outecg[3];	
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
			outecg[10]=r;
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
		 outecg[9]=right1;//onset
		outecg[11]=right2;//offset
		return 1;	
	}
    else return 0; 
}	
//*******************************************************************************************
//adaptive thresholding
//******************************************************************************************

void thresholding(int16_t n){
	
	static int16_t i, processedVal=0,aux;
	//int8_t groups=5;
	//int16_t valores[((n/groups))];
	int16_t cantidad[((n/groups)+1)];
	
	
	/*for(i=0;i<(n/groups)+1;i++){
		//aux2[i]=0;
		comprime(aux2,i,0);
		}*/
	//n=max-min+1;
	//valores=(int16_t *)malloc(((n/groups)+1)*sizeof(int16_t));
	//cantidad=(int16_t *)malloc(((n/groups)+1)*sizeof(int16_t));
	//valores[0]=min;//lista[0];
	for(i=0;i<distance;i++){
		cantidad[descomprime(aux1,i,0)/5]++;
		//comprime(aux2,descomprime(aux1,i,0)/5,descomprime(aux2,descomprime(aux1,i,0)/5,0)+1);
	}
	
	
	
	for(i=0;i<(n/groups)+1;i++){
		//dbg(DBG_USR1, "%d  val: \%d    \%d\n",i,i*groups,aux2[i]);
		//dbg(DBG_USR1, "%d  val: \%d    \%d\n",i,i*groups,descomprime(aux2,i,0));
	}
	//aux=aux2[(n/groups)];
	aux=cantidad[n/groups];
	//processedVal=aux2[(n/groups)];
	processedVal=cantidad[n/groups];
	//for(i=(n/groups)-1;i>0 && !(aux>=aux2[i] && aux2[i]<aux2[i-1] &&processedVal>10/*50*/);i--){
	//	processedVal+=aux2[i];
	//	aux=aux2[i]; 		
	//}
	for(i=(n/groups)-1;i>0 && !(aux>=cantidad[i] && cantidad[i]<cantidad[i-1] &&processedVal>10/*50*/);i--){
		processedVal+=cantidad[i];
		aux=cantidad[i]; 		
	}
	if(thr<i*groups)thr=i*groups;//valores[i];
	//aux=aux2[0];
	aux=cantidad[0];
	//processedVal=aux2[0];
	processedVal=cantidad[0];
	//for(i=1;i<(n/groups)+1 && !(aux>=aux2[i] && aux2[i]<aux2[i+1]  &&processedVal>100);i++){
	//	processedVal+=aux2[i];
	//	aux=aux2[i]; 		
	//}
	for(i=1;i<(n/groups)+1 && !(aux>=cantidad[i] && cantidad[i]<cantidad[i+1]  &&processedVal>100);i++){
		processedVal+=cantidad[i];
		aux=cantidad[i]; 		
	}
	thf=65;//i*groups;
	
	/*free(valores);
	free(cantidad);
	free(lista);
	 */
	
	
}


//******************************************************************************************
//***************************  METODO PRINCIPAL ********************************************
//**********************************************************************************************

int8_t ecg_detection(int16_t datum, int8_t fp[BUFLNZIP],int16_t out[12])
{ 
	static int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)
	
	static int8_t combine[4];//=(int8_t *)malloc(4*sizeof(int8_t));	
	static int16_t max,i; //para el thresholding
	comprime(fp,(count+BUFLN)%(BUFLN),datum);
	count=(count+1+BUFLN)%(BUFLN);
	                  
	init=((count+1)+BUFLN)%(BUFLN);  
	from=init+margin;//+NOPS*(1.5*LQRS*FS-1)/2;
	
	
	//Learning...
	if(initialize && count==0){
			initialize=0;
	}
	if(initialize){return 0;}
    
	// Step 2: multiscale morphological transform 
	
	
	//Thresholding calculation
	if(count==0){
		max=0;
		notnoise=(notnoise+BUFLN)%(BUFLN);
		for(i=0;i<distance;i++){	
			
			comprime(aux1,i,abs(mmt(((i+from)+BUFLN)%(BUFLN),fp)));
			
			if(max<descomprime(aux1,i,0))max=descomprime(aux1,i,0);
		}
		thresholding(max);
		//dbg(DBG_USR1, "thr: \%d thf: \%d \n",thr,thf);                                    
	}             
	
	
	if(notnoise>=from){
		//dbg(DBG_USR1, "\%d --> MMF: \%d \%d \%d\n",from%BUFLN,descomprime(buffer,(from+BUFLN)%(BUFLN),1),fp[(from+BUFLN)%(BUFLN)], mmt((from+BUFLN)%(BUFLN),fp));
		//dbg(DBG_USR1, "\%d --> MMF: \%d \%d\n",from%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp));
		
		
		return 0;	
	}
	
	// Step 3: Rpeaks detection, the local maxima and minima
	correct=rpeak_detection(fp,out);
	
	// Step 4: Rwave detection
	if (correct==1){		
		correct =-1;
      	correct=rwave(fp,out);	
      	if (correct==1){	   	
		// Step 5: Qwave detection
				notnoise=out[3]; 
				combine[3]=qwave(fp,out);
		// Step 6: Swave detection
				combine[2]= swave(fp,out);
		// Step 7: onset and offset, Pwave and Twave detection
				combine[1]=pwave(fp,out);
				combine[0]=twave(fp,out);
	
				out[0]=(out[0]+BUFLN)%(BUFLN);
				//out[1]=fp[(out[0]+BUFLN)%(BUFLN)];
				out[1]=descomprime(fp,(out[0]+BUFLN)%(BUFLN),0);
				out[2]=(out[2]+BUFLN)%(BUFLN);
				out[3]=(out[3]+BUFLN)%(BUFLN);
			  
				if(combine[3]==1)out[4]=(out[4]+BUFLN)%(BUFLN); else out[4]=0;
				if(combine[2]==1)out[5]=(out[5]+BUFLN)%(BUFLN); else out[5]=0;
				if(combine[1]==1){
					out[6]= (out[6]+BUFLN)%(BUFLN);
					//out[7]= fp[(out[7]+BUFLN)%(BUFLN)];
					out[7]=descomprime(fp,(out[7]+BUFLN)%(BUFLN),0);					
					out[8]=(out[8]+BUFLN)%(BUFLN);}
				else {out[6]= 0;out[7]=0;out[8]=0;}
				if(combine[0]==1){
					out[9]=(out[9]+BUFLN)%(BUFLN);
					//out[10]= fp[(out[10]+BUFLN)%(BUFLN)];
					out[10]=descomprime(fp,(out[10]+BUFLN)%(BUFLN),0);
					out[11]= (out[11]+BUFLN)%(BUFLN);}
				else {out[9]=0;out[10]= 0;out[11]= 0; notnoise=(from+10); }
				
			//dbg(DBG_USR1, "\%d --> MMF:  \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",from%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp),out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);	
			
		}else{
				//dbg(DBG_USR1, "\%d --> MMF:  \%d \%d Rwave not detected\n",from%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp)); 
				// dbg(DBG_USR1, "\%d --> MMF: \%d  \%d   \%d  Rwave not detected\n",from,buffer[(from+BUFLN)%(BUFLN)],fp[(from)&(BUFLN-1)],mmt((from)&(BUFLN-1),fp));
				}
	}else{
		//dbg(DBG_USR1, "\%d --> MMF:  \%d \%d Rpeak not detected\n",from%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp)); 
		//dbg(DBG_USR1, "\%d --> MMF: \%d \%d   \%d  Rpeak not detected\n",from,buffer[(from)&(BUFLN-1)],fp[(from)&(BUFLN-1)],mmt((from)&(BUFLN-1),fp));	
	}
	
	//(void)free(fp);
	return 0;
}


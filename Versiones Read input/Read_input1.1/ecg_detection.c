/**********************************************************************************************************
/ VERSION 1.1 - Monica Jimenez, Laura Gutierrez
/ Sin Filtro. Usa señales ya filtradas.
/ Con Comprobacion de las detecciones para validarlas.
/ Dividida en 8 pasos.
/ Soportada por el Nodo (muy lenta).                    
/***********************************************************************************************************/


#include <math.h>
#include "ecg_detection.h"

int16_t c,count=0, init=0,  from=0;//readed values number
int16_t notnoise=0;
int16_t thr=0,thf=0; //threshold
int8_t initialize=1;
int8_t aux1[BUFLNZIP];
int8_t filled_buffer; //number of times since the last Rpeak detection that the buffer has been completely filled. 
int16_t last_Rpeak; //saving the last rpeak instant
uint8_t hour=0,minute=0,second=0, positions=0;
int16_t out[12];
int8_t combine[4];
//**********************************************************************************************************
void comprime(int8_t f[BUFLNZIP],int16_t p,int16_t data){
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
	int16_t outd,aux;
	int8_t inter;
	if(isBuffer==0){
		if(p%2==0){
			outd=f[p+p/2];
			outd=outd<<4;
			inter=(f[p+p/2+1]>>4)&0x0f;
			outd=outd|inter;
			
		}else{
			inter=f[p+p/2]<<4;
			outd=inter<<4;
			aux=f[p+p/2+1]&0x00ff;
			outd=outd|aux;
	
		}
	}else {
		if(p%2==0){
			outd=f[p+p/2]&0x00ff;
			outd=outd<<4;
			inter=(f[p+p/2+1]>>4)&0x0f;
			outd=outd|inter;
			
		}else{
			outd=(f[p+p/2]&0x000f);
			outd=outd<<8;
			outd=outd|(f[p+p/2+1]&0x00ff);
	
		}
	}
	return outd;
}

//********************************************************************************************
// step2: multiscale morphological transform 
//*******************************************************************************************
int16_t mmt(int16_t current,int8_t f[BUFLNZIP]){
	
	int16_t max=0;
		int16_t min=0;
		int16_t t;
    
    if ((current < (from)) && (current > (from)+DISTANCE) ) {
		
	    return -1;
    }
	

		for (t = current-S; t <= current+S; t++){ //find the maximum and minimum local values 
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) > max) max = descomprime(f,(t+BUFLN)%(BUFLN),0);
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) < min) min = descomprime(f,(t+BUFLN)%(BUFLN),0);
		}
		return ((max+min-2*descomprime(f,(current+BUFLN)%(BUFLN),0)) *10 / S );	
		
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
	
    while( r<(from)+DISTANCE){
	    mt=mmt(r,f);

	  	if(mmt(r-1,f)>mt && mt<mmt(r+1,f)){
	    	if(mt<(-1*thr)){outecg[0]=r;return 1;}
		}
		
		//Special case: several equal values, get the first one
		if(mmt(r-1,f)>mt && mt==mmt(r+1,f))igual=r;
		if(mmt(r-1,f)==mt && mt<mmt(r+1,f)){
			if(mt<(-1*thr)){outecg[0]=igual;return 1;}
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
	
	right=-1;
	left=-1;
	//From Rpeak:   	
    	right_local_max= mmt(outecg[0],f);
    	left_local_max= mmt(outecg[0],f);
    //Looking for the first local maximun to right	          
    for(r=(outecg[0]+1);r<((from)+DISTANCE) && !(right_local_max<= mmt(r,f) && mmt(r,f)>mmt(r+1,f) && abs(mmt(r,f) )>thf);r++){
	     if(right_local_max< mmt(r,f)&& mmt(r,f)==mmt(r+1,f)){right=r;}		    
	    right_local_max=mmt(r,f);
	}
    //Looking for the first local maximun to left	     
     for(l=(outecg[0]-1);l>=(from) && !(left_local_max<=mmt(l,f) && mmt(l,f)>mmt(l-1,f) && abs(mmt(l,f) )>thf);l--){  
	     if(left_local_max< mmt(l,f)&& mmt(l,f)==mmt(l-1,f)){left=l;}	
	    left_local_max=mmt(l,f);	    
	}

    if(r< ((from)+DISTANCE) && l>=(from) )
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
	t1 = DETECINTERVAL;		
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
	t1 = DETECINTERVAL;		
	// Looking for the first local minumun to right
	 for(r=(outecg[3]+1);r<((from)+DISTANCE) && !(right_local_min>mmt(r,f) && mmt(r,f)<=mmt(r+1,f) && abs(mmt(r,f))>thf)&&(t1!=0);r++,t1--){    
		 right_local_min=mmt(r,f);	    
		}
   		outecg[5]=r;	
    	if(r<((from)+DISTANCE) && (t1!=0))  {return 1;}else return 0;
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
	t1 = DETECINTERVAL2;	
	//busca 1º maximo local a la izquierda (onset Pwave):   
	l=outecg[2];
	while(!encontrado){
		onsetP==mmt(l,f);
				
		for(left1=(l-1);left1>=(from) && !(onsetP<=mmt(left1,f) && mmt(left1,f)>mmt(left1-1,f)&& mmt(left1,f)>0 /*&& abs(mmt(left1,f))>thf*/ ) &&(t1!=0);left1--,t1--){ 
			onsetP=mmt(left1,f);	    
		}
		//busca minimo intermedio que supere thf
		for(l=left1;l>=(from) && !(mmt(l+1,f)>=mmt(l,f) && mmt(l,f)<mmt(l-1,f) ) &&(t1!=0) ;l--,t1--);

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
	t1 = DETECINTERVAL2;

	r=outecg[3];	
	//busca 1º maximo local a la derecha (onset Twave):   
	while(!encontrado){
		onsetT=mmt(r,f);
		
		for(right1=r+1;right1<((from)+DISTANCE) && !(onsetT<=mmt(right1,f) &&mmt(right1,f)>mmt(right1+1,f) && mmt(right1,f)>0/*&& abs(mmt(right1,f))>thf*/) &&(t1!=0);right1++,t1--){
			onsetT=mmt(right1,f);	    
		}
		//busca minimo intermedio 
		for(r=right1;r<((from)+DISTANCE) && !(mmt(r-1,f)>=mmt(r,f) && mmt(r,f)<mmt(r+1,f))&&(t1!=0);r++ ,t1--);
		
		//si no ha encontrado ningun minimo y se ha salido
		if(r>=((from)+DISTANCE) || (t1==0))return 0;
		if (abs(mmt(r,f))>thf && mmt(r,f)<thf ){
			outecg[10]=r;
			encontrado=1;
			
			}
	
	}
	
	//busca 2º maximo local a la derecha (offset Twave):   
	offsetT=mmt(r,f);
	 for(right2=(r+1);right2<((from)+DISTANCE) && !(offsetT<=mmt(right2,f) && mmt(right2,f)>mmt(right2+1,f) && mmt(right2,f)>0/* && abs(mmt(right2,f))>thf*/)&&(t1!=0);right2++,t1--){    
	   offsetT=mmt(right2,f);	    
		}
		
    if(right1< ((from)+DISTANCE) && right2< ((from)+DISTANCE)  &&(t1!=0))
    {		
		 outecg[9]=right1;//onset
		outecg[11]=right2;//offset
		return 1;	
	}
    else if(t1==0) return 2;
    else return 0; 
}	

//********************************  Timing  **********************************************

void addSecond(){
	
	positions+=100;
	second++;
	if(positions==200){ second++; positions=0;}
	if(second>=60){
		second-=60;
		minute++;
		if(minute==60){
			minute=0;
			hour++;
			if(hour==24) hour=0;
				
		}	
	}		
}
void giveTime(int16_t instant,uint8_t rtime[12]){
	int16_t pos;
	pos=positions;
	rtime[2]=second;
	rtime[1]=minute;
	rtime[0]=hour;
	
	rtime[2]+=((instant+BUFLN)%BUFLN)/200;
	
	pos+=((instant+BUFLN)%BUFLN)%200;
	if(pos>=200){ rtime[2]++; pos-=200;}
	rtime[3]=pos;
	if(rtime[2]>=60){
		rtime[2]=rtime[2]-60;
		rtime[1]++;
		if(rtime[1]==60){
			rtime[1]=0;
			rtime[0]++;
			if(rtime[0]==24) rtime[0]=0;
				
		}	
	}	
}
//********************************************************************************************
//out = Rpeak, Rpeak.amplitude, Rwave[0], Rwave[1], Qwave, Swave, Pwave[0], Pwave.amplitude, Pwave[1], Twave[0], Twave.amplitude, Twave[1]

int8_t validation(int16_t rr){
	int16_t q,s,heart_freq;
	int16_t qtc;
	//if Q or S dont exist, using Rwave[0] and Rwave[1] respectively
	if(out[4]==0) q=out[2]; else q=out[4];	
	if(out[5]==0) s=out[3]; else s=out[5];
                                  
	//rule 1: Q-S distance<= 0.10s
	if((((s-q+BUFLN)%BUFLN)*100/FREQ) > 10) return 1;  
		
	//rule 2: 0.20s >= onset P - Q 	>= 0.12
	if((((q-out[6]+BUFLN)%BUFLN)*100/FREQ) < 12 || (((q-out[6]+BUFLN)%BUFLN)*100/FREQ) > 20) return 2; 
	//rule 3: Twave.amplitude > 0
	if(out[10]<0)return 3;
	//rule 4: Q-Rpeak distance <= 0.03s
	if((((out[0]-q+BUFLN)%BUFLN)*100/FREQ) > 3){	return 4;}  
	//rule 5: QTc = Q-offset T / sqr(RR), RR= Rpeaks distance, QTc in a normal range (see table qtc)
	/*qtc=((out[11]-q+BUFLN)%BUFLN)*100/ (sqrt(rr*100/FREQ)*FREQ);
	
	heart_freq=60*FREQ/rr;
	dbg(DBG_USR1, "------------- %d    %d  %f\n",heart_freq,qtc, sqrt(rr*100/FREQ));
	switch(heart_freq/10){
		//table qtc
		case 4:	if(qtc < 41 || qtc > 51) return 5;  else break;
		case 5:	if(qtc < 38 || qtc > 46) return 5;  else break;
		case 6:	if(qtc < 35 || qtc > 43) return 5;  else break;
		case 7:	if(qtc < 33 || qtc > 41) return 5;  else break;
		case 8:	if(qtc < 32 || qtc > 39) return 5;  else break;
		case 9:	if(qtc < 30 || qtc > 36) return 5;  else break;
		case 10:if(qtc < 28 || qtc > 34) return 5;  else break;
		case 11:
		case 12:if(qtc < 26 || qtc > 32) return 5;  else break;
		case 13:
		case 14:
		case 15:if(qtc < 23 || qtc > 28) return 5; else break;
		case 16:
		case 17:
		case 18:if(qtc < 21 || qtc > 25) return 5; else break;
		case 19:
		case 20:if(qtc < 20 || qtc > 24) return 5; else break; 
	
		
		default: return 5;
		
	}*/
	
	//rule 6: between S - onset T should be isoelectric 	
	
	//correct qrs
	return 0;
			
}




//******************************************************************************************
//***************************  METODO PRINCIPAL ********************************************
//**********************************************************************************************

int8_t ecg_detection_datain(int16_t datum, int8_t fp[BUFLNZIP])
{  
	int16_t max,i; //para el thresholding

	comprime(fp,(count+BUFLN)%(BUFLN),datum);
	count=(count+1+BUFLN)%(BUFLN);
	                  
	init=((count+1)+BUFLN)%(BUFLN);  
	from=init+MARGIN;//+NOPS*(1.5*LQRS*FS-1)/2;
	
	//Learning...
	if(initialize && count==0){
			initialize=0;		
	}
	if(initialize){	return 0;}
	
	//Thresholding calculation
	if(count==0){
		//reloj -> SUMA 1seg y 50 ms 
		addSecond();
		filled_buffer++;
		max=0;
		notnoise=(notnoise+BUFLN)%(BUFLN);
		
		for(i=0;i<DISTANCE;i++){	
			comprime(aux1,i,abs(mmt(((i+from)+BUFLN)%(BUFLN),fp)));
			
			if(max<descomprime(aux1,i,0))max=descomprime(aux1,i,0);
		}

		thr=115; thf=25; 
                            
	}             
	return 1;	
}
//****************************************************************************************************************************************
int8_t ecg_detection_rpeak(int8_t fp[BUFLNZIP],uint8_t detection[12])
{  
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)

	if(notnoise>=from){
		//dbg(DBG_USR1, "\%d --> MMF: \%d \%d\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp));
		return 0;	
	}else notnoise=0;
	
	
	// Step 3: Rpeaks detection, the local maxima and minima
	correct=rpeak_detection(fp,out);
	
	// Step 4: Rwave detection
	if (correct==1){
		return 1;		
		
	}else{
		if(filled_buffer>1){ 
			giveTime(count,detection);
			filled_buffer=0;	
			//dbg(DBG_USR1, "****%d : %d : %d : % d *************\n",detection[0],detection[1],detection[2],detection[3]);	
			return 7; //Too much time without Rpeak detection
		}
		
		//dbg(DBG_USR1, "\%d --> MMF:  \%d \%d Rpeak not detected\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp)); 
		return 0;	
	}
	

	return 0;
	
	
}

//****************************************************************************************************************************************
int8_t ecg_detection_rwave(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3])
{  
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)	
	
	// Step 4: Rwave detection		
      	correct=rwave(fp,out);	
      	if (correct==1) {    
        	return 1;}	
      /*  else{
	        dbg(DBG_USR1, "\%d --> MMF:  \%d \%d Rwave not detected\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp)); 
		}*/


	return 0;
	
	
}
//****************************************************************************************************************************************
int8_t ecg_detection_qwave(int8_t fp[BUFLNZIP],uint8_t detection[12])
{  
		   	
		// Step 5: Qwave detection
				notnoise=out[3]; 
				combine[3]=qwave(fp,out);
	return 1;
	
	
}

//****************************************************************************************************************************************
int8_t ecg_detection_swave(int8_t fp[BUFLNZIP],uint8_t detection[12])
{        
		// Step 6: Swave detection
				combine[2]= swave(fp,out);	

	return 1;
	
	
}
//****************************************************************************************************************************************
int8_t ecg_detection_pwave(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3])
{  
	// Step 7: onset and offset, Pwave and Twave detection
	combine[1]=pwave(fp,out);
				
				
	if(combine[1]==1){return 1;}else {
		//dbg(DBG_USR1, "****888888888888888888888888888888888888888888**********  \%d \%d \%d %d %d  ***\n",out[0],out[2],out[3],out[4],out[5] );	
		return 8; //Pwave not detected
	}
	return 0;
				
				
}


//****************************************************************************************************************************************

int8_t ecg_detection_twave(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3])
{  
	
		// Step 7: onset and offset, Pwave and Twave detection
		combine[0]=twave(fp,out);
	
				
		if(combine[0]==1){
			out[9]=(out[9]+BUFLN)%(BUFLN);  detection[10]=(out[9]-out[0]+BUFLN)%(BUFLN);
			out[10]=descomprime(fp,(out[10]+BUFLN)%(BUFLN),0);  amplitudes[2]=out[10];		
			out[11]= (out[11]+BUFLN)%(BUFLN); detection[11]=(out[11]-out[0]+BUFLN)%(BUFLN);
			return 1;	
				
		}else {out[9]=0;out[10]= 0;out[11]= 0; 
			if(combine[0]==2 || (from+10+BUFLN)%BUFLN > out[6]){ 
			//dbg(DBG_USR1, "****9999999999999999999999999999999 ************  \%d \%d \%d %d %d  %d %d***\n",out[0],out[2],out[3],out[4],out[5],out[6],out[8] );
			return 9; //Twave not detected
			}else {notnoise=(from+10); }
					
		}
				
				
				return 0;
				
}
//****************************************************************************************************************************************
int8_t ecg_detection_valid(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3])
{  
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)	

				out[0]=(out[0]+BUFLN)%(BUFLN); giveTime(count,detection);
				out[1]=descomprime(fp,(out[0]+BUFLN)%(BUFLN),0);  amplitudes[0]=out[1];
				out[2]=(out[2]+BUFLN)%(BUFLN);  detection[4]=(out[0]-out[2]+BUFLN)%(BUFLN);
				out[3]=(out[3]+BUFLN)%(BUFLN);  detection[5]=(out[3]-out[0]+BUFLN)%(BUFLN);
				
				if(combine[3]==1){
					out[4]=(out[4]+BUFLN)%(BUFLN); 
					detection[6]=(out[0]-out[4]+BUFLN)%(BUFLN);
				}else out[4]=0;
				if(combine[2]==1){
					out[5]=(out[5]+BUFLN)%(BUFLN);
					detection[7]=(out[5]-out[0]+BUFLN)%(BUFLN);
				} else out[5]=0;

				
				if(combine[1]==1){
				out[6]= (out[6]+BUFLN)%(BUFLN);  detection[8]=(out[0]-out[6]+BUFLN)%(BUFLN);
				out[7]=descomprime(fp,(out[7]+BUFLN)%(BUFLN),0); amplitudes[1]=out[7];					
				out[8]=(out[8]+BUFLN)%(BUFLN); detection[9]=(out[0]-out[8]+BUFLN)%(BUFLN);
		
				}else {	out[6]= 0;out[7]=0;out[8]=0;}

				if(combine[0]==1){
					if(filled_buffer==0)correct=validation((out[0]-last_Rpeak+BUFLN)%BUFLN);
					else correct=validation(((out[0]-last_Rpeak+BUFLN)%BUFLN)+(filled_buffer-1)*BUFLN);
					
					filled_buffer=0;
					last_Rpeak=out[0];
					//dbg(DBG_USR1, "**** \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d *************\n",correct,correct,correct,correct,correct,correct,correct,correct,correct,correct,correct,correct);	
				//dbg(DBG_USR1, "\%d --> MMF:  \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp),out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);	
						
				    	return correct;
				}
				//else dbg(DBG_USR1, " hola \%d --> MMF:  \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp),out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);	
				return 0;
				
}




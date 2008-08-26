/**********************************************************************************************************
/ VERSION 1.4 - Monica Jimenez, Laura Gutierrez
/ Sin Filtro. Usa señales ya filtradas.
/ Sin Validaciones.
/ Dividida en 8 pasos. Lee un dato en cada paso.
/ Devuelve las detecciones en formato HH:MM:SS.miliseg
/ Soportada por el Nodo.                    
/***********************************************************************************************************/
#include <math.h>
#include "ecg_detection.h"

int16_t c,count=0, from=0;//readed values number
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
    for(r=(outecg[0]+1);r<from+DISTANCE && !(right_local_max<= mmt(r,f) && mmt(r,f)>mmt(r+1,f) && abs(mmt(r,f) )>thf);r++){
	     if(right_local_max< mmt(r,f)&& mmt(r,f)==mmt(r+1,f)){right=r;}		    
	    right_local_max=mmt(r,f);
	}
    //Looking for the first local maximun to left	     
     for(l=(outecg[0]-1);l>=from && !(left_local_max<=mmt(l,f) && mmt(l,f)>mmt(l-1,f) && abs(mmt(l,f) )>thf);l--){  
	     if(left_local_max< mmt(l,f)&& mmt(l,f)==mmt(l-1,f)){left=l;}	
	    left_local_max=mmt(l,f);	    
	}

    if((r< (from+DISTANCE)) && (l>=from) )
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
	 for(l=(outecg[2]-1);l>=from && !(left_local_min>mmt(l,f) && mmt(l,f)<=mmt(l-1,f) && abs(mmt(l,f))>thf)&&(t1!=0);l--,t1--){  
		left_local_min=mmt(l,f);	    
		}
	outecg[4]=l;	
    if(l>=from && (t1!=0)) {return 1;}else{return 0;}
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
	 for(r=(outecg[3]+1);r<(from+DISTANCE)&& !(right_local_min>mmt(r,f) && mmt(r,f)<=mmt(r+1,f) && abs(mmt(r,f))>thf)&&(t1!=0);r++,t1--){    
		 right_local_min=mmt(r,f);	    
		}
   		outecg[5]=r;	
   		
    	if((r<(from+DISTANCE)) && (t1!=0))  {return 1;}else return 0;
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
	int16_t l,min, minAbs=10000;
	int8_t encontrado=0;
	int16_t q;
	//if Q or S dont exist, using Rwave[0] and Rwave[1] respectively
	if(outecg[4]==0) q=outecg[2]; else q=outecg[4];	
	
	//busca 1º maximo local a la izquierda (onset Pwave):   
	onsetP==mmt(q,f);
				
		for(left1=(q-1);left1>=(from) && !(onsetP<=mmt(left1,f) && mmt(left1,f)>mmt(left1-1,f)/*&& mmt(left1,f)>thf */ ) ;left1--){ 
			onsetP=mmt(left1,f);	    
		}
		
	while(!encontrado ){
		
	//busca 2º maximo local a la izquierda(offset Pwave):   
	offsetP=mmt(left1,f);
	
	for(left2=left1-1;left2>=(from) && !(offsetP<=mmt(left2,f) &&mmt(left2,f)>mmt(left2-1,f) /*&& mmt(left2,f)>thf*/);left2--){ 
		offsetP=mmt(left2,f);	    
	}
	
	//SI SUPERA LOS UMBRALES
	if(mmt(left1,f)>thf && mmt(left2,f)>thf){
	
	//busca minimo  ABSOLUTO intermedio que supere thf
		for(l=left1-1;l>left2 ;l--){
			if(minAbs>mmt(l,f)){minAbs= mmt(l,f); min=l;}
			}
		
		if (abs(mmt(min,f))>thf && mmt(min,f)<thf){
			outecg[7]=min;
			encontrado=1;}
			else{ 
				//Sigue Buscando
				left1=left2;
				
				
				}
	//si se ha salido de rango
	if(left1<(from) || left2<(from)|| min<from)return 0;
	
	}else //si no supera los umbrales
	left1=left2;
	
	
	}

	//Ajustando el incio de P
	l=left2;
	while(mmt(l,f)==mmt(l+1,f)){ l++;}
	left2=l;

	
	if(left1>=(from) && left2>=(from)&& min>=from)
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
	int16_t r, min, minAbs=10000;
	int8_t encontrado=0;

	int16_t s;
	if(outecg[5]==0) s=outecg[3]; else s=outecg[5];
	
	//busca 1º maximo local a la derecha (onset Twave):   
	onsetT=mmt(s,f);
		
		for(right1=s+1;right1<((from)+DISTANCE) && !(onsetT<=mmt(right1,f) &&mmt(right1,f)>mmt(right1+1,f) /*&& mmt(right1,f)>thf*/) ;right1++){
			onsetT=mmt(right1,f);	    
		}
	while(!encontrado){
		
	//busca 2º maximo local a la derecha (offset Twave):   
	offsetT=mmt(right1,f);
	 for(right2=(right1+1);right2<((from)+DISTANCE) && !(offsetT<=mmt(right2,f) && mmt(right2,f)>mmt(right2+1,f) /*&& mmt(right2,f)>thf*/);right2++){    
	   offsetT=mmt(right2,f);	    
		}
		
	if(mmt(right1,f)>thf &&  mmt(right2,f)>thf){
	//busca minimo ABSOLUTO intermedio 
		for(r=right1+1;r<right2 && !(mmt(r-1,f)>=mmt(r,f) && mmt(r,f)<mmt(r+1,f));r++ ){
			if(minAbs>mmt(r,f)){minAbs= mmt(r,f); min=r;}
			}
		
		//si no ha encontrado ningun minimo y se ha salido
		if (abs(mmt(min,f))>thf && mmt(min,f)<thf ){
			outecg[10]=min;
			encontrado=1;
			
			}	else {right1=right2;}
		
		  if(right1>=((from)+DISTANCE) || right2>= ((from)+DISTANCE)|| min>=((from)+DISTANCE) )	return 0;
		}else 	//si no supera los umbrales
		right1=right2;	
     }

	//Ajustando el final de T
	r=right2;
	while(mmt(r,f)==mmt(r-1,f)){ r--;}
	right2=r;		
		
    if(right1< ((from)+DISTANCE) && right2< ((from)+DISTANCE)&& min<((from)+DISTANCE) )
    {		
		 outecg[9]=right1;//onset
		outecg[11]=right2;//offset
		return 1;	
	}
    else return 0; 
}	

//********************************  Timing  **********************************************

void addPosition(){
	//Reloj va con la hora de Count
	positions++;
	
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
	
	pos-=(count+BUFLN - instant)%BUFLN;
	
	while(pos<0){
		pos+=200;
		rtime[2]--;
		}
	while(rtime[2]<0){
		rtime[2]+=60;
		rtime[1]--;
		}
	while(rtime[1]<0){
		rtime[1]+=60;
		rtime[0]--;
		}	
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

//******************************************************************************************
//***************************  METODO PRINCIPAL ********************************************
//**********************************************************************************************

int8_t ecg_detection_datain(int16_t datum, int8_t fp[BUFLNZIP])
{  
	comprime(fp,(count+BUFLN)%(BUFLN),datum);
	count=(count+1+BUFLN)%(BUFLN);
	//Aumenta el reloj:
	 addPosition();                 
	from=((count+1)+BUFLN)%(BUFLN)+MARGIN;//+NOPS*(1.5*LQRS*FS-1)/2;
	
	//Learning...
	if(initialize && count==0){
			initialize=0;		
	}
	if(initialize){	return 0;}
	
	//dbg_clear(DBG_USR1, "\%d --> MMF: \%d \%d  \n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp));

	//Thresholding calculation
	if(count==0){	
		filled_buffer++;
		notnoise=(notnoise+BUFLN)%(BUFLN);
                          
	} 
	thr=140; thf=5;             
	return 1;	
}
//****************************************************************************************************************************************
int8_t ecg_detection_rpeak(int8_t fp[BUFLNZIP],uint8_t detection[12])
{  
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)

	if(notnoise>=from){
		return 0;	
	}else notnoise=0;
	
	
	// Step 3: Rpeaks detection, the local maxima and minima
	correct=rpeak_detection(fp,out);
	
	// Step 4: Rwave detection
	if (correct==1){
		return 1;		
		
	}else{
		if(filled_buffer>0){ 
			giveTime(count,detection);
			filled_buffer=0;	
		//	dbg_clear(DBG_USR1, "Rpeak not detected\n"); 
			return 10; //Too much time without Rpeak detection
		}
		
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
        else{
	        //dbg_clear(DBG_USR1, "\%d --> MMF:  \%d \%d Rwave not detected\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp));
        
		}


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
		//dbg_clear(DBG_USR1, "****888888888888888888888888888888888888888888**********  \%d \%d \%d %d %d  ***\n",(out[0]+BUFLN)%(BUFLN),(out[2]+BUFLN)%(BUFLN),(out[3]+BUFLN)%(BUFLN),(out[4]+BUFLN)%(BUFLN),(out[5]+BUFLN)%(BUFLN) );	
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
			out[9]=(out[9]+BUFLN)%(BUFLN);  detection[10]=(out[9]+BUFLN)%(BUFLN);
			out[10]=(out[10]+BUFLN)%(BUFLN);  amplitudes[2]=(out[10]+BUFLN)%(BUFLN);			
			out[11]= (out[11]+BUFLN)%(BUFLN); detection[11]=(out[11]+BUFLN)%(BUFLN);
			return 1;	
				
		}else {out[9]=0;out[10]= 0;out[11]= 0; 
			if(combine[0]==2 || (from+10+BUFLN)%BUFLN > out[6]){ 
			
			//dbg_clear(DBG_USR1, "****9999999999999999999999999999999 ************  \%d \%d \%d %d %d  %d %d ***\n",out[0],out[2],out[3],out[4],out[5],out[6],out[8] );
			return 9; //Twave not detected
			}else {notnoise=(from+10); }
					
		}
				
				
				return 0;
				
}
//****************************************************************************************************************************************
int8_t ecg_detection_valid(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3])
{  
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)	

				out[0]=(out[0]+BUFLN)%(BUFLN); 
				out[1]=descomprime(fp,(out[0]+BUFLN)%(BUFLN),0);  amplitudes[0]=out[1];
				out[2]=(out[2]+BUFLN)%(BUFLN);  detection[4]=(out[2]+BUFLN)%(BUFLN);
				out[3]=(out[3]+BUFLN)%(BUFLN);  detection[5]=(out[3]+BUFLN)%(BUFLN);
				
				
				
				if(combine[0]==1){
				out[9]=(out[9]+BUFLN)%(BUFLN);  detection[10]=(out[9]+BUFLN)%(BUFLN);
				out[10]=(out[10]+BUFLN)%(BUFLN);  amplitudes[2]=(out[10]+BUFLN)%(BUFLN);			
				out[11]= (out[11]+BUFLN)%(BUFLN); detection[11]=(out[11]+BUFLN)%(BUFLN);
			
				}else {out[9]=0;out[10]= 0;out[11]= 0; 
				if(combine[0]==2 || (from+10+BUFLN)%BUFLN > out[6]){ correct=9;	}
				}
				
				if(combine[1]==1){
				out[6]= (out[6]+BUFLN)%(BUFLN);  detection[8]=(out[6]+BUFLN)%(BUFLN);
				out[7]=(out[7]+BUFLN)%(BUFLN); amplitudes[1]=(out[7]+BUFLN)%(BUFLN);					
				out[8]=(out[8]+BUFLN)%(BUFLN); detection[9]=(out[8]+BUFLN)%(BUFLN);
				
				}else {	out[6]= 0;out[7]=0;out[8]=0; correct=8;}
				
				
				if(combine[0]==1 && combine[1]==1){
					correct=0;
					filled_buffer=0;
					last_Rpeak=out[0];} 
			   	
			    if(combine[3]==1){
					out[4]=(out[4]+BUFLN)%(BUFLN); 
					detection[6]=(out[4]+BUFLN)%(BUFLN);
				}else out[4]=0;   
			       
			      			          
			    /*giveTime(out[0],detection);
				dbg_clear(DBG_USR1, "%d : %d . % d   N \n",detection[1],detection[2],detection[3]*5);*/ 
				if(combine[2]==1){
					out[5]=(out[5]+BUFLN)%(BUFLN);
					detection[7]=(out[5]+BUFLN)%(BUFLN);
					
				/*	giveTime(detection[7],detection);
			    	dbg_clear(DBG_USR1, "%d : %d . % d   )\n",detection[1],detection[2],detection[3]*5); */
				} else out[5]=0;  
			   
			    
				/* if(combine[0]==1){
			   giveTime(detection[10],detection);
			    dbg_clear(DBG_USR1, "%d : %d . % d   (\n",detection[1],detection[2],detection[3]*5);    			          
			    giveTime(amplitudes[2],detection);
				dbg_clear(DBG_USR1, "%d : %d . % d   T\n",detection[1],detection[2],detection[3]*5);   			    
			   	giveTime(detection[11],detection);
			    dbg_clear(DBG_USR1, "%d : %d . % d   )\n",detection[1],detection[2],detection[3]*5);  }*/
			   
			// dbg_clear(DBG_USR1, "\%d --> MMF:  \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp),out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);	
  		
				return correct;
				
				
}




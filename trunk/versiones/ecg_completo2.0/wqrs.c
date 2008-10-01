/**********************************************************************************************************
/ VERSION 2.0 - Monica Jimenez, Laura Gutierrez
/ Devuelve las detecciones en formato HH:MM:SS.miliseg
/ Reduce variables y operaciones 
/ Resultados similares a los de chart - o - matic
/ Con Comprobacion de las detecciones para validarlas.
/ Devuelve las amplitudes de Rpeak, Pwave y Twave
/ Soportada por el Nodo   
/ Envio - Recepcion: Se envian detecciones solo cuando hay error y este se ha repetido 2 veces seguidas                  
/***********************************************************************************************************/
#include <math.h>
#include "wqrs.h"

int16_t count=0, from=0;//main circle buffer indexs  

int16_t notnoise=0; // you shouldnt analyze the next positions when you find a Rpeak, 
					// to avoid detect the same repeak again, until it get out of the buffer  
int16_t thr=0,thf=0; //thresholds
int8_t initialize=1, filled_mm=0; // initialize buffers 
int16_t filled_buffer_fp=0; //max MAXFILLED times --> number of times that the buffer has to be filled to sum 200 positions  

uint8_t hour=0,minute=0,second=0, positions=0; //clock 
int16_t out[12];  //positions of current detecction
int8_t combine[4]; // 0 ->Twave exist, 1-> Pwave exist,  2 ->S exist, 3 ->Q exist
int16_t countdet=0;  //max and min circle buffers index
int16_t detec[5]; //positions of detections in max and min buffers
uint16_t maxMin[POINTS];  //positions of the min and max values who are bigger than thf
int16_t valuesfp[POINTS]; //values of the original signal
int16_t values[POINTS];  //values of the transform signal
int8_t isMax[POINTS];//1 if it is maximum or 0 if it is minimum
int16_t valorAnterior; //used to find the minimum or maximum when there are several identical values in the signal
int16_t dist_rpeaks;   //distant between the current and last rpeak in positions



//**********************************************************************************************************
//    COMPRIME Y DESCOMPRIME
//    saving and taking data from comprissed buffers
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
	if(isBuffer==0){  //f could have positives and negatives values
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
	}else {		//f just have positives values
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
    
    if ((current < (from)) && (current > (from)+DISTANCE)) {
		
	    return -1;
    }
		for (t = current-S; t <= current+S; t++){ //find the maximum and minimum local values 
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) > max) max = descomprime(f,(t+BUFLN)%(BUFLN),0);
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) < min) min = descomprime(f,(t+BUFLN)%(BUFLN),0);
		}
		
		//return ((max+min-2*descomprime(f,(current+BUFLN)%(BUFLN),0)) *10 / S );	
		return (((max+min-2*descomprime(f,(current+BUFLN)%(BUFLN),0)) *10 )>>4); //we can use a right shift instead division
}	
	
//********************************************************************************************
// step3: Rpeaks detection, the local maxima and minima
// return 0 if there aren't any rpeaks detected
//********************************************************************************************
int8_t rpeak_detection(int8_t f[BUFLNZIP], int16_t outecg[12]){

    int16_t r;  
   
    // Looking for the first local minimun in the buffer, smaller than -thr 
	r=countdet;
    while(r<countdet+POINTS){
	    
		if(values[(r+POINTS)%POINTS]<(-1*thr) && isMax[(r+POINTS)%POINTS]==0){	
			outecg[0]=maxMin[(r+POINTS)%POINTS];
			outecg[1]=valuesfp[(r+POINTS)%POINTS];
			detec[0]=r;
			
			return 1;}	
	    r++;   
    }
    //analize the last value
    if(values[(r+POINTS)%POINTS]<(-1*thr) && isMax[(r+POINTS)%POINTS]==0){
	    outecg[0]=maxMin[(r+POINTS)%POINTS];
	    outecg[1]=valuesfp[(r+POINTS)%POINTS];
	    detec[0]=r;
	    return 1;}
   
	return 0;
	
}

//********************************************************************************************
// step4: Rwave detection
// return 0 if there aren't any rwave detected
// rWAVE= the firts two local maxima from Rpeak to the right and to the left
//********************************************************************************************
int8_t rwave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	int16_t rwave0,rwave1;
	
	rwave0=detec[0]-1;
	rwave1=detec[0]+1;
	while((rwave0>=countdet) && rwave1<(countdet+POINTS)){
		if((abs(values[(rwave0+POINTS)%POINTS])>thf) && (abs(values[(rwave1+POINTS)%POINTS])>thf)
		&& isMax[(rwave0+POINTS)%POINTS]==1 && isMax[(rwave1+POINTS)%POINTS]==1){ 
			outecg[2]=maxMin[(rwave0+POINTS)%POINTS];  detec[1]=rwave0;
			outecg[3]=maxMin[(rwave1+POINTS)%POINTS];  detec[2]=rwave1;
			return 1;
		}else{
			if((abs(values[(rwave0+POINTS)%POINTS])<=thf)||isMax[(rwave0+POINTS)%POINTS]==0 )	rwave0=(rwave0-1);
			if((abs(values[(rwave1+POINTS)%POINTS])<=thf) ||isMax[(rwave1+POINTS)%POINTS]==0)	rwave1=(rwave1+1);
		}	
	} 
	return 0;
}

//********************************************************************************************
// step5: Qwave detection
//		  the firts local minima from Rwave to the left
//********************************************************************************************
int8_t qwave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	int16_t qw = (detec[1]-1);
	
	while(qw>=countdet){
		if((abs(values[(qw+POINTS)%POINTS])>thf)  && (values[(qw+POINTS)%POINTS]>0)
		&& ((BUFLNVIRT - maxMin[(qw+POINTS)%POINTS] +maxMin[(detec[0]+POINTS)%POINTS])%BUFLNVIRT)<=DETECINTERVAL && isMax[(qw+POINTS)%POINTS]==0){  
			outecg[4]=maxMin[(qw+POINTS)%POINTS]; 
			detec[3]=qw; 		
			return 1; 
		}else{
			
			
			if((BUFLNVIRT - maxMin[(qw+POINTS)%POINTS] +maxMin[(detec[0]+POINTS)%POINTS])%BUFLNVIRT>DETECINTERVAL || (values[(qw+POINTS)%POINTS]<0))
				return 0;	
			if((abs(values[(qw+POINTS)%POINTS])<=thf)||isMax[(qw+POINTS)%POINTS]==1)	qw=(qw-1);
		}
	}
   return 0;
}
//********************************************************************************************
// step6: Swave detection
//        the firts local minima from Rwave to the right
//********************************************************************************************
int8_t swave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	
	int16_t sw = (detec[2]+1);
	
	while(sw<(countdet+POINTS)){	
		if( (abs(values[(sw+POINTS)%POINTS])>thf) && (values[(sw+POINTS)%POINTS]>0)
		&&  ((BUFLNVIRT - maxMin[(detec[0]+POINTS)%POINTS] +maxMin[(sw+POINTS)%POINTS])%BUFLNVIRT< DETECINTERVAL)  && isMax[(sw+POINTS)%POINTS]==0){  
			outecg[5]=maxMin[(sw+POINTS)%POINTS];  
			detec[4]=sw; 
			return 1; 
		}else {
			if((BUFLNVIRT - maxMin[(detec[0]+POINTS)%POINTS] +maxMin[(sw+POINTS)%POINTS])%BUFLNVIRT>DETECINTERVAL || (values[(sw+POINTS)%POINTS]<0))
				return 0;	
			if((abs(values[(sw+POINTS)%POINTS])<=thf)|| isMax[(sw+POINTS)%POINTS]==1)	sw=(sw+1);
		}
	}
   return 0;	
}
//********************************************************************************************
// step7: onset and offset, Pwave and Twave detection
//********************************************************************************************
int8_t pwave(int8_t f[BUFLNZIP], int16_t outecg[12]){	
	//Pwave=Searching two local maxima from Qwave (Rwave) to the left
	int16_t offsetP;
	int16_t onsetP;
	int16_t pPeak;
	
	if(combine[3]==1){ // if Qwave exists 
		offsetP=(detec[3]-1);
		pPeak=detec[3]-2;
		onsetP=(detec[3]-3);
	}else{				// if Qwave doesn`t exist 
		offsetP=(detec[1]-1);
		pPeak=detec[1]-2;
		onsetP=(detec[1]-3);
    }
	
 while(onsetP>=countdet){
		if((values[(onsetP+POINTS)%POINTS]>thf) && (values[(offsetP+POINTS)%POINTS]>thf) && (values[(pPeak+POINTS)%POINTS]<(-1)*thf)
			&&  isMax[(onsetP+POINTS)%POINTS]==1 &&  isMax[(offsetP+POINTS)%POINTS]==1 &&  isMax[(pPeak+POINTS)%POINTS]==0){ 
			
				outecg[6]=maxMin[(onsetP+POINTS)%POINTS];//onset
		 		outecg[8]=maxMin[(offsetP+POINTS)%POINTS];//offset    
		 		outecg[7]=valuesfp[(pPeak+POINTS)%POINTS]; 
		 			return 1;
	 	}else{
		 	if(isMax[(onsetP+POINTS)%POINTS]==0 && isMax[(offsetP+POINTS)%POINTS]==1 && isMax[(pPeak+POINTS)%POINTS]==0){
			 	if(values[(pPeak+POINTS)%POINTS]>=(-1)*thf){   //we can find several min between two maximum: max - min - min - ... - max
				 	pPeak=onsetP;
				 }
				 onsetP=(onsetP-1);	
			 }else{
				 onsetP=(offsetP-3);
				 pPeak=offsetP-2;
				 offsetP=(offsetP-1);
				 }
		}		
 }
 return 0; 
}	
//********************************************************
// Looking for Twave
//*******************************************************

int8_t twave(int8_t f[BUFLNZIP], int16_t outecg[12]){
//Twave= Searching two local maxima from Swave (Rwave) to the right
	int16_t offsetT;
	int16_t onsetT;
	int16_t tPeak;

	if(combine[2]==1){ // if Swave exists 
		onsetT=(detec[4]+1);
		offsetT=(detec[4]+3);
		tPeak=detec[4]+2;
	}
	else{				// if Swave doesn't exist 
		onsetT=(detec[2]+1);
		offsetT=(detec[2]+3);
		tPeak=detec[2]+2;
    }

 while(offsetT<(countdet+POINTS)){	
	if((values[(onsetT+POINTS)%POINTS]>thf) && (values[(offsetT+POINTS)%POINTS]>thf) && (values[(tPeak+POINTS)%POINTS]<(-1)*thf)
			&&  isMax[(onsetT+POINTS)%POINTS]==1 &&  isMax[(offsetT+POINTS)%POINTS]==1 &&  isMax[(tPeak+POINTS)%POINTS]==0){ 
			
				outecg[9]=maxMin[(onsetT+POINTS)%POINTS];//onset
		 		outecg[11]=maxMin[(offsetT+POINTS)%POINTS];//offset    
		 		outecg[10]=valuesfp[(tPeak+POINTS)%POINTS]; 
		 		notnoise=offsetT;
		 			return 1;
	 	}else{
		 	if(isMax[(offsetT+POINTS)%POINTS]==0 && isMax[(onsetT+POINTS)%POINTS]==1 && isMax[(tPeak+POINTS)%POINTS]==0){
			 	if(values[(tPeak+POINTS)%POINTS]>=(-1)*thf){  //we can find several min between two maximum: max - min - min - ... - max
				 	tPeak=offsetT;
				 }
				 offsetT=(offsetT+1);	
			 }else{
				 offsetT=(onsetT+3);
				 tPeak=onsetT+2;
				 onsetT=(onsetT+1);
				 }
		}	
 }	
 return 0; 
}	

//*************************************************************************************************************************************
//***********************************************************  Timing  ****************************************************************
//*************************************************************************************************************************************
//Incrementing clock a position ( clock respect Count)
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
//calculate the time of instant (instant is a position in the virtual buffer)
void giveTime(int16_t instant,int8_t rtime[12]){
	int16_t pos, rs, rm, rh;
	pos=positions;
	rs=second;
	rm=minute;
	rh=hour;
	
//calculate positions respect Count
	if(count<from) pos-=(count+(BUFLN*(filled_buffer_fp +1)) + BUFLNVIRT- instant)%BUFLNVIRT; 
	else pos-=(count+(BUFLN*filled_buffer_fp) + BUFLNVIRT- instant)%BUFLNVIRT; //instante ahora va a ser de 0 a 199!
	while(pos<0){
		pos+=200;
		rs--;
	}
	while(rs<0){
		rs+=60;
		rm--;
	}
	while(rm<0){
		rm+=60;
		rh--;
	}	         
	if(rs>=60){
		rs=rs-60;
		rm++;
		if(rm==60){
			rm=0;
			rh++;
			if(rh==24) rh=0;		
		}	
	}
	rtime[3]=pos;
	rtime[2]=rs;
	rtime[1]=rm;
	rtime[0]=rh;		
}
//******************************************************************************************************************************************
//****************************************               VALIDATION METHOD            ******************************************************
//******************************************************************************************************************************************
//Validate in function of the nomality rules
//out = Rpeak, Rpeak.amplitude, Rwave[0], Rwave[1], Qwave, Swave, Pwave[0], Pwave.amplitude, Pwave[1], Twave[0], Twave.amplitude, Twave[1]

int8_t validation(int16_t rr,uint8_t detection[12]){
	int16_t q,s,heart_freq;
	int16_t qtc;
	
	//if Q or S dont exist, using Rwave[0] and Rwave[1] respectively
	if(out[4]==-1){ 
		q=detection[4]>>1; 
	
	}else{ 
		q=detection[6]>>1; 
	}	
	if(out[5]==-1){ 
		s=detection[5]>>1; 	
	}else{
		s=detection[7]>>1; 
	}

	                                 
	//rule 1: Q-S distance<= 0.10s
	if((s+q) > 10) return 1;  
		
	//rule 2: 0.20s >= onset P - Q 	>= 0.12
	if(((detection[8]>>1)-q) < 12 || ((detection[8]>>1)-q) > 20) return 2; 
	
	//rule 3: Twave.amplitude > 0  
	if(out[10]<0)return 3;   
	
	//rule 4: Q-Rpeak distance <= 0.03s
	if(q > 3){	return 4;}  
	
	//rule 5: QTc = Q-offset T / sqr(RR), RR= Rpeaks distance, QTc in a normal range (see table qtc)
	
/*	
	qtc=((detection[11]>>1)+q)/ sqrt(rr);
	
	heart_freq=60/rr;
	dbg(DBG_USR1, "------------- %d    %d  %f\n",heart_freq,qtc, sqrt(rr));
	switch(heart_freq){
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
		
	}
	
	//rule 6: between S - onset T should be isoelectric 	
	*/
	//correct qrs
	return 0;
			
}

//***********************************************************************************************************************
//***************************                   LOOKING FOR MAX Y MIN VALUES          ***********************************
//***********************************************************************************************************************
//find minimun and maximun data
int8_t mainPoints( int8_t f[BUFLNZIP]){
	int16_t val1,val2,datum;
	int16_t j;
	j=from;
	//three values to compare
	datum= mmt((j+BUFLN)%(BUFLN),f);//last data saved in the buffer
	val1=mmt((j+1 +BUFLN)%(BUFLN),f);
	val2=mmt((j+2+BUFLN)%(BUFLN),f); 

	if(((val1==val2) && (val1>datum || val1<datum))&&(( abs(val1)>thr) || (abs(val1)>thf))){
		valorAnterior=datum;
		}
	
	//if val1 is maximum or minimum and it is bigger than thf, we save it 
	if(((val1>val2 && val1>datum)||(val1<val2 && val1<datum)) && (( abs(val1)>thr) || (abs(val1)>thf))){
		values[countdet]= val1;
		valuesfp[countdet]=descomprime(f,(j+1 +BUFLN)%(BUFLN),0);   
		
		//saving the position respect the virtual buffer with 200 longitude
		if( (j+1 +BUFLN)%(BUFLN)!=0 )maxMin[countdet]= (j+1+BUFLN)%(BUFLN)+BUFLN*filled_buffer_fp;
		else maxMin[countdet]= (j+1+BUFLN)%(BUFLN)+BUFLN*(filled_buffer_fp+1);
		if((val1>val2) && (val1>datum))isMax[countdet]=1;else isMax[countdet]=0;
		countdet=(countdet+1+POINTS)%POINTS;
		filled_mm=1;
		return 1;
	}else
	//if val1 is the last value of several identical values, and it is bigger than thf, we save it
		if(((val1==datum && valorAnterior<val1 && val1>val2)||(val1==datum && valorAnterior>val1 && val1<val2)) && (( abs(val1)>thr) || (abs(val1)>thf))){
			values[countdet]= val1;
			valuesfp[countdet]=descomprime(f,(j+1 +BUFLN)%(BUFLN),0);  
			
			//saving the position respect the virtual buffer with 200 longitude 
			if( (j+1 +BUFLN)%(BUFLN)!=0 )maxMin[countdet]= (j+1+BUFLN)%(BUFLN)+BUFLN*filled_buffer_fp;
			else maxMin[countdet]= (j+1+BUFLN)%(BUFLN)+BUFLN*(filled_buffer_fp+1);
			if((val1==datum) && (valorAnterior<val1 )&& (val1>val2))  isMax[countdet]=1;  else isMax[countdet]=0;
			countdet=(countdet+1+POINTS)%POINTS;
			filled_mm=1;
			return 1;
		}
		return 0;
}

//*****************************************************************************************************************
//***************************  METODO PRINCIPAL : divided in 8 steps   ********************************************
//******************************************************************************************************************


//*****************************************************************************************************************
// 1�STEP : Add a new data
//******************************************************************************************************************
int8_t ecg_detection_datain(int16_t datum, int8_t fp[BUFLNZIP])
{  
	
	static uint8_t detection[12];
	
//insert the new data in the circle buffer
	comprime(fp,(count+BUFLN)%(BUFLN),datum);
	
	count=(count+1+BUFLN)%(BUFLN);
	
	//clock update
	 addPosition();
	 dist_rpeaks++;

	                  
	from=((count+1+MARGIN+BUFLN)%(BUFLN));  //to avoid the "margin" initial values, because they are useless because of the mmt
	if(from==0){
		filled_buffer_fp++;
		if(filled_buffer_fp==MAXFILLED) filled_buffer_fp=0; 	
	}	
	
	//fixing thresholds
	thr=140; thf=5; 
	
	//searching for local minima or maxima points
	if(!mainPoints(fp)){
		giveTime((from) + (BUFLN*filled_buffer_fp),detection);
		return 0;
 	}
 	giveTime((from) + (BUFLN*filled_buffer_fp),detection);
	
 	
	//Learning...
	if(initialize &&  countdet==0 && filled_mm){
			initialize=0;	
	}

	if(initialize ){return 0;} //we dont analize the signtal until the maxmin buffer is filled

	if(countdet==0){		
		notnoise=(notnoise+POINTS)%(POINTS);	                   
	}
	if(notnoise==countdet) notnoise=0;   
	
			          
	return 1;	
	
}
//*****************************************************************************************************************
// 2�STEP : Looking for Rpeak
//******************************************************************************************************************
int8_t ecg_detection_rpeak(int8_t fp[BUFLNZIP],uint8_t detection[12]){ 
	int8_t correct=0;
	
	if(notnoise>countdet){
		return 0;	
	}else{ notnoise=0;}
	
// Step 3: Rpeaks detection, the local minima
	correct=rpeak_detection(fp,out);
	if (correct==1){
		return 1;		//Rpeak detected
		
	}else{
		
		if(dist_rpeaks>2*MAXFILLED*BUFLN){ 
			giveTime(count,detection);	
			return 10; //Too much time without Rpeak detection
		}	
}
	return 0;
	
	
}

//*****************************************************************************************************************
// 3�STEP : Looking for Rwave
//******************************************************************************************************************
int8_t ecg_detection_rwave(int8_t fp[BUFLNZIP]){  	
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)	
	// Step 4: Rwave detection		
      	correct=rwave(fp,out);	
      	if (correct==1) {    
        	return 1;}	
        
	return 0;
}
//*****************************************************************************************************************
// 4�STEP : Looking for Qwave
//******************************************************************************************************************
int8_t ecg_detection_qwave(int8_t fp[BUFLNZIP]){     
	// Step 5: Qwave detection
	notnoise=detec[2];
	combine[3]=qwave(fp,out);
	return 1;
}

//*****************************************************************************************************************
// 5�STEP : Looking for Swave
//******************************************************************************************************************
int8_t ecg_detection_swave(int8_t fp[BUFLNZIP]){       
	// Step 6: Swave detection
	combine[2]= swave(fp,out);	
	return 1;
}
//*****************************************************************************************************************
// 6�STEP : Looking for Pwave
//******************************************************************************************************************
int8_t ecg_detection_pwave(int8_t fp[BUFLNZIP]){  
	// Step 7: onset and offset, Pwave and Twave detection
	combine[1]=pwave(fp,out);
	if(combine[1]==1){
		return 1;	//Pwave detected
	}else {
		return 8; //Pwave not detected
	}
	return 0;
}
//*****************************************************************************************************************
// 7�STEP : Looking for Twave
//******************************************************************************************************************
int8_t ecg_detection_twave(int8_t fp[BUFLNZIP]){  	
		// Step 7: onset and offset, Pwave and Twave detection
		combine[0]=twave(fp,out);
		if(combine[0]==1){	
			return 1;	//Twave detected	
		}else {
			out[9]=-1;out[10]= -1;out[11]= -1; 
			combine[0]=2;
			return 9; //Twave not detected
	
		}
		return 0;
}
//*****************************************************************************************************************
// 8�STEP : Validate the deteccion
//******************************************************************************************************************
int8_t ecg_detection_valid(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3]){  
	int8_t correct=0; 
	
	//saving information in detection and amplitudes 
	giveTime(out[0],detection);
	amplitudes[0]=out[1];
	detection[4]=(BUFLNVIRT - out[2]+out[0])%BUFLNVIRT;
	detection[5]=(BUFLNVIRT - out[0]+out[3])%BUFLNVIRT;
						
	if(combine[0]==1){
		detection[10]=(BUFLNVIRT - out[0]+ out[9])%BUFLNVIRT; 
		amplitudes[2]=out[10];			
		detection[11]=(BUFLNVIRT - out[0]+out[11])%BUFLNVIRT;
	}else {
		detection[10]= 0;detection[11]= 0; 
		if(combine[0]==2){ correct=9;}
	}
	if(combine[1]==1){
		detection[8]=(BUFLNVIRT - out[6]+out[0])%BUFLNVIRT;
		amplitudes[1]=out[7];					
		detection[9]=(BUFLNVIRT - out[8]+out[0])%BUFLNVIRT;
	}else {	detection[9]=0;detection[8]=0; correct=8;}
				
	if(combine[0]==1 && combine[1]==1){
		correct=0;
	}
	if(combine[3]==1){
		
		detection[6]=(BUFLNVIRT - out[4]+out[0])%BUFLNVIRT;
	}else detection[6]=0;   

	if(combine[2]==1){
		
		detection[7]=(BUFLNVIRT - out[0]+out[5])%BUFLNVIRT;
	} else detection[7]=0;  
			   
	if(correct!=8 && correct!=9){
		//validating the detection
		correct=validation(dist_rpeaks>>1,detection);
	}	
	dist_rpeaks=0;

	//dbg_clear(DBG_USR1, "correct  \%d - \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",correct, out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);				
		
	//dbg_clear(DBG_USR1, " \%d --> \%d : %d : %d . %d (%d) %d %d \%d \%d %d (\%d) \%d \%d (\%d) %d\n",correct, detection[0],detection[1],detection[2],detection[3],amplitudes[0],detection[4],detection[5],detection[6],detection[7],detection[8], amplitudes[1],detection[9], detection[10],amplitudes[2], detection[11]);				
		
	return correct;

				
}




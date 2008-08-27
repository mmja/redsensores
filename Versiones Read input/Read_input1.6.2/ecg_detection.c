/**********************************************************************************************************
/ VERSION 1.6.2 - Monica Jimenez, Laura Gutierrez
/ Mejora de las detecciones con respecto a la 1.6
/ Not noise funcionando, from virtual de 0 a 199
/ No hay validación de los datos y la salida es en función de la posicion del buffer
/ Soportada por el Nodo                    
/***********************************************************************************************************/
#include <math.h>
#include "ecg_detection.h"

int16_t count=0, from=0;//readed values number
int16_t notnoise=0;
int16_t thr=0,thf=0; //threshold
int8_t initialize=1, filled_mm=0; //variables usadas como booleanos en la inicialización de los buffers
int8_t filled_buffer; //number of times since the last Rpeak detection that the buffer has been completely filled. 
int8_t filled_buffer_from=0; //max MAXFILLED times --> number of times that the buffer has to be filled to sum 200 positions  

int16_t out[12];
int8_t combine[4]; // 0 ->Twave exist, 1-> Pwave exist,  2 ->S exist, 3 ->Q exist
int16_t detec[5], countdet=0;
uint16_t maxMin[POINTS];
int16_t values[POINTS];
int16_t nfilled[POINTS];
int8_t isMax[POINTS];//Si es maximo se pone a 1 y si es minimo a 0
int16_t valorAnterior;
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
    
    if ((current < (from)) && (current > (from)+DISTANCE)) {
		
	    return -1;
    }
		for (t = current-S; t <= current+S; t++){ //find the maximum and minimum local values 
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) > max) max = descomprime(f,(t+BUFLN)%(BUFLN),0);
				if (descomprime(f,(t+BUFLN)%(BUFLN),0) < min) min = descomprime(f,(t+BUFLN)%(BUFLN),0);
		}
		return (((max+min-2*descomprime(f,(current+BUFLN)%(BUFLN),0)) *10 )>>4);
}	
	
//********************************************************************************************
// step3: Rpeaks detection, the local maxima and minima
// return 0 if there aren't any rpeaks detected
//********************************************************************************************
int8_t rpeak_detection(int8_t f[BUFLNZIP], int16_t outecg[12]){

    int16_t r;  
   
    // Looking for the first local minimun 
	r=countdet;
    while(r<countdet+POINTS){
	    
		if(values[(r+POINTS)%POINTS]<(-1*thr) && isMax[(r+POINTS)%POINTS]==0){	
			outecg[0]=maxMin[(r+POINTS)%POINTS]+(BUFLN*nfilled[(r+POINTS)%POINTS]);
			outecg[1]=values[(r+POINTS)%POINTS];
			detec[0]=r;
			
			return 1;}	
	    r++;   
    }
    //ANALIZA EL ULTIMO VALOR
    if(values[(r+POINTS)%POINTS]<(-1*thr) && isMax[(r+POINTS)%POINTS]==0){
	    outecg[0]=maxMin[(r+POINTS)%POINTS]+(BUFLN*nfilled[(r+POINTS)%POINTS]);
	    outecg[1]=values[(r+POINTS)%POINTS];
	    detec[0]=r;
	    return 1;}
   
	return 0;
	
}

//********************************************************************************************
// step4: Rwave detection
// return 0 if there aren't any rwave detected
//********************************************************************************************
int8_t rwave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	int16_t rwave0,rwave1;
	
	rwave0=detec[0]-1;
	rwave1=detec[0]+1;
	while((rwave0>=countdet) && rwave1<(countdet+POINTS)){
		if((abs(values[(rwave0+POINTS)%POINTS])>thf) && (abs(values[(rwave1+POINTS)%POINTS])>thf)
		&& isMax[(rwave0+POINTS)%POINTS]==1 && isMax[(rwave1+POINTS)%POINTS]==1){ 
			outecg[2]=maxMin[(rwave0+POINTS)%POINTS]+(BUFLN*nfilled[(rwave0+POINTS)%POINTS]);  detec[1]=rwave0;
			outecg[3]=maxMin[(rwave1+POINTS)%POINTS]+(BUFLN*nfilled[(rwave1+POINTS)%POINTS]);  detec[2]=rwave1;
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
//********************************************************************************************
int8_t qwave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	int16_t qw = (detec[1]-1);
	
	while(qw>=countdet){
		if((abs(values[(qw+POINTS)%POINTS])>thf)  && (values[(qw+POINTS)%POINTS]>0)
		&& (abs(maxMin[(detec[0]+POINTS)%POINTS]- maxMin[(qw+POINTS)%POINTS])<=DETECINTERVAL)&& isMax[(qw+POINTS)%POINTS]==0){  
			outecg[4]=maxMin[(qw+POINTS)%POINTS]+(BUFLN*nfilled[(qw+POINTS)%POINTS]); 
			detec[3]=qw; 		
			return 1; 
		}else{
			if(abs(maxMin[(detec[0]+POINTS)%POINTS]- maxMin[(qw+POINTS)%POINTS])>DETECINTERVAL || (values[(qw+POINTS)%POINTS]<0))
				return 0;	
			if((abs(values[(qw+POINTS)%POINTS])<=thf)||isMax[(qw+POINTS)%POINTS]==1)	qw=(qw-1);
		}
	}
   return 0;
}
//********************************************************************************************
// step6: Swave detection
//********************************************************************************************
int8_t swave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	
	int16_t sw = (detec[2]+1);
	
	while(sw<(countdet+POINTS)){	
		if( (abs(values[(sw+POINTS)%POINTS])>thf) && (values[(sw+POINTS)%POINTS]>0)
		&&  (abs(maxMin[(detec[0]+POINTS)%POINTS]- maxMin[(sw+POINTS)%POINTS])< DETECINTERVAL)  && isMax[(sw+POINTS)%POINTS]==0){  
			outecg[5]=maxMin[(sw+POINTS)%POINTS]+(BUFLN*nfilled[(sw+POINTS)%POINTS]);  
			detec[4]=sw; 
			return 1; 
		}else {
			if(abs(maxMin[(detec[0]+POINTS)%POINTS]- maxMin[(sw+POINTS)%POINTS])>DETECINTERVAL || (values[(sw+POINTS)%POINTS]<0))
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
	//Pwave=Buscamos 2 maximos locales desde Qwave hacia la izq:
	int16_t offsetP;
	int16_t onsetP;
	int16_t pPeak;
	
	if(combine[3]==1){ // si existe q
		offsetP=(detec[3]-1);
		pPeak=detec[3]-2;
		onsetP=(detec[3]-3);
	}else{				// si NO existe q
		offsetP=(detec[1]-1);
		pPeak=detec[1]-2;
		onsetP=(detec[1]-3);
    }
	
 while(onsetP>=countdet){
		if((values[(onsetP+POINTS)%POINTS]>thf) && (values[(offsetP+POINTS)%POINTS]>thf) && (values[(pPeak+POINTS)%POINTS]<(-1)*thf)
			&&  isMax[(onsetP+POINTS)%POINTS]==1 &&  isMax[(offsetP+POINTS)%POINTS]==1 &&  isMax[(pPeak+POINTS)%POINTS]==0){ 
			
				outecg[6]=maxMin[(onsetP+POINTS)%POINTS]+(BUFLN*nfilled[(onsetP+POINTS)%POINTS]);//onset
		 		outecg[8]=maxMin[(offsetP+POINTS)%POINTS]+(BUFLN*nfilled[(offsetP+POINTS)%POINTS]);//offset    
		 		outecg[7]=values[(pPeak+POINTS)%POINTS]; 
		 			return 1;
	 	}else{
		 	if(isMax[(onsetP+POINTS)%POINTS]==0 && isMax[(offsetP+POINTS)%POINTS]==1 && isMax[(pPeak+POINTS)%POINTS]==0){
			 	if(values[(pPeak+POINTS)%POINTS]>=(-1)*thf){   //permite la combinacion max - min - min - ... - max
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
int8_t twave(int8_t f[BUFLNZIP], int16_t outecg[12]){
	//Twave=Buscamos 2 maximos locales desde Swave hacia la dcha:
	int16_t offsetT;
	int16_t onsetT;
	int16_t tPeak;//=1000;

	if(combine[2]==1){ // si existe s
		onsetT=(detec[4]+1);
		offsetT=(detec[4]+3);
		tPeak=detec[4]+2;
	}
	else{				// si NO existe s
		onsetT=(detec[2]+1);
		offsetT=(detec[2]+3);
		tPeak=detec[2]+2;
    }

 while(offsetT<(countdet+POINTS)){	
	if((values[(onsetT+POINTS)%POINTS]>thf) && (values[(offsetT+POINTS)%POINTS]>thf) && (values[(tPeak+POINTS)%POINTS]<(-1)*thf)
			&&  isMax[(onsetT+POINTS)%POINTS]==1 &&  isMax[(offsetT+POINTS)%POINTS]==1 &&  isMax[(tPeak+POINTS)%POINTS]==0){ 
			
				outecg[9]=maxMin[(onsetT+POINTS)%POINTS]+(BUFLN*nfilled[(onsetT+POINTS)%POINTS]);//onset
		 		outecg[11]=maxMin[(offsetT+POINTS)%POINTS]+(BUFLN*nfilled[(offsetT+POINTS)%POINTS]);//offset    
		 		outecg[10]=values[(tPeak+POINTS)%POINTS]; 
		 		notnoise=offsetT;
		 			return 1;
	 	}else{
		 	if(isMax[(offsetT+POINTS)%POINTS]==0 && isMax[(onsetT+POINTS)%POINTS]==1 && isMax[(tPeak+POINTS)%POINTS]==0){
			 	if(values[(tPeak+POINTS)%POINTS]>=(-1)*thf){  //permite la combinacion max - min - min - ... - max
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

//********************************************************************************************
//out = Rpeak, Rpeak.amplitude, Rwave[0], Rwave[1], Qwave, Swave, Pwave[0], Pwave.amplitude, Pwave[1], Twave[0], Twave.amplitude, Twave[1]
int8_t mainPoints( int8_t f[BUFLNZIP]){
	int16_t val1,val2,datum;
	int16_t j;
	j=from;
	datum= mmt((j+BUFLN)%(BUFLN),f);
	val1=mmt((j+1 +BUFLN)%(BUFLN),f);//valor anterior (el del medio)
	val2=mmt((j+2+BUFLN)%(BUFLN),f); //valor mas anterior

	if(((val1==val2) && (val1>datum || val1<datum))&&(( abs(val1)>thr) || (abs(val1)>thf))){
		valorAnterior=datum;
		}
	
	//Si es maximo o minimo, y supera los umbrales (thr o thf)
	if(((val1>val2 && val1>datum)||(val1<val2 && val1<datum)) && (( abs(val1)>thr) || (abs(val1)>thf))){
		maxMin[countdet]= (j+1+BUFLN)%(BUFLN);
		values[countdet]= val1;
		if( (j+1 +BUFLN)%(BUFLN)!=0 )nfilled[countdet]=filled_buffer_from; else nfilled[countdet]=filled_buffer_from+1;
		if((val1>val2) && (val1>datum))isMax[countdet]=1;else isMax[countdet]=0;
		countdet=(countdet+1+POINTS)%POINTS;
		filled_mm=1;
		return 1;
	}else
	//Si es el ultimo  de muchos iguales y supera umabrles
		if(((val1==datum && valorAnterior<val1 && val1>val2)||(val1==datum && valorAnterior>val1 && val1<val2)) && (( abs(val1)>thr) || (abs(val1)>thf))){
			maxMin[countdet]= (j+1+BUFLN)%(BUFLN);
			values[countdet]= val1;
			if( (j+1 +BUFLN)%(BUFLN)!=0 )nfilled[countdet]=filled_buffer_from; else nfilled[countdet]=filled_buffer_from+1;
			if((val1==datum) && (valorAnterior<val1 )&& (val1>val2))  isMax[countdet]=1;  else isMax[countdet]=0;
			countdet=(countdet+1+POINTS)%POINTS;
			filled_mm=1;
			return 1;
		}
		return 0;
}

//******************************************************************************************
//***************************  METODO PRINCIPAL ********************************************
//**********************************************************************************************

int8_t ecg_detection_datain(int16_t datum, int8_t fp[BUFLNZIP])
{  
	comprime(fp,(count+BUFLN)%(BUFLN),datum);
	
	count=(count+1+BUFLN)%(BUFLN);
	
	//Aumenta el reloj:
	from=((count+1+MARGIN+BUFLN)%(BUFLN));//+NOPS*(1.5*LQRS*FS-1)/2;
	if(from==0){
		filled_buffer_from++;
		if(filled_buffer_from==MAXFILLED) filled_buffer_from=0; 	
	}
	//Fija los umbrales y Coge los puntos clave
	thr=140; thf=5; 
	if(!mainPoints(fp)){
		//dbg_clear(DBG_USR1, "\%d --> MMF: \%d \%d in \n",(from) + (BUFLN*filled_buffer_from),descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp));
 		return 0;
 	}
	//dbg_clear(DBG_USR1, "\%d --> MMF: \%d \%d -> %d  %d\n",(from) + (BUFLN*filled_buffer_from),descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp),notnoise,countdet);

	//Learning...
	if(initialize &&  countdet==0&& filled_mm){
		//dbg_clear(DBG_USR1, "inicializado\n");
			initialize=0;	
	}

	if(initialize ){return 0;}

	if(countdet==0){		
		filled_buffer++;
		notnoise=(notnoise+POINTS)%(POINTS);	                   
	}
	if(notnoise==countdet) notnoise=0;   
		          
	return 1;	
	
}
//****************************************************************************************************************************************
int8_t ecg_detection_rpeak(int8_t fp[BUFLNZIP],uint8_t detection[12]){ 
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)
	
	if(notnoise>countdet){
		return 0;	
	}else{ notnoise=0;}
	
// Step 3: Rpeaks detection, the local maxima and minima
	correct=rpeak_detection(fp,out);
	if (correct==1){
		return 1;		
		
	}else{
		
		if(filled_buffer>0){ 
			filled_buffer=0;	
			//dbg_clear(DBG_USR1, "Rpeak not detected\n"); 
			return 10; //Too much time without Rpeak detection
		}	
}
	return 0;
	
	
}

//****************************************************************************************************************************************
int8_t ecg_detection_rwave(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3]){  	
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)	
	// Step 4: Rwave detection		
      	correct=rwave(fp,out);	
      	if (correct==1) {    
        	return 1;}	
        else{
	      //  dbg_clear(DBG_USR1, "\%d --> MMF:  \%d \%d Rwave not detected  %d\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp),out[0]);
		}
	return 0;
}
//****************************************************************************************************************************************
int8_t ecg_detection_qwave(int8_t fp[BUFLNZIP],uint8_t detection[12]){     
	// Step 5: Qwave detection
	notnoise=detec[2];//out[3]; 
	combine[3]=qwave(fp,out);
	return 1;
}

//****************************************************************************************************************************************
int8_t ecg_detection_swave(int8_t fp[BUFLNZIP],uint8_t detection[12]){       
	// Step 6: Swave detection
	combine[2]= swave(fp,out);	
	return 1;
}
//****************************************************************************************************************************************
int8_t ecg_detection_pwave(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3]){  
	// Step 7: onset and offset, Pwave and Twave detection
	combine[1]=pwave(fp,out);
	if(combine[1]==1){
		return 1;
	}else {
		//dbg_clear(DBG_USR1, "****888888888888888888888888888888888888888888**********  \%d \%d \%d %d %d  ***\n",(out[0]),(out[2]),(out[3]),(out[4]),(out[5]) );	
		return 8; //Pwave not detected
	}
	return 0;
}
//****************************************************************************************************************************************
int8_t ecg_detection_twave(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3]){  	
		// Step 7: onset and offset, Pwave and Twave detection
		combine[0]=twave(fp,out);
		if(combine[0]==1){
			out[9]=(out[9]);	    detection[10]=(out[9]+BUFLN)%(BUFLN);
			amplitudes[2]=out[10];			
			out[11]= (out[11]); 	detection[11]=(out[11]+BUFLN)%(BUFLN);	
			return 1;		
		}else {
			out[9]=-1;out[10]= -1;out[11]= -1; 
			if(combine[1]!=1 || combine[0]==2 || (maxMin[(countdet+1+POINTS)%POINTS]+(BUFLN*nfilled[(countdet+1+POINTS)%POINTS])/*(from+10+BUFLN)%BUFLN*/) == out[6]){ 
				//dbg_clear(DBG_USR1, "****9999999999999999999999999999999 ************  \%d \%d \%d %d %d  %d %d ***\n",out[0],out[2],out[3],out[4],out[5],out[6],out[8] );
				return 9; //Twave not detected
			}
			else {
				notnoise=countdet+1;
			}		
		}
		return 0;
}
//****************************************************************************************************************************************
int8_t ecg_detection_valid(int8_t fp[BUFLNZIP],uint8_t detection[12],int16_t amplitudes[3])
{  
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)	
	out[0]=(out[0]);
	out[1]=descomprime(fp,(out[0]+BUFLN)%(BUFLN),0);    amplitudes[0]=out[1];
	out[2]=(out[2]); 	detection[4]=(out[2]+BUFLN)%(BUFLN);
	out[3]=(out[3]);	detection[5]=(out[3]+BUFLN)%(BUFLN);
						
	if(combine[0]==1){
		out[9]=(out[9]);		detection[10]=(out[9]+BUFLN)%(BUFLN);
		amplitudes[2]=out[10];			
		out[11]= (out[11]);		detection[11]=(out[11]+BUFLN)%(BUFLN);
	}else {
		out[9]=-1;out[10]= -1;out[11]= -1; 
		if(combine[0]==2 || (countdet+1) >= POINTS){ correct=9;	}
	}
	if(combine[1]==1){
		out[6]= (out[6]);		detection[8]=(out[6]+BUFLN)%(BUFLN);
		amplitudes[1]=out[7];					
		out[8]=(out[8]);		detection[9]=(out[8]+BUFLN)%(BUFLN);
		
	}else {	out[6]= -1;out[7]=-1;out[8]=-1; correct=8;}
				
	if(combine[0]==1 && combine[1]==1){
		correct=0;
		filled_buffer=0;
	}
		if(combine[3]==1){
			out[4]=(out[4]);//+BUFLN)%(BUFLN); 
			detection[6]=(out[4]+BUFLN)%(BUFLN);
 
		}else out[4]=-1;   

	if(combine[2]==1){
		out[5]=(out[5]);//+BUFLN)%(BUFLN);
		detection[7]=(out[5]+BUFLN)%(BUFLN);
			
	} else out[5]=-1;  
			   
			      
	//dbg_clear(DBG_USR1, "\%d --> MMF:  \%d \%d \%d %d %d %d %d \%d \%d %d \%d \%d  %d\n",(from)%BUFLN,descomprime(fp,(from+BUFLN)%(BUFLN),0), mmt((from+BUFLN)%(BUFLN),fp),out[0],out[2],out[3],out[4],out[5],out[6],out[7],out[8], out[9], out[10], out[11]);	
	return correct;

				
}




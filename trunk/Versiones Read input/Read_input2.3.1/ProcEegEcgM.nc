//make ucm_eeg_sta install.1
// VERSION 2.3.1
// Envio - Recepcion: El paquete contiene 17 resultados obtenidos y la frecuencia cardiaca de esos 17 rpeaks
/***********************************************************************************************************/


module ProcEegEcgM {
  uses {
    interface ReadEegEcg;
	  //interface StdControl as CommControl;
		interface SendMsg as SendData;
	}
}

implementation {
	#include "ecg_detection.c"
	#include "input.h"
	uint8_t numData=0, cycle=0;
	//uint8_t count=0;
	
	int8_t buffer[BUFLNZIP];
	uint8_t detection[12];
	int16_t amplitudes[3];
	int16_t first_detection[4];
	int16_t data[8];
	int8_t countT=0;
	static uint16_t get_sample_from_core();
	static uint16_t heart_freq_calc();
	static result_t send_result_to_host();
  
  enum{
    SAMPLES = 2,
    PERIODS =5 //se pierden 5 de cada +- 40 (12%)    //Muestras mal 58 de 410   (15%)
    //PERIODS =6
  };
  
  uint16_t dataEegEcg[SAMPLES*PERIODS];
  uint16_t indData=0;
 // uint8_t seqNo=0;
  uint8_t whichPacket=0;

	TOS_Msg datapck; //paquetes a enviar
	TOS_Msg datapck2;
	



  task void processData(){
    
    
	static uint8_t i=0, j=0;
	//static uint16_t data;
	static int16_t heart_freq;
	static int8_t result;
	//static uint8_t c=0;
	
    //el sensor muestrea a una frecuencia de 1000hz, entonces coge un dato de cada 5 para muestrear a 200hz
    //data = dataEegEcg[1]; //es el dato q le viene del sensor, tiene 10 posiciones y viene 5 datos del primer canal y del segundo alternados
    
    //detectamos qrs
    //TOSH_TOGGLE_GREEN_LED_PIN(); //TOSH_SET_MISC1_PIN();
//TOSH_TOGGLE_GREEN_LED_PIN();
	//TOSH_SET_MISC1_PIN();
		cycle++;
	switch(cycle){
	
		case 1: data[j++] = get_sample_from_core();
				for(i=0;i<j;i++){
						 result = ecg_detection_datain(data[i],buffer);
				}
				j=0; 
				if(result==0) cycle--; break;
		case 2: data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_rpeak(buffer,detection);if(result==10) cycle=7;if(result==0) cycle=0;} break;
		case 3:	data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_rwave(buffer); if(result!=1) cycle=7;} break;
		case 4: data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_qwave(buffer); /*if(result!=1) cycle=7;*/} break;
		case 5: data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_swave(buffer); /*if(result!=1) cycle=7;*/} break;
		case 6: data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_pwave(buffer); /*if(result!=1) cycle=7;*/} break;
		case 7: data[j++] = get_sample_from_core(); result =  ecg_detection_twave(buffer);
					while(result==9 && countT<50){
						countT+=j;
						data[j++] = get_sample_from_core();
						for(i=0;i<j;i++){result = ecg_detection_datain(data[i],buffer);}
						j=0; 
						result =  ecg_detection_twave(buffer);
					}

				countT =0;
		//TOSH_TOGGLE_GREEN_LED_PIN();		
				 break;
		case 8:data[j++] = get_sample_from_core(); 
			if(result<10 && result!=0) {
				result=ecg_detection_valid(buffer,detection,amplitudes);
			
			}
			if(numData==0){
				for(i=0;i<4;i++){ 
					first_detection[i] = detection[i];
				}	
			}
			
			if(whichPacket==0){
				datapck.data[numData++] = result;	
				if (numData>16){  //se envia el paquete
					datapck.data[numData++] =(uint8_t)heart_freq_calc();	
					send_result_to_host();
					numData=0;
				}
			}else{
				datapck2.data[numData++] = result;
				if (numData>16){  //se envia el paquete
				
					datapck2.data[numData++] = (uint8_t)heart_freq_calc();
					send_result_to_host();
					numData=0;
				}
			}
				
				
			
	   
			result=0;
			cycle=0;
			break;
		default: result = 0;cycle=0;
	
	
	}

    //result = ecg_detection(data,buffer,detection,amplitudes); //c++;
    
   //TOSH_CLR_MISC1_PIN();
    

		//if(c==1){TOSH_CLR_MISC1_PIN();c=0;}

    
  }

  async event void ReadEegEcg.fired(uint16_t *pData){  //se llama cada vez q se leen dos datos (dos canales)
    uint8_t i;
    
    for(i=0;i<SAMPLES;i++)
      dataEegEcg[indData++]=pData[i]; //pdata es un array de todos los canales que se esta leyendo
    
    if(indData ==SAMPLES*PERIODS){
      post processData();
      indData=0;
    }
    
  }
  
  static uint16_t get_sample_from_core()
	{
		uint16_t input_d;
		static unsigned int counter=0;
		
		input_d = (uint16_t)testinput[counter++];
		if(counter==495){//771){//163){//2900){//241){
			counter=0;
		}
		
		return(input_d);
	}
	
	static uint16_t heart_freq_calc()
	{
		uint16_t hfreq;
		int8_t i;
		for(i=0;i<4;i++){ 
			first_detection[i] = detection[i] - first_detection[i];
		}
		while(first_detection[3]<0){
			first_detection[3]+=200;
			first_detection[2]--;
		}
		while(first_detection[2]<0){
			first_detection[2]+=60;
			first_detection[1]--;
		}
		while(first_detection[1]<0){
			first_detection[1]+=60;
			first_detection[0]--;
		}
		hfreq= (16*(60000 / (first_detection[1]*6000+first_detection[2]*100+(first_detection[3]>>1))))/10;
		return hfreq;
			         
		
	}
	
	
  
  event result_t SendData.sendDone(TOS_MsgPtr pMsg, result_t success) {
   

    return SUCCESS;
	}
	
	
	
	static result_t send_result_to_host()
	{
		// Send out result
		
	TOSH_TOGGLE_GREEN_LED_PIN();
		if(whichPacket==0){
			//no encuentra el campo s_addr
			datapck.s_addr = TOS_LOCAL_ADDRESS;
			whichPacket = 1;
			return (call SendData.send(0, sizeof(AMdata), &datapck));
		}
		else{
			datapck2.s_addr = TOS_LOCAL_ADDRESS;
			whichPacket = 0;
			return (call SendData.send(0, sizeof(AMdata), &datapck2));
		}
	}

}
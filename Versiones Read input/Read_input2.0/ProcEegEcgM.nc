//make ucm_eeg_sta install.1
// VERSION 2.0
// Envio - Recepcion: Se envian detecciones solo cuando hay error y este se ha repetido 2 veces seguidas               
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
	int16_t data[8];
	int8_t countT=0;
	uint8_t results[]={0};
	static uint16_t get_sample_from_core();
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
	uint8_t ldata, mdata;
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
		case 2: data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_rpeak(buffer,detection);if(result!=1) cycle=7;} break;
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
			
			
			
			if((result==results[0])&& (result>=1)){
	     		
			  	//ldata = (uint8_t) (out[i] & 0x00ff);  // lower 8bit
			  	//ldata=(uint8_t) (result & 0x00ff);
				//mdata = (uint8_t) ((out[i] & 0xff00) >> 8);  // higher 8bit
				//mdata=(uint8_t) ((result& 0xff00) >> 8);
				if(whichPacket==0){
					datapck.data[numData++] = result;
					for(i=1;i<12;i++){
						datapck.data[numData++] = detection[i];
						}
					
					for(i=0;i<3;i++){
						ldata=(uint8_t) (amplitudes[i] & 0x00ff);
						mdata=(uint8_t) ((amplitudes[i] & 0xff00) >> 8);
						datapck.data[numData++] = mdata;
						datapck.data[numData++] = ldata;
					}
				}
				else{
						datapck2.data[numData++] = result;
					for(i=1;i<12;i++){
						datapck2.data[numData++] = detection[i];
						}
					
					for(i=0;i<3;i++){
						ldata=(uint8_t) (amplitudes[i] & 0x00ff);
						mdata=(uint8_t) ((amplitudes[i] & 0xff00) >> 8);
						datapck2.data[numData++] = mdata;
						datapck2.data[numData++] = ldata;
					}
				}
				
				
				if (numData>1){  //se envia el paquete
					send_result_to_host();
					numData=0;
				}
	   
			} 
			results[0]=result;
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

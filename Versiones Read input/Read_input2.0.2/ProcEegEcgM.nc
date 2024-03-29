//make ucm_eeg_sta install.1
// VERSION 2.0.2
// Envio - Recepcion: Se envian detecciones y estas se ha repetido VARIAS veces SEGUIDAS
//(si no se ha enviado ya)             
// Registro de Historia de con "history" valores
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
	int8_t buffer[BUFLNZIP];
	uint8_t detection[12];
	int16_t amplitudes[3];
	int16_t data[8];
	int8_t countT=0;
	uint8_t results[HISTORY];
	int8_t lastSendResult=0;
	static uint16_t get_sample_from_core();
	static result_t send_result_to_host();
  
  enum{
    SAMPLES = 2,
    PERIODS =5 //se pierden 5 de cada +- 40 (12%)    //Muestras mal 58 de 410   (15%)
    
  };
  
  uint16_t dataEegEcg[SAMPLES*PERIODS];
  uint16_t indData=0;
  uint8_t whichPacket=0;

	TOS_Msg datapck; //paquetes a enviar
	TOS_Msg datapck2;
	



  task void processData(){
    
    
	static int8_t i=0, j=0;
	uint8_t ldata, mdata , numRepeatedResult=0;//Numero de veces repetidas del result en la Historia
	static int8_t result;

		cycle++;
	switch(cycle){
	
		case 1: data[j++] = get_sample_from_core();
				for(i=0;i<j;i++){
						 result = ecg_detection_datain(data[i],buffer);
				}
				j=0; 
				if(result==0) cycle--; break;
		case 2: data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_rpeak(buffer,detection);if(result==10) cycle=7;if(result==0) cycle=0;} break;
		case 3:	data[j++] = get_sample_from_core();if(result==1){result =  ecg_detection_rwave(buffer); if(result!=1) cycle=0;} break;
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
	
				 break;
		case 8:data[j++] = get_sample_from_core(); 
			if(result<10 && result!=0) {
				result=ecg_detection_valid(buffer,detection,amplitudes);
			
			}
			
			//Numero de veces repetidas SEGUIDAS Y ULTIMAS que ya ha dado ese resultado
			i=HISTORY-1;
			numRepeatedResult=0;
			while(result==results[i]&& i>=0){
				numRepeatedResult++;
				i--;
				}
			//Si ya ha pasado mas de 2 veces, es o NO un error, y no se envio la ultima vez --> enviamos el error
			if((numRepeatedResult>=1) /*&& (result>=1)*/&& result!=lastSendResult){
	  			lastSendResult=result;
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
			
			//Guardamos la nueva HISTORIA
			for(i=0;i<HISTORY-1;i++){
				results[i]=results[i+1];
				}
				results[HISTORY-1]=result;
				
			result=0;
			cycle=0;
			break;
		default: result = 0;cycle=0;
	
	
	}

    
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

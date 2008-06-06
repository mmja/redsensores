//make ucm_eeg_sta install.1
/**
 *
 * @author Joaquin Recas
 */


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
	uint8_t numData=0;
	//uint8_t count=0;
	
	int16_t buffer[BUFLN];//,*buffer=&_buffer;
	int16_t out[12];//,*out=&_out;
	
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
    
    
	uint8_t i;
	uint16_t data;
	uint8_t ldata, mdata;
	int8_t result;
	static uint8_t c=0;
	//if(c==0){TOSH_SET_MISC1_PIN();c=1;}
	//else {TOSH_CLR_MISC1_PIN();c=0;}
    //el sensor muestrea a una frecuencia de 1000hz, entonces coge un dato de cada 5 para muestrear a 200hz
    //data = dataEegEcg[1]; //es el dato q le viene del sensor, tiene 10 posiciones y viene 5 datos del primer canal y del segundo alternados
    data = get_sample_from_core();
    //detectamos qrs
    TOSH_TOGGLE_GREEN_LED_PIN(); //TOSH_SET_MISC1_PIN();
//TOSH_TOGGLE_GREEN_LED_PIN();
    result = ecg_detection(data,buffer,out); //c++;
    
    if(result==1){
	     
			//par obtener el valor de la señal en que se ha detectado se usa getsample(result,buffer), pero se supone que esto no es importante
			//solo interesa el momento en que se detecta el qrs
		  // dbg(DBG_USR1, " \%d  %d  [ %d , %d ]  %d  %d  [ \%d , %d ,\%d ]  [ \%d ,%d,  \%d ] \n",out[0],out[1],out[2],out[3],out[4],out[5],out[6],out[7],out[8],out[9], out[10], out[11]);
			for(i=0;i<12;i++){
			  	ldata = (uint8_t) (out[i] & 0x00ff);  // lower 8bit
				mdata = (uint8_t) ((out[i] & 0xff00) >> 8);  // higher 8bit
				if(whichPacket==0){
					datapck.data[2*numData] = mdata;
					datapck.data[2*numData+1] = ldata;
				}
				else{
					datapck2.data[2*numData] = mdata;
					datapck2.data[2*numData+1] = ldata;
				}
				numData = numData+1;
				
				if (numData==9){  //se envia el paquete
					send_result_to_host();
					numData=0;
				}
	  }	  
	} 
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
		if(counter==203){//771){//163){//2900){//241){
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

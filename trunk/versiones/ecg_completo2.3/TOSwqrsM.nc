// VERSION 2.3
// Envio - Recepcion: El paquete contiene solo el error detectado y el instante de tiempo del rpeak asociado
// 					  Envia 4 rpeaks por cada paquete (tambi�n envia cuando es correcto)         
/***********************************************************************************************************/


includes TOSwqrs;
includes IntMsg;

module TOSwqrsM {
	provides {
		interface StdControl;
	}
	uses {
		interface Timer;//FRAN
		interface Leds;
		//interface IntOutput;//FRAN
		interface StdControl as CommControl;
		interface SendMsg as SendData;
		interface ReceiveMsg as ReceiveDataMsg;		
    	//interface BareSendMsg as UARTSend;//FRAN
	}
}

implementation {
	
	#include "types.h"
	
	//#include "wqrs_aux.c"
	#include "wqrs.c"
	
	#include "input.h"
	
	static sample_t get_sample_from_core();
	static result_t send_result_to_host();
	uint8_t whichPacket=0;

	TOS_Msg datapck; //paquetes a enviar
	TOS_Msg datapck2;
	
	//int8_t _buffer,*buffer=&_buffer;
	int8_t buffer[BUFLNZIP];
	uint8_t detection[12];
	int16_t amplitudes[3];
	int16_t data[8];
	uint8_t numData=0, cycle=0;
	int8_t countT=0;

	command result_t StdControl.init() {
		//Inicializamos el nodo
		call Leds.init();
		call CommControl.init();
		return SUCCESS;
	}
	
	command result_t StdControl.start() {
		//Ponemos el modo a funcionar
		call CommControl.start();
		if(TOS_LOCAL_ADDRESS!=0){
			//Esto crea un timer que se dispara cada 100ms
			// dbg(DBG_USR1, " Rpeak   Amplitud    Rwave       Qwave   Swave      Pwave                  Twave \n");
			call Timer.start(TIMER_REPEAT, 5);
		}
		return SUCCESS;
	}
	
	command result_t StdControl.stop() {
		call CommControl.stop();
		if(TOS_LOCAL_ADDRESS!=0){
			call Timer.stop();
		}
		
		return SUCCESS;
	}
	
	event result_t Timer.fired(){
		
    
	static uint8_t i=0, j=0;
	//static uint16_t data;
	
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
			
				if(whichPacket==0){
					datapck.data[numData++] = result;
					for(i=1;i<4;i++){ //solo envio min:seg:mlseg
						datapck.data[numData++] = detection[i];
					}
					
					
				}
				else{
						datapck2.data[numData++] = result;
					for(i=1;i<4;i++){
						datapck2.data[numData++] = detection[i];
						}
				}
				
				
				if (numData>15){  //se envia el paquete
					send_result_to_host();
					numData=0;
				}
	   
			result=0;
			cycle=0;
			break;
		default: result = 0;cycle=0;
	
	
	}
		return SUCCESS;
	}
	
	event result_t SendData.sendDone(TOS_MsgPtr pMsg, result_t success) {
		return SUCCESS;
	}
	
	event TOS_MsgPtr ReceiveDataMsg.receive(TOS_MsgPtr m) {
		
		datapck = *m;
  	
	  	datapck.addr = 0xAA00;
	  	//datapck.s_addr &= 0xF;
	  	//datapck.s_addr = (datapck.s_addr + (0xAA<<8));
	  	datapck.type = 0x0C;
	  	datapck.group = 0x35;
	  	datapck.length = 18;	 
	  	//datapck.seqNo = 0x00;
	  	datapck.crc = 1;
	  	
		//datapck.seqNo = datapck.seqNo + 1;
		
		//dbg(DBG_USR3,"Paquete recibido\n");
		//call Leds.redToggle();
      	//call UARTSend.send(&datapck);//FRAN
		return m;
	}
	
	static sample_t get_sample_from_core()
	{
		sample_t input_d;
		static unsigned int counter=0;
		
		input_d = (sample_t)testinput[counter++];
		if(counter==495){//771){//163){//2900){//241){
			counter=0;
			//call Timer.stop();
		}
		
		return(input_d);
	}
	
	static result_t send_result_to_host()
	{
		
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

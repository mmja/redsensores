
// VERSION 1.9.2
// Envio - Recepcion: Se envian detecciones solo cuando hay error.            
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
		//Cada vez que se dispara el timer entramos por este m�todo, aqu� tenemos que leer la muestra que acabamos de leer y llamar al algoritmo
		//wqrs con dicha muestra, tras la evaluaci�n de la muestra por el algoritmo, enviaremos un mensaje a la estaci�n base o no haremos nada
		//y saldremos de este m�todo.
		
		//static sample_t data;
		static int8_t result;
		static uint8_t i=0, j=0;
		uint8_t ldata, mdata;
		//Declaraci�n de las dem�s variables que necesitamos
		if(TOS_LOCAL_ADDRESS==1){ // IF para 5 nodos
		//dbg(DBG_USR1, "Timer disparado\n");
		
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
		case 7: data[j++] = get_sample_from_core();	result =  ecg_detection_twave(buffer);
					while(result==9 && countT<50){
						countT+=j;
						data[j++] = get_sample_from_core();
						for(i=0;i<j;i++){result = ecg_detection_datain(data[i],buffer);}
						j=0; 
						result =  ecg_detection_twave(buffer);
					}
				countT=0;
				
				 break;
		case 8:data[j++] = get_sample_from_core(); 
			if(result<10 && result!=0) {
				result=ecg_detection_valid(buffer,detection,amplitudes);
			
			}
			if(result>=1){
	     		
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

			result=0;
			cycle=0;
			break;
		default: result = 0;cycle=0;
	
	}
		//Ahora evaluamos el resultado y en funci�n de lo que hayamos obtenido mandaremos un paquete, o no haremos nada, etc.
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

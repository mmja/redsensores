
// VERSION 1.9.0
// Envio - Recepcion: Se envian TODOS LOS DATOS DE LA SEÑAL.  SIN ANALISIS NI DETECCIONES.          
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
	//int8_t buffer[BUFLNZIP];
	//uint8_t detection[12];
	//int16_t amplitudes[3];
	int16_t data[8];
	uint8_t numData=0;//, cycle=0;
	//int8_t countT=0;

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
		
		get_sample_from_core();
		//Ahora evaluamos el resultado y en función de lo que hayamos obtenido mandaremos un paquete, o no haremos nada, etc.
		
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
		uint8_t ldata, mdata;
		
		input_d = (sample_t)testinput[counter++];
		if(counter==495){
			counter=0;
			//call Timer.stop();
		}
		/*
		if(whichPacket==0){
						ldata=(uint8_t) (input_d & 0x00ff);
						mdata=(uint8_t) ((input_d & 0xff00) >> 8);
						datapck.data[numData++] = mdata;
						datapck.data[numData++] = ldata;
				}
				else{
						ldata=(uint8_t) (input_d & 0x00ff);
						mdata=(uint8_t) ((input_d & 0xff00) >> 8);
						datapck2.data[numData++] = mdata;
						datapck2.data[numData++] = ldata;
					
				}
				
				
				if (numData>1){  //se envia el paquete
					send_result_to_host();
					numData=0;
				}
	   
		
		
		*/
		
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

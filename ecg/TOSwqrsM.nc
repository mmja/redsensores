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
	static result_t send_result_to_host(sample_t sample,esint32 rdet,sample_t fval);
	
	TOS_Msg datapck;
	
	sample_t _buffer,*buffer=&_buffer;
	int16_t c=0;
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
			call Timer.start(TIMER_REPEAT, 100);
		}
		return SUCCESS;
	}
	
	command result_t StdControl.stop() {
		call CommControl.stop();
		if(TOS_LOCAL_ADDRESS!=0){
			call Timer.stop();
		}
		freeBuffers();
		return SUCCESS;
	}
	
	event result_t Timer.fired(){
		//Cada vez que se dispara el timer entramos por este método, aquí tenemos que leer la muestra que acabamos de leer y llamar al algoritmo
		//wqrs con dicha muestra, tras la evaluación de la muestra por el algoritmo, enviaremos un mensaje a la estación base o no haremos nada
		//y saldremos de este método.
		
		sample_t sample;
		int32_t result;
		
		//Declaración de las demás variables que necesitamos
		
		//dbg(DBG_USR1, "Timer disparado\n");
		
		sample = get_sample_from_core();//Con esta llamada, tenemos en la variable "sample" la muestra que acabamos de leer
		
		//Ahora tenemos que llamar al algoritmo con la muestra que acabamos de leer, el resultado del procesamiento de la muestra
		//se almacena en la variable "resultado":
		
		//if(c<256){
			result = wqrs(sample,buffer); //c++;
		//}
		if(result!=0){
			//result lleva el instante de tiempo en que se detecta el qrs y es lo que se tiene que enviar
			//par obtener el valor de la señal en que se ha detectado se usa getsample(result,buffer), pero se supone que esto no es importante
			//solo interesa el momento en que se detecta el qrs
		   //dbg(DBG_USR1, "QRS detected:\%d  value: \%d\n",result,getsample(result,buffer));
		}
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
		
		input_d = (sample_t)testinput[counter++];
		if(counter==163){
			counter=0;
		}
		
		return(input_d);
	}
	
	static result_t send_result_to_host(sample_t sample,esint32 rdet,sample_t fval)
	{
		// Send out result
		//datapck.s_addr = TOS_LOCAL_ADDRESS;
		
		return (call SendData.send(0, sizeof(AMdata), &datapck));
	}
	
}

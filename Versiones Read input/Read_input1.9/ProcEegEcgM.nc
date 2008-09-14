//make ucm_eeg_sta install.1



module ProcEegEcgM {
  uses {
    interface ReadEegEcg;
		interface SendMsg as SendData;
	}
}

implementation {
	#include "ecg_detection.c"
	#include "input.h"
	uint8_t numData=0, cycle=0;
	//uint8_t count=0;
	
	int8_t buffer[BUFLNZIP]; //buffer where we save a piece of the signal
	uint8_t detection[12]; //buffer where we save the current detection: result, rpeak hours, minutes, seconds, positions, 
							// positions respect rpeak of rwave (onset, offset), qwave, swave, pwave (on, off), twave (on, off) 
	int16_t amplitudes[3]; //buffer where we save the amplitudes of rpeak, pwave and twave
	int16_t data[8]; //buffer where we save the last 8 data received while we analyze the main buffer
	int8_t countT=0;
	static uint16_t get_sample_from_core();
	static result_t send_result_to_host();
  
  enum{
    SAMPLES = 2,
    PERIODS =5 

  };
  
  uint16_t dataEegEcg[SAMPLES*PERIODS];
  uint16_t indData=0;
  uint8_t whichPacket=0;

	TOS_Msg datapck; //two packet to send, alternated
	TOS_Msg datapck2;
	



  task void processData(){
    
    
	static uint8_t i=0, j=0;
	uint8_t ldata, mdata;
	static int8_t result;
	

    //data = dataEegEcg[1]; //this is the data that we take from the sensor
    						//dataEegEcg has 10 positions, 5 from each channel, alternated, we dont use it yet
    						
    

		cycle++;
	switch(cycle){
	
		case 1: data[j++] = get_sample_from_core(); //here, we take a data from the sample signal
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
					//we searh Twave for 0.25s, if we dont find it, error 9 occurs
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
			//validating the detection
			if(result<10 && result!=0) {
				result=ecg_detection_valid(buffer,detection,amplitudes);
			
			}
			 //we send the detecction to the base station   
				if(whichPacket==0){
					datapck.data[numData++] = result;
					for(i=1;i<12;i++){
						datapck.data[numData++] = detection[i];
						}
					//there is no enough space to send everything in the packet (18 bytes)
					//we dont send the amplitudes, but it is posible in that way
					/*for(i=0;i<3;i++){
						ldata=(uint8_t) (amplitudes[i] & 0x00ff);
						mdata=(uint8_t) ((amplitudes[i] & 0xff00) >> 8);
						datapck.data[numData++] = mdata;
						datapck.data[numData++] = ldata;
					}*/
				}
				else{
					datapck2.data[numData++] = result;
					for(i=1;i<12;i++){
						datapck2.data[numData++] = detection[i];
						}				
					/*for(i=0;i<3;i++){
						ldata=(uint8_t) (amplitudes[i] & 0x00ff);
						mdata=(uint8_t) ((amplitudes[i] & 0xff00) >> 8);
						datapck2.data[numData++] = mdata;
						datapck2.data[numData++] = ldata;
					}*/
				}
				if (numData>1){  //se envia el paquete
					send_result_to_host();
					numData=0;
				} 
			result=0;
			cycle=0;
			break;
		default: result = 0;cycle=0;
	}
  }

  async event void ReadEegEcg.fired(uint16_t *pData){  //se llama cada vez q se leen dos datos (dos canales)
    uint8_t i;
   //Sensor samples at 1000Hz, so we just take 1 data each 5 datas, to sample at 200Hz
    for(i=0;i<SAMPLES;i++)
      dataEegEcg[indData++]=pData[i]; //pdata is the array with all the channels thar are readed (2 channels)
    
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
		if(counter==495){
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

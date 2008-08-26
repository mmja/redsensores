includes TOSwqrs;
includes NetworkGenericComm;

configuration TOSwqrs {
}
implementation {
	components 	Main,
				TOSwqrsM,
				LedsC,
				SingleTimer,
				//IntToUart,//FRAN
				//UARTFramedPacket as UARTPacket,//FRAN
				NetworkGenericComm;
				
	Main.StdControl -> SingleTimer.StdControl;
	Main.StdControl -> TOSwqrsM.StdControl;
	//Main.StdControl -> IntToUart;//FRAN
	
	TOSwqrsM.Timer -> SingleTimer.Timer;
	TOSwqrsM.Leds -> LedsC;
	
	TOSwqrsM.CommControl -> NetworkGenericComm;
	TOSwqrsM.SendData -> NetworkGenericComm.SendMsg[AM_DATA];
	TOSwqrsM.ReceiveDataMsg -> NetworkGenericComm.ReceiveMsg[AM_DATA];
	
	//RpeakM.IntOutput -> IntToUart.IntOutput;//FRAN
	
	//RpeakM.UARTSend -> UARTPacket.Send;//FRAN

}

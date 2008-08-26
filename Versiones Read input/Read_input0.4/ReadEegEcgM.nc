
/**
 *
 * @author Joaquin Recas
 */


module ReadEegEcgM {
  provides {
    interface StdControl;
    interface ReadEegEcg;
  }
  uses {
    //Captura de señal Enable
    interface MSP430Interrupt    as  Enable;
  }
}

implementation {

  MSP430REG_NORACE(ADC12CTL0);
  MSP430REG_NORACE(ADC12CTL1);
  MSP430REG_NORACE(ADC12IFG);
  MSP430REG_NORACE(ADC12IE);
  MSP430REG_NORACE(ADC12IV);
  
  MSP430REG_NORACE(P6OUT);
  MSP430REG_NORACE(P3OUT);


  //volatile uint16_t *pData=(uint16_t *)data;    //Puntero a buffer de datos
  volatile uint16_t sample=0;
  volatile uint16_t sLost=0;
  
  //FRAN:
  const int impchannelno[27] = {25,26,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
  uint16_t i;

  void setGainEeg(uint8_t gain){
	  register unsigned char tmp;	// for glitch-free transition

	  tmp   =  P2OUT;
	  tmp  &= ~(0x07<<UP_A0_EEG_P2);
	  tmp  |=  (gain&0x07)<<UP_A0_EEG_P2;
	  P2OUT =  tmp;
	}

  void setGainEcg(uint8_t gain){
    register unsigned char tmp; // for glitch-free transition

    tmp   =  P1OUT;
    tmp  &= ~(0x07<<UP_A0_ECG_P1);
    tmp  |=  (gain&0x07)<<UP_A0_ECG_P1;
    P1OUT =  tmp;
  }
  
  command result_t StdControl.init() {
	  
	  /** fake impedance measurement
	      don't know exactly WHAT of this is needed, but with it the ECG channel works
	      otherwise it only works after doing an impedance measurement, crap data otherwise
		TO DO: figure out what of this is needed and what not***/
	  
	  ADC12CTL0 = ADC12ON|REFON|REF2_5V;			// ADC12 & reference voltage 2.5V on
	  ADC12CTL1 = 0;		// manual sampling
	  //ADC12CTL0 = ADC12ON+REFON+REF2_5V+SHT0_8+MSC;  // Turn on ADC12 & ref 2.5V, set sampling time
	  //ADC12CTL1 = SHP+CONSEQ_2;             // Use sampling timer, set mode consecutive sampling, single channel
	  ADC12MCTL0 = SREF_1|IMP_OUT_P6;           // ref=VREF+, select channel
	  //ADC12CTL0 |= ENC;                     // Enable conversions
	  
	  P1OUT &= ~(1<<IMP_CS_P1);	// enable MUX output
	  for (i=0; i<27; i++)
	  {
	   	// close mux this electrode, all other electrodes open
		
		P5OUT &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4));
		P5OUT |= (impchannelno[i]&31)<<0;
		P1OUT &= ~(1<<IMP_WR_P1);
		nop();
		P1OUT |= (1<<IMP_WR_P1);		// new address latched in on rising edge of WR
		
		DELAYM(10);
	  }
	  P5OUT &= ~(1<<IMP_STIM_P5);	// low stimulation
	  
	  P5OUT &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4));
	P5OUT |= (31&31)<<0;
	P1OUT &= ~(1<<IMP_WR_P1);
	nop();
	P1OUT |= (1<<IMP_WR_P1);		// new address latched in on rising edge of WR
	  
	  P1OUT |= (1<<IMP_CS_P1);	// disable MUX output
	  
	  ADC12CTL0 &= ~ENC;                  // Clear ENC bit (needed to be able to change other bits)
  	  ADC12CTL0 = 0;					// ADC12 & reference voltages OFF
	  
	  /**** end required code **/

    ADC12CTL0 = REF2_5V|REFON|ADC12ON|ADC12OVIE;                // ADC12 & reference voltage 2.5V on, deshabilitamos la conversión (para modificar registros), Interrupciones MEMOV

    ADC12CTL1  = SHS_1|ADC12DIV_0|ADC12SSEL_0|CONSEQ_1;          // Sequence Of Channels, ADC12OSC (5Mhz), CLKDiv=0, Timer_A.OUT1 sampling en flanco de bajada
    ADC12MCTL0 =SREF_1|INCH_0;                                   // Canal normal, referencia interna Vr+=Vref+, Vr-=AVss, canal AD0
    ADC12MCTL1 =SREF_1|INCH_0|EOS;                               // Último canal -> End Of Sequence
    //ADC12IE = 0x3;                                               // Interrupción en la lectura del primer y segundo canal
    ADC12IE = 0x2;                                               //Interrupción en la lectura del segundo canal

    return SUCCESS;
  }

  command result_t StdControl.start() {

    //Ganancia por defecto 5700
    setGainEeg(5);
    //Ganancia por defecto 570
    setGainEcg(5);

    DELAYM(5);
    TOSH_CLR_STARTUP_ASIC_PIN();    // get chip out of startup state
    DELAYM(5);
    TOSH_SET_UPRESET_ASIC_PIN();    // bring EEG chip out of reset

    //Evento de la señal Enable para flanco de subida
    call Enable.edge(TRUE);
    //Activamos el evento de la señal Enable
    call Enable.enable();
    
    TOSH_CLR_GREEN_LED_PIN();
    TOSH_CLR_MISC1_PIN();
    TOSH_CLR_MISC2_PIN();
    TOSH_CLR_MISC3_PIN();
    TOSH_CLR_MISC4_PIN();
    
    //Deshabilitamos los modos de bajo consumo de energía
    //LPMode_disable();

    return SUCCESS;
  }

  command result_t StdControl.stop() {
    ADC12CTL0 &= ~ENC;                  // Clear ENC bit (needed to be able to change other bits)
    ADC12CTL0 = 0;                      // ADC12 & reference voltages OFF
    ADC12IE = 0x00;
    return SUCCESS;
  }

  //Vector de interrupción del ADC12
  TOSH_SIGNAL(ADC_VECTOR) {
    uint16_t  iv=ADC12IV;
    uint16_t pData[2];

    //FRANTOSH_SET_MISC2_PIN();

    switch(iv){
      
      //ADC12MEM overflow!!!!
      case 0x2:
        //FRANTOSH_SET_MISC4_PIN();
        break;

      //ADC12MEM1 interrupt flag
      case 0x8:
        //TOSH_TOGGLE_MISC2_PIN();
        //TOSH_SET_MISC1_PIN(); TOSH_CLR_MISC1_PIN();
        pData[0]=ADC12MEM0;
        pData[1]=ADC12MEM1;
        
        ADC12CTL0 &= ~ENC;//FRAN
        
        //dataReady=1;

        //pData[0]=sample;
        //pData[1]=sLost;
        
        signal ReadEegEcg.fired(pData);
        
        break;

     //Unspected!!!!
      default:
        //FRANTOSH_SET_MISC4_PIN();
      }

    //FRANTOSH_CLR_MISC2_PIN();
  }
  async event void Enable.fired(){
    //FRANTOSH_SET_MISC2_PIN();

    sample++;

    //Not sync!!!
    if((call Enable.getValue())!=1){
      sLost++;
      //FRANTOSH_SET_MISC4_PIN();
      //FRANTOSH_CLR_MISC4_PIN();
    }
      

    //Activamos la conversión AD
    ADC12CTL0 |= ENC;
    //Borramos el evento
    call Enable.clear();

    //FRANTOSH_CLR_MISC2_PIN();
    
  }
  
}

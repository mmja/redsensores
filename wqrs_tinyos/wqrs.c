/*************************************************************************************
*******************comienza el programa**********************************************
*************************************************************************************/

//#define BUFLN  16384	/* must be a power of 2, see ltsamp() */
#define EYE_CLS 0.25    /* eye-closing period is set to 0.25 sec (250 ms) */ 
//#define LPERIOD 1000	/* learning period is the first LPERIOD samples */
#define MaxQRSw 0.13    /* maximum QRS width (130ms) */                        
#define NDP	 2.5    /* adjust threshold if no QRS found in NDP seconds */
#define TmDEF	 100	/* minimum threshold value (default) */
#define sps 150.		/* sampling frequency, in Hz (SR) */
#define  PWFreq 100  //opcion -p

//char *pname;		/* the name by which this program was invoked */
int32_t lfsc;		/* length function scale constant */
int8_t *ebuf;
//int8_t nsig;		/* number of input signals */
int8_t LPn, LP2n;          /* filter parameters (dependent on sampling rate) */
int8_t LTwindow;           /* LT window size */
//int8_t sig = 0;	        /* signal number of signal to be analyzed */
int8_t Tm = TmDEF;		/* minimum threshold value */
int16_t *lbuf = NULL;
int16_t count;
double Ta, T0;			     /* high and low detection thresholds */
WFDB_Time  t1;	
int8_t EyeClosing;                  /* eye-closing period, related to SR */
int8_t ExpectPeriod;                /* if no QRS is detected over this period,
					the threshold is automatically reduced
					to a minimum value;  the threshold is
					restored upon a detection */		


/* ltsamp() returns a sample of the length transform of the input at time t.
   Since this program analyzes only one signal, ltsamp() does not have an
   input argument for specifying a signal number; rather, it always filters
   and returns samples from the signal designated by the global variable
   'sig'.  The caller must never "rewind" by more than BUFLN samples (the
   length of ltsamp()'s buffers). */

WFDB_Sample ltsamp(WFDB_Time t,int16_t *buffer)
{
    int8_t dy;
    static int8_t Yn, Yn1, Yn2;
    static WFDB_Time tt = (WFDB_Time)-1L;

    if (lbuf == NULL) {
		lbuf = (WFDB_Sample *)malloc((unsigned)BUFLN*sizeof(WFDB_Sample));
		ebuf = (int8_t *)malloc(BUFLN * sizeof(int8_t));
		if (lbuf && ebuf) {
		    for (ebuf[0] = sqrtf(lfsc), tt = 1L; tt < BUFLN; tt++)
				ebuf[tt] = ebuf[0];
		    if (t > BUFLN) tt = (WFDB_Time)(t - BUFLN);
		    else tt = (WFDB_Time)-1L;
		    Yn = Yn1 = Yn2 = 0;
		}
		else {
		    exit(2);
		}
    }
    if (t < tt - BUFLN) {
		exit(2);
    }
    while (t > tt) {
		static int8_t aet = 0, et;
		WFDB_Sample v0, v1, v2;
	
		Yn2 = Yn1;
		Yn1 = Yn;
		if ((v0 = sample(/*sig,*/ tt,buffer)) != WFDB_INVALID_SAMPLE &&
		    (v1 = sample(/*sig,*/ tt-LPn,buffer)) != WFDB_INVALID_SAMPLE &&
		    (v2 = sample(/*sig,*/ tt-LP2n,buffer)) != WFDB_INVALID_SAMPLE)
		    Yn = 2*Yn1 - Yn2 + v0 - 2*v1 + v2;
		dy = (Yn - Yn1) / LP2n;		/* lowpass derivative of input */
		et = ebuf[(++tt)&(BUFLN-1)] = sqrtf(lfsc +dy*dy); /* length transform */
		lbuf[(tt)&(BUFLN-1)] = aet += et - ebuf[(tt-LTwindow)&(BUFLN-1)];
		/* lbuf contains the average of the length-transformed samples over
		   the interval from tt-LTwindow+1 to tt */
    }
    return (lbuf[t&(BUFLN-1)]);
}

int8_t init(int16_t *buffer){
	
	Tm = muvadu(Tm);
    LTwindow = sps * MaxQRSw;     /* length transform window size */
	
	EyeClosing = sps * EYE_CLS;   /* set eye-closing period */
    ExpectPeriod = sps * NDP;	   /* maximum expected RR interval */
	
	lfsc = 1.25*WFDB_DEFGAIN*WFDB_DEFGAIN/sps;	/* length function scale constant */

	LPn = sps/PWFreq;   /* The LP filter will have a notch at the
				    power line (mains) frequency */
    LP2n = 2 * LPn;
	
	/* Average the first 8 seconds of the length-transformed samples
       to determine the initial thresholds Ta and T0. The number of samples
       in the average is limited to half of the ltsamp buffer if the sampling
       frequency exceeds about 2 KHz. */
    //(void)sample(/*sig,*/ 0L,buffer);
	t1 = (int16_t)(8*ifreq + 0.5); 
	for (T0 = 0, t = 0; t < BUFLN /*&& sample_vflag*/; t++)
		T0 += ltsamp(t,buffer);
    T0 /= BUFLN;
    Ta = 3 * T0;
    count=40;
}
int8_t wqrs(int16_t datum, int16_t *buffer,int8_t from)
{ 
	     
    int8_t i, max, min, onset, timer;

    WFDB_Time  t, tpq, tt;
    int8_t to;
    

    // to = strtim("e");//siempre hace else ya que to=0L, va a dar to=nsambles=65000
    to=(from+BUFLN-1)&(BUFLN-1);
    
    /******************************** Main loop *******************************/
    //for (t = 0; t < to || (to == 0L && sample_vflag); t++) {
		static int8_t learning = 1, T1;
	
		if (learning) {
		    if (t > t1) {
				learning = 0;
				T1 = T0;
				t = 0;	/* start over */
	    	}
	    	else  T1 = 2*T0;
		}
	/* Compare a length-transformed sample against T1. */
		if (ltsamp(t,buffer) > T1) {	/* found a possible QRS near t */
		    timer = 0; /* used for counting the time after previous QRS */
		    max = min = ltsamp(t,buffer);
		    for (tt = t+1; tt < t + EyeClosing/2; tt++) //de t+1 a t+18 (no incluido)
				if (ltsamp(tt,buffer) > max) max = ltsamp(tt,buffer);
		    for (tt = t-1; tt > t - EyeClosing/2; tt--) //de t-11 a t-18 (no incluido)
				if (ltsamp(tt,buffer) < min) min = ltsamp(tt,buffer);
		    if (max > min+10) { /* There is a QRS near tt */
			/* Find the QRS onset (PQ junction) */
				onset = max/100 + 2;
				tpq = t - 5;
				for (tt = t; tt > t - EyeClosing/2; tt--) {
				    if (ltsamp(tt,buffer)   - ltsamp(tt-1,buffer) < onset &&
					ltsamp(tt-1,buffer) - ltsamp(tt-2,buffer) < onset &&
					ltsamp(tt-2,buffer) - ltsamp(tt-3,buffer) < onset &&
					ltsamp(tt-3,buffer) - ltsamp(tt-4,buffer) < onset) {
					tpq = tt - LP2n;	/* account for phase shift */
					break;
				    }
				}
	
				if (!learning) {
				    /* Check that we haven't reached the end of the record. */
				    (void)sample(/*sig,*/ tpq,buffer);
				    if (sample_vflag == 0) break;
				    /* Record an annotation at the QRS onset */

				    /********************************************************
				    	aqui es donde tenemos que imprimir el tpq (annot.time)!!!
				    ********************************************************/
                    
				 }
	
				/* Adjust thresholds */
				Ta += (max - Ta)/10;
				T1 = Ta / 3;

				/* Lock out further detections during the eye-closing period */
				t += EyeClosing;
		    }
		}
		else if (!learning) {
		    /* Once past the learning period, decrease threshold if no QRS
		       was detected recently. */
		    if (++timer > ExpectPeriod && Ta > Tm) {
				Ta--;
				T0 = Ta / 3;
		    }      
		}
    //}
      //metemos el nuevo valor datum al buffer en la posicion to (se pierde el primer dato 
   
    
   
}
void freeBuffers(){
	
	(void)free(lbuf);
    (void)free(ebuf);
    
 
	
}




/*************************************************************************************
*******************comienza el programa**********************************************
*************************************************************************************/

//#define BUFLN  16384	/* must be a power of 2, see ltsamp() */
#define EYE_CLS 0.25    /* eye-closing period is set to 0.25 sec (250 ms) */ 
//#define LPERIOD 1000	/* learning period is the first LPERIOD samples */
#define MaxQRSw 0.13    /* maximum QRS width (130ms) */                        
#define NDP	 2.5    /* adjust threshold if no QRS found in NDP seconds */
#define PWFreqDEF 60    /* power line (mains) frequency, in Hz (default) */
#define TmDEF	 100	/* minimum threshold value (default) */


//char *pname;		/* the name by which this program was invoked */
int32_t lfsc;		/* length function scale constant */
int8_t *ebuf;
//int8_t nsig;		/* number of input signals */
int8_t LPn, LP2n;          /* filter parameters (dependent on sampling rate) */
int8_t LTwindow;           /* LT window size */
int8_t PWFreq = PWFreqDEF;	/* power line (mains) frequency, in Hz */
//int8_t sig = 0;	        /* signal number of signal to be analyzed */
int8_t Tm = TmDEF;		/* minimum threshold value */
int16_t *lbuf = NULL;


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

int8_t wqrs(int16_t datum, int16_t *buffer)
{ 
    float sps;			     /* sampling frequency, in Hz (SR) */
    int8_t i, max, min, onset, timer;
     
    int8_t EyeClosing;                  /* eye-closing period, related to SR */
    int8_t ExpectPeriod;                /* if no QRS is detected over this period,
					the threshold is automatically reduced
					to a minimum value;  the threshold is
					restored upon a detection */
    double Ta, T0;			     /* high and low detection thresholds */
    WFDB_Gain gain;
    WFDB_Time  t, tpq, tt, t1,from = 0L, to = 0L;

    PWFreq=100;  //opcion -p
   
    //sfreq = ffreq;//setgvmode(0|WFDB_GVPAD);
	
    //if ( readheader() < 1) exit(2); //inicializa algunas variables
    
    //ffreq=(WFDB_Frequency)360; 
    //sfreq = ffreq;
    sfreq=(WFDB_Frequency)360; 
    nsamples=650000;
	infogain=(WFDB_Gain)200;  

    if ((gain = infogain) == 0.0) gain = WFDB_DEFGAIN;
    sps = sfreq; //sampfreq((char *)NULL); no hace falta usar este metodo, ya he comprobado que es 0
    
    ifreq=150.;
    sps=150.;
   
     to = strtim("e");//siempre hace else ya que to=0L, va a dar to=nsambles=65000

    Tm = muvadu(Tm);
    lfsc = 1.25*gain*gain/sps;	/* length function scale constant */

    LPn = sps/PWFreq;   /* The LP filter will have a notch at the
				    power line (mains) frequency */
    if (LPn > 8)  LPn = 8;	/* avoid filtering too agressively */
    LP2n = 2 * LPn;
    EyeClosing = sps * EYE_CLS;   /* set eye-closing period */
    ExpectPeriod = sps * NDP;	   /* maximum expected RR interval */
    LTwindow = sps * MaxQRSw;     /* length transform window size */

    (void)sample(/*sig,*/ 0L,buffer);

    /* Average the first 8 seconds of the length-transformed samples
       to determine the initial thresholds Ta and T0. The number of samples
       in the average is limited to half of the ltsamp buffer if the sampling
       frequency exceeds about 2 KHz. */
    if ((t1 = strtim("8")) > BUFLN*0.9)
	t1 = BUFLN/2;
    t1 += from;
    for (T0 = 0, t = from; t < t1 && sample_vflag; t++)
		T0 += ltsamp(t,buffer);
    T0 /= t1 - from;
    Ta = 3 * T0;

    /******************************** Main loop *******************************/
    for (t = from; t < to || (to == 0L && sample_vflag); t++) {
		static int8_t learning = 1, T1;
	
		if (learning) {
		    if (t > t1) {
				learning = 0;
				T1 = T0;
				t = from;	/* start over */
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
    }
    (void)free(lbuf);
    (void)free(ebuf);
    
    exit(0);
}


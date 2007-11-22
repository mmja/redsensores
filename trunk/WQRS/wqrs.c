/* 
MODIFICACION DEL WQRS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

file: wqrs.c		Wei Zong      23 October 1998
			Last revised: 25 February 2006 (by G. Moody)
-----------------------------------------------------------------------------
wqrs: Single-lead QRS detector based on length transform
Copyright (C) 1998-2006 Wei Zong

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA.

You may contact the author by e-mail (wzong@mit.edu) or postal mail
(MIT Room E25-505, Cambridge, MA 02139, USA).  For updates to this software,
please visit PhysioNet (http://www.physionet.org/).
------------------------------------------------------------------------------

This program analyzes an ECG signal, detecting QRS onsets and J-points, using
a nonlinearly-scaled ECG curve length feature.  This version has been optimized
for ECGs sampled at 125 Hz, but it can analyze ECGs sampled at any frequency
using on-the-fly resampling provided by the WFDB library.

`wqrs' can process records containing any number of signals, but it uses only
one signal for QRS detection (signal 0 by default;  this can be changed using
the `-s' option, see below).  'wqrs' has been optimized for adult human ECGs.
For other ECGs, it may be necessary to experiment with the input sampling
frequency and the time constants indicated below.

To compile this program under GNU/Linux, MacOS/X, MS-Windows, or Unix, use gcc:
	gcc -o wqrs wqrs.c -lwfdb -lm
You must have installed the WFDB library, available at	
	http://www.physionet.org/physiotools/wfdb.shtml
gcc is standard with GNU/Linux and is available for other platforms from:
	http://www.gnu.org/		(sources and Unix binaries)
	http://fink.sourceforge.net	(Mac OS/X only)
	http://www.cygwin.com/   	(MS-Windows only)
	
For a usage summary, see the help text at the end of this file.  The input
record may be in any of the formats readable by the WFDB library, and it may
be anywhere in the WFDB path (in a local directory or on a remote web or ftp
server).  The output of 'wqrs' is an annotation file named RECORD.wqrs (where
RECORD is replaced by the name of the input record).  Within the output
annotation file, the time of each NORMAL annotation marks a QRS onset;  if
the '-j' option is used, additional JPT annotations mark the J points (the
ends of the QRS complexes).  During the learning period (the first LPERIOD
samples), LEARN annotations are used instead of NORMAL annotations, and there
are no JPT annotations.

For example, to mark QRS complexes in record 100 beginning 5 minutes from the
start, ending 10 minutes and 35 seconds from the start, and using signal 1, use
the command:
    wqrs -r 100 -f 5:0 -t 10:35 -s 1
The output may be read using (for example):
    rdann -a wqrs -r 100
To evaluate the performance of this program, run it on the entire record, by:
    wqrs -r 100
and then compare its output with the reference annotations by:
    bxb -r 100 -a atr wqrs
*/

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
#include "wqrs.h"





/*************************************************************************************
*******************comienza el programa**********************************************
*************************************************************************************/

#define BUFLN  16384	/* must be a power of 2, see ltsamp() */
#define EYE_CLS 0.25    /* eye-closing period is set to 0.25 sec (250 ms) */ 
//#define LPERIOD 1000	/* learning period is the first LPERIOD samples */
#define MaxQRSw 0.13    /* maximum QRS width (130ms) */                        
#define NDP	 2.5    /* adjust threshold if no QRS found in NDP seconds */
#define PWFreqDEF 60    /* power line (mains) frequency, in Hz (default) */
#define TmDEF	 100	/* minimum threshold value (default) */


char *pname;		/* the name by which this program was invoked */
int32_t lfsc;		/* length function scale constant */
int8_t *ebuf;
int8_t nsig;		/* number of input signals */
int8_t LPn, LP2n;          /* filter parameters (dependent on sampling rate) */
int8_t LTwindow;           /* LT window size */
int8_t PWFreq = PWFreqDEF;	/* power line (mains) frequency, in Hz */
int8_t sig = 0;	        /* signal number of signal to be analyzed */
int8_t Tm = TmDEF;		/* minimum threshold value */
WFDB_Sample *lbuf = NULL;


/* ltsamp() returns a sample of the length transform of the input at time t.
   Since this program analyzes only one signal, ltsamp() does not have an
   input argument for specifying a signal number; rather, it always filters
   and returns samples from the signal designated by the global variable
   'sig'.  The caller must never "rewind" by more than BUFLN samples (the
   length of ltsamp()'s buffers). */

WFDB_Sample ltsamp(WFDB_Time t)
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
		if ((v0 = sample(sig, tt)) != WFDB_INVALID_SAMPLE &&
		    (v1 = sample(sig, tt-LPn)) != WFDB_INVALID_SAMPLE &&
		    (v2 = sample(sig, tt-LP2n)) != WFDB_INVALID_SAMPLE)
		    Yn = 2*Yn1 - Yn2 + v0 - 2*v1 + v2;
		dy = (Yn - Yn1) / LP2n;		/* lowpass derivative of input */
		et = ebuf[(++tt)&(BUFLN-1)] = sqrtf(lfsc +dy*dy); /* length transform */
		lbuf[(tt)&(BUFLN-1)] = aet += et - ebuf[(tt-LTwindow)&(BUFLN-1)];
		/* lbuf contains the average of the length-transformed samples over
		   the interval from tt-LTwindow+1 to tt */
    }
    return (lbuf[t&(BUFLN-1)]);
}

main(int8_t argc, char **argv)
{ 
    
    float sps;			     /* sampling frequency, in Hz (SR) */
    //float samplingInterval;          /* sampling interval, in milliseconds */
    int8_t i, max, min, onset, timer;
    
    int8_t Rflag = 0;		     /* if non-zero, resample at 120 or 150 Hz  */
    
    int8_t EyeClosing;                  /* eye-closing period, related to SR */
    int8_t ExpectPeriod;                /* if no QRS is detected over this period,
					the threshold is automatically reduced
					to a minimum value;  the threshold is
					restored upon a detection */
    double Ta, T0;			     /* high and low detection thresholds */
   
    WFDB_Gain gain;
    //WFDB_Sample *v;
    WFDB_Siginfo *s;
    WFDB_Time  t, tpq, tt, t1,from = 0L, to = 0L;
    static int8_t gvmode = 0; //esta se usa para la opcion H pero me creo q tb se usa en otras cosas
    char *prog_name();
    
   
   

    pname = prog_name(argv[0]);

    for (i = 1; i < argc; i++) {
	if (*argv[i] == '-') 
	switch (*(argv[i]+1)) {
	
	  case 'p':	/* specify power line (mains) frequency */
	    if (++i >= argc || (PWFreq = atoi(argv[i])) <= 0) {
		//(void)fprintf(stderr,"%s: power line frequency ( > 0) must follow -p\n", pname);
		exit(1);
	    }
	    break;
	  case 'r':	// record name 
	    if (++i >= argc) {
		
		exit(1);
	    }
	   
	    break;
	  case 'R':	// resample 
	    Rflag = 1;
	    break;
	
	  default:
	   
	    exit(1);
	}
	else {
	  
	    exit(1);
	}
    }
    


   
    setgvmode(gvmode|WFDB_GVPAD);
	//nota: isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig)
    //if ((nsig = isigopen("100"/*record*/, NULL, 0)) < 1) exit(2); //nsig=1 luego aqui no hace nada porq el segundo parametro es null
    nsig=1;
    
    if ((s = (WFDB_Siginfo *)malloc(nsig * sizeof(WFDB_Siginfo))) == NULL) {
		
		exit(2);
    }
    //a.name = "wqrs"; a.stat = WFDB_WRITE;
    if ((nsig = wfdbinit("100"/*record*/, /*&a, 1, */s, nsig)) < 1) exit(2); //aqui rellena la estructura s -->solucionado!!!
    
    
    
    sig=0;//analizamos una sola señal
    if ((gain = s[sig].gain) == 0.0) gain = WFDB_DEFGAIN;
    sps = sfreq; //sampfreq((char *)NULL); no hace falta usar este metodo, ya he comprobado que es 0
    if (Rflag) {  
    	if (PWFreq == 60.0) setifreq(sps = 120.);
    	else setifreq(sps = 150.); //solo deberia quedarse esta opcion
    }
   
     to = strtim("e");//siempre hace else ya que to=0L

   
    Tm = muvadu(sig, Tm);
    //samplingInterval = 1000.0/sps;
    lfsc = 1.25*gain*gain/sps;	/* length function scale constant */
   
    
    LPn = sps/PWFreq;   /* The LP filter will have a notch at the
				    power line (mains) frequency */
    if (LPn > 8)  LPn = 8;	/* avoid filtering too agressively */
    LP2n = 2 * LPn;
    EyeClosing = sps * EYE_CLS;   /* set eye-closing period */
    ExpectPeriod = sps * NDP;	   /* maximum expected RR interval */
    LTwindow = sps * MaxQRSw;     /* length transform window size */

    (void)sample(sig, 0L);
    
    
    
    
    /* Average the first 8 seconds of the length-transformed samples
       to determine the initial thresholds Ta and T0. The number of samples
       in the average is limited to half of the ltsamp buffer if the sampling
       frequency exceeds about 2 KHz. */
    if ((t1 = strtim("8")) > BUFLN*0.9)
	t1 = BUFLN/2;
    t1 += from;
    for (T0 = 0, t = from; t < t1 && sample_valid(); t++)
		T0 += ltsamp(t);
    T0 /= t1 - from;
    Ta = 3 * T0;

    /******************************** Main loop *******************************/
    for (t = from; t < to || (to == 0L && sample_valid()); t++) {
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
		if (ltsamp(t) > T1) {	/* found a possible QRS near t */
		    timer = 0; /* used for counting the time after previous QRS */
		    max = min = ltsamp(t);
		    for (tt = t+1; tt < t + EyeClosing/2; tt++)
				if (ltsamp(tt) > max) max = ltsamp(tt);
		    for (tt = t-1; tt > t - EyeClosing/2; tt--)
				if (ltsamp(tt) < min) min = ltsamp(tt);
		    if (max > min+10) { /* There is a QRS near tt */
			/* Find the QRS onset (PQ junction) */
				onset = max/100 + 2;
				tpq = t - 5;
				for (tt = t; tt > t - EyeClosing/2; tt--) {
				    if (ltsamp(tt)   - ltsamp(tt-1) < onset &&
					ltsamp(tt-1) - ltsamp(tt-2) < onset &&
					ltsamp(tt-2) - ltsamp(tt-3) < onset &&
					ltsamp(tt-3) - ltsamp(tt-4) < onset) {
					tpq = tt - LP2n;	/* account for phase shift */
					break;
				    }
				}
	
				if (!learning) {
				    /* Check that we haven't reached the end of the record. */
				    (void)sample(sig, tpq);
				    if (sample_valid() == 0) break;
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

char *prog_name(s)
char *s;
{
    char *p = s + strlen(s);

	#ifdef MSDOS
	    while (p >= s && *p != '\\' && *p != ':') {
		if (*p == '.')
		    *p = '\0';		/* strip off extension */
		if ('A' <= *p && *p <= 'Z')
		    *p += 'a' - 'A';	/* convert to lower case */
		p--;
	    }
	#else
	    while (p >= s && *p != '/')
		p--;
	#endif
	    return (p+1);
}


//#include <stdint.h>
//typedef int16_t	     WFDB_Sample;   /* units are adus */
typedef int32_t 	 WFDB_Time;	    /* units are sample intervals */
typedef double	 WFDB_Gain;	    /* units are adus per physical unit */
typedef double	     WFDB_Frequency;/* units are Hz (samples/second/signal) */
#define BUFLN  164//16384	/* must be a power of 2, see ltsamp() */
#define WFDB_INVALID_SAMPLE (-32768) /* samples from getvec or getframe with this value are not valid */
#define WFDB_DEFGAIN	200.0  /* default value for gain (adu/physical unit) */
/*************************** variables en signal.c **********************/
//static int8_t gvc;			/* getvec sample-within-frame counter */
static int8_t sample_vflag;	/* if non-zero, last value returned by sample() was valid */	
static WFDB_Frequency ffreq;	/* frame rate (frames/second) frame rate*/
static WFDB_Frequency ifreq;	/* samples/second/signal returned by getvec */
static WFDB_Frequency sfreq;	/* samples/second/signal read by getvec sampling rate*/
static WFDB_Time nsamples;	/* duration of signals (in samples) */
WFDB_Gain infogain;	/* gain (ADC units/physical unit, 0: uncalibrated) */

/****************************contenidos de wfdbf.c***********************/
#ifndef BSD
# include <string.h>
#else		// for Berkeley UNIX only 
# include <strings.h>
#endif
//variables y metodos externos
int16_t sample( WFDB_Time t, int16_t *sbuf ){
void setgvmode(int8_t mode);
int8_t readheader();
int16_t muvadu(/*WFDB_Signal s,*/ int8_t v);
int16_t ltsamp(WFDB_Time t);



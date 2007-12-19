#include <math.h>
#include "wqrs.h"
#include <io.h>
/************************************declaraciones*******************************************/

/* buffer used by sample() */
//#define BUFLN   4096	/* must be a power of 2, see sample() */
//********************************************* SAMPLE  ***************************************
//consultar funciones http://physionet.org/physiotools/wpg/wpg_toc.htm
//This function return the value (in raw adus) of sample number current in open signal s,
//if successful, or the value of the previous successfully read sample.
int16_t getsample( WFDB_Time dat, int16_t *sbuf ){
 	static int16_t v;
    /* If the caller specified a negative sample number, prepare to return
       sample 0.  This behavior differs from the convention that only the
       absolute value of the sample number matters. */
    if (dat < 0L) dat = 0L;
    /* The requested sample is in the buffer.  Set sample_vflag and
       return the requested sample. */
    if ((v = (sbuf [dat%(BUFLN)] /*+ s*/)) == WFDB_INVALID_SAMPLE)
        sample_vflag = -1;
    else
        sample_vflag = 1;
    return (v);
}

//valores que se meten en siarray
	/*siarray[0].fname="100.dat";
    siarray[0].desc="MLII";
    siarray[0].units=NULL;
    siarray[0].gain=0;
    siarray[0].initval=995;
    siarray[0].group=0;
    siarray[0].fmt=212;
    siarray[0].spf=1;
    siarray[0].bsize=0;
    siarray[0].adcres=11;
    siarray[0].adczero=1024;
    siarray[0].baseline=1024;
    siarray[0].nsamp=65000;
    siarray[0].cksum=-22131;
    return (1);*/
//-------------------------------------------muvadu----------------------------------------------------
//his function converts the potential difference v from microvolts to ADC units, 
//based on the gain for input signal s.

int16_t muvadu( int8_t v){
	
    int32_t x;
    WFDB_Gain g = WFDB_DEFGAIN;

    if (g == 0.) g = WFDB_DEFGAIN;
    x = g*v*0.001;
    if (x >= 0.0)
	return ((int8_t)(x + 0.5));
    else
	return ((int8_t)(x - 0.5));

}








#include <math.h>
#include "wqrs.h"
#include <io.h>
/************************************declaraciones*******************************************/
WFDB_Sample sbuf[BUFLN]={	
990,
938,
944,
960,
955,
958,
960,
961,
956,
957,
955,
958,
957,
959,
953,
956,
961,
960,
957,
956,
954,
952,
957,
958,
955,
957,
959,
956,
957,
956,
954,
952,
957,
958,
956,
956,
957,
954,
954,
956,
957,
953,
956,
957,
954,
952,
955,
954,
952,
951,
951,
948,
950,
952,
949,
950,
951,
951,
950,
958,
958,
956,
962,
965,
965,
966,
971,
974,
971,
976,
976,
973,
974,
974,
973,
974,
972,
971,
970,
971,
970,
966,
970,
970,
967,
968,
970,
968,
966,
968,
966,
963,
964,
963,
961,
965,
967,
964,
963,
965,
962,
960,
963,
964,
958,
961,
963,
960,
958,
961,
962,
962,
963,
964,
963,
963,
967,
963,
961,
964,
968,
969,
969,
973,
974,
980,
983,
981,
978,
979,
978,
977,
976,
981,
980,
968,
965,
959,
958,
960,
960,
956,
955,
955,
953,
956,
958,
957,
953,
959,
957,
952,
949,
937,
927,
917,
936,
979,
1040,
1132,
1198,
1208,
1144,
1033};	/* buffer used by sample() */
//#define BUFLN   4096	/* must be a power of 2, see sample() */
//********************************************* SAMPLE  ***************************************
//consultar funciones http://physionet.org/physiotools/wpg/wpg_toc.htm
//This function return the value (in raw adus) of sample number t in open signal s,
//if successful, or the value of the previous successfully read sample.
WFDB_Sample sample(/*WFDB_Signal s,*/ WFDB_Time t){
 	static WFDB_Sample v;
    /* If the caller specified a negative sample number, prepare to return
       sample 0.  This behavior differs from the convention that only the
       absolute value of the sample number matters. */
    if (t < 0L) t = 0L;
    /* The requested sample is in the buffer.  Set sample_vflag and
       return the requested sample. */
    if ((v = *(sbuf +  (t&(BUFLN-1)) /*+ s*/)) == WFDB_INVALID_SAMPLE)
        sample_vflag = -1;
    else
        sample_vflag = 1;
    return (v);
}

//----------------------------------------------- readheader --------------------------------------------------
//reads a header file ->lo metemos a capon en hsd
int8_t readheader()
{ 	
    /* Determine the frame rate, if present and not set already.*/
    ffreq=(WFDB_Frequency)360; //(WFDB_Frequency)atof(p)

    /* Set the sampling rate to the frame rate for now.  This may be
       changed later by isigopen or by setgvmode, if this is a multi-
       frequency record and WFDB_HIGHRES mode is in effect. */
    sfreq = ffreq;
  
    /* Determine the number of samples per signal, if present and not
       set already. */
    nsamples=650000;

	/* Determine the gain in ADC units per physical unit.  This number
		   may be zero or missing;  if so, the signal is uncalibrated. */
	infogain=(WFDB_Gain)200;  

    return (1);			/* return number of available signals */
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

WFDB_Sample muvadu( int8_t v){
	
    int32_t x;
    WFDB_Gain g = infogain;

    if (g == 0.) g = WFDB_DEFGAIN;
    x = g*v*0.001;
    if (x >= 0.0)
	return ((int8_t)(x + 0.5));
    else
	return ((int8_t)(x - 0.5));

}

//-----------------------------------------------strtim--------------------------------------------------
//http://physionet.org/physiotools/wpg/wpg_23.htm#SEC85
WFDB_Time strtim(char *string){
	char *p;
    double f, x, y, z;
   
    WFDB_Time t;

    if (ifreq > 0.) f = ifreq;
    else if (sfreq > 0.) f = sfreq;
    else f = 1.0;
    while (*string==' ' || *string=='\t' || *string=='\n' || *string=='\r')
	string++;
    switch (*string) {

    case 'e':	return  nsamples ;  
      default:  
		//x = atof(string); entra un "8", entero, y los atoi si los coge
		x=atoi(string);
	if ((p = strchr(string, ':')) == NULL) return ((int16_t)(x*f + 0.5));
	//y = atof(++p);
	y=atoi(++p);
	if ((p = strchr(p, ':')) == NULL) return ((int16_t)((60.*x + y)*f + 0.5));
	//z = atof(++p);
	z=atoi(++p);
	return ((WFDB_Time)((3600.*x + 60.*y + z)*f + 0.5));
    }	
	
}






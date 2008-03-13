typedef int32_t  WFDB_Time;	    /* units are sample intervals */
typedef double	     WFDB_Frequency;/* units are Hz (samples/second/signal) */
#define BUFLN 64//16384	/* must be a power of 2, see ltsamp() */


static int8_t sample_vflag;	/* if non-zero, last value returned by sample() was valid */	


#define WFDB_INVALID_SAMPLE (-32768) /* samples from getvec or getframe with this value are not valid */
#define WFDB_DEFGAIN	200.0  /* default value for gain (adu/physical unit) */

#define FS 150.0 //sampling frecuency Paso 2
#define W 1 //wave width Paso 2 !!!!averiguarlo



int16_t getsample( int16_t dat, int16_t *f );
int32_t wqrs(int16_t datum, int16_t *buffer);


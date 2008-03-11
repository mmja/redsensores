typedef int32_t  WFDB_Time;	    /* units are sample intervals */
typedef double	     WFDB_Frequency;/* units are Hz (samples/second/signal) */
#define BUFLN 64//16384	/* must be a power of 2, see ltsamp() */


#define WFDB_INVALID_SAMPLE (-32768) /* samples from getvec or getframe with this value are not valid */
#define WFDB_DEFGAIN	200.0  /* default value for gain (adu/physical unit) */



int16_t getsample( WFDB_Time dat, int16_t *sbuf );
int32_t wqrs(int16_t datum, int16_t *buffer);


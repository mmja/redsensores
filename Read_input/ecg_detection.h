#define BUFLN 512//16384	/* must be a power of 2, see ltsamp() */


static int8_t sample_vflag;	/* if non-zero, last value returned by sample() was valid */	

#define WFDB_INVALID_SAMPLE (-32767) /* samples from getvec or getframe with this value are not valid */

#define FS 200.0//150.0 //sampling frecuency Paso 2
#define W 0.1 //wave width Paso 2 !!!!averiguarlo
#define LQRS 0.1 //qrs length
#define NOPS 8 //qrs length


int16_t getsample( int16_t dat, int16_t *f );
int32_t ecg_detection(int16_t datum, int16_t *buffer, int16_t *out);
void freeBuffers();



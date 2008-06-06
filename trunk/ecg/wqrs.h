#define BUFLN 350//16384	/* must be a power of 2, see ltsamp() */


//static int8_t sample_vflag;	/* if non-zero, last value returned by sample() was valid */	

//#define WFDB_INVALID_SAMPLE (-32768) /* samples from getvec or getframe with this value are not valid */

#define FS 200.0//150.0 //sampling frecuency Paso 2
#define W 0.1 //wave width Paso 2 !!!!averiguarlo
#define LQRS 0.1 //qrs length
#define NOPS 6 //qrs length
#define detecinterval  24.5//(0.12*FS + 0.5)
#define detecinterval2 80.5//(0.40*FS + 0.5);
#define s 19//=FS*W-1;
#define distance 401//=to-from  = (BUFLN - 55 )- (1 + 55);
#define margin 74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;

#define lo 20 //=LQRS*FS;
#define lc 30 //=1.5*lo;
#define l1 5 //=5;

//int16_t getsample( int16_t dat, int16_t *f );
int8_t wqrs(int16_t datum, int16_t buffer[BUFLN],int16_t out[12]);
//void freeBuffers();







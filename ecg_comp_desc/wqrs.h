#define BUFLN 300	/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 450

//static int8_t sample_vflag;	/* if non-zero, last value returned by sample() was valid */	

//#define WFDB_INVALID_SAMPLE (-32768) /* samples from getvec or getframe with this value are not valid */

//#define FS 200//150.0 //sampling frecuency Paso 2
//#define W 0.1 //wave width Paso 2 !!!!averiguarlo
//#define LQRS 0.1 //qrs length
//#define NOPS 6 //qrs length
#define detecinterval  24//(0.12*FS + 0.5)
#define detecinterval2 80//(0.40*FS + 0.5);
#define s 19//=FS*W-1;
#define distance 151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define margin 74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;

#define lo 20 //=LQRS*FS;
#define lc 30 //=1.5*lo;
#define l1 5 //=5;
#define groups 5 
//int16_t getsample( int16_t dat, int16_t *f );
int8_t wqrs(int16_t datum, int8_t buffer[BUFLNZIP],int16_t out[12]);
//void freeBuffers();







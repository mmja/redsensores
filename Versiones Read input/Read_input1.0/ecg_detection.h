/**********************************************************************************************************
/ VERSION 1.0 - Monica Jimenez, Laura Gutierrez
/ Sin Filtro. Usa señales ya filtradas.
/ Con Comprobacion de las detecciones para validarlas.
/ Soportada por el Nodo (insuficiente tiempo para procesar los datos).                    
/***********************************************************************************************************/


#define BUFLN 300	/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 450

#define FREQ 200
#define DETECINTERVAL  12//24//(0.12*FS + 0.5)
#define DETECINTERVAL2 80//(0.40*FS + 0.5);
#define S 19//=FS*W-1;
#define DISTANCE 151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define MARGIN 74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;

#define LO 20 //=LQRS*FS;
#define LC 30 //=1.5*lo;
#define L1 5 //=5;
#define GROUPS 5 
int8_t ecg_detection(int16_t datum, int8_t fp[BUFLNZIP],int8_t detection[12],int16_t amplitudes[3]);








/**********************************************************************************************************
/ VERSION 0.3 - Monica Jimenez, Laura Gutierrez
/ Buffers comprimidos. Metodos para descomprimirlos.
/ Optimizacion del thresholding
/ No soportada por el Nodo (insuficiente tiempo para procesar los datos).                    
/***********************************************************************************************************/

#define BUFLN 300	/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 450

#define detecinterval  24//(0.12*FS + 0.5)
#define detecinterval2 80//(0.40*FS + 0.5);
#define s 19//=FS*W-1;
#define distance 151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define margin 74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;

#define lo 20 //=LQRS*FS;
#define lc 30 //=1.5*lo;
#define l1 5 //=5;
#define groups 5 

int8_t wqrs(int16_t datum, int8_t buffer[BUFLNZIP],int16_t out[12]);








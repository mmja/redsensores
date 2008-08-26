/**********************************************************************************************************
/ VERSION 0.2 - Monica Jimenez, Laura Gutierrez
/ Con Arrays. Reduccion del numero de variables.
/ No soportada por el Nodo (no entra en memoria).                    
/***********************************************************************************************************/


#define BUFLN 300	/* must be a power of 2, see ltsamp() */
#define detecinterval  24//(0.12*FS + 0.5)
#define detecinterval2 80//(0.40*FS + 0.5);
#define s 19//=FS*W-1;
#define distance 151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define margin 74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;

#define lo 20 //=LQRS*FS;
#define lc 30 //=1.5*lo;
#define l1 5 

int8_t wqrs(int16_t datum, int16_t buffer[BUFLN],int16_t out[12]);








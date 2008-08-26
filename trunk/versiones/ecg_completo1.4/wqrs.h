/**********************************************************************************************************
/ VERSION 1.4 - Monica Jimenez, Laura Gutierrez
/ Sin Filtro. Usa señales ya filtradas.
/ Sin Validaciones.
/ Dividida en 8 pasos. Lee un dato en cada paso.
/ Devuelve las detecciones en formato HH:MM:SS.miliseg
/ Soportada por el Nodo.                    
/***********************************************************************************************************/

#define BUFLN 300	/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 450

#define FREQ 200.0
#define DETECINTERVAL  24//(0.12*FS + 0.5)

#define S 19  //=FS*W-1;
#define DISTANCE 261//151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define MARGIN 19//74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;







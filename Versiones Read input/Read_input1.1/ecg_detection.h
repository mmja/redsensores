/**********************************************************************************************************
/ VERSION 1.1 - Monica Jimenez, Laura Gutierrez
/ Sin Filtro. Usa señales ya filtradas.
/ Con Comprobacion de las detecciones para validarlas.
/ Dividida en 8 pasos.
/ Soportada por el Nodo (muy lenta).                    
/***********************************************************************************************************/


#define BUFLN 300	/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 450

#define FREQ 200.0
#define DETECINTERVAL  12//24//(0.12*FS + 0.5)
#define DETECINTERVAL2 80//(0.40*FS + 0.5);
#define S 19  //=FS*W-1;
#define DISTANCE 151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define MARGIN 74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;









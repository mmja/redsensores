/**********************************************************************************************************
/ VERSION 1.6 - Monica Jimenez, Laura Gutierrez
/ Sin Filtro. Usa señales ya filtradas.
/ Sin Validaciones.
/ Disminucion del tamaño del buffer a 40 elementos
/ Con transformada aproximada (/16 en vez de /19)
/ Con vector de 24 puntos Maximos y Minimos que reduce la busqueda
/ Dividida en 8 pasos. Lee un dato en cada paso.
/ Soportada por el Nodo - No detecta demasiado bien.                    
/***********************************************************************************************************/



#define BUFLN 40//34	//300/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 60//51//450

#define MAXFILLED  5//(0.12*FS + 0.5)

#define FREQ 200.0
#define DETECINTERVAL  24//(0.12*FS + 0.5)

#define S 16//19  //=FS*W-1;
#define DISTANCE 7//261//151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define MARGIN 16//19//74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;

#define POINTS 24 //PWAVE(3) + Q(1) + RPEAK(1)+ S(1) +RWAVE(2) + TWAVE(3) 








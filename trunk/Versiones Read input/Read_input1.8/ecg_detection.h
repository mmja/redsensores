/**********************************************************************************************************
/ VERSION 1.8 - Monica Jimenez, Laura Gutierrez
/ Devuelve las detecciones en formato HH:MM:SS.miliseg
/ Con Comprobacion de las detecciones para validarlas.
/ Detecta bien (Mejora de la busqueda de onda T).
/ Eliminacion de un buffer y variables sobrantes.
/ Reduccion del tama�o de buffers (de 24 a 18)
/ Soportada por el Nodo                    
/***********************************************************************************************************/
#define BUFLN 40//34	//300/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 60//51//450

#define MAXFILLED  5//(0.12*FS + 0.5)

#define FREQ 200.0
#define DETECINTERVAL  24//(0.12*FS + 0.5)

#define S 16//19  //=FS*W-1;
#define DISTANCE 7//261//151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define MARGIN 16//19//74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;


#define POINTS 18 //PWAVE(3) + Q(1) + RPEAK(1)+ S(1) +RWAVE(2) + TWAVE(3) 







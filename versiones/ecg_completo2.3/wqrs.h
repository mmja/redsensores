/**********************************************************************************************************
/ VERSION 2.3 - Monica Jimenez, Laura Gutierrez
/ Devuelve las detecciones en formato HH:MM:SS.miliseg
/ Reduce variables y operaciones 
/ Resultados similares a los de chart - o - matic
/ Con Comprobacion de las detecciones para validarlas.
/ Devuelve las amplitudes de Rpeak, Pwave y Twave
/ Soportada por el Nodo   
/ Envio - Recepcion:  El paquete contiene solo el error detectado y el instante de tiempo del rpeak asociado
/       			  Envia 4 rpeaks por cada paquete (también envia cuando es correcto)                          
/***********************************************************************************************************/
#define BUFLN 40//34	//300/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 60//51//450

#define MAXFILLED  5//(0.12*FS + 0.5)

#define BUFLNVIRT 200 //BUFLN*MAXFILLED
#define DETECINTERVAL  24//(0.12*FS + 0.5)

#define S 16//19  //=FS*W-1;
#define DISTANCE 7//261//151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define MARGIN 16//19//74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;


#define POINTS 18 //PWAVE(3) + Q(1) + RPEAK(1)+ S(1) +RWAVE(2) + TWAVE(3) 








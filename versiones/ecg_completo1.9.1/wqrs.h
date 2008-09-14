/**********************************************************************************************************
/ VERSION 2.0 - Monica Jimenez, Laura Gutierrez
/ Devuelve las detecciones en formato HH:MM:SS.miliseg
/ Reduce variables y operaciones 
/ Resultados similares a los de chart - o - matic
/ Con Comprobacion de las detecciones para validarlas.
/ Devuelve las amplitudes de Rpeak, Pwave y Twave
/ Soportada por el Nodo   
/ Envio - Recepcion: Se envian detecciones solo cuando hay error y este se ha repetido 2 veces seguidas                  
/***********************************************************************************************************/
#define BUFLN 40
#define BUFLNZIP 60//compressed buffer longitude = BUFLN*3/2

#define MAXFILLED  5 //200/40 --> number of times that the buffer should be filled to get 1 second (200 positions)

#define BUFLNVIRT 200 //Virtual Buffer Longitude --> BUFLN*MAXFILLED
#define DETECINTERVAL  24//(0.12*FS + 0.5)

#define S 16//F*W; --> where F=200 (sampling freq) and w = [0.06,0.12] --> 16 = 2^4 
#define DISTANCE 7//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 33;
#define MARGIN 16 // =S

#define POINTS 17 //PWAVE(3) + Q(1) + RPEAK(1)+ S(1) +RWAVE(2) + TWAVE(3) (+6 to prevent)








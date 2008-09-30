/**********************************************************************************************************
/ VERSION 9 - Monica Jimenez
/ Apply a morfological filtering on a ECG signal
/ Analyze the filtered ECG signal to detect characterisctic waves (Rpeak, Rwave, Qonset, Soffset, Pwave and Twave)
/ Return the detections in HH:MM:SS:positions
/ The detections are validated to verify their cardiopaties        
/ The motes dont support it because they havent enough memory       
/***********************************************************************************************************/

#define BUFLN 200//34	//300/* must be a power of 2, see ltsamp() */
#define BUFLNZIP 300//51//450

#define MAXFILLED  1//(0.12*FS + 0.5)

#define BUFLNVIRT 200 //BUFLN*MAXFILLED
#define DETECINTERVAL  24//(0.12*FS + 0.5)

#define S 16//19  //=FS*W-1;
#define DISTANCE 57//261//151//201//401//=to-from  = (BUFLN - margin )- (1 + margin) = BUFLN - 149;
#define MARGIN 71//19//74 //55+s -------  en vez de NOPS*(1.5*LQRS*FS-1)/2;

#define GROUPS 5 

#define POINTS 30//17 //PWAVE(3) + Q(1) + RPEAK(1)+ S(1) +RWAVE(2) + TWAVE(3) 

#define ABS(a) ((a<0)?-a:a);

#define lo 20 //=LQRS*FS;
#define lc 30 //=1.5*lo;
#define l1 5 //=5;





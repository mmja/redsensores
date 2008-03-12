#include <math.h>
#include "wqrs.h"
//VARIABLES

//Para el Paso 1
int16_t *f0;//Fo= señal original
int16_t *fb;//Fb=señal de corrección de línea
int16_t *f;//F= señal después del preprocesado
int16_t *B,*Bo,*Bc;//B, Bo (apertura) y Bc (cierre) = se seleccionan basándose en las propiedades de las ondas características de ECG (elementos estructurales)



//TODOS SON ARRAYS DE 2 POSICIONES EN LA POS.0 SE GUARDA LA POSICION DE INCIO DE f y en la POS.1 la posicion final respecto de f
int16_t *Rpeaks;//Paso 3 Rpeaks= Locales minimos entre Thf y Thr. 
int16_t *Rwave;//Paso 4 (entre el primer max local a la izq y a la derecha de Rpeak)X CADA RPEAK????
int16_t *Qwave;//Paso 5 (puede que no se detecte)1º minimo local a la izq de Rwave
int16_t *Swave;//Paso 6 (puede que no se detecte)1ºminimo local desde la drecha de la parte positiva de Rwave

//Paso 7: Onset y Offset de Pwave y Twave (puede que no se detecte)
int16_t *Pwave;// los 2 primeros maximos locales desde la izq de Pwave
int16_t *Twave;// los 2 primeros maximos locales desde la dcha de Twave

//CONSTANTES (DESPUES HABRA QUE PONERLO COMO #define ... Nº)
int8_t fs; //sampling frecuency Paso 2
int8_t w; //wave width Paso 2
int8_t s; //window length of (2s+1) samples, s<W*Fs, para el Paso 2 (mmt)
int8_t thf, thr; //threshold para el Paso 3 (detectar los Rpeaks) 
int8_t detecinterval; // detection interval= 0,12 segundos, se usa en el Paso 5 y 6 (Qwave y Swave)


//************************************************************************************

//This function return the value (in raw adus) of sample number current in open signal s,
//if successful, or the value of the previous successfully read sample.
int16_t getsample( WFDB_Time dat, int16_t *sbuf ){
 	static int16_t v;
    /* If the caller specified a negative sample number, prepare to return
       sample 0.  This behavior differs from the convention that only the
       absolute value of the sample number matters. */
    if (dat < 0L) dat = 0L;
    //if (dat+from>to) dat = to-from; 
    /* The requested sample is in the buffer.  Set sample_vflag and
       return the requested sample. */
    if ((v = (sbuf [(dat)&(BUFLN-1)] /*+ s*/)) == WFDB_INVALID_SAMPLE || v==0 )
        sample_vflag = -1;
    else
        sample_vflag = 1;
    return (v);
}
//********************************************************************************************
// step1: morphological filtering for noise reduction and baseline correction
//********************************************************************************************
void mmf(){
	
	
}

//********************************************************************************************
// step2: multiscale morphological transform 
//********************************************************************************************
void mmt(){
	
	
}	
	
//********************************************************************************************
// step3: Rpeaks detection, the local maxima and minima
// return 1 if there aren't any rpeaks detected
//********************************************************************************************
int8_t rpeak_detection(){
// Se rellena aqui el array de Rpeaks[] de tipo int8_t.
// Se van buscando las locales minimas entre Thf y Thr.
// EN EL ARRAY DE RPEAKS SE GUARDAN LAS POSICIONES DONDE SE ENCUENTRAN ESAS MINIMAS LOCALES DENTRO DE LA SEÑAL F
// devuelve 0 si todo fue OK y 1 si fallo algo.	
}

//********************************************************************************************
// step4: Rwave detection
// return 1 if there aren't any rwave detected
//********************************************************************************************
int8_t rwave(){
	
	int8_t current_rpeak; // PARA CUANDO HAYA MÁS DE UNO
	int8_t right_local_max;
	int8_t left_local_max;
	int8_t r,l;//posiciones right y left
	//For the first Rpeak:
    if(Rpeaks[0]==NULL) return 1;
    else{
    	current_rpeak=Rpeaks[0];
    	right_local_max=f[Rpeaks[0]];
    	left_local_max=f[Rpeaks[0]];
    //busca 1º maximo local a la derecha:	
    r=Rpeaks[0]+1;
    while (f(r)!=NULL && right_local_max<f(r)){right_local_max=f(r);r++;}
    //despues le resto de nuevo uno a la posicion r:
    r--;
    
    //busca 1º maximo local a la izquierda:
    l=Rpeaks[0]-1;
    while (f(l)!=NULL && left_local_max<f(l)){left_local_max=f(l);l--;}
    //despues le sumo de nuevo uno a la posicion l:
    l++;
    
    // si los ha encontrado, crea Rwave y devuelve 0, sino devuelve 1
    if(f[Rpeaks[0]]<right_local_max && f[Rpeaks[0]]<left_local_max)
    {
	//Rwave -->[posicion l........posicion r]   
	//Rwave es una array de 2 posiciones donde guardamos los incides de inicio y fin de la onda,
	//Los valores estaran el f[l...r], asi ahorramos espacio
	Rwave[0]=l;
	Rwave[1]=r;
	}
    else return 1;
    //******************* IMPORTANTE *************************************************
    //NO ENTIENDO MUY BIEN SI SON VARIOS RWAVE O Q PASA, PENSABA QUE SOLO HABIA UNO
    	//For each Rpeak: AQUI SE USARIA EL CURRET_RPEAK
		//for (i = 1; Rpeaks[i] != NULL; i++)
	//*********************************************************************************
	}		
	
}

//********************************************************************************************
// step5: Qwave detection
//********************************************************************************************
int8_t qwave(){
	
	//Calculamos el 1º minimo local a la izq de Rwave (del intervalo de Rwave no??)
	int8_t left_local_min= f[Rwave[0]];//partimos de la izq de Rwave.
	int8_t l; //posicion del minimo
	int8_t count= detecinterval; // tienen que tradar menos de 0,12 seg en encontrar el minimo
	
	//**********************************************
	//*** FALTA LA CUENTA ATRAS DE TIEMPO ********** usando count desde 0,12 seg a 0 seg. si no lo encuentra en ese 
	//********************************************** tiempo tendra que devolver un 1, como que ha fallado
	
	// buscamos el 1º minimo hacia la izqda:
	l=Rwave[0]-1;
    while (f(l)!=NULL && left_local_min>f(l)){left_local_min=f(l);l--;}
    //despues le sumo de nuevo uno a la posicion l:
    l++;
	
	// si los ha encontrado, crea Qwave y devuelve 0, sino devuelve 1
    if(f[Rwave[0]]>left_local_min) 
	{
	//Qwave -->[posicion l........posicion Rwave[0]]   
	//Qwave es una array de 2 posiciones donde guardamos los incides de inicio y fin de la onda,
	//Los valores estaran el f[l...inicio de Rwave], asi ahorramos espacio
	Qwave[0]=l;
	Qwave[1]=Rwave[0];
	}
    else return 1;
	
	//************* CUENTA ATRAS **********************************
	
	
}
//********************************************************************************************
// step6: Swave detection
//********************************************************************************************
int8_t swave(){
	
	//Calculamos el 1º minimo local a la DCHA de Rwave (del intervalo de Rwave no??)
	// desde la derecha del todo o desde la derecha de la parte positiva?????
	//DE MOMENTO LO HAGO DESDE LA DERECHA DEL TODO, SI LUEGO VEMOS QUE NO ES ASI YA LO CAMBIO
	int8_t right_local_min= f[Rwave[1]];//partimos de la izq de Rwave.
	int8_t r; //posicion del minimo
	int8_t count= detecinterval; // tienen que tradar menos de 0,12 seg en encontrar el minimo
	
	//**********************************************
	//*** FALTA LA CUENTA ATRAS DE TIEMPO ********** usando count desde 0,12 seg a 0 seg. si no lo encuentra en ese 
	//********************************************** tiempo tendra que devolver un 1, como que ha fallado
	
	// buscamos el 1º minimo hacia la izqda:
	r=Rwave[1]+1;
    while (f(r)!=NULL && right_local_min>f(r)){right_local_min=f(r);r++;}
    //despues le sumo de nuevo uno a la posicion l:
    r--;
	
	// si los ha encontrado, crea Qwave y devuelve 0, sino devuelve 1
    if(f[Rwave[1]]>right_local_min) 
	{
	//Swave -->[posicion Rwave[1].....posicion r]   
	//Swave es una array de 2 posiciones donde guardamos los incides de inicio y fin de la onda,
	//Los valores estaran el f[fin de Rwave.....r], asi ahorramos espacio
	Swave[0]=Rwave[1];
	Swave[1]=r;
	}
    else return 1;
	
	//************* CUENTA ATRAS **********************************
	
	
}

//********************************************************************************************
// step7: onset and offset, Pwave and Twave detection
//********************************************************************************************
int8_t TandPwave(){
	
	
	
	//Pwave=Buscamos 2 maximos locales desde la izq de Qwave hacia la dcha:
	
	int8_t left= Qwave[0]+1;	
	//Buscamos el ONset de Pwave (1º maximo local)
	int8_t onsetP=f[Qwave[0]];
	 while (f(left)!=NULL &&  onsetP<f(left)){onsetP=f(left);left++;}
	 Pwave[0]=left-1;
	 
	//Ahora buscamos el OFFset de Pwave (2º maximo local)
	int8_t offsetP=f[left];
	 while (f(left)!=NULL &&  offsetP<f(left)){offsetP=f(left);left++;}
	Pwave[1]=left-1;
	
	//Twave=Buscamos 2 maximos locales desde la dcha de Qwave hacia la izda:
	
	
	int8_t right= Qwave[1]-1;
	
	//Buscamos el ONset de Pwave (1º maximo local)
	int8_t onsetT=f[Qwave[1]];
	 while (f(right)!=NULL &&  onsetT<f(right)){onsetT=f(right);right--;}
	 Twave[0]=right+1; // SERIA Twave[1]= right+1;  ?????
	 
	//Ahora buscamos el OFFset de Pwave (2º maximo local)
	int8_t offsetT=f[right];
	 while (f(right)!=NULL &&  offsetT<f(right)){offsetT=f(right);right--;}
	 Twave[1]=right+1; // SERIA Twave[0]= right+1;  ?????
	
	//************* FALTARIA COMPROBAR QUE LOS HA ENCONTRADO BIEN!!!!!! return 0 o 1
	return 0;
	
}
//**********************************************************************************************


int32_t wqrs(int16_t datum, int16_t *buffer)
{ 
	int8_t correct=0; // comprobamos si cada paso es correcto (correct =0) o si ha fallado (correct =1)
	
//Bucle for		
	
	// Step 1: morphological filtering for noise reduction and baseline correction
	mmf();
	// Step 2: multiscale morphological transform 
	mmt();
	// Step 3: Rpeaks detection, the local maxima and minima
	correct=rpeak_detection();
	// Step 4: Rwave detection
	if (correct==0)
		correct=rwave();
	
	if (correct==0){
		// Step 5: Qwave detection
		qwave();
		// Step 6: Swave detection
		correct=swave();
		// Step 7: onset and offset, Pwave and Twave detection
		if (correct==0) 
			correct=TandPwave();
	}
	
	//if(correct==0)//todo ha sido detectado
		return 0;
// fin del bucle	
	
}


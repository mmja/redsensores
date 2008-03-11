#include <math.h>
#include "wqrs.h"

int8_t fs; //sampling frecuency
int8_t w; //wave width
int8_t s; //window length of (2s+1) samples, s<W*Fs
int8_t thf, thr; //threshold 
//ojo: definir B0, Bc y B, fb, f0 y f (paso 1)
//Fo= señal original
//Fb=señal de corrección de línea
//F= señal después del preprocesado
//B, Bo y Bc = se seleccionan basándose en las propiedades de las ondas características de ECG (elementos estructurales)




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
//********************************************************************************************
void rpeak_detection(){
	
	
}

//********************************************************************************************
// step4: Rwave detection
//********************************************************************************************
void rwave(){
	
	
}

//********************************************************************************************
// step5: Qwave detection
//********************************************************************************************
void qwave(){
	
	
}
//********************************************************************************************
// step6: Swave detection
//********************************************************************************************
void swave(){
	
	
}

//********************************************************************************************
// step7: onset and offset, Pwave and Twave detection
//********************************************************************************************
void TandPwave(){
	
	
}
//**********************************************************************************************


int32_t wqrs(int16_t datum, int16_t *buffer)
{ 
	mmf();
	mmt();
	rpeak_detection();
	rwave();
	qwave();
	swave();
	TandPwave();
	
		
	
	
}


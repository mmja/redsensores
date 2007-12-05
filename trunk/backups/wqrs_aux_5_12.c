//eliminamos los grupos
//#include <stdio.h>
#include <math.h>
#include "wqrs.h"
//# include <stdlib.h>
//# include <stdio.h>

#include <io.h>
/************************************declaraciones*******************************************/
#define lonbuf 164
WFDB_Sample sbuf[lonbuf]={	
990,
938,
944,
960,
955,
958,
960,
961,
956,
957,
955,
958,
957,
959,
953,
956,
961,
960,
957,
956,
954,
952,
957,
958,
955,
957,
959,
956,
957,
956,
954,
952,
957,
958,
956,
956,
957,
954,
954,
956,
957,
953,
956,
957,
954,
952,
955,
954,
952,
951,
951,
948,
950,
952,
949,
950,
951,
951,
950,
958,
958,
956,
962,
965,
965,
966,
971,
974,
971,
976,
976,
973,
974,
974,
973,
974,
972,
971,
970,
971,
970,
966,
970,
970,
967,
968,
970,
968,
966,
968,
966,
963,
964,
963,
961,
965,
967,
964,
963,
965,
962,
960,
963,
964,
958,
961,
963,
960,
958,
961,
962,
962,
963,
964,
963,
963,
967,
963,
961,
964,
968,
969,
969,
973,
974,
980,
983,
981,
978,
979,
978,
977,
976,
981,
980,
968,
965,
959,
958,
960,
960,
956,
955,
955,
953,
956,
958,
957,
953,
959,
957,
952,
949,
937,
927,
917,
936,
979,
1040,
1132,
1198,
1208,
1144,
1033};	/* buffer used by sample() */
//#define BUFLN   4096	/* must be a power of 2, see sample() */








//......................................... allocisig ............................................

//pone el numero maximo de señales abiertas a la vez
static int8_t allocisig()
{
    
		    if ((isd = (isdata *)malloc(sizeof(struct isdata))) == NULL) return 0;
			// wfdb_error("init: too many (%d) input signals\n", n);
			
			   
    return (1);
}




//......................................... copysi ............................................

//copia estructuras WFDB_siginfo
static int8_t copysi(WFDB_Siginfo *to, WFDB_Siginfo *from)
{
    if (to == NULL || from == NULL) return (0);
    *to = *from;
    /* The next line works around an optimizer bug in gcc (version 2.96, maybe
       others). */
    to->fname = to->desc = to->units = NULL;
    if (from->fname) {
        to->fname = (char *)malloc((size_t)strlen(from->fname)+1);
	if (to->fname == NULL) return (-1);
	(void)strcpy(to->fname, from->fname);
    }
    if (from->desc) {
        to->desc = (char *)malloc((size_t)strlen(from->desc)+1);
	if (to->desc == NULL) {
	    (void)free(to->fname);
	    return (-1);
	}
	(void)strcpy(to->desc, from->desc);
    }
    if (from->units) {
        to->units = (char *)malloc((size_t)strlen(from->units)+1);
	if (to->units == NULL) {
	    (void)free(to->desc);
	    (void)free(to->fname);
	    return (-1);
	}
	(void)strcpy(to->units, from->units);
    }
    return (1);
}

//......................................... hsdfree ............................................

//libera memoria usada por readheader (estructura hsdata)
static void hsdfree(void)
{
    //struct hsdata *hs;

    if (hsd) {
	//while (maxhsig)
	    //if (hs = hsd[--maxhsig]) {
			if (hsd->info.fname) (void)free(hsd->info.fname);
			if (hsd->info.units) (void)free(hsd->info.units);
			if (hsd->info.desc)  (void)free(hsd->info.desc);
			(void)free(hsd);
	    //}
	//(void)free(hsd);
	hsd = NULL;
    }
    maxhsig = 0;
}

//......................................... isigclose ............................................

//libera las señales abiertas (estructura isdata)
static void isigclose(void)  
{
    struct isdata *is;
    //struct igdata *ig;

    if (nisig == 0) return;
    if (sbuf) {
	(void)free(sbuf);
	//sbuf = NULL;
	sample_vflag = 0;
    }
    if (isd) {

		if (isd->info.fname) (void)free(isd->info.fname);
		if (isd->info.units) (void)free(isd->info.units);
		if (isd->info.desc)  (void)free(isd->info.desc);
		(void)free(isd);
	    

	isd = NULL;
	nisig = 0;
    }
    

   
    //gvc = ispfmax = 1;
    
   
	hsdfree();
}




//......................................... isgsettime ............................................

//skips to a specified time in a specified signal group
int8_t isgsettime(/*WFDB_Group g,*/ WFDB_Time t)
{
    int8_t spf,  tr;

    /* Handle negative arguments as equivalent positive arguments. */
    if (t < 0L) t = -t;

    tr = t;

    /* Convert t to raw sample int8_tervals if we are resampling. */
    if (ifreq > (WFDB_Frequency)0)
	t = (WFDB_Time)(t * sfreq/ifreq);

    /* If we're in WFDB_HIGHRES mode, convert t from samples to frames, and
       save the remainder (if any) in trem. */
    if (sfreq != ffreq) {
		spf = (int8_t)(sfreq/ffreq);
		
		t /= spf;
    }

   
    if (ifreq > (WFDB_Frequency)0 && tr != t) 
	t = (WFDB_Time)(t * ifreq/sfreq);

	

    return (1);
}

//......................................... isigsettime ............................................


//skips to a specified time in each signal
int8_t isigsettime(WFDB_Time t)
{
    int8_t stat = 0;
    WFDB_Signal s;
	
    /* Return immediately if no seek is needed. */
    if (t == 0 || nisig == 0) return (0);

  
    /* Seek on signal group 0 last (since doing so updates istime and would
       confuse isgsettime if done first). */
    if (stat == 0) stat = isgsettime(/*0,*/ t);
    return (stat);
}


//********************************************* SAMPLE  ***************************************
//consultar funciones http://physionet.org/physiotools/wpg/wpg_toc.htm
//This function return the value (in raw adus) of sample number t in open signal s,
//if successful, or the value of the previous successfully read sample.
WFDB_Sample sample(/*WFDB_Signal s,*/ WFDB_Time t){
 	static WFDB_Sample v;
    static WFDB_Time tt;

    /* Allocate the sample buffer on the first call. */
    if (sbuf == NULL) {
		//sbuf= (WFDB_Sample *)malloc((unsigned)nisig*BUFLN*sizeof(WFDB_Sample));
		if (sbuf) tt = (WFDB_Time)-1L;
		else {
		  //  (void)fprint8_tf(stderr, "sample(): insufficient memory\n");
		    exit(2);
		}
    }

    /* If the caller requested a sample from an unavailable signal, return
       an invalid value.  Note that sample_vflag is not cleared in this
       case.  */
    /*if (s < 0 || s >= nisig) {
        sample_vflag = -1; //esto es para sample_valid
		return (WFDB_INVALID_SAMPLE);
    }*/

    /* If the caller specified a negative sample number, prepare to return
       sample 0.  This behavior differs from the convention that only the
       absolute value of the sample number matters. */
    if (t < 0L) t = 0L;

    /* If the caller has requested a sample that is no inter in the buffer,
       or if the caller has requested a sample that is further ahead than the
       length of the buffer, we need to reset the signal file pointer(s).
       If we do this, we must be sure that the buffer is refilled so that
       any subsequent requests for samples between t - BUFLN+1 and t will
       receive correct responses. */
    /*if (t <= tt - BUFLN || t > tt + BUFLN) {
		tt = t - BUFLN;
		if (tt < 0L) tt = -1L;
		else if (isigsettime(tt-1) < 0) exit(2);
    }*/
    /* If the requested sample is not yet in the buffer, read and buffer
       more samples.  If we reach the end of the record, clear sample_vflag
       and return the last valid value. */
    /*while (t > tt)
        if (getvec(sbuf + nisig * ((++tt)&(BUFLN-1))) < 0) {
	    --tt;
	    sample_vflag = 0;
	    return (*(sbuf + nisig * (tt&(BUFLN-1)) + s));
	}*/

    /* The requested sample is in the buffer.  Set sample_vflag and
       return the requested sample. */
    if ((v = *(sbuf + nisig * (t&(lonbuf-1)) /*+ s*/)) == WFDB_INVALID_SAMPLE)
        sample_vflag = -1;
    else
        sample_vflag = 1;
    return (v);
}



//1: The most recent value returned by sample was valid 
//0: The most recent t given to sample follows the end of the record 
//-1: The most recent value returned by sample was invalid (because signal s is not available at time t) 
int8_t sample_valid(void){
	
	 return (sample_vflag);	
}


//----------------------------------------------- setgvmode --------------------------------------------------
//ver http://physionet.org/physiotools/wpg/wpg_20.htm#SEC66
void setgvmode(int8_t mode){
	  
	/* if (mode < 0) {	// (re)set to default mode (para nuestro programa nunca se va a dar esto)
	char *p;

        if (p = getenv("WFDBGVMODE"))
	    mode = atoi(p);
	else
	    mode = DEFWFDBGVMODE;  // igual A  WFDB_LOWRES
    }*/
    mode = WFDB_LOWRES; //modo por defecto

    
		gvmode = WFDB_LOWRES;
		sfreq = ffreq;
    
	
	if ((mode & WFDB_GVPAD) == WFDB_GVPAD)
	gvpad = 1;
    else
	gvpad = 0;	
	
}








//----------------------------------------------- readheader --------------------------------------------------
//reads a header file ->lo metemos a capon en hsd
static int8_t readheader()
{
    	
	//char linebuf[256], *p, *q;
    WFDB_Frequency f;
    WFDB_Signal s;
    WFDB_Time ns;
    uint8_t i, nsig;
   
    nsig = (unsigned)1;//(unsigned)atoi(p);   --> ya que p apunta al 1 del fichero

    /* Determine the frame rate, if present and not set already.
    if (p = strtok((char *)NULL, sep)) {   //p=primera linea 3 palabra  ->360 tasa de frames*/   
    f=(WFDB_Frequency)360; //(WFDB_Frequency)atof(p)
	if (f  <= (WFDB_Frequency)0.) {
	    
	    return (-2);
	}
	if (ffreq > (WFDB_Frequency)0. && f != ffreq) {
	   //error
	}
	else
	    ffreq = f;
   
    /* Set the sampling rate to the frame rate for now.  This may be
       changed later by isigopen or by setgvmode, if this is a multi-
       frequency record and WFDB_HIGHRES mode is in effect. */
    sfreq = ffreq;

    
    /* Determine the number of samples per signal, if present and not
       set already. */
    	ns=650000;
    	if (ns  < 0L) {
		    //  error
		    return (-2);
		}
		if (nsamples == (WFDB_Time)0L)
		    nsamples = ns;
		else if (ns > (WFDB_Time)0L && ns != nsamples ) {
		    // error
		    /* nsamples must match the shortest record duration. */
		    if (nsamples > ns)
			nsamples = ns;
		}
       
    /* Allocate workspace. -  reserva el espacio a la estructura hsd segun el numero de señales*/
    if (maxhsig < nsig) {
		unsigned m = maxhsig;
		//struct hsdata **hsdnew = realloc(hsd, nsig*sizeof(struct hsdata *));
		//ya no tenemos un array asi que el hsdnew no se usa
		//struct hsdata **hsdnew = (hsdata**)malloc(nsig*sizeof(struct hsdata *));
		/*hds no tiene espacio reservado: Si ptr es un puntero nulo, la función realloc 
		se comporta a igual que la función malloc para el tamaño especificado. De lo contrario,
		 si ptr no es igual a un puntero previamente retornado por la función calloc, malloc, o 
		 realloc, o si el espacio ha sido desadjudicado por una llamada a la función free, o realloc, 
		 el comportamiento no está definido. 
		 hsd=malloc(nsig*sizeof(struct hsdata *));
		 hdsnew=hds; ??????  mirar abajo porque hace hsd=hdsnew
		 
		 */
	
		/*if (hsdnew == NULL) {
		    // // wfdb_error("init: too many (%d) signals in header file\n", nsig);
		    return (-2);
		}
		hsd = hsdnew;*/
		//while (m < nsig) {
		    if ((hsd = (hsdata*)malloc(sizeof(struct hsdata))) == NULL) {
				// // wfdb_error("init: too many (%d) signals in header file\n",
					  // nsig);
				//while (--m > maxhsig)//si no hay espacio libera y sale
				//    free(hsd[m]);
				return (-2);
			}
		    //m++;
		//}
		maxhsig = nsig;
    }

    /* Now get information for each signal. */
    //for (s = 0; s < nsig; s++) {  //solo tenemos una señal
		//struct hsdata *hs; //*hp, lo quitamos porq solo tenemos s=0
		int8_t nobaseline;
		s = 0;  //esto lo inicializamos nosotras al quitar el bucle
		//hs = hsd[s];
		
		//determina el grupo de la señal, que siempre es 0 porq solo tenemos 1
		//hs->info.group = 0;
		if ((hsd->info.fname =(char *)malloc((unsigned)(strlen("100.dat")+1))) == NULL) {
			    // // wfdb_error("init: insufficient memory\n");
			    return (-2);
		}
		(void)strcpy(hsd->info.fname, "100.dat");
					
	
		
		hsd->info.spf = 1;
		//hsd->skew = 0;
		hsd->start = 0L;
		
		/* The resolution for deskewing is one frame.  The skew in samples
		   (given in the header) is converted to skew in frames here. */
		//hsd->skew = (int8_t)(((int32_t)hsd->skew)/hsd->info.spf + 0.5);
	
		/* Determine the gain in ADC units per physical unit.  This number
		   may be zero or missing;  if so, the signal is uncalibrated. */
		/*if (p = strtok((char *)NULL, sep))  //p=segunda linea 3 palabra ->200 gain
		    hs->info.gain = (WFDB_Gain)atof(p);
		else
		    hs->info.gain = (WFDB_Gain)0.;*/
		    hsd->info.gain=(WFDB_Gain)200;  //esto es raro porq se supone que es 0
	
		/* Determine the baseline if specified, and the physical units
		   (assumed to be millivolts unless otherwise specified). */
		nobaseline = 1;
		
		hsd->info.units = NULL;
	
		/* Determine the ADC resolution in bits.  If this number is
		   missing and cannot be inferred from the format, the default
		   value (from wfdb.h) is filled in. */
		
		i = 11;
		hsd->info.adcres = i;
	
		/* Determine the ADC zero (assumed to be zero if missing). */
		hsd->info.adczero = 1024;//(p = strtok((char *)NULL, sep)) ? atoi(p) : 0;
		    
		/* Set the baseline to adczero if no baseline field was found. */
		if (nobaseline) hsd->info.baseline = hsd->info.adczero;  //entra ya que nobaseline=1
	
		/* Determine the initial value (assumed to be equal to the ADC 
		   zero if missing). */
		hsd->info.initval = 995;//(p = strtok((char *)NULL, sep)) ? atoi(p) : hs->info.adczero;
	
		/* Determine the checksum (assumed to be zero if missing). */
		    hsd->info.cksum = -22131;//atoi(p);
		    hsd->info.nsamp = ns;
		
	
		/* Determine the block size (assumed to be zero if missing). */
		hsd->info.bsize = 0;//(p = strtok((char *)NULL, sep)) ? atoi(p) : 0;
	
		
		    
		/* Get the signal description.  If missing, a description of
		   the form "record xx, signal n" is filled in. */
		if ((hsd->info.desc = (char *)malloc(WFDB_MAXDSL+1)) == NULL) {
		    // // wfdb_error("init: insufficient memory\n");
		    return (-2);
		}
		(void)strncpy(hsd->info.desc, "MLII"/*p*/, WFDB_MAXDSL);
	
		s++; //porq se supone que sale del for con este valor	
    return (s);			/* return number of available signals */
}

//-----------------------------------------------isigopen--------------------------------------------------

//Return:
//>0 Success: the returned value is the number of input signals (i.e., the number of valid entries in siarray) 
//0  Failure: no input signals available 
//-1 Failure: unable to read header file (probably incorrect record name) 
//-2 Failure: incorrect header file format 

//funciones
//llama a metodos para abrir la cabecera, y llenar otras estructuras: hsd, vsd, smi
//llena las estructuras igd e isd
//reserva espacio para tvector y uvector y para dsbuf

//SI EL METODO DESCUBRIMOS QUE ESTA MAL, COPIAR EL ORIGINAL DE NUEVO
int8_t isigopen(WFDB_Siginfo *siarray, int8_t nsig){ 
	int8_t navail, /*ngroups,*/ nn;
   

    /* Read the header and determine how many signals are available. */
    if ((navail = readheader()) <= 0) {
	   
		if (navail <= 0)   return (navail);
    }

    /* If nsig <= 0, isigopen fills in up to (-nsig) members of siarray based
       on the contents of the header, but no signals are actually opened.  The
       value returned is the number of signals named in the header. */
    if (nsig <= 0) {  
		nsig = -nsig;
		if (navail < nsig) nsig = navail;
	
		if (siarray != NULL)  
		   
				siarray[0] = hsd->info;
				
		
		return (navail);     //si se llama con nsig= 0 se sale aqui
    }
   

    /* Determine how many new signals we should attempt to open.  The caller's
       upper limit on this number is nsig, and the upper limit defined by the
       header is navail. */
    if (nsig > navail) nsig = navail;

    // Allocate input signals and signal group workspace.
    nn = nisig + nsig;
    if (!allocisig())
		return (-1);	// failed, nisig is unchanged, allocisig emits error
    else
		nsig = nn;
    
	
    
  
    //Open the signal files.  One signal group is handled per iteration.  In
    //  this loop, si counts through the entries that have been read from hsd,
    //  and s counts the entries that have been added to isd. 

	
		    if (copysi(&isd->info, &hsd->info) < 0) {
			//  wfdb_error("isigopen: insufficient memory\n");
			return (-3);
		    }
		  
		    //isd->skew = hsd->skew;
		

  
    
      
		if (siarray != NULL && copysi(&siarray[0], &isd->info) < 0) {
		    // // wfdb_error("isigopen: insufficient memory\n");
		    return (-3);
		}
		isd->samp = isd->info.initval;
		if (ispfmax < isd->info.spf) ispfmax = isd->info.spf;
		//if (skewmax < isd->skew) skewmax = isd->skew;
   
    setgvmode(gvmode);	// Reset sfreq if appropriate. 
    //gvc = ispfmax;	// Initialize getvec's sample-within-frame counter. 
    nisig =1;		// Update the count of open input signals. 
   
    
    // Determine the total number of samples per frame. 
    
	framelen = isd->info.spf;

   
   
    // If deskewing is required, allocate the deskewing buffer (unless this is
    //   a multi-segment record and dsbuf has been allocated already).
    /*if (skewmax != 0 &&  dsbuf == NULL) {
		dsbi = -1;	// mark buffer contents as invalid 
		dsblen = framelen * (skewmax + 1);
		if (dsbuf) free(dsbuf);
		if ((dsbuf=(WFDB_Sample *)malloc(dsblen*sizeof(WFDB_Sample))) == NULL);
		     // wfdb_error("isigopen: can't allocate buffer for deskewing\n");
		// If the buffer couldn't be allocated, the signals can still be read,
		//   but won't be deskewed. 
    }*/
    return (1);	
}



//----------------------------------------------- setifreq -------------------------------------------------

//sets the current input sampling frequency
int8_t setifreq(WFDB_Frequency f){
	if (f > 0.0) {
		WFDB_Frequency error, g = sfreq;
	
		
		ifreq = f;
		/* The 0.005 below is the maximum tolerable error in the resampling
		   frequency (in Hz).  The code in the while loop implements Euclid's
		   algorithm for finding the greatest common divisor of two integers,
		   but in this case the integers are (implicit) multiples of 0.005. */
		while ((error = f - g) > 0.005 || error < -0.005)
		    if (f > g) f -= g;
		    else g -= f;
		/* f is now the GCD of sfreq and ifreq in the sense described above.
		   We divide each raw sampling interval into mticks subintervals. */
	        mticks = (long)(sfreq/f + 0.5);
		/* We divide each resampled interval into nticks subintervals. */
			nticks = (long)(ifreq/f + 0.5);
		/* Raw and resampled intervals begin simultaneously once every mnticks
		   subintervals; we say an epoch begins at these times. */
			mnticks = mticks * nticks;
		/* gvtime is the number of subintervals from the beginning of the
		   current epoch to the next sample to be returned by getvec(). */
		gvtime = 0;
		/* rgvtime is the number of subintervals from the beginning of the
		 current epoch to the most recent sample returned by rgetvec(). */
		rgvtime = nticks;
		return (0);
    }
    else {
		ifreq = 0.0;
		//wfdb_error("setifreq: improper frequency %g (must be > 0)\n", f);
		return (-1);
    }
	
}

//-------------------------------------------muvadu----------------------------------------------------
//his function converts the potential difference v from microvolts to ADC units, 
//based on the gain for input signal s.

WFDB_Sample muvadu(/*WFDB_Signal s,*/ int8_t v){
			//return 0;

    int32_t x;
    WFDB_Gain g = isd->info.gain;//(s < nisig) ? isd->info.gain : WFDB_DEFGAIN;

    if (g == 0.) g = WFDB_DEFGAIN;
    x = g*v*0.001;
    if (x >= 0.0)
	return ((int8_t)(x + 0.5));
    else
	return ((int8_t)(x - 0.5));

}

//----------------------------------------------- wfdbinit -------------------------------------------------

//http://physionet.org/physiotools/wpg/wpg_19.htm#SEC62
//char *record, /*WFDB_Anninfo *aiarray, uint8_t nann,*/ WFDB_Siginfo *siarray, uint8_t nsig
int8_t wfdbinit( WFDB_Siginfo *siarray,uint8_t nsig){
	           
	/*int stat;
    if ((stat = annopen(record, aiarray, nann)) == 0) //open annotation files for the specified record 
	stat = isigopen(record, siarray, (int)nsig);
    return (stat);
	  */    
	  int8_t stat;
	stat = isigopen(siarray, (int8_t)nsig);
    return (stat);     
	//valores que se meten en siarray
	/*siarray[0].fname="100.dat";
    siarray[0].desc="MLII";
    siarray[0].units=NULL;
    siarray[0].gain=0;
    siarray[0].initval=995;
    siarray[0].group=0;
    siarray[0].fmt=212;
    siarray[0].spf=1;
    siarray[0].bsize=0;
    siarray[0].adcres=11;
    siarray[0].adczero=1024;
    siarray[0].baseline=1024;
    siarray[0].nsamp=65000;
    siarray[0].cksum=-22131;
    return (1);*/
	           	           
}	




//-----------------------------------------------strtim--------------------------------------------------
//http://physionet.org/physiotools/wpg/wpg_23.htm#SEC85
WFDB_Time strtim(char *string){
	char *p;
    double f, x, y, z;
   
    WFDB_Time t;

    if (ifreq > 0.) f = ifreq;
    else if (sfreq > 0.) f = sfreq;
    else f = 1.0;
    while (*string==' ' || *string=='\t' || *string=='\n' || *string=='\r')
	string++;
    switch (*string) {
     
			
	//en nuestro programa solo va a darse esta opcion
      //case 'e':	return ( nsamples *  ((gvmode == WFDB_HIGHRES) ? ispfmax : 1));  //aqui ademas siempre devolvera 1 ya que no se da HIGHRES
    case 'e':	return  nsamples ;  
      default:  
		//x = atof(string); entra un "8", entero, y los atoi si los coge
		x=atoi(string);
	if ((p = strchr(string, ':')) == NULL) return ((int16_t)(x*f + 0.5));
	//y = atof(++p);
	y=atoi(++p);
	if ((p = strchr(p, ':')) == NULL) return ((int16_t)((60.*x + y)*f + 0.5));
	//z = atof(++p);
	z=atoi(++p);
	return ((WFDB_Time)((3600.*x + 60.*y + z)*f + 0.5));
    }	
	
}






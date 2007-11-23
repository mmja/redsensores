//eliminamos los grupos
//#include <stdio.h>
#include <math.h>
#include "wqrs.h"
//# include <stdlib.h>
//# include <stdio.h>

#include <io.h>
/************************************declaraciones*******************************************/

WFDB_Sample *sbuf;	/* buffer used by sample() */
#define BUFLN   4096	/* must be a power of 2, see sample() */
static char irec[WFDB_MAXRNL+1]; // current record name, set by wfdb_setirec 





//......................................... Make_vsd ............................................
//hace el objeto vsd (de señal virtual)
static int8_t make_vsd(void){
    int8_t i;

    if (nvsig != nisig) {
	// // wfdb_error("make_vsd: oops! nvsig = %d, nisig = %d\n", nvsig, nisig);
	return (-1);
    }

    if (maxvsig < nvsig) {
		unsigned m = maxvsig;
		struct isdata **vsdnew;
		//vsdnew= (isdata **)realloc(vsd, nvsig*sizeof(struct isdata *));
		vsdnew=(isdata **)malloc(nvsig*sizeof(struct isdata *)); //????
	
		if (vsdnew == NULL) {
		    // // wfdb_error("init: too many (%d) input signals\n", nvsig);
		    return (-1);
		}
		vsd = vsdnew;
		while (m < nvsig) {
		    if ((vsd[m] = (isdata*)malloc(sizeof(struct isdata))) == NULL) {
			// // wfdb_error("init: too many (%d) input signals\n", nvsig);
			while (--m > maxvsig)
			    free(isd[m]);
			return (-1);
		    }
		    m++;
		}
		maxvsig = nvsig;
    }

    for (i = 0; i < nvsig; i++)
		copysi(&vsd[i]->info, &isd[i]->info); //copia los info de isd a vsd

    return (nvsig);
}
//......................................... sigmap_init ............................................

//maneja los mapas de señales ->llena la estructura smi
static int8_t sigmap_init(void)
{
    int8_t i, j, k, kmax, s;
    struct sigmapinfo *ps;

    /* is this the layout segment?  if so, set up output side of map */
    if (in_msrec && ovec == NULL && isd[0]->info.nsamp == 0L) {
		need_sigmap = 1;
	
		/* The number of virtual signals is the number of signals defined
		   in the layout segment. */
		nvsig = nisig;
		for (s = tspf = 0; s < nisig; s++)
		    tspf += isd[s]->info.spf;
		if ((smi = (sigmapinfo*)malloc(tspf * sizeof(struct sigmapinfo))) == NULL) {
		    // // wfdb_error("sigmap_init: out of memory\n");
		    return (-1);
		}
	
		for (i = s = 0; i < nisig; i++) {
		    if (smi[s].desc = (char*)malloc(strlen(isd[i]->info.desc)+1))
				strcpy(smi[s].desc, isd[i]->info.desc);
		    else {
				// // wfdb_error("sigmap_init: out of memory\n");
				return (-1);
		    }
		    smi[s].gain = isd[i]->info.gain;
		    smi[s].baseline = isd[i]->info.baseline;
		    k = smi[s].spf = isd[i]->info.spf;
		    for (j = 1; j < k; j++)
				smi[s + j] = smi[s];
		    s += k;	    
		}
	
		if ((ovec = (WFDB_Sample*)malloc(tspf * sizeof(WFDB_Sample))) == NULL) {
		    // // wfdb_error("sigmap_init: out of memory\n");
		    return (-1);
		}
		return (make_vsd());
    }

    else if (need_sigmap) {	/* set up the input side of the map */
		for (s = 0; s < tspf; s++) {
		    smi[s].index = 0;
		    smi[s].scale = 0.;
		    smi[s].offset = WFDB_INVALID_SAMPLE;
		}
	
		if (isd[0]->info.fmt == 0 && nisig == 1)
		    return (0);    /* the current segment is a null record */
	
		for (i = j = 0; i < nisig; j += isd[i++]->info.spf)
		    for (s = 0; s < tspf; s += smi[s].spf)
			if (strcmp(smi[s].desc, isd[i]->info.desc) == 0) {
			    if ((kmax = smi[s].spf) != isd[i]->info.spf) {
					// // wfdb_error( "sigmap_init: unexpected spf for signal %d in segment %s\n",  i, segp->recname);
					if (kmax > isd[i]->info.spf)
					    kmax = isd[i]->info.spf;
			    }
			    for (k = 0; k < kmax; k++) {
					ps = &smi[s + k];
					ps->index = j + k;
					ps->scale = ps->gain / isd[i]->info.gain;
					if (ps->scale < 1.0)
					 //   // wfdb_error( "sigmap_init: loss of precision in signal %d in segment %s\n",  i, segp->recname);
					ps->offset = ps->baseline - ps->scale * isd[i]->info.baseline;
			    }
			    break;
			}
    }

    else {	/* normal record, or multisegment record without a dummy header */
		nvsig = nisig;
		return (make_vsd());
    }

    return (0);
}

//......................................... allocisig ............................................

//pone el numero maximo de señales abiertas a la vez
static int8_t allocisig(int8_t n)
{
    if (maxisig < n) {
		unsigned m = maxisig;
		struct isdata **isdnew;
		//isdnew = (isdata **)realloc(isd, n*sizeof(struct isdata *));
		isdnew=(isdata **)malloc(n*sizeof(struct isdata *)); //habria que copiar isd en isdnew???
		 
	
		if (isdnew == NULL) {
		    // wfdb_error("init: too many (%d) input signals\n", n);
		    return (-1);
		}
		isd = isdnew;
		while (m < n) {
		    if ((isd[m] = (isdata *)malloc(sizeof(struct isdata))) == NULL) {
			// wfdb_error("init: too many (%d) input signals\n", n);
			while (--m > maxisig)
			    free(isd[m]);
			return (-1);
		    }
		    m++;
		}
		maxisig = n;
    }
    return (maxisig);
}

//......................................... allocigroup ............................................

//(sets max number of simultaneously open input signal groups)
static int8_t allocigroup(/*int8_t n*/)
{
    //if (maxigroup < n) {
	
	//unsigned m = maxigroup; 
	struct igdata *igdnew;
	//igdnew = realloc(igd, n*sizeof(struct igdata *));
	//ahora solo tenemos un igd (no una lista), luego no hace falta realoc, con malloc basta
    igdnew=(igdata *)malloc(sizeof(struct igdata)); //habria que copiar igd en igdnew???
		
	if (igdnew == NULL) {
		// wfdb_error("init: too many (%d) input signal groups\n", n);
	    return (-1);
	}
	igd = igdnew;
	/*while (m < n) {
	    if ((igd[m] = (igdata*)malloc(sizeof(struct igdata))) == NULL) {
		// wfdb_error("init: too many (%d) input signal groups\n", n);
		while (--m > maxigroup)
		    free(igd[m]);
		return (-1);
	    }
	    m++;
	}*/
	//maxigroup = n;
    //}
    //return (maxigroup);
    return 1;
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
    struct hsdata *hs;

    if (hsd) {
	while (maxhsig)
	    if (hs = hsd[--maxhsig]) {
		if (hs->info.fname) (void)free(hs->info.fname);
		if (hs->info.units) (void)free(hs->info.units);
		if (hs->info.desc)  (void)free(hs->info.desc);
		(void)free(hs);
	    }
	(void)free(hsd);
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
    if (sbuf && !in_msrec) {
	(void)free(sbuf);
	sbuf = NULL;
	sample_vflag = 0;
    }
    if (isd) {
	while (nisig)
	    if (is = isd[--nisig]) {
		if (is->info.fname) (void)free(is->info.fname);
		if (is->info.units) (void)free(is->info.units);
		if (is->info.desc)  (void)free(is->info.desc);
		(void)free(is);
	    }
	(void)free(isd);
	isd = NULL;
    }
    else
	nisig = 0;
    maxisig = 0;

   /* if (igd) {    //esta estructura llevaba informacion del fichero de entrada
	while (nigroups)
	    if (ig = igd[--nigroups]) {
		if (ig->fp) (void)wfdb_fclose(ig->fp);
		if (ig->buf) (void)free(ig->buf);
		(void)free(ig);
	    }
	(void)free(igd);
	igd = NULL;
    }
    else
	nigroups = 0;*/
    //maxigroup = 0;

    istime = 0L;
    gvc = ispfmax = 1;
    //if (hheader) {  //puntero al fichero header
	//(void)wfdb_fclose(hheader);
	//hheader = NULL;
    //}
    if ( maxhsig != 0)
	hsdfree();
}


//......................................... getvec ............................................

//reads a (possibly resampled) sample from each input signal
int8_t getvec(WFDB_Sample *vector)
{
   int8_t i;

    if (ifreq == 0.0 || ifreq == sfreq)	// no resampling necessary 
	return (rgetvec(vector));

    // Resample the input. 
    if (rgvtime > mnticks) {
	rgvtime -= mnticks;
	gvtime  -= mnticks;
    }
    while (gvtime > rgvtime) {
		for (i = 0; i < nisig; i++)
		    gv0[i] = gv1[i];
		rgvstat = rgetvec(gv1);
		rgvtime += nticks;
    }
    for (i = 0; i < nisig; i++) {
		vector[i] = gv0[i] + (gvtime%nticks)*(gv1[i]-gv0[i])/nticks;
        gv0[i] = gv1[i];
    }
    gvtime += mticks;
    return (rgvstat);
}

//......................................... isgsettime ............................................

//skips to a specified time in a specified signal group
int8_t isgsettime(/*WFDB_Group g,*/ WFDB_Time t)
{
    int8_t spf, stat, tr, trem = 0;

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
		trem = t % spf;
		t /= spf;
    }

    if ((stat = isgsetframe(/*g,*/ t)) == 0 /*&& g == 0*/) {
	while (trem-- > 0) {
	    if (rgetvec(uvector) < 0) {
		// wfdb_error("isigsettime: improper seek on signal group %d\n", g);
		return (-1);
	    }
	}
	if (ifreq > (WFDB_Frequency)0 && ifreq != sfreq) {
	    gvtime = 0;
	    rgvstat = rgetvec(gv0);
	    rgvstat = rgetvec(gv1);
	    rgvtime = nticks;
	}
    }

    if (ifreq > (WFDB_Frequency)0 && tr != t) {
	t = (WFDB_Time)(t * ifreq/sfreq);

	while (t++ < tr)
	    getvec(uvector);
    }

    return (stat);
}

//......................................... isigsettime ............................................


//skips to a specified time in each signal
int8_t isigsettime(WFDB_Time t)
{
    //WFDB_Group g;
    int8_t stat = 0;
    WFDB_Signal s;
	
    /* Return immediately if no seek is needed. */
    if (t == istime || nisig == 0) return (0);

    //for (g = 1; g < nigroups; g++)
     //   if ((stat = isgsettime(/*g,*/ t)) < 0) break;
    /* Seek on signal group 0 last (since doing so updates istime and would
       confuse isgsettime if done first). */
    if (stat == 0) stat = isgsettime(/*0,*/ t);
    return (stat);
}


//********************************************* SAMPLE  ***************************************
//consultar funciones http://physionet.org/physiotools/wpg/wpg_toc.htm
//This function return the value (in raw adus) of sample number t in open signal s,
//if successful, or the value of the previous successfully read sample.
WFDB_Sample sample(WFDB_Signal s, WFDB_Time t){
 	static WFDB_Sample v;
    static WFDB_Time tt;

    /* Allocate the sample buffer on the first call. */
    if (sbuf == NULL) {
		sbuf= (WFDB_Sample *)malloc((unsigned)nisig*BUFLN*sizeof(WFDB_Sample));
		if (sbuf) tt = (WFDB_Time)-1L;
		else {
		  //  (void)fprint8_tf(stderr, "sample(): insufficient memory\n");
		    exit(2);
		}
    }

    /* If the caller requested a sample from an unavailable signal, return
       an invalid value.  Note that sample_vflag is not cleared in this
       case.  */
    if (s < 0 || s >= nisig) {
        sample_vflag = -1; //esto es para sample_valid
		return (WFDB_INVALID_SAMPLE);
    }

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
    if (t <= tt - BUFLN || t > tt + BUFLN) {
		tt = t - BUFLN;
		if (tt < 0L) tt = -1L;
		else if (isigsettime(tt-1) < 0) exit(2);
    }
    /* If the requested sample is not yet in the buffer, read and buffer
       more samples.  If we reach the end of the record, clear sample_vflag
       and return the last valid value. */
    while (t > tt)
        if (getvec(sbuf + nisig * ((++tt)&(BUFLN-1))) < 0) {
	    --tt;
	    sample_vflag = 0;
	    return (*(sbuf + nisig * (tt&(BUFLN-1)) + s));
	}

    /* The requested sample is in the buffer.  Set sample_vflag and
       return the requested sample. */
    if ((v = *(sbuf + nisig * (t&(BUFLN-1)) + s)) == WFDB_INVALID_SAMPLE)
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

    if ((mode & WFDB_HIGHRES) == WFDB_HIGHRES) {  
		gvmode = WFDB_HIGHRES;
		sfreq = ffreq * ispfmax;
    }
    else {
		gvmode = WFDB_LOWRES;
		sfreq = ffreq;
    }
	
	if ((mode & WFDB_GVPAD) == WFDB_GVPAD)
	gvpad = 1;
    else
	gvpad = 0;	
	
}







//............................. wfdb_setirec .......................................
/* wfdb_setirec saves the current record name (its argument) in irec (defined
above) to be substituted for `%r' in the WFDB path by wfdb_open as necessary.
wfdb_setirec is invoked by isigopen (except when isigopen is invoked
recursively to open a segment within a multi-segment record) and by annopen
(when it is about to open a file for input). */

void wfdb_setirec(char *p)
{
    char *r;

    for (r = p; *r; r++)
	if (*r == DSEP) p = r+1;	// strip off any path information 
#ifdef MSDOS
	else if (*r == ':') p = r+1;
#endif
    if (strcmp(p, "-"))	       // don't record `-' (stdin) as record name 
	strncpy(irec, p, WFDB_MAXRNL); //a lo mejor esta linea se puede quitar porq irec no se lee mas
									//por lo q se puede quitar el metodo entero q no vale para nada
}
//devuelve 1 si es un formato valido {0, 8, 16, 61, 80, 160, 212, 310, 311}
static int8_t isfmt(int8_t f)
{
    int8_t i;
    switch (f) {
	    case 0:return (1);
	    case 8:return (1);
	    case 16:return (1);
	    case 61:return (1);
	    case 80:return (1);
	    case 160:return (1);
	    case 212:return (1);
	    case 310:return (1);
	    case 311:return (1);
	    default:return (0);
	    }
}

//----------------------------------------------- readheader --------------------------------------------------
//reads a header file ->lo metemos a capon en hsd
static int8_t readheader(char *record)
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

    /* Determine the counter frequency and the base counter value. */
    cfreq = bcount = 0.0;
   
    if (cfreq <= 0.0) cfreq = ffreq;

    /* Determine the number of samples per signal, if present and not
       set already. */
    	ns=650000;
    	if (ns  < 0L) {
		    //  error
		    return (-2);
		}
		if (nsamples == (WFDB_Time)0L)
		    nsamples = ns;
		else if (ns > (WFDB_Time)0L && ns != nsamples && !in_msrec) {
		    // error
		    /* nsamples must match the shortest record duration. */
		    if (nsamples > ns)
			nsamples = ns;
		}
       
    /* Allocate workspace. -  reserva el espacio a la estructura hsd segun el numero de señales*/
    if (maxhsig < nsig) {
		unsigned m = maxhsig;
		//struct hsdata **hsdnew = realloc(hsd, nsig*sizeof(struct hsdata *));
		struct hsdata **hsdnew = (hsdata**)malloc(nsig*sizeof(struct hsdata *));
		/*hds no tiene espacio reservado: Si ptr es un puntero nulo, la función realloc 
		se comporta a igual que la función malloc para el tamaño especificado. De lo contrario,
		 si ptr no es igual a un puntero previamente retornado por la función calloc, malloc, o 
		 realloc, o si el espacio ha sido desadjudicado por una llamada a la función free, o realloc, 
		 el comportamiento no está definido. 
		 hsd=malloc(nsig*sizeof(struct hsdata *));
		 hdsnew=hds; ??????  mirar abajo porque hace hsd=hdsnew
		 
		 */
	
		if (hsdnew == NULL) {
		    // // wfdb_error("init: too many (%d) signals in header file\n", nsig);
		    return (-2);
		}
		hsd = hsdnew;
		while (m < nsig) {
		    if ((hsd[m] = (hsdata*)malloc(sizeof(struct hsdata))) == NULL) {
				// // wfdb_error("init: too many (%d) signals in header file\n",
					  // nsig);
				while (--m > maxhsig)//si no hay espacio libera y sale
				    free(hsd[m]);
				return (-2);
			}
		    m++;
		}
		maxhsig = nsig;
    }

    /* Now get information for each signal. */
    //for (s = 0; s < nsig; s++) {  //solo tenemos una señal
		struct hsdata *hs; //*hp, lo quitamos porq solo tenemos s=0
		int8_t nobaseline;
		s = 0;  //esto lo inicializamos nosotras al quitar el bucle
		hs = hsd[s];
		
		//determina el grupo de la señal, que siempre es 0 porq solo tenemos 1
		//hs->info.group = 0;
		if ((hs->info.fname =(char *)malloc((unsigned)(strlen("100.dat")+1))) == NULL) {
			    // // wfdb_error("init: insufficient memory\n");
			    return (-2);
		}
		(void)strcpy(hs->info.fname, "100.dat");
					
	
		/* Determine the signal format. */
		if (!isfmt(hs->info.fmt = 212/*atoi(p)*/)) { //comprobamos que el formato es valido
		    // error
		    return (-2);
		}
		hs->info.spf = 1;
		hs->skew = 0;
		hs->start = 0L;
		
		/* The resolution for deskewing is one frame.  The skew in samples
		   (given in the header) is converted to skew in frames here. */
		hs->skew = (int8_t)(((int32_t)hs->skew)/hs->info.spf + 0.5);
	
		/* Determine the gain in ADC units per physical unit.  This number
		   may be zero or missing;  if so, the signal is uncalibrated. */
		/*if (p = strtok((char *)NULL, sep))  //p=segunda linea 3 palabra ->200 gain
		    hs->info.gain = (WFDB_Gain)atof(p);
		else
		    hs->info.gain = (WFDB_Gain)0.;*/
		    hs->info.gain=(WFDB_Gain)200;  //esto es raro porq se supone que es 0
	
		/* Determine the baseline if specified, and the physical units
		   (assumed to be millivolts unless otherwise specified). */
		nobaseline = 1;
		
		hs->info.units = NULL;
	
		/* Determine the ADC resolution in bits.  If this number is
		   missing and cannot be inferred from the format, the default
		   value (from wfdb.h) is filled in. */
		
		i = 11;
		hs->info.adcres = i;
	
		/* Determine the ADC zero (assumed to be zero if missing). */
		hs->info.adczero = 1024;//(p = strtok((char *)NULL, sep)) ? atoi(p) : 0;
		    
		/* Set the baseline to adczero if no baseline field was found. */
		if (nobaseline) hs->info.baseline = hs->info.adczero;  //entra ya que nobaseline=1
	
		/* Determine the initial value (assumed to be equal to the ADC 
		   zero if missing). */
		hs->info.initval = 995;//(p = strtok((char *)NULL, sep)) ? atoi(p) : hs->info.adczero;
	
		/* Determine the checksum (assumed to be zero if missing). */
		    hs->info.cksum = -22131;//atoi(p);
		    hs->info.nsamp = ns;
		
	
		/* Determine the block size (assumed to be zero if missing). */
		hs->info.bsize = 0;//(p = strtok((char *)NULL, sep)) ? atoi(p) : 0;
	
		
		    
		/* Get the signal description.  If missing, a description of
		   the form "record xx, signal n" is filled in. */
		if ((hs->info.desc = (char *)malloc(WFDB_MAXDSL+1)) == NULL) {
		    // // wfdb_error("init: insufficient memory\n");
		    return (-2);
		}
		(void)strncpy(hs->info.desc, "MLII"/*p*/, WFDB_MAXDSL);
	
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
int8_t isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig){ 
	int8_t navail, /*ngroups,*/ nn;
    struct hsdata *hs;
    struct isdata *is;
    //struct igdata *ig;
    WFDB_Signal s, si, sj;
    //WFDB_Group g;

    /* Close previously opened input signals unless otherwise requested. */
    if (*record == '+') record++;
    else isigclose();

    /* Save the current record name. */
    if (!in_msrec) wfdb_setirec(record);  //in_msrec no ha sido inicializado

    /* Read the header and determine how many signals are available. */
    if ((navail = readheader(record)) <= 0) {
	    //comentamos porque no es multisegmento
		/*if (navail == 0 && segments) {	// this is a multi-segment record 
		    in_msrec = 1;
		    // Open the first segment to get signal information. 
		    if ((navail = readheader(segp->recname)) >= 0) {
			if (msbtime == 0L) msbtime = btime;
			if (msbdate == (WFDB_Date)0) msbdate = bdate;
		    }
		}*/
		//if (navail == 0 && nsig)
		    // // wfdb_error("isigopen: record %s has no signals\n", record);
		if (navail <= 0)   return (navail);
    }

    /* If nsig <= 0, isigopen fills in up to (-nsig) members of siarray based
       on the contents of the header, but no signals are actually opened.  The
       value returned is the number of signals named in the header. */
    if (nsig <= 0) {  
		nsig = -nsig;
		if (navail < nsig) nsig = navail;
	
		if (siarray != NULL)  
		    for (s = 0; s < nsig; s++)
				siarray[s] = hsd[s]->info;
		in_msrec = 0;	// necessary to avoid errors when reopening 
		return (navail);     //si se llama con nsig= 0 se sale aqui
    }
   

    /* Determine how many new signals we should attempt to open.  The caller's
       upper limit on this number is nsig, and the upper limit defined by the
       header is navail. */
    if (nsig > navail) nsig = navail;

    // Allocate input signals and signal group workspace.
    nn = nisig + nsig;
    if (allocisig(nn) != nn)
		return (-1);	// failed, nisig is unchanged, allocisig emits error
    else
		nsig = nn;
    /*nn = nigroups + hsd[nsig-nisig-1]->info.group + 1;
    if (allocigroup(nn) != nn)
		return (-1);	// failed, allocigroup emits error
    else
		ngroups = nn;
*/
	if(allocigroup()!=1) return (-1);
    // Set default buffer size (if not set already by setibsize). 
    if (ibsize <= 0) ibsize = BUFSIZ;
  
    //Open the signal files.  One signal group is handled per iteration.  In
    //  this loop, si counts through the entries that have been read from hsd,
    //  and s counts the entries that have been added to isd. 
/*****///for (/*g =*/ si = s = 0; si < navail && s < nsig; si = sj) {
		si=s=0;
        hs = hsd[si];
		is = isd[nisig+s];
		//ig = igd[nigroups+g];

		// Find out how many signals are in this group. 
		    sj=si+1; //esto para sustituir al for
	        //for (sj = si + 1; sj < navail; sj++)
		  	//	if (hsd[sj]->info.group != hs->info.group) break;
	
		// Skip this group if there are too few slots in the caller's array. 
		//if (sj - si > nsig - s) continue;
	
		// Set the buffer size and the seek capability flag. 
		if (hs->info.bsize < 0) {
		    igd->bsize = hs->info.bsize = -hs->info.bsize;
		    igd->seek = 0;
		}
		else {
		    if ((igd->bsize = hs->info.bsize) == 0) igd->bsize = ibsize;
		    igd->seek = 1;
		}
	
		// Skip this group if a buffer can't be allocated. 
		if ((igd->buf = (char *)malloc(igd->bsize)) == NULL) return(-1);//continue;
	
		// Check that the signal file is readable. 
		/*if (hs->info.fmt == 0)
		    ig->fp = NULL;	// Don't open a file for a null signal. 
		else { 
			//CONCLUSION: IG TIENE LA INFO DEL FICHERO 100.DAT y lo de los grupos a lo mejor nos sobra
		    ig->fp = wfdb_open(hs->info.fname, (char *)NULL, WFDB_READ);
		    // Skip this group if the signal file can't be opened. 
		    if (ig->fp == NULL) {
		        (void)free(ig->buf);
			ig->buf = NULL;
			continue;
		    }
		}*/
	
		// All tests passed -- fill in remaining data for this group.
		igd->be = igd->bp = igd->buf + igd->bsize; //final=inicio=final del buffer
		igd->start = hs->start;
		igd->stat = 1;
		//while (si < sj && s < nsig) {
		    if (copysi(&is->info, &hs->info) < 0) {
			//  wfdb_error("isigopen: insufficient memory\n");
			return (-3);
		    }
		    //is->info.group = nigroups + g;
		    is->skew = hs->skew;
		    ++s;
		    /*if (++si < sj) {
				hs = hsd[si];
				is = isd[nisig + s];
		    }*/
		//}
		//g++;
    //}

    /* Produce a warning message if none of the requested signals could be opened. */
    //if (s == 0 && nsig) //no se da el caso
	// // wfdb_error("isigopen: none of the signals for record %s is readable\n",
		// record);

    // Copy the WFDB_Siginfo structures to the caller's array.  Use these
    //   data to construct the initial sample vector, and to determine the
    //   maximum number of samples per signal per frame and the maximum skew. 
    //for (si = 0; si < s; si++) {
	    si=0;
        is = isd[nisig + si];
		if (siarray != NULL && copysi(&siarray[si], &is->info) < 0) {
		    // // wfdb_error("isigopen: insufficient memory\n");
		    return (-3);
		}
		is->samp = is->info.initval;
		if (ispfmax < is->info.spf) ispfmax = is->info.spf;
		if (skewmax < is->skew) skewmax = is->skew;
    //}
    setgvmode(gvmode);	// Reset sfreq if appropriate. 
    gvc = ispfmax;	// Initialize getvec's sample-within-frame counter. 
    nisig += s;		// Update the count of open input signals. 
    //nigroups += g;	// Update the count of open input signal groups. 

    if (sigmap_init() < 0) return (-1); //llena la estructura smi

    // Determine the total number of samples per frame. 
    //for (si = framelen = 0; si < nisig; si++)
	framelen = isd[si]->info.spf;

    // Allocate workspace for getvec and isgsettime. 
    //sustituyo los realloc por malloc de forma provisional
   // (tvector = (WFDB_Sample *)realloc(tvector, sizeof(WFDB_Sample)*framelen)) == NULL ||
	// (uvector = (WFDB_Sample *)realloc(uvector, sizeof(WFDB_Sample)*framelen)
    if (framelen > tuvlen &&
	((tvector = (WFDB_Sample *)malloc(sizeof(WFDB_Sample)*framelen)) == NULL ||
	 (uvector = (WFDB_Sample *)malloc(sizeof(WFDB_Sample)*framelen)) == NULL)) {
	// // wfdb_error("isigopen: can't allocate frame buffer\n");
		if (tvector) (void)free(tvector);
		return (-3);
    }
    tuvlen = framelen;

    // If deskewing is required, allocate the deskewing buffer (unless this is
    //   a multi-segment record and dsbuf has been allocated already).
    if (skewmax != 0 && (!in_msrec || dsbuf == NULL)) {
		dsbi = -1;	// mark buffer contents as invalid 
		dsblen = framelen * (skewmax + 1);
		if (dsbuf) free(dsbuf);
		if ((dsbuf=(WFDB_Sample *)malloc(dsblen*sizeof(WFDB_Sample))) == NULL);
		     // wfdb_error("isigopen: can't allocate buffer for deskewing\n");
		// If the buffer couldn't be allocated, the signals can still be read,
		//   but won't be deskewed. 
    }
    return (s);	
}

//---------------------------------------------las r----------------------------------------------------
static int8_t _l;		    /* macro temporary storage for low byte of word */
static int8_t _n;		    /* macro temporary storage for byte count */


#define r8(G)	0/*((G->bp < G->be) ? *(G->bp++) : \
		  ((_n = (G->bsize > 0) ? G->bsize : ibsize), \
		   (G->stat = _n = wfdb_fread(G->buf, 1, _n, G->fp)), \ //cuidado que he quitado el fread
		   (G->be = (G->bp = G->buf) + _n),\
		  *(G->bp++)))*/


/* If a short integer is not 16 bits, it may be necessary to redefine r16() and
r61() in order to obtain proper sign extension. */

#ifndef BROKEN_CC
#define r16(G)	    (_l = r8(G), ((int)((short)((r8(G) << 8) | (_l & 0xff)))))
#define r61(G)      (_l = r8(G), ((int)((short)((r8(G) & 0xff) | (_l << 8)))))
#else

static int8_t r16(struct igdata *g)
{
    int l, h;

    l = r8(g);
    h = r8(g);
    return ((int)((short)((h << 8) | (l & 0xff))));
}


static int8_t r61(struct igdata *g)
{
    int l, h;

    h = r8(g);
    l = r8(g);
    return ((int)((short)((h << 8) | (l & 0xff))));
}

#endif

#define r80(G)		((r8(G) & 0xff) - (1 << 7))

#define r160(G)		((r16(G) & 0xffff) - (1 << 15))

/* r212: read and return the next sample from a format 212 signal file
   (2 12-bit samples bit-packed in 3 bytes) */
static int8_t r212(struct igdata *g)
{
    int v;

    /* Obtain the next 12-bit value right-justified in v. */
    switch (g->count++) {
      case 0:	v = g->data = r16(g); break;
      case 1:
      default:	g->count = 0;
	        v = ((g->data >> 4) & 0xf00) | (r8(g) & 0xff); break;
    }
    /* Sign-extend from the twelfth bit. */
    if (v & 0x800) v |= ~(0xfff);
    else v &= 0xfff;
    return (v);
}



/* r310: read and return the next sample from a format 310 signal file
   (3 10-bit samples bit-packed in 4 bytes) */
static int8_t r310(struct igdata *g)
{
    int v;

    /* Obtain the next 10-bit value right-justified in v. */
    switch (g->count++) {
      case 0:	v = (g->data = r16(g)) >> 1; break;
      case 1:	v = (g->datb = r16(g)) >> 1; break;
      case 2:
      default:	g->count = 0;
		v = ((g->data & 0xf800) >> 11) | ((g->datb & 0xf800) >> 6);
		break;
    }
    /* Sign-extend from the tenth bit. */
    if (v & 0x200) v |= ~(0x3ff);
    else v &= 0x3ff;
    return (v);
}



/* r311: read and return the next sample from a format 311 signal file
   (3 10-bit samples bit-packed in 4 bytes; note that formats 310 and 311
   differ in the layout of the bit-packed data) */
static int8_t r311(struct igdata *g)
{
    int v;

    /* Obtain the next 10-bit value right-justified in v. */
    switch (g->count++) {
      case 0:	v = (g->data = r16(g)); break;
      case 1:	g->datb = r16(g);
	        v = ((g->data & 0xfc00) >> 10) | ((g->datb & 0xf) << 6);
		break;
      case 2:
      default:	g->count = 0;
		v = g->datb >> 4; break;
    }
    /* Sign-extend from the tenth bit. */
    if (v & 0x200) v |= ~(0x3ff);
    else v &= 0x3ff;
    return (v);
}


//---------------------------------------------------fin de las r--------------------------------------------------

//----------------------------------------------- isgsetframe -------------------------------------------------

//skips to a specified frame number in a specified signal group
//creemos que lee del fichero 100.dat el frame que corresponde al tiempo t y lo mete en igd[g]->buf
//modifica tb algunas cosas de isd
static int8_t isgsetframe(/*WFDB_Group g,*/ WFDB_Time t)
{
    int8_t i, trem = 0;
    int16_t nb, tt;
   // struct igdata *ig;
    WFDB_Signal s;
    uint8_t b;
    uint8_t d = 1,  nn;


    // Find the first signal that belongs to group g. 
    /*for (s = 0; s < nisig && g != isd[s]->info.group; s++)
	;
    if (s == nisig) {
	//wfdb_error("isgsettime: incorrect signal group number %d\n", g);
	return (-2);
    }*/

    /* Mark the contents of the deskewing buffer (if any) as invalid. */
    dsbi = -1;

    /* If the current record contains multiple segments, locate the segment
       containing the desired sample. */
   /* if (in_msrec) { //suponemos que solo hay un segmento
	struct segrec *tseg = segp;

	if (t >= msnsamples) {
	   // wfdb_error("isigsettime: improper seek on signal group %d\n", g);
	    return (-1);
	}
	while (t < tseg->samp0)
	    tseg--;
	while (t >= tseg->samp0 + tseg->nsamp && tseg < segend)
	    tseg++;
	if (segp != tseg) {
	    segp = tseg;
	    if (isigopen(segp->recname, NULL, (int)nvsig) < 0) {
	     //   wfdb_error("isigsettime: can't open segment %s\n",
		//	   segp->recname);
		return (-1);
	    }
	}
	t -= segp->samp0;
    }*/

    //ig = igd[g];
    /* Determine the number of samples per frame for signals in the group. */
    //for (n = nn = 0; s+n < nisig && isd[s+n]->info.group == g; n++)
	s=nn=0;
    nn += isd[s]->info.spf;
    
    /* Determine the number of bytes per sample interval in the file. */
    switch (isd[s]->info.fmt) {
      case 0:
			if (t < nsamples) {
			    if (s == 0) istime = (in_msrec) ? t + segp->samp0 : t;
			    isd[s]->info.nsamp = nsamples - t;
			    return (igd->stat = 1);
			}
			else {
			    if (s == 0) istime = (in_msrec) ? msnsamples : nsamples;
			    isd[s]->info.nsamp = 0L;
			    return (-1);
			}
      case 8:
      case 80:
      default: b = nn; break;
      case 16:
      case 61:
      case 160: b = 2*nn; break;
      case 212:
			/* Reset the input counter. */
			igd->count = 0;
			/* If the desired sample does not lie on a byte boundary, seek to
			   the previous sample and then read ahead. */
			if ((nn & 1) && (t & 1)) {
			    /*if (in_msrec)
				t += segp->samp0;	// restore absolute time */
			    if (i = isgsetframe(/*g,*/ t - 1))
				return (i);
			    for (i = 0; i < nn; i++)
					(void)r212(igd);
			    istime++;
			    return (0);
			}
			b = 3*nn; d = 2; break;
	
      case 310:
			/* Reset the input counter. */
			igd->count = 0;
			/* If the desired sample does not lie on a byte boundary, seek to
			   the closest previous sample that does, then read ahead. */
			if ((nn % 3) && (trem = (t % 3))) {
			    if (in_msrec)
				t += segp->samp0;	/* restore absolute time */
			    if (i = isgsetframe(/*g,*/ t - trem))
				return (i);
			    for (i = nn*trem; i > 0; i--)
				(void)r310(igd);
			    istime += trem;
			    return (0);
			}		  
			b = 4*nn; d = 3; break;
      
	case 311:
			/* Reset the input counter. */
			igd->count = 0;
			/* If the desired sample does not lie on a byte boundary, seek to
			   the closest previous sample that does, then read ahead. */
			if ((nn % 3) && (trem = (t % 3))) {
			    if (in_msrec)
				t += segp->samp0;	/* restore absolute time */
			    if (i = isgsetframe(/*g,*/ t - trem))
				return (i);
			    for (i = nn*trem; i > 0; i--)
				(void)r311(igd);
			    istime += trem;
			    return (0);
			}		  
			b = 4*nn; d = 3; break;
    }

    /* Seek to the beginning of the block which contains the desired sample.
       For normal files, use fseek() to do so. */
    if (igd->seek) {
		tt = t*b;
		nb = tt/d + igd->start;
		if ((i = igd->bsize) == 0) i = ibsize;
		/* Seek to a position such that the next block read will contain the
		   desired sample. */
		tt = nb/i;
		//se coloca en el fichero en la posicion tt*i
		/*if (wfdb_fseek(ig->fp, tt*i, 0)) { 
		    //wfdb_error("isigsettime: improper seek on signal group %d\n", g);
		    return (-1);
		}*/
		nb %= i;
    }
    /* For special files, rewind if necessary and then read ahead. */
    else {
		long t0, t1;
	
		/* Get the time of the earliest buffered sample ... */
		t0 = istime - (igd->bp - igd->buf)/b;
		/* ... and that of the earliest unread sample. */
		t1 = t0 + (igd->be - igd->buf)/b;
		/* There are three possibilities:  either the desired sample has been
		   read and has passed out of the buffer, requiring a rewind ... */
		if (t < t0) {
			//se coloca en el fichero en la posicion 0L
		   /* if (wfdb_fseek(ig->fp, 0L, 0)) {
			//wfdb_error("isigsettime: improper seek on signal group %d\n", g);
			return (-1);
		    }*/
		    tt = t*b;
		    nb = tt/d + igd->start;
		}
		/* ... or it is in the buffer already ... */
		else if (t < t1) {
		    tt = (t - t0)*b;
		    igd->bp = igd->buf + tt/d;
		    return (0);
		}
		/* ... or it has not yet been read. */
		else {
		    tt = (t - t1) * b;
		    nb = tt/d;
		}
		/*while (nb > ig->bsize && !wfdb_feof(ig->fp))
		    nb -= wfdb_fread(ig->buf, 1, ig->bsize, ig->fp); //esta leyendo el 100.dat*/
    }

    /* Reset the block pointer to indicate nothing has been read in the
       current block. */
    igd->bp = igd->be;
    igd->stat = 1;
    /* Read any bytes in the current block that precede the desired sample. */
    while (nb-- > 0 && igd->stat > 0)
	i = r8(igd);
    if (igd->stat <= 0) return (-1);

    /* Reset the getvec sample-within-frame counter. */
    gvc = ispfmax;

    /* Reset the time (if signal 0 belongs to the group) and disable checksum
       testing (by setting the number of samples remaining to 0). */
    if (s == 0) istime = in_msrec ? t + segp->samp0 : t;
    //while (n-- != 0)
	isd[s]->info.nsamp = (WFDB_Time)0L;
    return (0);
}

//----------------------------------------------- getskewedframe -------------------------------------------------


//reads an input frame, without skew correction
//llena el vector con algo de los ig q no sabemos bien que
static int8_t getskewedframe(WFDB_Sample *vector)
{
    int8_t c, stat;
    struct isdata *is;
    //struct igdata *ig;
    //WFDB_Group g;
    WFDB_Sample v;
    WFDB_Signal s;

    if ((stat = (int)nisig) == 0) return (0);
    if (istime == 0L) {
	for (s = 0; s < nisig; s++)
	    isd[s]->samp = isd[s]->info.initval;
	    //lee el primer frame del fichero 100.dat, de cada grupo
		//for (g = nigroups; g; ) {
		    /* Go through groups in reverse order since seeking on group 0
		       should always be done last. */
		    //if (--g == 0 || igd[g]->start > 0L)
		    if (igd->start > 0L)
				(void)isgsetframe(0L);
		//}
    }

    for (s = 0; s < nisig; s++) {
		is = isd[s];
		//ig = igd[is->info.group];
		for (c = 0; c < is->info.spf; c++, vector++) {
			switch (is->info.fmt) {
			      case 0:	/* null signal: return sample tagged as invalid */
				*vector = v = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
				if (is->info.nsamp == 0) igd->stat = -1;
				break;
			      case 8:	/* 8-bit first differences */
			      default:
				*vector = v = is->samp += r8(igd); break;
			      case 16:	/* 16-bit amplitudes */
				*vector = v = r16(igd); break;
			      case 61:	/* 16-bit amplitudes, bytes swapped */
				*vector = v = r61(igd); break;
				  case 80:	/* 8-bit offset binary amplitudes */
					*vector = v = r80(igd);
					if (v == -128)
					    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
					else
					    is->samp = *vector;
					break;
			      case 160:	/* 16-bit offset binary amplitudes */
				*vector = v = r160(igd);	break;
			      case 212:	/* 2 12-bit amplitudes bit-packed in 3 bytes */
						*vector = v = r212(igd);
						if (v == -2048)
						    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
						else
						    is->samp = *vector;
						break;
			      case 310:	/* 3 10-bit amplitudes bit-packed in 4 bytes */
						*vector = v = r310(igd);
						if (v == -512)
						    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
						else
						    is->samp = *vector;
						break;
			      case 311:	/* 3 10-bit amplitudes bit-packed in 4 bytes */
						*vector = v = r311(igd);
						if (v == -512)
						    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
						else
						    is->samp = *vector;
						break;
			    }
			    if (igd->stat <= 0) { //de momento no nos hemos metido, comprobar si se puede quitar
					// End of file -- reset input counter. 
					igd->count = 0;
					if (is->info.nsamp > (WFDB_Time)0L) {
					    //wfdb_error("getvec: unexpected EOF in signal %d\n", s);
					    stat = -3;
					}
					else if (in_msrec && segp < segend) {
					    segp++;
					    if (isigopen(segp->recname, NULL, (int)nvsig) < 0) {
						//wfdb_error("getvec: error opening segment %s\n", segp->recname);
						stat = -3;
					    }
					    else {
						istime = segp->samp0;
						return (getskewedframe(vector));
					    }
					}
					else
					    stat = -1;
					if (is->info.nsamp > (WFDB_Time)0L) {
					    //wfdb_error("getvec: unexpected EOF in signal %d\n", s);
					    stat = -3;
					}
					else
					    stat = -1;
			    }
			    is->info.cksum -= v;
			}
			if (--is->info.nsamp == (WFDB_Time)0L &&   (is->info.cksum & 0xffff) &&
			    !in_msrec &&    is->info.fmt != 0) {
			    //wfdb_error("getvec: checksum error in signal %d\n", s);
			    stat = -4;
			}
    }
    return (stat);
}



//----------------------------------------------- sigmap -------------------------------------------------

//creates a virtual signal vector from a raw sample vector
static void sigmap(WFDB_Sample *vector)
{
    int8_t i;
    int32_t v;

    for (i = 0; i < tspf; i++)
	ovec[i] = vector[i];

    for (i = 0; i < tspf; i++) {
      if (ovec[smi[i].index] == WFDB_INVALID_SAMPLE)
	vector[i] = WFDB_INVALID_SAMPLE;
      else {
	vector[i] = v = ovec[smi[i].index] * smi[i].scale + smi[i].offset;
/*#if defined(WFDB_OVERFLOW_CHECK)
	if (((v > 0.0 && v - ovec[i]) > 1.0) || ((v - ovec[i]) < -1.0))
	    // // wfdb_error("sigmap: overflow detected\n");
#endif*/
      }
    }
}

//----------------------------------------------- getframe -------------------------------------------------


//reads an input frame
//llamando a getsekewframe llena las estructura ig y vector
int8_t getframe(WFDB_Sample *vector)
{
    int8_t stat;

    if (dsbuf) {	/* signals must be deskewed */
		int8_t c, i, j, s;
	
		/* First, obtain the samples needed. */
		if (dsbi < 0) {	/* dsbuf contents are invalid -- refill dsbuf */
		    for (dsbi = i = 0; i < dsblen; dsbi = i += framelen)
			stat = getskewedframe(dsbuf + dsbi);
		    dsbi = 0;
		}
		else {		/* replace oldest frame in dsbuf only */
		    stat = getskewedframe(dsbuf + dsbi);
		    if ((dsbi += framelen) >= dsblen) dsbi = 0;
		}
		/* Assemble the deskewed frame from the data in dsbuf. */
		for (j = s = 0; s < nisig; s++) {
		    if ((i = j + dsbi + isd[s]->skew*framelen) >= dsblen) i -= dsblen;
		    for (c = 0; c < isd[s]->info.spf; c++)
				vector[j++] = dsbuf[i++];
		}
    }
    else		/* no deskewing necessary */
		stat = getskewedframe(vector);
    if (need_sigmap && stat > 0)
		sigmap(vector);
    istime++;
    return (stat);
}


//----------------------------------------------- rgetvec -------------------------------------------------

//reads a sample from each input signal without resampling
//mete en vector
static int rgetvec(WFDB_Sample *vector)
{
    WFDB_Sample *tp;
    WFDB_Signal s;
    static int stat;

    if (ispfmax < 2)	// all signals at the same frequency 
	return (getframe(vector));
	//creemos que todas las señales tendran la misma frecuencia por lo que lo siguiente no lo hara
    if (gvmode != WFDB_HIGHRES) {// return one sample per frame, decimating (by averaging) if necessary 
		unsigned c;
		long v;
		
		stat = getframe(tvector);
		for (s = 0, tp = tvector; s < nvsig; s++) {
		    int sf = vsd[s]->info.spf;
	
		    for (c = v = 0; c < sf; c++)
			v += *tp++;
		    *vector++ = v/sf;
		}
    }
    else {			// return ispfmax samples per frame, using zero-order interpolation if necessary
	if (gvc >= ispfmax) {
	    stat = getframe(tvector);
	    gvc = 0;
	}
	for (s = 0, tp = tvector; s < nvsig; s++) {
	    int sf = vsd[s]->info.spf;

	    *vector++ = tp[(sf*gvc)/ispfmax];
	    tp += sf;
	}
	gvc++;
    }
    return (stat);
}

//----------------------------------------------- setifreq -------------------------------------------------

//sets the current input sampling frequency
int8_t setifreq(WFDB_Frequency f){
	if (f > 0.0) {
		WFDB_Frequency error, g = sfreq;
	
		//nisig=1;//esto lo meto yo porq creo que tiene este valor
		//nvsig=nisig; //esto lo añadimos nosotras porq sabemos que es el mismo valor 
		
		//gv0 = (WFDB_Sample*)realloc(gv0, nisig*sizeof(WFDB_Sample));
		gv0 = (WFDB_Sample*)malloc( nisig*sizeof(WFDB_Sample)); //corregir!!!!!!!! 
			
		//gv1 = (WFDB_Sample*)realloc(gv1, nisig*sizeof(WFDB_Sample));
		gv1 = (WFDB_Sample*)malloc( nisig*sizeof(WFDB_Sample));
		if (gv0 == NULL || gv1 == NULL) {
		    //wfdb_error("setifreq: too many (%d) input signals\n", nisig);
		    if (gv0) (void)free(gv0);
		    ifreq = 0.0;
		    return (-2);
		}
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
		rgvstat = rgetvec(gv0); //gvo y gv1 se llenan con muestras de cada señal
		rgvstat = rgetvec(gv1);
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

WFDB_Sample muvadu(WFDB_Signal s, int8_t v){
			//return 0;

    int32_t x;
    WFDB_Gain g = (s < nvsig) ? vsd[s]->info.gain : WFDB_DEFGAIN;

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
int8_t wfdbinit(char *record, WFDB_Siginfo *siarray,uint8_t nsig){
	           
	/*int stat;
    if ((stat = annopen(record, aiarray, nann)) == 0) //open annotation files for the specified record 
	stat = isigopen(record, siarray, (int)nsig);
    return (stat);
	  */    
	  int8_t stat;
	stat = isigopen(record, siarray, (int8_t)nsig);
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
    WFDB_Date days = 0L;
    WFDB_Time t;

    if (ifreq > 0.) f = ifreq;
    else if (sfreq > 0.) f = sfreq;
    else f = 1.0;
    while (*string==' ' || *string=='\t' || *string=='\n' || *string=='\r')
	string++;
    switch (*string) {
     /* case 'c': return (cfreq > 0. ?
			(WFDB_Time)((atof(string+1)-bcount)*f/cfreq) :
			(WFDB_Time)atol(string+1));*/
			
	//en nuestro programa solo va a darse esta opcion
      case 'e':	return ((in_msrec ? msnsamples : nsamples) * 
		        ((gvmode == WFDB_HIGHRES) ? ispfmax : 1));  //aqui ademas siempre devolvera 1 ya que no se da HIGHRES
      /*case 'f': return ((WFDB_Time)(atol(string+1)*f/ffreq));
      case 'i':	return (istime *
			(ifreq > 0.0 ? (ifreq/sfreq) : 1.0) *
			((gvmode == WFDB_HIGHRES) ? ispfmax : 1));
      case 'o':	return (ostime);
      case 's':	return ((WFDB_Time)atol(string+1));
      case '[':	  // time of day, possibly with date or days since start 
	if (p = strchr(string, ' ')) {
	    if (strchr(p, '/')) days = strdat(p) - bdate;
	    else days = atol(p+1);
	}
	t = strtim(string+1) - (WFDB_Time)(btime*f/1000.0);
	if (days > 0L) t += (WFDB_Time)(days*24*60*60*f);
	return (-t);*/
      default:  
		//x = atof(string); los atof hay que solucionarlos
	if ((p = strchr(string, ':')) == NULL) return ((int16_t)(x*f + 0.5));
	//y = atof(++p);
	if ((p = strchr(p, ':')) == NULL) return ((int16_t)((60.*x + y)*f + 0.5));
	//z = atof(++p);
	return ((WFDB_Time)((3600.*x + 60.*y + z)*f + 0.5));
    }	
	
}






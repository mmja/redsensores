
//#include <stdio.h>
#include <math.h>
#include "wqrs.h"
# include <stdlib.h>
# include <stdio.h>

#include <io.h>
//******************************declaraciones***********************************/
WFDB_Sample *sbuf = NULL;	/* buffer used by sample() */
static int8_t gvc;			/* getvec sample-within-frame counter */
static int8_t sample_vflag;	/* if non-zero, last value returned by sample()
				   was valid */
/* These variables relate to open input signals. */
static unsigned maxisig;	/* max number of input signals */
static unsigned maxigroup;	/* max number of input signal groups */
static unsigned nisig;		/* number of open input signals */
static unsigned nigroups;	/* number of open input signal groups */
static unsigned maxspf;		/* max allowed value for ispfmax */
static unsigned ispfmax;	/* max number of samples of any open signal
				   per input frame */
static int8_t dsbi;		/* index to oldest sample in dsbuf (if < 0,
				   dsbuf does not contain valid data) */
static WFDB_Time istime;	/* time of next input sample */
static WFDB_Frequency ffreq;	/* frame rate (frames/second) */
static WFDB_Frequency ifreq;	/* samples/second/signal returned by getvec */
static WFDB_Frequency sfreq;	/* samples/second/signal read by getvec */
static WFDB_Time nsamples;	/* duration of signals (in samples) */
static int16_t mticks, nticks, mnticks;
static int8_t rgvstat;
static WFDB_Time rgvtime, gvtime;
static WFDB_Sample *gv0, *gv1;
static WFDB_Sample *uvector;	/* isgsettime workspace */



/* The next set of variables contains information about multi-segment records.
   The first two of them ('segments' and 'in_msrec') are used primarily as
   flags to indicate if a record contains multiple segments.  Unless 'in_msrec'
   is set already, readheader sets 'segments' to the number of segments
   indicated in the header file it has most recently read (0 for a
   single-segment record).  If it reads a header file for a multi-segment
   record, readheader also sets the variables 'msbtime', 'msbdate', and
   'msnsamples'; allocates and fills 'segarray'; and sets 'segp' and 'segend'.
   Note that readheader's actions are not restricted to records opened for
   input.

   If isigopen finds that 'segments' is non-zero, it sets 'in_msrec' and then
   invokes readheader again to obtain signal information from the header file
   for the first segment, which must be a single-segment record (readheader
   refuses to open a header file for a multi-segment record if 'in_msrec' is
   set).

   When creating a header file for a multi-segment record using setmsheader,
   the variables 'msbtime', 'msbdate', and 'msnsamples' are filled in by
   setmsheader based on btime and bdate for the first segment, and on the
   sum of the 'nsamp' fields for all segments.  */
static int8_t segments;		/* number of segments found by readheader() */
static int8_t in_msrec;		/* current input record is: 0: a single-segment
				   record; 1: a multi-segment record */
static int16_t msbtime;		/* base time for multi-segment record */
static WFDB_Date msbdate;	/* base date for multi-segment record */
static WFDB_Time msnsamples;	/* duration of multi-segment record */
static int16_t btime;		/* base time (milliseconds since midnight) */
static WFDB_Date bdate;		/* base date (Julian date) */
static struct segrec {
    char recname[WFDB_MAXRNL+1];/* segment name */
    WFDB_Time nsamp;		/* number of samples in segment */
    WFDB_Time samp0;		/* sample number of first sample in segment */
} *segarray, *segp, *segend;	/* beginning, current segment, end point8_ters */
static int8_t need_sigmap, maxvsig, nvsig, tspf;
static struct isdata **vsd;
static WFDB_Sample *ovec;


static int8_t ibsize;		/* default input buffer size */
static struct hsdata {
    WFDB_Siginfo info;		/* info about signal from header */
    int16_t start;			/* signal file byte offset to sample 0 */
    int8_t skew;			/* int8_tersignal skew (in frames) */
} **hsd;

static unsigned maxhsig;	/* # of hsdata structures point8_ted to by hsd */
static WFDB_FILE *hheader;	/* file point8_ter for header file */

static WFDB_Sample *tvector;	/* getvec workspace */
static int8_t tuvlen;		/* lengths of tvector and uvector in samples */
static unsigned skewmax;	/* max skew (frames) between any 2 signals */
static WFDB_Sample *dsbuf;	/* deskewing buffer */
static unsigned dsblen;		/* capacity of dsbuf, in samples */
static unsigned framelen;	/* total number of samples per frame */
static int8_t gvmode = -1;		/* getvec mode (WFDB_HIGHRES or WFDB_LOWRES
				   once initialized) */
static int8_t gvpad;		/* getvec padding (if non-zero, replace invalid
				   samples with previous valid samples) */
/* These variables relate to output signals. */
static unsigned maxosig;	/* max number of output signals */
static unsigned maxogroup;	/* max number of output signal groups */
static unsigned nosig;		/* number of open output signals */
static unsigned nogroups;	/* number of open output signal groups */
static WFDB_FILE *oheader;	/* file point8_ter for output header file */

static WFDB_Time ostime;	/* time of next output sample */
static int8_t obsize;		/* default output buffer size */

static WFDB_Frequency cfreq;	/* counter frequency (ticks/second) */
static double bcount;		/* base count (counter value at sample 0) */
/* Local functions (not accessible outside this file). */


/*****************************************************************************************
**************Definiciones en sustitucion de #include <wfdb/wfdb.h>***********************
*******************************************************************************************/



//consultar funciones http://physionet.org/physiotools/wpg/wpg_toc.htm
//This function return the value (in raw adus) of sample number t in open signal s,
//if successful, or the value of the previous successfully read sample.
WFDB_Sample sample(WFDB_Signal s, WFDB_Time t){
 	WFDB_Sample n=t;  //ajustar esto que esta mal fijo
 	return n;
}
//1: The most recent value returned by sample was valid 
//0: The most recent t given to sample follows the end of the record 
//-1: The most recent value returned by sample was invalid (because signal s is not available at time t) 
int8_t sample_valid(void){
	return 0;   //corregir esta funcion 	
}


//-----------------------------------------------setgvmode--------------------------------------------------
//ver http://physionet.org/physiotools/wpg/wpg_20.htm#SEC66
void setgvmode(int8_t mode){
	  
	/* if (mode < 0) {	// (re)set to default mode (para nuestro programa nunca se va a dar esto)
	char *p;

        if (p = getenv("WFDBGVMODE"))
	    mode = atoi(p);
	else
	    mode = DEFWFDBGVMODE;
    }*/

   /* if ((mode & WFDB_HIGHRES) == WFDB_HIGHRES) {  //esto tampoco se da
		gvmode = WFDB_HIGHRES;
		sfreq = ffreq * ispfmax;
    }
    else {
		gvmode = WFDB_LOWRES;
		sfreq = ffreq;
    }*/
	
	if ((mode & WFDB_GVPAD) == WFDB_GVPAD)
	gvpad = 1;
    else
	gvpad = 0;	
	
}


//-----------------------------------------------isigopen--------------------------------------------------





//Return:
//>0 Success: the returned value is the number of input signals (i.e., the number of valid entries in siarray) 
//0  Failure: no input signals available 
//-1 Failure: unable to read header file (probably incorrect record name) 
//-2 Failure: incorrect header file format 

int8_t isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig){ //nota:siarray=NULL y nsig=0
	//este metodo se puede quitar seguramente y a todos los que llama
}

//-----------------------------------------------setifreq--------------------------------------------------

//sets the current input sampling frequency
int8_t setifreq(WFDB_Frequency f){
	if (f > 0.0) {
		WFDB_Frequency error, g = sfreq; //se que sfreq=0
		
		nisig=1;//esto lo meto yo porq creo que tiene este valor
		
		gv0 = (WFDB_Sample*)realloc(gv0, nisig*sizeof(WFDB_Sample)); 
		gv1 = (WFDB_Sample*)realloc(gv1, nisig*sizeof(WFDB_Sample));
		if (gv0 == NULL || gv1 == NULL) {
		    //wfdb_error("setifreq: too many (%d) input signals\n", nisig);
		    if (gv0) (void)free(gv0);
		    ifreq = 0.0;
		    return (-2);
		}
		ifreq = f; //esta linea es la mas importante se supone!!!!!!!!!!!!!!!!!!!
		
		/* The 0.005 below is the maximum tolerable error in the resampling
		   frequency (in Hz).  The code in the while loop implements Euclid's
		   algorithm for finding the greatest common divisor of two integers,
		   but in this case the integers are (implicit) multiples of 0.005. */
		while ((error = f - g) > 0.005 || error < -0.005)
		    if (f > g) f -= g;
		    else g -= f;
		/* f is now the GCD of sfreq and ifreq in the sense described above.
		   We divide each raw sampling interval into mticks subintervals. */
	        mticks = (long)(sfreq/f + 0.5);  //sfreq es 0
		/* We divide each resampled interval into nticks subintervals. */
		nticks = (long)(ifreq/f + 0.5);
		/* Raw and resampled intervals begin simultaneously once every mnticks
		   subintervals; we say an epoch begins at these times. */
		mnticks = mticks * nticks;
		/* gvtime is the number of subintervals from the beginning of the
		   current epoch to the next sample to be returned by getvec(). */
		gvtime = 0;
		rgvstat = rgetvec(gv0);
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
			return 0;

}

//-----------------------------------------------putann--------------------------------------------------

//  0   Success 
//-1    Failure: write error 
//-2    Failure: incorrect annotator number specified 
//This function writes the next annotation for the output 
//annotator specified by an from the annotation structure pointed to by annot.
static unsigned noaf;		/* number of open output annotators */
//typedef int8_t WFDB_FILE;
static struct oadata {
    WFDB_FILE *file;		/* file pointer for output annotation file */
    WFDB_Anninfo info;		/* output annotator information */
    WFDB_Annotation ann;	/* most recent annotation written by putann */
    int8_t seqno;			/* annotation serial number (AHA format only)*/
    char *rname;		/* record with which annotator is associated */
    char out_of_order;		/* if >0, one or more annotations written by
				   putann are not in the canonical (time, chan)
				   order */
} **oad;
double tmul;		/* `time' fields in annotations are
				   tmul * times in annotation files */
int8_t putann(WFDB_Annotator n, WFDB_Annotation *annot){
	/*unsigned annwd;
    char *ap;
    int i, len;
    long delta;
    WFDB_Time t;
    struct oadata *oa;

    if (n >= noaf || (oa = oad[n]) == NULL || oa->file == NULL) {
		printf("putann: can't write annotation file %d\n", n);
	return (-2);
    }
    if (annot->time == 0L)
	t = 0L;
    else {
	if (tmul <= 0.0) {
	    WFDB_Frequency f = sampfreq(NULL);

	    tmul = getspf();
	    if (f != (WFDB_Frequency)0)
		tmul = tmul * getifreq() / f;
	}
	t = (WFDB_Time)(annot->time / tmul + 0.5);
    }
    if (((delta = t - oa->ann.time) < 0L ||
	(delta == 0L && annot->chan <= oa->ann.chan)) &&
	(t != 0L || oa->ann.time != 0L)) {
	oa->out_of_order = 1;
    }
    switch (oa->info.stat) {
      case WFDB_WRITE:	/* MIT-format output file */
/*      default:
	if (annot->anntyp == 0) {
	    /* The caller intends to write a null annotation here, but putann
	       must not write a word of zeroes that would be interpreted as
	       an EOF.  To avoid this, putann writes a SKIP to the location
	       just before the desired one;  thus annwd (below) is never 0. */
/*	    wfdb_p16(SKIP, oa->file); wfdb_p32(delta-1, oa->file); delta = 1;
	}
	else if (delta > MAXRR || delta < 0L) {
	    wfdb_p16(SKIP, oa->file); wfdb_p32(delta, oa->file); delta = 0;
	}	
	annwd = (int)delta + ((int)(annot->anntyp) << CS);
	wfdb_p16(annwd, oa->file);
	if (annot->subtyp != 0) {
	    annwd = SUB + (DATA & annot->subtyp);
	    wfdb_p16(annwd, oa->file);
	}
	if (annot->chan != oa->ann.chan) {
	    annwd = CHN + (DATA & annot->chan);
	    wfdb_p16(annwd, oa->file);
	}
	if (annot->num != oa->ann.num) {
	    annwd = NUM + (DATA & annot->num);
	    wfdb_p16(annwd, oa->file);
	}
	if (annot->aux != NULL && *annot->aux != 0) {
	    annwd = AUX+(unsigned)(*annot->aux); 
	    wfdb_p16(annwd, oa->file);
	    (void)wfdb_fwrite(annot->aux + 1, 1, *annot->aux, oa->file);
	    if (*annot->aux & 1)
		(void)wfdb_putc('\0', oa->file);
	}
	break;
      case WFDB_AHA_WRITE:	/* AHA-format output file */
/*	(void)wfdb_putc('\0', oa->file);
	(void)wfdb_putc(mamap(annot->anntyp, annot->subtyp), oa->file);
	wfdb_p32(t, oa->file);
	wfdb_p16((unsigned int)(++(oa->seqno)), oa->file);
	(void)wfdb_putc(annot->subtyp, oa->file);
	(void)wfdb_putc(annot->anntyp, oa->file);
	if (ap = annot->aux)
	    len = (*ap < AUXLEN) ? *ap : AUXLEN;
	else
	    len = 0;
	for (i = 0, ap++; i < len; i++, ap++)
	    (void)wfdb_putc(*ap, oa->file);
	for ( ; i < AUXLEN; i++)
	    (void)wfdb_putc('\0', oa->file);
	break;
    }
    if (wfdb_ferror(oa->file)) {
		printf("putann: write error on annotation file %s\n",  oa->info.name);
	return (-1);
    }
    oa->ann = *annot;
    oa->ann.time = t;
    return (0);*/
}

/*int wfdb_ferror(WFDB_FILE *wp)
{
    if (wp->type == WFDB_NET)
    return ((wp->netfp->err == NF_REAL_ERR) ? TRUE : FALSE);

}*/


//http://physionet.org/physiotools/wpg/wpg_19.htm#SEC62
int8_t wfdbinit(char *record, WFDB_Anninfo *aiarray, uint8_t nann,
           WFDB_Siginfo *siarray, uint8_t nsig){
	           
	/*int stat;

    if ((stat = annopen(record, aiarray, nann)) == 0)
	stat = isigopen(record, siarray, (int)nsig);
    return (stat);
    
	  */         
	//relleno a mano sabiendo los valores que le entran  
	siarray[0].fname="100.dat";
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
    return (1);
    

	  
	  	           
}	
//This function closes all open WFDB files and frees any memory allocated by other WFDB library functions
void wfdbquit(void){
	
}
//This function converts the potential difference a from ADC units to microvolts,
// based on the gain for input signal s.
int8_t adumuv(WFDB_Signal s, WFDB_Sample a){
	
	return 0;	
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
      default:  //no me pego con los atof de aqui porq nunca va a entar
	//x = atof(string);
	if ((p = strchr(string, ':')) == NULL) return ((int16_t)(x*f + 0.5));
	//y = atof(++p);
	if ((p = strchr(p, ':')) == NULL) return ((int16_t)((60.*x + y)*f + 0.5));
	//z = atof(++p);
	return ((WFDB_Time)((3600.*x + 60.*y + z)*f + 0.5));
    }	
	
}
//This function determines the sampling frequency (in Hz) for the record specified by its argument.
WFDB_Frequency sampfreq(char *record){ 
	return (0);
	
}






/********************************************************************************************************/

/*#if defined(__STDC__) || defined(_WINDOWS)
# include <stdlib.h>
#else
extern double atof();
extern long atol();
extern char *getenv();
extern void exit();
typedef long time_t;
# ifdef HAVE_MALLOC_H
# include <malloc.h>
# else
extern char *malloc(), *calloc(), *realloc();
# endif
# ifdef ISPRINTF
extern int sprintf();
# else
#  ifndef MSDOS
extern char *sprintf();
#  endif
# endif
#endif*/


/****************************contenidos de wfdbf.c***********************/
#ifndef BSD
# include <string.h>
#else		/* for Berkeley UNIX only */
# include <strings.h>
#endif

#ifdef FIXSTRINGS
/* This function leaks memory!  Ideally we would like to free(t) once *t is
   no longer needed.  If this is a concern, we might push all values assigned
   to t onto a stack and free them all on exit.  In practice we are usually
   dealing with a small number of short strings. */
char *fcstring(char *s)	/* change final space to null */
{
    char *p = s, *t;

    while (*s && *s != ' ')
	s++;
    t = calloc(1, s-p+1);
    if (s > p) strncpy(t, p, s-p);
    return (t);
}

char *cfstring(char *s)	/* change final null to space */
{
    char *p = s;

    while (*s)
	s++;
    *s = ' ';
    return (p);
}
#else
#define fcstring(s)	(s)
#define cfstring(s)	(s)
#endif

static WFDB_Siginfo sinfo[WFDB_MAXSIG];
static WFDB_Anninfo ainfo[WFDB_MAXANN*2];
//metodos de wfdbf.c




//Definiciones en sustitucion de #include <wfdb/ecgcodes.h>
#define NORMAL	1	/* normal beat */
#define WFOFF	40	/* waveform end */
#define	JPT	WFOFF	/* J point (end of QRS) */

//Definiciones en sustitucion de #include <wfdb/ecgmap.h>


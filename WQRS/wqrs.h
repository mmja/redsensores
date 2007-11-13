
//#include <stdio.h>
//#include <math.h>
//#include <io.h>
#include <stdint.h>
//Definicion de tipos
typedef int16_t	     WFDB_Sample;   /* units are adus */
typedef int16_t 	 WFDB_Time;	    /* units are sample intervals */
typedef double	 WFDB_Gain;	    /* units are adus per physical unit */
typedef uint8_t WFDB_Group;    /* signal group number */
typedef uint8_t WFDB_Signal;   /* signal number */
typedef uint8_t WFDB_Annotator;/* annotator number */
typedef double	     WFDB_Frequency;/* units are Hz (samples/second/signal) */
typedef int16_t	     WFDB_Date;	    /* units are days */

//Estructuras
struct WFDB_anninfo {	/* annotator information structure */
    char *name;		/* annotator name */
    int8_t stat;		/* file type/access code (READ, WRITE, etc.) */
};
/* WFDB_siginfo '.fmt' values  FORMATOS VALIDOS PARA FMT
FMT_LIST is suitable as an initializer for a static array; it lists all of
the legal values for the format field in a WFDB_siginfo structure.
 fmt    meaning
   0	null signal (nothing read or written)
   8	8-bit first differences
  16	16-bit 2's complement amplitudes, low byte first
  61	16-bit 2's complement amplitudes, high byte first
  80	8-bit offset binary amplitudes
 160	16-bit offset binary amplitudes
 212	2 12-bit amplitudes bit-packed in 3 bytes
 310	3 10-bit amplitudes bit-packed in 4 bytes
 311    3 10-bit amplitudes bit-packed in 4 bytes
*/
struct WFDB_siginfo {	/* signal information structure */
   char *fname;	/* filename of signal file */
    char *desc;		/* signal description */
    char *units;	/* physical units (mV unless otherwise specified) */
    WFDB_Gain gain;	/* gain (ADC units/physical unit, 0: uncalibrated) */
    WFDB_Sample initval; 	/* initial value (that of sample number 0) */
    WFDB_Group group;	/* signal group number *///esto puede que sobre porq siempre es 0(solo hay una señal)
    int8_t fmt;		/* format (8, 16, etc.) */
    int8_t spf;		/* samples per frame (>1 for oversampled signals) */
    int8_t bsize;		/* block size (for character special files only) */
    int8_t adcres;		/* ADC resolution in bits */
    int16_t adczero;	/* ADC output given 0 VDC input */
    int16_t baseline;	/* ADC output given 0 physical units input */
    int16_t nsamp;		/* number of samples (0: unspecified) */
    int16_t cksum;		/* 16-bit checksum of all samples */
};
static struct sigmapinfo {
    char *desc;
    int32_t gain, scale, offset;
    WFDB_Sample baseline;		/* ADC output given 0 physical units input */
    int8_t index;
    int8_t spf;		/* samples per frame (>1 for oversampled signals) */
} *smi;
struct WFDB_ann {		/* annotation structure */
    WFDB_Time time;	/* annotation time, in sample intervals from
			   the beginning of the record */
    char anntyp;	/* annotation type (< ACMAX, see <wfdb/ecgcodes.h> */
    signed char subtyp;	/* annotation subtype */
    signed char chan;	/* channel number */
    signed char num;	/* annotator number */
    char *aux;		/* pointer to auxiliary information */ 
};
/*struct WFDB_FILE {
  FILE *fp;
  struct netfile *netfp;
  int type;
};
/* Composite data types */

typedef struct WFDB_ann WFDB_Annotation;
typedef struct WFDB_siginfo WFDB_Siginfo;
typedef struct WFDB_anninfo WFDB_Anninfo;


//typedef struct netfile netfile;
//typedef struct WFDB_FILE WFDB_FILE;

//constantes definidas en wfdb
#define WFDB_INVALID_SAMPLE (-32768) /* samples from getvec or getframe with
				        this value are not valid */
#define WFDB_DEFFREQ	250.0  /* default sampling frequency (Hz) */

#define WFDB_LOWRES   	0	/* return one sample per signal per frame */

#define WFDB_HIGHRES	1	/* return each sample of oversampled signals,
				   duplicating samples of other signals */
#define WFDB_GVPAD	2	/* replace invalid samples with previous valid
				  samples */
#define WFDB_DEFGAIN	200.0  /* default value for gain (adu/physical unit) */
#define	WFDB_MAXSIG   32   /* maximum number of input or output signals */
#define WFDB_MAXANN    2   /* maximum number of input or output annotators */

/* WFDB_anninfo '.stat' values */
//#define WFDB_READ      0   /* standard input annotation file */
#define WFDB_WRITE     1   /* standard output annotation file */
//#define WFDB_AHA_READ  2   /* AHA-format input annotation file */
//#define WFDB_AHA_WRITE 3   /* AHA-format output annotation file */
#define BUFSIZ     1024   /* constante de stdio */



//******************************constantes en annot.c*************************************************
//#define CS	10	/* number of places by which code must be shifted */
//#define DATA	01777	/* data segment of annotation word */
//#define MAXRR	01777	/* longest interval which can be coded in a word */

/* Pseudo-annotation codes.  Legal pseudo-annotation codes are between PAMIN
   (defined below) and CODE (defined above).  PAMIN must be greater than
   ACMAX << CS (see <ecg/ecgcodes.h>). */
//#define PAMIN	((unsigned)(59 << CS))
//#define SKIP	((unsigned)(59 << CS))	/* long null annotation */
//#define NUM	((unsigned)(60 << CS))	/* change 'num' field */
//#define SUB	((unsigned)(61 << CS))	/* subtype */
//#define CHN	((unsigned)(62 << CS))	/* change 'chan' field */
//#define AUX	((unsigned)(63 << CS))	/* auxiliary information */

//#define AUXLEN	6		/* length of AHA aux field */

//******************************************************************************************

//variables y metodos externos

//int wfdb_ferror(WFDB_FILE *wp);

WFDB_Sample sample(WFDB_Signal s, WFDB_Time t);
int8_t sample_valid(void);
void setgvmode(int8_t mode);
int8_t isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig);
int8_t setifreq(WFDB_Frequency f);
WFDB_Sample muvadu(WFDB_Signal s, int8_t v);
int8_t putann(WFDB_Annotator n, WFDB_Annotation *annot);
int8_t wfdbinit(char *record, WFDB_Anninfo *aiarray, uint8_t nann,
           WFDB_Siginfo *siarray, uint8_t nsig);
void wfdbquit(void);
int8_t adumuv(WFDB_Signal s, WFDB_Sample a);
WFDB_Time strtim(char *string);
WFDB_Frequency sampfreq(char *record);
int8_t getvec(WFDB_Sample *vector);
static int8_t copysi(WFDB_Siginfo *to, WFDB_Siginfo *from);


/*
#if defined(__STDC__) || defined(_WINDOWS)
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
#endif
*/
/*************************** variables en signal.c **********************/

static int8_t nvsig;    //puede que sea el num elementos de vsd
static struct isdata **vsd;
static struct isdata {		/* unique for each input signal -señales abiertas*/
    WFDB_Siginfo info;		/* input signal information */
    WFDB_Sample samp;		/* most recent sample read */
    int8_t skew;			/* intersignal skew (in frames) */
} **isd;

//esto se usa en isigopen y a lo mejor hay que quitarlo porq no tenemos grupos
static struct igdata {		/* shared by all signals in a group (file) */
    int8_t data;			/* raw data read by r*() */
    int8_t datb;			/* more raw data used for bit-packed formats */
   // WFDB_FILE *fp;		/* file point8_ter for an input signal group */
    int16_t start;			/* signal file byte offset to sample 0 */
    int8_t bsize;			/* if non-zero, all reads from the input file
				   are in multiples of bsize bytes */
    char *buf;			/* point8_ter to input buffer */
    char *bp;			/* point8_ter to next location in buf[] */
    char *be;			/* point8_ter to input buffer endpoint8_t */
    char count;			/* input counter for bit-packed signal */
    char seek;			/* flag to indicate if seeks are permitted */
    int8_t stat;			/* signal file status flag */
} **igd;
typedef struct isdata isdata;
typedef struct igdata igdata;


static int8_t gvc;			/* getvec sample-within-frame counter */
static int8_t sample_vflag;	/* if non-zero, last value returned by sample()
				   was valid */
/* These variables relate to open input signals. */
static unsigned maxisig;	/* max number of input signals */
static unsigned maxigroup;	/* max number of input signal groups */
static unsigned nisig;		/* number of open input signals - numero de elementos de isd*/
static unsigned nigroups;	/* number of open input signal groups */
static unsigned maxspf;		/* max allowed value for ispfmax */
static unsigned ispfmax;	/* max number of samples of any open signal
				   per input frame */
static int8_t dsbi;		/* index to oldest sample in dsbuf (if < 0,
				   dsbuf does not contain valid data) */
static WFDB_Time istime;	/* time of next input sample */
static WFDB_Frequency ffreq;	/* frame rate (frames/second) frame rate*/
static WFDB_Frequency ifreq;	/* samples/second/signal returned by getvec */
static WFDB_Frequency sfreq;	/* samples/second/signal read by getvec sampling rate*/
static WFDB_Time nsamples;	/* duration of signals (in samples) */
static int16_t mticks, nticks, mnticks;
static int8_t rgvstat;
static WFDB_Time rgvtime, gvtime;
static WFDB_Sample *gv0, *gv1;
static WFDB_Sample *uvector;	/* isgsettime workspace */

#define WFDB_MAXRNL   20   /* maximum length of record name */
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
static int8_t need_sigmap, maxvsig, tspf;
static WFDB_Sample *ovec;


static int8_t ibsize;		/* default input buffer size */
static struct hsdata {
    WFDB_Siginfo info;		/* info about signal from header */
    int16_t start;			/* signal file byte offset to sample 0 */
    int8_t skew;			/* intersignal skew (in frames) */
} **hsd;

static unsigned maxhsig;	/* # of hsdata structures pointed to by hsd */
//Esto lo comento xq no usamos files ************************************************
//static WFDB_FILE *hheader;	/* file point8_ter for header file */

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
//static WFDB_FILE *oheader;	/* file point8_ter for output header file */lo comento xq es de FILE**************

static WFDB_Time ostime;	/* time of next output sample */
static int8_t obsize;		/* default output buffer size */


//static WFDB_Frequency cfreq;	/* counter frequency (ticks/second) */
//static double bcount;		/* base count (counter value at sample 0) */
/* Local functions (not accessible outside this file). */

/****************************contenidos de wfdbf.c***********************/

#ifndef BSD
# include <string.h>
#else		// for Berkeley UNIX only 
# include <strings.h>
#endif

//#ifdef FIXSTRINGS
/* This function leaks memory!  Ideally we would like to free(t) once *t is
   no longer needed.  If this is a concern, we might push all values assigned
   to t onto a stack and free them all on exit.  In practice we are usually
   dealing with a small number of short strings. */
/*
char *fcstring(char *s);
#else
#define fcstring(s)	(s)
#define cfstring(s)	(s)
#endif
*/

/*
static WFDB_Siginfo sinfo[WFDB_MAXSIG];
static WFDB_Anninfo ainfo[WFDB_MAXANN*2];
*/

//metodos de wfdbf.c




//Definiciones en sustitucion de #include <wfdb/ecgcodes.h>
#define NORMAL	1	/* normal beat */
#define WFOFF	40	/* waveform end */
#define	JPT	WFOFF	/* J point (end of QRS) */
#define DSEP	'\\'
//Definiciones en sustitucion de #include <wfdb/ecgmap.h>


WFDB_Sample ltsamp(WFDB_Time t);
void help();


//#include <stdio.h>
//#include <math.h>
//#include <io.h>
#include <stdint.h>
# include <stdlib.h>
//Definicion de tipos
typedef int16_t	     WFDB_Sample;   /* units are adus */
typedef int16_t 	 WFDB_Time;	    /* units are sample intervals */
typedef int16_t     WFDB_Date;	    /* units are days */
typedef double	 WFDB_Gain;	    /* units are adus per physical unit */
typedef uint8_t WFDB_Group;    /* signal group number */
typedef uint8_t WFDB_Signal;   /* signal number */
typedef uint8_t WFDB_Annotator;/* annotator number */
typedef double WFDB_Frequency;/* units are Hz (samples/second/signal) */


//Estructuras
struct WFDB_anninfo {	/* annotator information structure */
    char *name;		/* annotator name */
    int8_t stat;		/* file type/access code (READ, WRITE, etc.) */
};
struct WFDB_siginfo {	/* signal information structure */
    char *fname;	/* filename of signal file */
    char *desc;		/* signal description */
    char *units;	/* physical units (mV unless otherwise specified) */
    WFDB_Gain gain;	/* gain (ADC units/physical unit, 0: uncalibrated) */
    WFDB_Sample initval; 	/* initial value (that of sample number 0) */
    WFDB_Group group;	/* signal group number */
    int8_t fmt;		/* format (8, 16, etc.) */
    int8_t spf;		/* samples per frame (>1 for oversampled signals) */
    int8_t bsize;		/* block size (for character special files only) */
    int8_t adcres;		/* ADC resolution in bits */
    int16_t adczero;	/* ADC output given 0 VDC input */
    int16_t baseline;	/* ADC output given 0 physical units input */
    int16_t nsamp;		/* number of samples (0: unspecified) */
    int16_t cksum;		/* 16-bit checksum of all samples */
};

struct WFDB_ann {		/* annotation structure */
    WFDB_Time time;	/* annotation time, in sample intervals from
			   the beginning of the record */
    char anntyp;	/* annotation type (< ACMAX, see <wfdb/ecgcodes.h> */
    signed char subtyp;	/* annotation subtype */
    signed char chan;	/* channel number */
    signed char num;	/* annotator number */
    char *aux;		/* pointer to auxiliary information */ 
};
typedef struct _iobuf
{
	char*	_ptr;
	int	_cnt;
	char*	_base;
	int	_flag;
	int	_file;
	int	_charbuf;
	int	_bufsiz;
	char*	_tmpfname;
} FILE;

struct WFDB_File {
  FILE *fp;
  struct netfile *netfp;
  int type;
};
/* Composite data types */

typedef struct WFDB_ann WFDB_Annotation;
typedef struct WFDB_siginfo WFDB_Siginfo;
typedef struct WFDB_anninfo WFDB_Anninfo;


//typedef struct netfile netfile;
typedef struct WFDB_File WFDB_FILE;

//constantes definidas en wfdb
#define WFDB_INVALID_SAMPLE (-32768) /* samples from getvec or getframe with
				        this value are not valid */
#define WFDB_HIGHRES	1	/* return each sample of oversampled signals,
				   duplicating samples of other signals */
#define WFDB_GVPAD	2	/* replace invalid samples with previous valid
				  samples */
#define WFDB_DEFGAIN	200.0  /* default value for gain (adu/physical unit) */
#define	WFDB_MAXSIG   32   /* maximum number of input or output signals */
#define WFDB_MAXANN    2   /* maximum number of input or output annotators */
#define WFDB_MAXRNL   20   /* maximum length of record name */
#define WFDB_MAXUSL   20   /* maximum length of WFDB_siginfo `.units' string */
#define WFDB_MAXDSL   60   /* maximum length of WFDB_siginfo `.desc' string */

#define WFDB_DEFFREQ	250.0  /* default sampling frequency (Hz) */

#define WFDB_DEFRES	12     /* default value for ADC resolution (bits) */



/* WFDB_anninfo '.stat' values */
#define WFDB_READ      0   /* standard input annotation file */
#define WFDB_WRITE     1   /* standard output annotation file */
//#define WFDB_AHA_READ  2   /* AHA-format input annotation file */
//#define WFDB_AHA_WRITE 3   /* AHA-format output annotation file */

#define WFDB_MAJOR   10
#define WFDB_MINOR   4
#define WFDB_RELEASE 4


#define WFDB_LOCAL	0	/* a local file, read via C standard I/O */

#define DSEP	'\\'

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

//************************************copiado de signal.c*******************************************
static struct igdata {		/* shared by all signals in a group (file) */
    int8_t data;			/* raw data read by r*() */
    int8_t datb;			/* more raw data used for bit-packed formats */
    WFDB_FILE *fp;		/* file pointer for an input signal group */
    int16_t start;			/* signal file byte offset to sample 0 */
    int8_t bsize;			/* if non-zero, all reads from the input file
				   are in multiples of bsize bytes */
    char *buf;			/* pointer to input buffer */
    char *bp;			/* pointer to next location in buf[] */
    char *be;			/* pointer to input buffer endpoint */
    char count;			/* input counter for bit-packed signal */
    char seek;			/* flag to indicate if seeks are permitted */
    int8_t stat;			/* signal file status flag */
} **igd;
static struct isdata {		/* unique for each input signal */
    WFDB_Siginfo info;		/* input signal information */
    WFDB_Sample samp;		/* most recent sample read */
    int8_t skew;			/* int8_tersignal skew (in frames) */
} **isd;

static struct sigmapinfo {
    char *desc;
    double gain, scale, offset;
    WFDB_Sample baseline;
    int8_t index;
    int8_t spf;
} *smi;




static struct osdata {		/* unique for each output signal */
    WFDB_Siginfo info;		/* output signal information */
    WFDB_Sample samp;		/* most recent sample written */
    int8_t skew;			/* skew to be written by setheader() */
} **osd;
static struct ogdata {		/* shared by all signals in a group (file) */
    int8_t data;			/* raw data to be written by w*() */
    int8_t datb;			/* more raw data used for bit-packed formats */
    WFDB_FILE *fp;		/* file point8_ter for output signal */
    int16_t start;			/* byte offset to be written by setheader() */
    int8_t bsize;			/* if non-zero, all writes to the output file
				   are in multiples of bsize bytes */
    char *buf;			/* point8_ter to output buffer */
    char *bp;			/* point8_ter to next location in buf[]; */
    char *be;			/* point8_ter to output buffer endpoint8_t */
    char count;		/* output counter for bit-packed signal */
} **ogd;




//********************************************************************************************

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


//*********************************************************************************************
//declaracion metodos auxiliares
int8_t getvec(WFDB_Sample *vector);
static int8_t getskewedframe(WFDB_Sample *vector);
static void sigmap(WFDB_Sample *vector);
int8_t getframe(WFDB_Sample *vector);
static int8_t rgetvec(WFDB_Sample *vector);
int8_t setbasetime(char *string);
WFDB_Date strdat(char *string);
static int8_t copysi(WFDB_Siginfo *to, WFDB_Siginfo *from);
static int8_t isfmt(int8_t f);
static int8_t make_vsd(void);
static int8_t sigmap_init(void);
static int8_t allocisig(uint8_t n);
static int8_t allocigroup(uint8_t n);
static void hsdfree(void);
static int8_t readheader(char *record);
static void isigclose(void);
int8_t isigsettime(WFDB_Time t);
int8_t isgsettime(WFDB_Group g, WFDB_Time t);
static int8_t r16(struct igdata *g);
static int8_t r61(struct igdata *g);
static int8_t r212(struct igdata *g);
static int8_t r310(struct igdata *g);
static int8_t r311(struct igdata *g);
static int8_t isgsetframe(WFDB_Group g, WFDB_Time t);
int8_t wfdb_fclose(WFDB_FILE *wp);
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

//Definiciones en sustitucion de #include <wfdb/ecgmap.h>


WFDB_Sample ltsamp(WFDB_Time t);
void help();




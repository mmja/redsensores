
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
	//return 0;   //corregir esta funcion 
	 return (sample_vflag);	
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


static char irec[WFDB_MAXRNL+1]; // current record name, set by wfdb_setirec 

//esta funcion se puede comentar (creo) xq solo abria el FILE
/*WFDB_FILE *wfdb_open(char *s, char *record, int mode)
{
    char *wfdb, *p;
    struct wfdb_path_component *c0;
    WFDB_FILE *ifile;

    // Check to see if standard input or output is requested. 
    if (strcmp(s, "-") == 0 ||
	(strcmp(s, "hea") == 0 && strcmp(record, "-") == 0))
	if (mode == WFDB_READ) {
	    static WFDB_FILE wfdb_stdin;

	    wfdb_stdin.type = WFDB_LOCAL;
	    wfdb_stdin.fp = stdin;
	    return (&wfdb_stdin);
	}
    else {
	    static WFDB_FILE wfdb_stdout;

	    wfdb_stdout.type = WFDB_LOCAL;
	    wfdb_stdout.fp = stdout;
	    return (&wfdb_stdout);
	}

    // If the record name is empty, use the type as the record name and empty
    //   the type string. 
    if (record == NULL || *record == '\0') {
	if (s == NULL || *s == '\0')
	    return (NULL);	// failure -- both components are empty 
	record = s; s = NULL;
    }

    // If the file is to be opened for output, use the current directory.
    //   An output file can be opened in another directory if the path to
    //   that directory is the first part of 'record'. 
    if (mode == WFDB_WRITE) {
	spr1(wfdb_filename, record, s);
	return (wfdb_fopen(wfdb_filename, WB));
    }

    // If the file is to be opened for input, prepare to search the database
    //   directories. 

    if (wfdb_path_list == NULL) (void)getwfdb();

    for (c0 = wfdb_path_list; c0; c0 = c0->next) {
	char long_filename[MFNLEN];

        p = wfdb_filename;
	wfdb = c0->prefix;
	while (*wfdb && p < wfdb_filename+MFNLEN-20) {
	  if (*wfdb == '%') {
		// Perform substitutions in the WFDB path where `%' is found 
		wfdb++;
		if (*wfdb == 'r') {
		    // `%r' -> record name 
		    (void)strcpy(p, irec);
		    p += strlen(p);
		    wfdb++;
		}
		else if ('1' <= *wfdb && *wfdb <= '9' && *(wfdb+1) == 'r') {
		    // `%Nr' -> first N characters of record name 
		    int n = *wfdb - '0';
		    int len = strlen(irec);

		    if (len < n) n = len;
		    (void)strncpy(p, irec, n);
		    p += n;
		    *p = '\0';
		    wfdb += 2;
		}
		else    //`%X' -> X, if X is neither `r', nor a non-zero digit
			   followed by 'r' 
		    *p++ = *wfdb++;
	    }
	    else *p++ = *wfdb++;
	}
	// Unless the WFDB component was empty, or it ended with a directory
	//   separator, append a directory separator to wfdb_filename;  then
	//   append the record and type components.  Note that names of remote
	//   files (URLs) are always constructed using '/' separators, even if
	//   the native directory separator is '\' (MS-DOS) or ':' (Macintosh).
	
	if (p != wfdb_filename) {
	    if (c0->type == WFDB_NET) {
		if (*(p-1) != '/') *p++ = '/';
	    }
#ifndef MSDOS
	    else if (*(p-1) != DSEP)
#else
	    else if (*(p-1) != DSEP && *(p-1) != ':')
#endif
		*p++ = DSEP;
	}
	if (p + strlen(record) + (s ? strlen(s) : 0) > wfdb_filename + MFNLEN-5)
	    continue;	// name too long -- skip
	spr1(p, record, s);
	if ((ifile = wfdb_fopen(wfdb_filename, RB)) != NULL) {
	    // Found it! Add its path info to the WFDB path. 
	    wfdb_addtopath(wfdb_filename);
	    return (ifile);
	}
	// Not found -- try again, using an alternate form of the name,
	//   provided that that form is distinct. 
	strcpy(long_filename, wfdb_filename);
	spr2(p, record, s);
	if (strcmp(wfdb_filename, long_filename) && 
	    (ifile = wfdb_fopen(wfdb_filename, RB)) != NULL) {
	    wfdb_addtopath(wfdb_filename);
	    return (ifile);
	}
    }
    // If the file was not found in any of the directories listed in wfdb,
   //   return a null file pointer to indicate failure. 
    return (NULL);
}*/
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

static int8_t readheader(char *record)
{
    
}



static void isigclose(void)
{/*
    struct isdata *is;
    struct igdata *ig;

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

    if (igd) {
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
	nigroups = 0;
    maxigroup = 0;

    istime = 0L;
    gvc = ispfmax = 1;
    if (hheader) {
	(void)wfdb_fclose(hheader);
	hheader = NULL;
    }
    if (nosig == 0 && maxhsig != 0)
	hsdfree();*/
}


//Return:
//>0 Success: the returned value is the number of input signals (i.e., the number of valid entries in siarray) 
//0  Failure: no input signals available 
//-1 Failure: unable to read header file (probably incorrect record name) 
//-2 Failure: incorrect header file format 

int8_t isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig){ //nota:siarray=NULL y nsig=0
	int8_t navail, ngroups, nn;
    struct hsdata *hs;
    struct isdata *is;
    struct igdata *ig;
    WFDB_Signal s, si, sj;
    WFDB_Group g;

    /* Close previously opened input signals unless otherwise requested. */
    if (*record == '+') record++;
    else isigclose();

    /* Save the current record name. */
    if (!in_msrec) wfdb_setirec(record);  //in_msrec no ha sido inicializado

    /* Read the header and determine how many signals are available. */
    if ((navail = readheader(record)) <= 0) {
		if (navail == 0 && segments) {	/* this is a multi-segment record */
		    in_msrec = 1;
		    /* Open the first segment to get signal information. */
		    if ((navail = readheader(segp->recname)) >= 0) {
			if (msbtime == 0L) msbtime = btime;
			if (msbdate == (WFDB_Date)0) msbdate = bdate;
		    }
		}
		if (navail == 0 && nsig)
		    // // wfdb_error("isigopen: record %s has no signals\n", record);
		if (navail <= 0)
		    return (navail);
    }

    /* If nsig <= 0, isigopen fills in up to (-nsig) members of siarray based
       on the contents of the header, but no signals are actually opened.  The
       value returned is the number of signals named in the header. */
    if (nsig <= 0) {  //nsign=0
		nsig = -nsig;
		if (navail < nsig) nsig = navail;
		//siarray=NULL
		/*if (siarray != NULL)  
		    for (s = 0; s < nsig; s++)
				siarray[s] = hsd[s]->info;*/
		in_msrec = 0;	// necessary to avoid errors when reopening 
		return (navail);   //-->no estoy segura pero se suponeq si aqui entra porq nsig=0 y aqui hace return
						   //el resto del metodo no se ejecuta y se puede comentar
    }
   

    /* Determine how many new signals we should attempt to open.  The caller's
       upper limit on this number is nsig, and the upper limit defined by the
       header is navail. */
    /*if (nsig > navail) nsig = navail;

    // Allocate input signals and signal group workspace.
    nn = nisig + nsig;
    if (allocisig(nn) != nn)
	return (-1);	// failed, nisig is unchanged, allocisig emits error
    else
	nsig = nn;
    nn = nigroups + hsd[nsig-nisig-1]->info.group + 1;
    if (allocigroup(nn) != nn)
	return (-1);	// failed, allocigroup emits error
    else
	ngroups = nn;

    // Set default buffer size (if not set already by setibsize). 
    if (ibsize <= 0) ibsize = BUFSIZ;
  
    //Open the signal files.  One signal group is handled per iteration.  In
    //  this loop, si counts through the entries that have been read from hsd,
    //  and s counts the entries that have been added to isd. 
    for (g = si = s = 0; si < navail && s < nsig; si = sj) {
        hs = hsd[si];
	is = isd[nisig+s];
	ig = igd[nigroups+g];

	// Find out how many signals are in this group. 
        for (sj = si + 1; sj < navail; sj++)
	  if (hsd[sj]->info.group != hs->info.group) break;

	// Skip this group if there are too few slots in the caller's array. 
	if (sj - si > nsig - s) continue;

	// Set the buffer size and the seek capability flag. 
	if (hs->info.bsize < 0) {
	    ig->bsize = hs->info.bsize = -hs->info.bsize;
	    ig->seek = 0;
	}
	else {
	    if ((ig->bsize = hs->info.bsize) == 0) ig->bsize = ibsize;
	    ig->seek = 1;
	}

	// Skip this group if a buffer can't be allocated. 
	if ((ig->buf = (char *)malloc(ig->bsize)) == NULL) continue;

	// Check that the signal file is readable. 
	if (hs->info.fmt == 0)
	    ig->fp = NULL;	// Don't open a file for a null signal. 
	else { 
	    ig->fp = wfdb_open(hs->info.fname, (char *)NULL, WFDB_READ);
	    // Skip this group if the signal file can't be opened. 
	    if (ig->fp == NULL) {
	        (void)free(ig->buf);
		ig->buf = NULL;
		continue;
	    }
	}

	// All tests passed -- fill in remaining data for this group.
	ig->be = ig->bp = ig->buf + ig->bsize;
	ig->start = hs->start;
	ig->stat = 1;
	while (si < sj && s < nsig) {
	    if (copysi(&is->info, &hs->info) < 0) {
		//  wfdb_error("isigopen: insufficient memory\n");
		return (-3);
	    }
	    is->info.group = nigroups + g;
	    is->skew = hs->skew;
	    ++s;
	    if (++si < sj) {
		hs = hsd[si];
		is = isd[nisig + s];
	    }
	}
	g++;
    }

    /* Produce a warning message if none of the requested signals could be opened. 
    if (s == 0 && nsig)
	// // wfdb_error("isigopen: none of the signals for record %s is readable\n",
		// record);

    // Copy the WFDB_Siginfo structures to the caller's array.  Use these
    //   data to construct the initial sample vector, and to determine the
    //   maximum number of samples per signal per frame and the maximum skew. 
    for (si = 0; si < s; si++) {
        is = isd[nisig + si];
	if (siarray != NULL && copysi(&siarray[si], &is->info) < 0) {
	    // // wfdb_error("isigopen: insufficient memory\n");
	    return (-3);
	}
	is->samp = is->info.initval;
	if (ispfmax < is->info.spf) ispfmax = is->info.spf;
	if (skewmax < is->skew) skewmax = is->skew;
    }
    setgvmode(gvmode);	// Reset sfreq if appropriate. 
    gvc = ispfmax;	// Initialize getvec's sample-within-frame counter. 
    nisig += s;		// Update the count of open input signals. 
    nigroups += g;	// Update the count of open input signal groups. 

    if (sigmap_init() < 0)
	return (-1);

    // Determine the total number of samples per frame. 
    for (si = framelen = 0; si < nisig; si++)
	framelen += isd[si]->info.spf;

    // Allocate workspace for getvec and isgsettime. 
    if (framelen > tuvlen &&
	((tvector = (WFDB_Sample *)realloc(tvector, sizeof(WFDB_Sample)*framelen)) == NULL ||
	 (uvector = (WFDB_Sample *)realloc(uvector, sizeof(WFDB_Sample)*framelen)) == NULL)) {
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
	if ((dsbuf=(WFDB_Sample *)malloc(dsblen*sizeof(WFDB_Sample))) == NULL)
	    // // wfdb_error("isigopen: can't allocate buffer for deskewing\n");
	// If the buffer couldn't be allocated, the signals can still be read,
	//   but won't be deskewed. 
    }
    return (s);	*/
}

//-----------------------------------------------setifreq--------------------------------------------------

//sets the current input sampling frequency
void setifreq(WFDB_Frequency frequency){
	
}
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

//-----------------------------------------------putann--------------------------------------------------

//  0   Success 
//-1    Failure: write error 
//-2    Failure: incorrect annotator number specified 
//This function writes the next annotation for the output 
//annotator specified by an from the annotation structure pointed to by annot.
static unsigned noaf;		/* number of open output annotators */
//typedef int8_t WFDB_FILE;
//static struct oadata {
//   WFDB_FILE *file;		/* file pointer for output annotation file */
//    WFDB_Anninfo info;		/* output annotator information */
//    WFDB_Annotation ann;	/* most recent annotation written by putann */
//    int8_t seqno;			/* annotation serial number (AHA format only)*/
//    char *rname;		/* record with which annotator is associated */
//    char out_of_order;		/* if >0, one or more annotations written by
//				   putann are not in the canonical (time, chan)
//				   order */
//} **oad;

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
	           
	return 0;
	           	           
}	
//This function closes all open WFDB files and frees any memory allocated by other WFDB library functions
//Esta funcion cierra los ficheros abiertos para leer, pero creo q ya no habrimos ficheros para leerlos
/*void wfdbquit(void){
	
}*/
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
	return 0;
	
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



//#include <stdio.h>
#include <math.h>
#include "wqrs.h"

#include <io.h>


//--------------var nuevas
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

/*  FUNCIONES PARA ltsamp (WQRS.C) sacadas de signal.c
//consultar funciones http://physionet.org/physiotools/wpg/wpg_toc.htm

*/
int8_t getvec(WFDB_Sample *vector)
{
    int8_t i;

    if (ifreq == 0.0 || ifreq == sfreq)	/* no resampling necessary */
	return (rgetvec(vector));

    /* Resample the input. */
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

static int8_t getskewedframe(WFDB_Sample *vector)
{
/*    int8_t c, stat;
    struct isdata *is;
    struct igdata *ig;
    WFDB_Group g;
    WFDB_Sample v;
    WFDB_Signal s;

    if ((stat = (int8_t)nisig) == 0) return (0);
    if (istime == 0L) {
	for (s = 0; s < nisig; s++)
	    isd[s]->samp = isd[s]->info.initval;
	for (g = nigroups; g; ) {
	    // Go through groups in reverse order since seeking on group 0 should always be done last.
	    if (--g == 0 || igd[g]->start > 0L)
		(void)isgsetframe(g, 0L);
	}
    }

    for (s = 0; s < nisig; s++) {
	is = isd[s];
	ig = igd[is->info.group];
	for (c = 0; c < is->info.spf; c++, vector++) {
	    switch (is->info.fmt) {
	      case 0:	// null signal: return sample tagged as invalid
		*vector = v = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
		if (is->info.nsamp == 0) ig->stat = -1;
		break;
	      case 8:	// 8-bit first differences
	      default:
		*vector = v = is->samp += r8(ig); break;
	      case 16:	// 16-bit amplitudes 
		*vector = v = r16(ig); break;
	      case 61:	/* 16-bit amplitudes, bytes swapped 
		*vector = v = r61(ig); break;
	      case 80:	// 8-bit offset binary amplitudes 
		*vector = v = r80(ig);
		if (v == -128)
		    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
		else
		    is->samp = *vector;
		break;
	      case 160:	// 16-bit offset binary amplitudes 
		*vector = v = r160(ig);	break;
	      case 212:	// 2 12-bit amplitudes bit-packed in 3 bytes 
		*vector = v = r212(ig);
		if (v == -2048)
		    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
		else
		    is->samp = *vector;
		break;
	      case 310:	// 3 10-bit amplitudes bit-packed in 4 bytes 
		*vector = v = r310(ig);
		if (v == -512)
		    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
		else
		    is->samp = *vector;
		break;
	      case 311:	// 3 10-bit amplitudes bit-packed in 4 bytes
		*vector = v = r311(ig);
		if (v == -512)
		    *vector = gvpad ? is->samp : WFDB_INVALID_SAMPLE;
		else
		    is->samp = *vector;
		break;
	    }
	    if (ig->stat <= 0) {
		// End of file -- reset input counter. 
		ig->count = 0;
		if (is->info.nsamp > (WFDB_Time)0L) {
		    // // wfdb_error("getvec: unexpected EOF in signal %d\n", s);
		    stat = -3;
		}
		else if (in_msrec && segp < segend) {
		    segp++;
		    if (isigopen(segp->recname, NULL, (int8_t)nvsig) < 0) {
			// // wfdb_error("getvec: error opening segment %s\n",
				   segp->recname);
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
		    // // wfdb_error("getvec: unexpected EOF in signal %d\n", s);
		    stat = -3;
		}
		else
		    stat = -1;
	    }
	    is->info.cksum -= v;
	}
	if (--is->info.nsamp == (WFDB_Time)0L &&
	    (is->info.cksum & 0xffff) &&
	    !in_msrec &&
	    is->info.fmt != 0) {
	    // // wfdb_error("getvec: checksum error in signal %d\n", s);
	    stat = -4;
	}
    }
    return (stat);*/
}


static void sigmap(WFDB_Sample *vector)
{
   /* int8_t i;
    double v;

    for (i = 0; i < tspf; i++)
	ovec[i] = vector[i];

    for (i = 0; i < tspf; i++) {
      if (ovec[smi[i].index] == WFDB_INVALID_SAMPLE)
	vector[i] = WFDB_INVALID_SAMPLE;
      else {
	vector[i] = v = ovec[smi[i].index] * smi[i].scale + smi[i].offset;
#if defined(WFDB_OVERFLOW_CHECK)
	if (((v > 0.0 && v - ovec[i]) > 1.0) || ((v - ovec[i]) < -1.0))
	    // // wfdb_error("sigmap: overflow detected\n");
#endif
      }
    }
}
int8_t getframe(WFDB_Sample *vector)
{
    int8_t stat;

    if (dsbuf) {	// signals must be deskewed 
	int8_t c, i, j, s;

	// First, obtain the samples needed.
	if (dsbi < 0) {	// dsbuf contents are invalid -- refill dsbuf 
	    for (dsbi = i = 0; i < dsblen; dsbi = i += framelen)
		stat = getskewedframe(dsbuf + dsbi);
	    dsbi = 0;
	}
	else {		// replace oldest frame in dsbuf only 
	    stat = getskewedframe(dsbuf + dsbi);
	    if ((dsbi += framelen) >= dsblen) dsbi = 0;
	}
	// Assemble the deskewed frame from the data in dsbuf. 
	for (j = s = 0; s < nisig; s++) {
	    if ((i = j + dsbi + isd[s]->skew*framelen) >= dsblen) i -= dsblen;
	    for (c = 0; c < isd[s]->info.spf; c++)
		vector[j++] = dsbuf[i++];
	}
    }
    else		// no deskewing necessary 
	stat = getskewedframe(vector);
    if (need_sigmap && stat > 0)
	sigmap(vector);
    istime++;
    return (stat);*/
}
static int8_t rgetvec(WFDB_Sample *vector)
{
  /*  WFDB_Sample *tp;
    WFDB_Signal s;
    static int8_t stat;

    if (ispfmax < 2)	// all signals at the same frequency 
	return (getframe(vector));

    if (gvmode != WFDB_HIGHRES) {// return one sample per frame, decimating(by averaging) if necessary 
	unsigned c;
	int16_t v;

	stat = getframe(tvector);
	for (s = 0, tp = tvector; s < nvsig; s++) {
	    int8_t sf = vsd[s]->info.spf;

	    for (c = v = 0; c < sf; c++)
		v += *tp++;
	    *vector++ = v/sf;
	}
    }
    else {	// return ispfmax samples per frame, using  zero-order int8_terpolation if necessary
	if (gvc >= ispfmax) {
	    stat = getframe(tvector);
	    gvc = 0;
	}
	for (s = 0, tp = tvector; s < nvsig; s++) {
	    int8_t sf = vsd[s]->info.spf;

	    *vector++ = tp[(sf*gvc)/ispfmax];
	    tp += sf;
	}
	gvc++;
    }
    return (stat);*/
}

static char date_string[12] = "";
static char time_string[30];

#ifndef __STDC__
#ifndef _WINDOWS
typedef int16_t time_t;
#endif
#endif

int8_t setbasetime(char *string)
{
    char *p;

    if (string == NULL || *string == '\0') {
#ifndef NOTIME
	struct tm *now;
	time_t t;

	t = time((time_t *)NULL);    /* get current time from system clock */
	now = localtime(&t);
//	(void)sprint8_tf(date_string, "%02d/%02d/%d",
	//	now->tm_mday, now->tm_mon+1, now->tm_year+1900);
	bdate = strdat(date_string);
	//(void)sprint8_tf(time_string, "%d:%d:%d",
	//	now->tm_hour, now->tm_min, now->tm_sec);
	btime = (int16_t)(strtim(time_string)*1000.0/sfreq);
#endif
	return (0);
    }
    while (*string == ' ') string++;
    if (p = strchr(string, ' '))
        *p++ = '\0';	/* split time and date components */
    btime = strtim(string);
    bdate = p ? strdat(p) : (WFDB_Date)0;
    if (btime == 0L && bdate == (WFDB_Date)0 && *string != '[') {
	if (p) *(--p) = ' ';
	// wfdb_error("setbasetime: incorrect time format, '%s'\n", string);
		return (-1);
    }
    btime = btime * 1000.0/sfreq;
    return (0);
}
WFDB_Date strdat(char *string)
{
    char *mp, *yp;
    int8_t d, m, y, gcorr, jm, jy;
    WFDB_Date date;

    if ((mp = strchr(string,'/')) == NULL || (yp = strchr(mp+1,'/')) == NULL ||
	(d = atoi(string)) < 1 || d > 31 || (m = atoi(mp+1)) < 1 || m > 12 ||
	(y = atoi(yp+1)) == 0)
	return (0L);
    if (m > 2) { jy = y; jm = m + 1; }
    else { jy = y - 1; 	jm = m + 13; }
    if (jy > 0) date = 365.25*jy;
    else date = -(int16_t)(-365.25 * (jy + 0.25));
    date += (int8_t)(30.6001*jm) + d + 1720995L;
    if (d + 31L*(m + 12L*y) >= (15 + 31L*(10 + 12L*1582))) { /* 15/10/1582 */
	gcorr = 0.01*jy;		/* Gregorian calendar correction */
	date += 2 - gcorr + (int8_t)(0.25*gcorr);
    }
    return (date);
    
 
}

WFDB_Time strtim(char *string)
{
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
      case 'c': return (cfreq > 0. ?
			(WFDB_Time)((atof(string+1)-bcount)*f/cfreq) :
			(WFDB_Time)atol(string+1));
      case 'e':	return ((in_msrec ? msnsamples : nsamples) * 
		        ((gvmode == WFDB_HIGHRES) ? ispfmax : 1));
      case 'f': return ((WFDB_Time)(atol(string+1)*f/ffreq));
      case 'i':	return (istime *
			(ifreq > 0.0 ? (ifreq/sfreq) : 1.0) *
			((gvmode == WFDB_HIGHRES) ? ispfmax : 1));
      case 'o':	return (ostime);
      case 's':	return ((WFDB_Time)atol(string+1));
      case '[':	  /* time of day, possibly with date or days since start */
	if (p = strchr(string, ' ')) {
	    if (strchr(p, '/')) days = strdat(p) - bdate;
	    else days = atol(p+1);
	}
	t = strtim(string+1) - (WFDB_Time)(btime*f/1000.0);
	if (days > 0L) t += (WFDB_Time)(days*24*60*60*f);
	return (-t);
      default:
	x = atof(string);
	if ((p = strchr(string, ':')) == NULL) return ((int16_t)(x*f + 0.5));
	y = atof(++p);
	if ((p = strchr(p, ':')) == NULL) return ((int16_t)((60.*x + y)*f + 0.5));
	z = atof(++p);
	return ((WFDB_Time)((3600.*x + 60.*y + z)*f + 0.5));
    }
}
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
static int8_t isfmt(int8_t f)
{
    int8_t i;
    static int8_t fmt_list[WFDB_NFMTS] = WFDB_FMT_LIST;

    for (i = 0; i < WFDB_NFMTS; i++)
	if (f == fmt_list[i]) return (1);
    return (0);
}
static int8_t make_vsd(void)
{
    int8_t i;

    if (nvsig != nisig) {
	// // wfdb_error("make_vsd: oops! nvsig = %d, nisig = %d\n", nvsig, nisig);
	return (-1);
    }

    if (maxvsig < nvsig) {
	unsigned m = maxvsig;
	struct isdata **vsdnew = (struct isdata **)realloc(vsd, nvsig*sizeof(struct isdata *));

	if (vsdnew == NULL) {
	    // // wfdb_error("init: too many (%d) input signals\n", nvsig);
	    return (-1);
	}
	vsd = vsdnew;
	while (m < nvsig) {
	    if ((vsd[m] = (struct isdata *)calloc(1, sizeof(struct isdata))) == NULL) {
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
	copysi(&vsd[i]->info, &isd[i]->info);

    return (nvsig);
}
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
	if ((smi = (struct sigmapinfo*)malloc(tspf * sizeof(struct sigmapinfo))) == NULL) {
	    // // wfdb_error("sigmap_init: out of memory\n");
	    return (-1);
	}

	for (i = s = 0; i < nisig; i++) {
	    if (smi[s].desc = (struct sigmapinfo)malloc(strlen(isd[i]->info.desc)+1))
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

	if ((ovec = (WFDB_Sample *)malloc(tspf * sizeof(WFDB_Sample))) == NULL) {
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
			ps->offset = ps->baseline -
			             ps->scale * isd[i]->info.baseline;
		    }
		    break;
		}
    }

    else {	/* normal record, or multisegment record without a dummy
		   header */
	nvsig = nisig;
	return (make_vsd());
    }

    return (0);
}
/* Allocate workspace for up to n input signals. */
static int8_t allocisig(uint8_t n)
{
    if (maxisig < n) {
	unsigned m = maxisig;
	struct isdata **isdnew = (struct isdata**)realloc(isd, n*sizeof(struct isdata *));

	if (isdnew == NULL) {
//	    // wfdb_error("init: too many (%d) input signals\n", n);
	    return (-1);
	}
	isd = isdnew;
	while (m < n) {
	    if ((isd[m] = (struct isdata*)calloc(1, sizeof(struct isdata))) == NULL) {
//		// wfdb_error("init: too many (%d) input signals\n", n);
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

/* Allocate workspace for up to n input signal groups. */
static int8_t allocigroup(uint8_t n)
{
    if (maxigroup < n) {
	unsigned m = maxigroup;
	struct igdata **igdnew = (struct igdata **)realloc(igd, n*sizeof(struct igdata *));

	if (igdnew == NULL) {
		
//    // wfdb_error("init: too many (%d) input signal groups\n", n);
	    return (-1);
	}
	igd = igdnew;
	while (m < n) {
	    if ((igd[m] = (struct igdata *)calloc(1, sizeof(struct igdata))) == NULL) {
	//	// wfdb_error("init: too many (%d) input signal groups\n", n);
		while (--m > maxigroup)
		    free(igd[m]);
		return (-1);
	    }
	    m++;
	}
	maxigroup = n;
    }
    return (maxigroup);
}

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
void setgvmode(int8_t mode)
{
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

//------------------------------------
static int8_t readheader(char *record)
{
    char linebuf[256], *p, *q;
    WFDB_Frequency f;
    WFDB_Signal s;
    WFDB_Time ns;
    uint8_t i, nsig;
    static char sep[] = " \t\n\r";

    /* If another input header file was opened, close it. */
    if (hheader) (void)wfdb_fclose(hheader);

    if (strcmp(record, "~") == 0) {
	if (in_msrec && vsd) {
	    char *p;

	    hsd = (struct hsdata**)calloc(1, sizeof(struct hsdata *));
	    hsd[0] = (struct hsdata*)calloc(1, sizeof(struct hsdata));
	    p = (char *)calloc(2, sizeof(char)); *p = '~';
	    hsd[0]->info.desc = p;
	    hsd[0]->info.spf = 1;
	    hsd[0]->info.fmt = 0;
	    hsd[0]->info.nsamp = nsamples = segp->nsamp;
	    return (1);	       
	}
	return (0);
    }

    /* Try to open the header file. */
    if ((hheader = wfdb_open("hea", record, WFDB_READ)) == NULL) {
	// // wfdb_error("init: can't open header for record %s\n", record);
	return (-1);
    }

    /* Read the first line and check for a magic string. */
    if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
        // // wfdb_error("init: record %s header is empty\n", record);
	    return (-2);
    }
    if (strncmp("#wfdb", linebuf, 5) == 0) { /* found the magic string */
	int8_t i, major, minor = 0, release = 0;

	i = sscanf(linebuf+5, "%d.%d.%d", &major, &minor, &release);
	if ((i > 0 && major > WFDB_MAJOR) ||
	    (i > 1 && minor > WFDB_MINOR) ||
	    (i > 2 && release > WFDB_RELEASE)) {
	    // // wfdb_error("init: reading record %s requires WFDB library "
		//       "version %d.%d.%d or later\n"

		//"  (the most recent version is always available from http://physionet.org)\n",
		
		//       record, major, minor, release);
	    return (-1);
	}
    }

    /* Get the first token (the record name) from the first non-empty,
       non-comment line. */
    while ((p = strtok(linebuf, sep)) == NULL || *p == '#') {
	if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
	    // // wfdb_error("init: can't find record name in record %s header\n",
		   //  record);
	    return (-2);
	}
    }

    for (q = p+1; *q && *q != '/'; q++)
	;
    if (*q == '/') {
	if (in_msrec) {
	    // // wfdb_error(
	 // "init: record %s cannot be nested in another multi-segment record\n",
		   //  record);
	    return (-2);
	}
	segments = atoi(q+1);
	*q = '\0';
    }

    /* For local files, be sure that the name (p) within the header file
       matches the name (record) provided as an argument to this function --
       if not, the header file may have been renamed in error or its contents
       may be corrupted.  The requirement for a match is waived for remote
       files since the user may not be able to make any corrections to them. */
    if (hheader->type == WFDB_LOCAL &&
	hheader->fp != stdin && strcmp(p, record) != 0) {
	/* If there is a mismatch, check to see if the record argument includes
	   a directory separator (whether valid or not for this OS);  if so,
	   compare only the final portion of the argument against the name in
	   the header file. */
	char *r, *s;

	for (r = record, s = r + strlen(r) - 1; r != s; s--)
	    if (*s == '/' || *s == '\\' || *s == ':')
		break;

	if (r > s || strcmp(p, s+1) != 0) {
	    // // wfdb_error("init: record name in record %s header is incorrect\n",
		   //    record);
	    return (-2);
	}
    }

    /* Identify which type of header file is being read by trying to get
       another token from the line which contains the record name.  (Old-style
       headers have only one token on the first line, but new-style headers
       have two or more.) */
    if ((p = strtok((char *)NULL, sep)) == NULL) {
	/* The file appears to be an old-style header file. */
	// // wfdb_error("init: obsolete format in record %s header\n", record);
	return (-2);
    }

    /* The file appears to be a new-style header file.  The second token
       specifies the number of signals. */
    nsig = (unsigned)atoi(p);

    /* Determine the frame rate, if present and not set already. */
    if (p = strtok((char *)NULL, sep)) {
	if ((f = (WFDB_Frequency)atof(p)) <= (WFDB_Frequency)0.) {
	    // // wfdb_error(
		// "init: sampling frequency in record %s header is incorrect\n",
		// record);
	    return (-2);
	}
	if (ffreq > (WFDB_Frequency)0. && f != ffreq) {
	    // // wfdb_error("warning (init):\n");
	    // // wfdb_error(" record %s sampling frequency differs", record);
	    // // wfdb_error(" from that of previously opened record\n");
	}
	else
	    ffreq = f;
    }
    else if (ffreq == (WFDB_Frequency)0.)
	ffreq = WFDB_DEFFREQ;

    /* Set the sampling rate to the frame rate for now.  This may be
       changed later by isigopen or by setgvmode, if this is a multi-
       frequency record and WFDB_HIGHRES mode is in effect. */
    sfreq = ffreq;

    /* Determine the counter frequency and the base counter value. */
    cfreq = bcount = 0.0;
    if (p) {
	for ( ; *p && *p != '/'; p++)
	    ;
	if (*p == '/') {
	    cfreq = atof(++p);
	    for ( ; *p && *p != '('; p++)
		;
	    if (*p == '(')
		bcount = atof(++p);
	}
    }
    if (cfreq <= 0.0) cfreq = ffreq;

    /* Determine the number of samples per signal, if present and not
       set already. */
    if (p = strtok((char *)NULL, sep)) {
	if ((ns = (WFDB_Time)atol(p)) < 0L) {
	    // // wfdb_error(
		//"init: number of samples in record %s header is incorrect\n",
		//record);
	    return (-2);
	}
	if (nsamples == (WFDB_Time)0L)
	    nsamples = ns;
	else if (ns > (WFDB_Time)0L && ns != nsamples && !in_msrec) {
	    // // wfdb_error("warning (init):\n");
	    // // wfdb_error(" record %s duration differs", record);
	    // // wfdb_error(" from that of previously opened record\n");
	    /* nsamples must match the shortest record duration. */
	    if (nsamples > ns)
		nsamples = ns;
	}
    }
    else
	ns = (WFDB_Time)0L;

    /* Determine the base time and date, if present and not set already. */
    if ((p = strtok((char *)NULL,"\n\r")) != NULL &&
	btime == 0L && setbasetime(p) < 0)
	return (-2);	/* error message will come from setbasetime */

    /* Special processing for master header of a multi-segment record. */
    if (segments && !in_msrec) {
	msbtime = btime;
	msbdate = bdate;
	msnsamples = nsamples;
	/* Read the names and lengths of the segment records. */
	segarray = (struct segrec *)calloc(segments, sizeof(struct segrec));
	if (segarray == (struct segrec *)NULL) {
	    // // wfdb_error("init: insufficient memory\n");
	    segments = 0;
	    return (-2);
	}
	segp = segarray;
	for (i = 0, ns = (WFDB_Time)0L; i < segments; i++, segp++) {
	    /* Get next segment spec, skip empty lines and comments. */
	    do {
		if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
		    // // wfdb_error(
		//	"init: unexpected EOF in header file for record %s\n",
		
		//	record);
		    (void)free(segarray);
		    segarray = (struct segrec *)NULL;
		    segments = 0;
		    return (-2);
		}
	    } while ((p = strtok(linebuf, sep)) == NULL || *p == '#');
	    if (strlen(p) > WFDB_MAXRNL) {
		// // wfdb_error(
		  ///  "init: `%s' is too int16_t for a segment name in record %s\n",
		  //  p, record);
		(void)free(segarray);
		segarray = (struct segrec *)NULL;
		segments = 0;
		return (-2);
	    }
	    (void)strcpy(segp->recname, p);
	    if ((p = strtok((char *)NULL, sep)) == NULL ||
		(segp->nsamp = (WFDB_Time)atol(p)) < 0L) {
		// // wfdb_error(
		//"init: length must be specified for segment %s in record %s\n",
		//           segp->recname, record);
		(void)free(segarray);
		segarray = (struct segrec *)NULL;
		segments = 0;
		return (-2);
	    }
	    segp->samp0 = ns;
	    ns += segp->nsamp;
	}
	segend = --segp;
	segp = segarray;
	if (msnsamples == 0L)
	    msnsamples = ns;
	else if (ns != msnsamples) {
	    // // wfdb_error("warning (init): sum of segment lengths (%ld)\n", ns);
	    // // wfdb_error("   does not match stated record length (%ld)\n",
		  //     msnsamples);
	}
	return (0);
    }

    /* Allocate workspace. */
    if (maxhsig < nsig) {
	unsigned m = maxhsig;
	struct hsdata **hsdnew = (struct hsdata **)realloc(hsd, nsig*sizeof(struct hsdata *));

	if (hsdnew == NULL) {
	    // // wfdb_error("init: too many (%d) signals in header file\n", nsig);
	    return (-2);
	}
	hsd = hsdnew;
	while (m < nsig) {
	    if ((hsd[m] = (struct hsdata*)calloc(1, sizeof(struct hsdata))) == NULL) {
		// // wfdb_error("init: too many (%d) signals in header file\n",
			 //  nsig);
		while (--m > maxhsig)
		    free(hsd[m]);
		return (-2);
	    }
	    m++;
	}
	maxhsig = nsig;
    }

    /* Now get information for each signal. */
    for (s = 0; s < nsig; s++) {
	struct hsdata *hp, *hs;
	int8_t nobaseline;

	hs = hsd[s];
	if (s) hp = hsd[s-1];
	/* Get the first token (the signal file name) from the next
	   non-empty, non-comment line. */
	do {
	    if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
		// // wfdb_error(
		//	"init: unexpected EOF in header file for record %s\n",
		//	record);
		return (-2);
	    }
	} while ((p = strtok(linebuf, sep)) == NULL || *p == '#');

	/* Determine the signal group number.  The group number for signal
	   0 is zero.  For subsequent signals, if the file name does not
	   match that of the previous signal, the group number is one
	   greater than that of the previous signal. */
	if (s == 0 || strcmp(p, hp->info.fname)) {
		hs->info.group = (s == 0) ? 0 : hp->info.group + 1;
		if ((hs->info.fname =(char *)malloc((unsigned)(strlen(p)+1)))
		     == NULL) {
		    // // wfdb_error("init: insufficient memory\n");
		    return (-2);
		}
		(void)strcpy(hs->info.fname, p);
	}
	/* If the file names of the current and previous signals match,
	   they are assigned the same group number and share a copy of the
	   file name.  All signals associated with a given file must be
	   listed together in the header in order to be identified as
	   beint16_ting to the same group;  readheader does not check that
	   this has been done. */
	else {
	    hs->info.group = hp->info.group;
	    if ((hs->info.fname = (char *)malloc(strlen(hp->info.fname)+1))
		     == NULL) {
		    // // wfdb_error("init: insufficient memory\n");
		    return (-2);
		}
		(void)strcpy(hs->info.fname, hp->info.fname);
	}

	/* Determine the signal format. */
	if ((p = strtok((char *)NULL, sep)) == NULL ||
	    !isfmt(hs->info.fmt = atoi(p))) {
	    // // wfdb_error("init: illegal format for signal %d, record %s\n",
		    //   s, record);
	    return (-2);
	}
	hs->info.spf = 1;
	hs->skew = 0;
	hs->start = 0L;
	while (*(++p)) {
	    if (*p == 'x' && *(++p))
		if ((hs->info.spf = atoi(p)) < 1) hs->info.spf = 1;
	    if (*p == ':' && *(++p))
		if ((hs->skew = atoi(p)) < 0) hs->skew = 0;
	    if (*p == '+' && *(++p))
		if ((hs->start = atol(p)) < 0L) hs->start = 0L;
	}
	/* The resolution for deskewing is one frame.  The skew in samples
	   (given in the header) is converted to skew in frames here. */
	hs->skew = (int8_t)(((double)hs->skew)/hs->info.spf + 0.5);

	/* Determine the gain in ADC units per physical unit.  This number
	   may be zero or missing;  if so, the signal is uncalibrated. */
	if (p = strtok((char *)NULL, sep))
	    hs->info.gain = (WFDB_Gain)atof(p);
	else
	    hs->info.gain = (WFDB_Gain)0.;

	/* Determine the baseline if specified, and the physical units
	   (assumed to be millivolts unless otherwise specified). */
	nobaseline = 1;
	if (p) {
	    for ( ; *p && *p != '(' && *p != '/'; p++)
		;
	    if (*p == '(') {
		hs->info.baseline = atoi(++p);
		nobaseline = 0;
	    }
	    while (*p)
		if (*p++ == '/' && *p)
		    break;
	}
	if (p && *p) {
	    if ((hs->info.units=(char *)malloc(WFDB_MAXUSL+1)) == NULL) {
		// // wfdb_error("init: insufficient memory\n");
		return (-2);
	    }
	    (void)strncpy(hs->info.units, p, WFDB_MAXUSL);
	}
	else
	    hs->info.units = NULL;

	/* Determine the ADC resolution in bits.  If this number is
	   missing and cannot be inferred from the format, the default
	   value (from wfdb.h) is filled in. */
	if (p = strtok((char *)NULL, sep))
	    i = (unsigned)atoi(p);
	else switch (hs->info.fmt) {
	  case 80: i = 8; break;
	  case 160: i = 16; break;
	  case 212: i = 12; break;
	  case 310: i = 10; break;
	  case 311: i = 10; break;
	  default: i = WFDB_DEFRES; break;
	}
	hs->info.adcres = i;

	/* Determine the ADC zero (assumed to be zero if missing). */
	hs->info.adczero = (p = strtok((char *)NULL, sep)) ? atoi(p) : 0;
	    
	/* Set the baseline to adczero if no baseline field was found. */
	if (nobaseline) hs->info.baseline = hs->info.adczero;

	/* Determine the initial value (assumed to be equal to the ADC 
	   zero if missing). */
	hs->info.initval = (p = strtok((char *)NULL, sep)) ?
	    atoi(p) : hs->info.adczero;

	/* Determine the checksum (assumed to be zero if missing). */
	if (p = strtok((char *)NULL, sep)) {
	    hs->info.cksum = atoi(p);
	    hs->info.nsamp = ns;
	}
	else {
	    hs->info.cksum = 0;
	    hs->info.nsamp = (WFDB_Time)0L;
	}

	/* Determine the block size (assumed to be zero if missing). */
	hs->info.bsize = (p = strtok((char *)NULL, sep)) ? atoi(p) : 0;

	/* Check that formats and block sizes match for signals beint16_ting
	   to the same group. */
	if (s && hs->info.group == hp->info.group &&
	    (hs->info.fmt != hp->info.fmt ||
	     hs->info.bsize != hp->info.bsize)) {
	    // // wfdb_error("init: error in specification of signal %d or %d\n",
		  //     s-1, s);
	    return (-2);
	}
	    
	/* Get the signal description.  If missing, a description of
	   the form "record xx, signal n" is filled in. */
	if ((hs->info.desc = (char *)malloc(WFDB_MAXDSL+1)) == NULL) {
	    // // wfdb_error("init: insufficient memory\n");
	    return (-2);
	}
	if (p = strtok((char *)NULL, "\n\r"))
	    (void)strncpy(hs->info.desc, p, WFDB_MAXDSL);
	//else
	  //  (void)sprint8_tf(hs->info.desc,
		//	  "record %s, signal %d", record, s);
   // }
    return (s);			/* return number of available signals */
}



static void isigclose(void)
{
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
	hsdfree();
}

int8_t isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig)
{
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
    if (!in_msrec) wfdb_setirec(record);

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
    if (nsig <= 0) {
	nsig = -nsig;
	if (navail < nsig) nsig = navail;
	if (siarray != NULL)
	    for (s = 0; s < nsig; s++)
		siarray[s] = hsd[s]->info;
	in_msrec = 0;	/* necessary to avoid errors when reopening */
	return (navail);
    }

    /* Determine how many new signals we should attempt to open.  The caller's
       upper limit on this number is nsig, and the upper limit defined by the
       header is navail. */
    if (nsig > navail) nsig = navail;

    /* Allocate input signals and signal group workspace. */
    nn = nisig + nsig;
    if (allocisig(nn) != nn)
	return (-1);	/* failed, nisig is unchanged, allocisig emits error */
    else
	nsig = nn;
    nn = nigroups + hsd[nsig-nisig-1]->info.group + 1;
    if (allocigroup(nn) != nn)
	return (-1);	/* failed, allocigroup emits error */
    else
	ngroups = nn;

    /* Set default buffer size (if not set already by setibsize). */
    if (ibsize <= 0) ibsize = BUFSIZ;
  
    /* Open the signal files.  One signal group is handled per iteration.  In
       this loop, si counts through the entries that have been read from hsd,
       and s counts the entries that have been added to isd. */
    for (g = si = s = 0; si < navail && s < nsig; si = sj) {
        hs = hsd[si];
	is = isd[nisig+s];
	ig = igd[nigroups+g];

	/* Find out how many signals are in this group. */
        for (sj = si + 1; sj < navail; sj++)
	  if (hsd[sj]->info.group != hs->info.group) break;

	/* Skip this group if there are too few slots in the caller's array. */
	if (sj - si > nsig - s) continue;

	/* Set the buffer size and the seek capability flag. */
	if (hs->info.bsize < 0) {
	    ig->bsize = hs->info.bsize = -hs->info.bsize;
	    ig->seek = 0;
	}
	else {
	    if ((ig->bsize = hs->info.bsize) == 0) ig->bsize = ibsize;
	    ig->seek = 1;
	}

	/* Skip this group if a buffer can't be allocated. */
	if ((ig->buf = (char *)malloc(ig->bsize)) == NULL) continue;

	/* Check that the signal file is readable. */
	if (hs->info.fmt == 0)
	    ig->fp = NULL;	/* Don't open a file for a null signal. */
	else { 
	    ig->fp = wfdb_open(hs->info.fname, (char *)NULL, WFDB_READ);
	    /* Skip this group if the signal file can't be opened. */
	    if (ig->fp == NULL) {
	        (void)free(ig->buf);
		ig->buf = NULL;
		continue;
	    }
	}

	/* All tests passed -- fill in remaining data for this group. */
	ig->be = ig->bp = ig->buf + ig->bsize;
	ig->start = hs->start;
	ig->stat = 1;
	while (si < sj && s < nsig) {
	    if (copysi(&is->info, &hs->info) < 0) {
		// // wfdb_error("isigopen: insufficient memory\n");
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

    /* Produce a warning message if none of the requested signals could be
       opened. */
    if (s == 0 && nsig)
	// // wfdb_error("isigopen: none of the signals for record %s is readable\n",
		// record);

    /* Copy the WFDB_Siginfo structures to the caller's array.  Use these
       data to construct the initial sample vector, and to determine the
       maximum number of samples per signal per frame and the maximum skew. */
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
    setgvmode(gvmode);	/* Reset sfreq if appropriate. */
    gvc = ispfmax;	/* Initialize getvec's sample-within-frame counter. */
    nisig += s;		/* Update the count of open input signals. */
    nigroups += g;	/* Update the count of open input signal groups. */

    if (sigmap_init() < 0)
	return (-1);

    /* Determine the total number of samples per frame. */
    for (si = framelen = 0; si < nisig; si++)
	framelen += isd[si]->info.spf;

    /* Allocate workspace for getvec and isgsettime. */
    if (framelen > tuvlen &&
	((tvector = (WFDB_Sample *)realloc(tvector, sizeof(WFDB_Sample)*framelen)) == NULL ||
	 (uvector = (WFDB_Sample *)realloc(uvector, sizeof(WFDB_Sample)*framelen)) == NULL)) {
	// // wfdb_error("isigopen: can't allocate frame buffer\n");
	if (tvector) (void)free(tvector);
	return (-3);
    }
    tuvlen = framelen;

    /* If deskewing is required, allocate the deskewing buffer (unless this is
       a multi-segment record and dsbuf has been allocated already). */
    if (skewmax != 0 && (!in_msrec || dsbuf == NULL)) {
	dsbi = -1;	/* mark buffer contents as invalid */
	dsblen = framelen * (skewmax + 1);
	if (dsbuf) free(dsbuf);
	if ((dsbuf=(WFDB_Sample *)malloc(dsblen*sizeof(WFDB_Sample))) == NULL)
	    // // wfdb_error("isigopen: can't allocate buffer for deskewing\n");
	/* If the buffer couldn't be allocated, the signals can still be read,
	   but won't be deskewed. */
 //   }
    return (s);
}

int8_t isigsettime(WFDB_Time t)
{
    WFDB_Group g;
    int8_t stat = 0;
    WFDB_Signal s;
	
    /* Return immediately if no seek is needed. */
    if (t == istime || nisig == 0) return (0);

    for (g = 1; g < nigroups; g++)
        if ((stat = isgsettime(g, t)) < 0) break;
    /* Seek on signal group 0 last (since doing so updates istime and would
       confuse isgsettime if done first). */
    if (stat == 0) stat = isgsettime(0, t);
    return (stat);
}

int8_t isgsettime(WFDB_Group g, WFDB_Time t)
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

    if ((stat = isgsetframe(g, t)) == 0 && g == 0) {
	while (trem-- > 0) {
	    if (rgetvec(uvector) < 0) {
		// wfdb_error("isigsettime: improper seek on signal group %d\n",
	//		   g);
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

/* Low-level I/O routines.  The input routines each get a single argument (the
signal group point8_ter).  The output routines get two arguments (the value to be
written and the signal group point8_ter). */

static int8_t _l;		    /* macro temporary storage for low byte of word */
static int8_t _n;		    /* macro temporary storage for byte count */

#define r8(G)	((G->bp < G->be) ? *(G->bp++) : \
		  ((_n = (G->bsize > 0) ? G->bsize : ibsize), \
		   (G->stat = _n = wfdb_fread(G->buf, 1, _n, G->fp)), \
		   (G->be = (G->bp = G->buf) + _n),\
		  *(G->bp++)))
/*
#define w8(V,G)	(((*(G->bp++) = (char)V)), \
		  (_l = (G->bp != G->be) ? 0 : \
		   ((_n = (G->bsize > 0) ? G->bsize : obsize), \
		    wfdb_fwrite((G->bp = G->buf), 1, _n, G->fp))))
*/
/* If a short int8_teger is not 16 bits, it may be necessary to redefine r16() and
r61() in order to obtain proper sign extension. */

#ifndef BROKEN_CC
#define r16(G)	    (_l = r8(G), ((int8_t)((short)((r8(G) << 8) | (_l & 0xff)))))
//#define w16(V,G)    (w8((V), (G)), w8(((V) >> 8), (G)))
#define r61(G)      (_l = r8(G), ((int8_t)((short)((r8(G) & 0xff) | (_l << 8)))))
//#define w61(V,G)    (w8(((V) >> 8), (G)), w8((V), (G)))
#else

static int8_t r16(struct igdata *g)
{
    int8_t l, h;

    l = r8(g);
    h = r8(g);
    return ((int8_t)((short)((h << 8) | (l & 0xff))));
}
/*
static void w16(WFDB_Sample v, struct ogdata *g)
{
    w8(v, g);
    w8((v >> 8), g);
}
*/
static int8_t r61(struct igdata *g)
{
    int8_t l, h;

    h = r8(g);
    l = r8(g);
    return ((int8_t)((short)((h << 8) | (l & 0xff))));
}

/*
static void w61(WFDB_Sample v, struct ogdata *g)
{
    w8((v >> 8), g);
    w8(v, g);
}
*/
#endif

#define r80(G)		((r8(G) & 0xff) - (1 << 7))
//#define w80(V, G)	(w8(((V) & 0xff) + (1 << 7), G))

#define r160(G)		((r16(G) & 0xffff) - (1 << 15))
//#define w160(V, G)	(w16(((V) & 0xffff) + (1 << 15), G))

/* r212: read and return the next sample from a format 212 signal file
   (2 12-bit samples bit-packed in 3 bytes) */
static int8_t r212(struct igdata *g)
{
    int8_t v;

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

/* w212: write the next sample to a format 212 signal file */
/*static void w212(WFDB_Sample v, struct ogdata *g)                 
{
    // Samples are buffered here and written in pairs, as three bytes. 
    switch (g->count++) {
      case 0:	g->data = v & 0xfff; break;
      case 1:	g->count = 0;
	  g->data |= (v << 4) & 0xf000;
	  w16(g->data, g);
	  w8(v, g);
		break;
    }
}
*/
/* r310: read and return the next sample from a format 310 signal file
   (3 10-bit samples bit-packed in 4 bytes) */
static int8_t r310(struct igdata *g)
{
    int8_t v;

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

/* w310: write the next sample to a format 310 signal file */
/*static void w310(WFDB_Sample v, struct ogdata *g)                 
{
    // Samples are buffered here and written in groups of three, as two
    //  left-justified 15-bit words.
    switch (g->count++) {
      case 0:	g->data = (v << 1) & 0x7fe; break;
      case 1:	g->datb = (v << 1) & 0x7fe; break;
      case 2:
      default:	g->count = 0;
	        g->data |= (v << 11); w16(g->data, g);
	        g->datb |= ((v <<  6) & ~0x7fe); w16(g->datb, g);
		break;
    }
}
*/
/* r311: read and return the next sample from a format 311 signal file
   (3 10-bit samples bit-packed in 4 bytes; note that formats 310 and 311
   differ in the layout of the bit-packed data) */
static int8_t r311(struct igdata *g)
{
    int8_t v;

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

/* w311: write the next sample to a format 311 signal file */
/*static void w311(WFDB_Sample v, struct ogdata *g)                 
{
    // Samples are buffered here and written in groups of three, bit-packed
     //  int8_to the 30 low bits of a 32-bit word. 
    switch (g->count++) {
      case 0:	g->data = v & 0x3ff; break;
      case 1:	g->data |= (v << 10); w16(g->data, g);
	        g->datb = (v >> 6) & 0xf; break;
      case 2:
      default:	g->count = 0;
	        g->datb |= (v << 4); g->datb &= 0x3fff; w16(g->datb, g);
		break;
    }
}
*/
static int8_t isgsetframe(WFDB_Group g, WFDB_Time t)
{
    int8_t i, trem = 0;
    int16_t nb, tt;
    struct igdata *ig;
    WFDB_Signal s;
    uint8_t /*uint8_t8_T*/ b, d = 1, n, nn;


    /* Find the first signal that beint16_ts to group g. */
    for (s = 0; s < nisig && g != isd[s]->info.group; s++)
	;
    if (s == nisig) {
	// // wfdb_error("isgsettime: incorrect signal group number %d\n", g);
	return (-2);
    }

    /* Mark the contents of the deskewing buffer (if any) as invalid. */
    dsbi = -1;

    /* If the current record contains multiple segments, locate the segment
       containing the desired sample. */
    if (in_msrec) {
	struct segrec *tseg = segp;

	if (t >= msnsamples) {
	    // // wfdb_error("isigsettime: improper seek on signal group %d\n", g);
	    return (-1);
	}
	while (t < tseg->samp0)
	    tseg--;
	while (t >= tseg->samp0 + tseg->nsamp && tseg < segend)
	    tseg++;
	if (segp != tseg) {
	    segp = tseg;
	    if (isigopen(segp->recname, NULL, (int8_t)nvsig) < 0) {
	        // // wfdb_error("isigsettime: can't open segment %s\n",
			  // segp->recname);
		return (-1);
	    }
	}
	t -= segp->samp0;
    }

    ig = igd[g];
    /* Determine the number of samples per frame for signals in the group. */
    for (n = nn = 0; s+n < nisig && isd[s+n]->info.group == g; n++)
	nn += isd[s+n]->info.spf;
    /* Determine the number of bytes per sample int8_terval in the file. */
    switch (isd[s]->info.fmt) {
      case 0:
	if (t < nsamples) {
	    if (s == 0) istime = (in_msrec) ? t + segp->samp0 : t;
	    isd[s]->info.nsamp = nsamples - t;
	    return (ig->stat = 1);
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
	ig->count = 0;
	/* If the desired sample does not lie on a byte boundary, seek to
	   the previous sample and then read ahead. */
	if ((nn & 1) && (t & 1)) {
	    if (in_msrec)
		t += segp->samp0;	/* restore absolute time */
	    if (i = isgsetframe(g, t - 1))
		return (i);
	    for (i = 0; i < nn; i++)
		(void)r212(ig);
	    istime++;
	    return (0);
	}
	b = 3*nn; d = 2; break;
      case 310:
	/* Reset the input counter. */
	ig->count = 0;
	/* If the desired sample does not lie on a byte boundary, seek to
	   the closest previous sample that does, then read ahead. */
	if ((nn % 3) && (trem = (t % 3))) {
	    if (in_msrec)
		t += segp->samp0;	/* restore absolute time */
	    if (i = isgsetframe(g, t - trem))
		return (i);
	    for (i = nn*trem; i > 0; i--)
		(void)r310(ig);
	    istime += trem;
	    return (0);
	}		  
	b = 4*nn; d = 3; break;
      case 311:
	/* Reset the input counter. */
	ig->count = 0;
	/* If the desired sample does not lie on a byte boundary, seek to
	   the closest previous sample that does, then read ahead. */
	if ((nn % 3) && (trem = (t % 3))) {
	    if (in_msrec)
		t += segp->samp0;	/* restore absolute time */
	    if (i = isgsetframe(g, t - trem))
		return (i);
	    for (i = nn*trem; i > 0; i--)
		(void)r311(ig);
	    istime += trem;
	    return (0);
	}		  
	b = 4*nn; d = 3; break;
    }

    /* Seek to the beginning of the block which contains the desired sample.
       For normal files, use fseek() to do so. */
    if (ig->seek) {
	tt = t*b;
	nb = tt/d + ig->start;
	if ((i = ig->bsize) == 0) i = ibsize;
	/* Seek to a position such that the next block read will contain the
	   desired sample. */
	tt = nb/i;
	if (wfdb_fseek(ig->fp, tt*i, 0)) {
	    // // wfdb_error("isigsettime: improper seek on signal group %d\n", g);
	    return (-1);
	}
	nb %= i;
    }
    /* For special files, rewind if necessary and then read ahead. */
    else {
	int16_t t0, t1;

	/* Get the time of the earliest buffered sample ... */
	t0 = istime - (ig->bp - ig->buf)/b;
	/* ... and that of the earliest unread sample. */
	t1 = t0 + (ig->be - ig->buf)/b;
	/* There are three possibilities:  either the desired sample has been
	   read and has passed out of the buffer, requiring a rewind ... */
	if (t < t0) {
	    if (wfdb_fseek(ig->fp, 0L, 0)) {
		// // wfdb_error("isigsettime: improper seek on signal group %d\n",
			   //g);
		return (-1);
	    }
	    tt = t*b;
	    nb = tt/d + ig->start;
	}
	/* ... or it is in the buffer already ... */
	else if (t < t1) {
	    tt = (t - t0)*b;
	    ig->bp = ig->buf + tt/d;
	    return (0);
	}
	/* ... or it has not yet been read. */
	else {
	    tt = (t - t1) * b;
	    nb = tt/d;
	}
	while (nb > ig->bsize && !wfdb_feof(ig->fp))
	    nb -= wfdb_fread(ig->buf, 1, ig->bsize, ig->fp);
    }

    /* Reset the block point8_ter to indicate nothing has been read in the
       current block. */
    ig->bp = ig->be;
    ig->stat = 1;
    /* Read any bytes in the current block that precede the desired sample. */
    while (nb-- > 0 && ig->stat > 0)
	i = r8(ig);
    if (ig->stat <= 0) return (-1);

    /* Reset the getvec sample-within-frame counter. */
    gvc = ispfmax;

    /* Reset the time (if signal 0 beint16_ts to the group) and disable checksum
       testing (by setting the number of samples remaining to 0). */
    if (s == 0) istime = in_msrec ? t + segp->samp0 : t;
    while (n-- != 0)
	isd[s+n]->info.nsamp = (WFDB_Time)0L;
    return (0);
}

#define BUFLN   4096	/* must be a power of 2, see sample() */



/* sample(s, t) provides buffered random access to the input signals.  The
arguments are the signal number (s) and the sample number (t); the returned
value is the sample from signal s at time t.  On return, the global variable
sample_vflag is true (non-zero) if the requested sample is not beyond the end
of the record, false (zero) otherwise.  The caller must open the input signals
and must set the global variable nisig to the number of input signals before
invoking sample().  Once this has been done, the caller may request samples in
any order. */
//This function return the value (in raw adus) of sample number t in open signal s,
//if successful, or the value of the previous successfully read sample.
WFDB_Sample sample(WFDB_Signal s, WFDB_Time t)
{
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
        sample_vflag = -1;
	return (WFDB_INVALID_SAMPLE);
    }

    /* If the caller specified a negative sample number, prepare to return
       sample 0.  This behavior differs from the convention that only the
       absolute value of the sample number matters. */
    if (t < 0L) t = 0L;

    /* If the caller has requested a sample that is no int16_ter in the buffer,
       or if the caller has requested a sample that is further ahead than the
       length of the buffer, we need to reset the signal file point8_ter(s).
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
int8_t sample_valid(void)
{
    return (sample_vflag);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////  AQUI TERMINA LA PARTE DE LAURA  ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////





//ver http://physionet.org/physiotools/wpg/wpg_20.htm#SEC66
//void setgvmode(int8_t mode){}
//Return:
//>0 Success: the returned value is the number of input signals (i.e., the number of valid entries in siarray) 
//0  Failure: no input signals available 
//-1 Failure: unable to read header file (probably incorrect record name) 
//-2 Failure: incorrect header file format 

//int8_t isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig){return 0;}
//sets the current input sampling frequency
void setifreq(WFDB_Frequency frequency){
	
}
//his function converts the potential difference v from microvolts to ADC units, 
//based on the gain for input signal s.
WFDB_Sample muvadu(WFDB_Signal s, int8_t v){
			return 0;

}
//  0   Success 
//-1    Failure: write error 
//-2    Failure: incorrect annotator number specified 
//This function writes the next annotation for the output 
//annotator specified by an from the annotation structure pointed to by annot.
static unsigned noaf;		/* number of open output annotators */
typedef int8_t WFDB_FILE;
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
int8_t wfdbinit(char *record, WFDB_Anninfo *aiarray, uint8_t nann, WFDB_Siginfo *siarray, uint8_t nsig){
	           
	return 0;
	           	           
}	
//This function closes all open WFDB files and frees any memory allocated by other WFDB library functions
/*void wfdbquit(void){
	
}*/
//This function converts the potential difference a from ADC units to microvolts,
// based on the gain for input signal s.
/*
int8_t adumuv(WFDB_Signal s, WFDB_Sample a){
	
	return 0;	
}
//http://physionet.org/physiotools/wpg/wpg_23.htm#SEC85
WFDB_Time strtim(char *string){
	return 0;	
	
}
//This function determines the sampling frequency (in Hz) for the record specified by its argument.
WFDB_Frequency sampfreq(char *record){
	return 0;
	
}




*/

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

/********************************wfdbio.c*****************************************/
int8_t wfdb_fclose(WFDB_FILE *wp)
{
    int status;

#if WFDB_NETFILES
    status = (wp->type == WFDB_NET) ? nf_fclose(wp->netfp) : fclose(wp->fp);
#else
    status = fclose(wp->fp);
#endif
    if (wp->fp != stdin)
	(void)free(wp);
    return (status);
}


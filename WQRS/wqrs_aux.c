
//#include <stdio.h>
#include <math.h>
#include "wqrs.h"
# include <stdlib.h>
//# include <stdio.h>

#include <io.h>
/************************************declaraciones*******************************************/

WFDB_Sample *sbuf;	/* buffer used by sample() */


/*****************************************************************************************
**************Definiciones en sustitucion de #include <wfdb/wfdb.h>***********************
*******************************************************************************************/



//hace el objeto vsd (de se�al virtual)
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
	
		if (vsdnew == NULL) {
		    // // wfdb_error("init: too many (%d) input signals\n", nvsig);
		    return (-1);
		}
		vsd = vsdnew;
		while (m < nvsig) {
		    if ((vsd[m] = malloc(sizeof(struct isdata))) == NULL) {
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
//maneja los mapas de se�ales
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
	if ((smi = malloc(tspf * sizeof(struct sigmapinfo))) == NULL) {
	    // // wfdb_error("sigmap_init: out of memory\n");
	    return (-1);
	}

	for (i = s = 0; i < nisig; i++) {
	    if (smi[s].desc = malloc(strlen(isd[i]->info.desc)+1))
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

	if ((ovec = malloc(tspf * sizeof(WFDB_Sample))) == NULL) {
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

//pone el numero maximo de se�ales abiertas a la vez
static int8_t allocisig(int8_t n)
{
    if (maxisig < n) {
		unsigned m = maxisig;
		struct isdata **isdnew;
		//isdnew = (isdata **)realloc(isd, n*sizeof(struct isdata *));
	
		if (isdnew == NULL) {
	//	    // wfdb_error("init: too many (%d) input signals\n", n);
		    return (-1);
		}
		isd = isdnew;
		while (m < n) {
		    if ((isd[m] = (isdata *)malloc(sizeof(struct isdata))) == NULL) {
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
//libera las se�ales abiertas (estructura isdata)
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
    maxigroup = 0;

    istime = 0L;
    gvc = ispfmax = 1;
    //if (hheader) {  //puntero al fichero header
	//(void)wfdb_fclose(hheader);
	//hheader = NULL;
    //}
    if (nosig == 0 && maxhsig != 0)
	hsdfree();
}

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
	
	//char linebuf[256], *p, *q;
    WFDB_Frequency f;
    WFDB_Signal s;
    WFDB_Time ns;
    uint8_t8_t i, nsig;
    //static char sep[] = " \t\n\r";

    /* If another input header file was opened, close it. */
    //if (hheader) (void)wfdb_fclose(hheader);

    if (strcmp(record, "~") == 0) {
	if (in_msrec && vsd) {
	    char *p;

	    hsd = malloc(sizeof(struct hsdata *));
	    hsd[0] = malloc(sizeof(struct hsdata));
	    p = malloc(2*sizeof(char)); *p = '~';
	    hsd[0]->info.desc = p;
	    hsd[0]->info.spf = 1;
	    hsd[0]->info.fmt = 0;
	    hsd[0]->info.nsamp = nsamples = segp->nsamp;
	    return (1);	       
	}
	return (0);
    }

    /* Try to open the header file. */
    //if ((hheader = wfdb_open("hea", record, WFDB_READ)) == NULL) {
	// // wfdb_error("init: can't open header for record %s\n", record);
	//return (-1);
    //}

    /* Read the first line and check for a magic string. */
    //if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
        // // wfdb_error("init: record %s header is empty\n", record);
	//    return (-2);
    //}
    /*if (strncmp("#wfdb", linebuf, 5) == 0) { // found the magic string 
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
   /* while ((p = strtok(linebuf, sep)) == NULL || *p == '#') {
	if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
	    // // wfdb_error("init: can't find record name in record %s header\n",
		     record);
	    return (-2);
	}
    }*/

 /*   for (q = p+1; *q && *q != '/'; q++)
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
*/
    /* For local files, be sure that the name (p) within the header file
       matches the name (record) provided as an argument to this function --
       if not, the header file may have been renamed in error or its contents
       may be corrupted.  The requirement for a match is waived for remote
       files since the user may not be able to make any corrections to them. */
 /*   if (hheader->type == WFDB_LOCAL &&
	hheader->fp != stdin && strcmp(p, record) != 0) {*/
	/* If there is a mismatch, check to see if the record argument includes
	   a directory separator (whether valid or not for this OS);  if so,
	   compare only the final portion of the argument against the name in
	   the header file. */
/*	char *r, *s;

	for (r = record, s = r + strlen(r) - 1; r != s; s--)
	    if (*s == '/' || *s == '\\' || *s == ':')
		break;

	if (r > s || strcmp(p, s+1) != 0) {
	    // // wfdb_error("init: record name in record %s header is incorrect\n",
		       record);
	    return (-2);
	}
    }
*/
    /* Identify which type of header file is being read by trying to get
       another token from the line which contains the record name.  (Old-style
       headers have only one token on the first line, but new-style headers
       have two or more.) */
  /*  if ((p = strtok((char *)NULL, sep)) == NULL) {
	 //The file appears to be an old-style header file. 
	// // wfdb_error("init: obsolete format in record %s header\n", record);
	return (-2);
    }*/

    /* The file appears to be a new-style header file.  The second token
       specifies the number of signals. */
    nsig = 1;//(unsigned)atoi(p);

    /* Determine the frame rate, if present and not set already.
    if (p = strtok((char *)NULL, sep)) {*/
    f=360; //(WFDB_Frequency)atof(p)
	if (f  <= (WFDB_Frequency)0.) {
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
   // }
   // else if (ffreq == (WFDB_Frequency)0.)
     
     
	ffreq = WFDB_DEFFREQ;

    /* Set the sampling rate to the frame rate for now.  This may be
       changed later by isigopen or by setgvmode, if this is a multi-
       frequency record and WFDB_HIGHRES mode is in effect. */
    sfreq = ffreq;

    /* Determine the counter frequency and the base counter value. */
  /*  cfreq = bcount = 0.0;
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
    if (cfreq <= 0.0) cfreq = ffreq;*/

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
		       msnsamples);
	}
	return (0);
    }

    /* Allocate workspace. */
    if (maxhsig < nsig) {
	unsigned m = maxhsig;
	struct hsdata **hsdnew = realloc(hsd, nsig*sizeof(struct hsdata *));

	if (hsdnew == NULL) {
	    // // wfdb_error("init: too many (%d) signals in header file\n", nsig);
	    return (-2);
	}
	hsd = hsdnew;
	while (m < nsig) {
	    if ((hsd[m] = calloc(1, sizeof(struct hsdata))) == NULL) {
		// // wfdb_error("init: too many (%d) signals in header file\n",
			  // nsig);
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
	hs->skew = (int8_t)(((int32_t)hs->skew)/hs->info.spf + 0.5);

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
		       s-1, s);
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
	else
	  //  (void)sprint8_tf(hs->info.desc,
		//	  "record %s, signal %d", record, s);
    }
    return (s);			/* return number of available signals */
}






//Return:
//>0 Success: the returned value is the number of input signals (i.e., the number of valid entries in siarray) 
//0  Failure: no input signals available 
//-1 Failure: unable to read header file (probably incorrect record name) 
//-2 Failure: incorrect header file format 

int8_t isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig){ //nota:esto en un principio se puede quitar pero cuidado con las variables internas
	int8_t navail, ngroups, nn;
    struct hsdata *hs;
    struct isdata *is;
    //struct igdata *ig;
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
	
		if (siarray != NULL)  
		    for (s = 0; s < nsig; s++)
				siarray[s] = hsd[s]->info;
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
static int rgetvec(WFDB_Sample *vector)
{
   /* WFDB_Sample *tp;
    WFDB_Signal s;
    static int stat;

    if (ispfmax < 2)	/* all signals at the same frequency */
	/*return (getframe(vector));

    if (gvmode != WFDB_HIGHRES) {/* return one sample per frame, decimating
				   (by averaging) if necessary */
/*	unsigned c;
	long v;
	
	stat = getframe(tvector);
	for (s = 0, tp = tvector; s < nvsig; s++) {
	    int sf = vsd[s]->info.spf;

	    for (c = v = 0; c < sf; c++)
		v += *tp++;
	    *vector++ = v/sf;
	}
    }
    else {			/* return ispfmax samples per frame, using
				   zero-order interpolation if necessary */
	/*if (gvc >= ispfmax) {
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
    return (stat);*/
}


//sets the current input sampling frequency
int8_t setifreq(WFDB_Frequency f){
	if (f > 0.0) {
	WFDB_Frequency error, g = sfreq;

	nisig=1;//esto lo meto yo porq creo que tiene este valor
	nvsig=nisig; //esto lo a�adimos nosotras porq sabemos que es el mismo valor 
	
	//gv0 = (WFDB_Sample*)realloc(gv0, nisig*sizeof(WFDB_Sample));
	//gv1 = (WFDB_Sample*)realloc(gv1, nisig*sizeof(WFDB_Sample));
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
int8_t putann(WFDB_Annotator n, WFDB_Annotation *annot){ //sabemos n=0
	/*unsigned annwd;
    char *ap;
    int i, len;
    long delta;
    WFDB_Time t;*/
    //struct oadata *oa;

   /* if (n >= noaf || (oa = oad[n]) == NULL || oa->file == NULL) {
		//printf("putann: can't write annotation file %d\n", n);
	return (-2);
    }*/
   /* if (annot->time == 0L)
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
   /*   default:
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
		//printf("putann: write error on annotation file %s\n",  oa->info.name);
	return (-1);
    }
    oa->ann = *annot;
    oa->ann.time = t;
    return (0);*/
}




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


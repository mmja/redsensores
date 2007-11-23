
//----------------------------------------------- adumuv -------------------------------------------------

//This function converts the potential difference a from ADC units to microvolts,
// based on the gain for input signal s.
int8_t adumuv(WFDB_Signal s, WFDB_Sample a){
	
	int32_t x;
    WFDB_Gain g = (s < nvsig) ? vsd[s]->info.gain : WFDB_DEFGAIN;

    if (g == 0.) g = WFDB_DEFGAIN;
    x = a*1000./g;
    if (x >= 0.0)
	return ((int8_t)(x + 0.5));
    else
	return ((int8_t)(x - 0.5));
}

//--------------------------------------- readheader -------------------------------------------------------
static int8_t readheader(char *record)
{
    	
	//char linebuf[256], *p, *q;
    WFDB_Frequency f;
    WFDB_Signal s;
    WFDB_Time ns;
    uint8_t8_t i, nsig;
    //static char sep[] = " \t\n\r";

    /* If another input header file was opened, close it. */
    //if (hheader) (void)wfdb_fclose(hheader);

    /*if (strcmp(record, "~") == 0) {    //esto es cuando record no es correcto
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
    }*/

    /* Try to open the header file. */
    //if ((hheader = wfdb_open("hea", record, WFDB_READ)) == NULL) { //mete la informacion del fichero en hheader
	// // wfdb_error("init: can't open header for record %s\n", record);
	//return (-1);
    //}

    // Read the first line and check for a magic string. 
    //if (wfdb_fgets(linebuf, 256, hheader) == NULL) {  //lee la primera linea del fichero (256 caracteres)
        // // wfdb_error("init: record %s header is empty\n", record);
	//    return (-2);
    //}
    
    /*//OTRO FORMATO DE FICHERO
    //mira la version de la libreria, por si no esta actualizada
    if (strncmp("#wfdb", linebuf, 5) == 0) { // found the magic string 
		int8_t i, major, minor = 0, release = 0;
	
		i = sscanf(linebuf+5, "%d.%d.%d", &major, &minor, &release);
		if ((i > 0 && major > WFDB_MAJOR) ||
		    (i > 1 && minor > WFDB_MINOR) ||
		    (i > 2 && release > WFDB_RELEASE)) {
			    // wfdb_error("init: reading record %s requires WFDB library "
				//       "version %d.%d.%d or later\n"
		
				//"  (the most recent version is always available from http://physionet.org)\n",
				
				//       record, major, minor, release);
			    return (-1);
		}
    }

    // Get the first token (the record name) from the first non-empty,
    //   non-comment line. 
    //salta lineas hasta encontrar una linea valida
   /* while ((p = strtok(linebuf, sep)) == NULL || *p == '#') {   //p apunta al primer token de la primera linea valida 
		if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
		    // // wfdb_error("init: can't find record name in record %s header\n",
			     record);
		    return (-2);
		}
    }*/
	//al final de esto p=primera linea 1 palabra
 /*   for (q = p+1; *q && *q != '/'; q++)  //aqui busca una barra "/" que deben ser para los segmentados
	;
    if (*q == '/') {
		if (in_msrec) {
		    // wfdb_error("init: record %s cannot be nested in another multi-segment record\n",
			//  record);
		    return (-2);
		}
		segments = atoi(q+1);
		*q = '\0';
    }
*/


//comprueba que el nombre del record y su primer argumento coincidan o que sea valido 
    /* For local files, be sure that the name (p) within the header file
       matches the name (record) provided as an argument to this function --
       if not, the header file may have been renamed in error or its contents
       may be corrupted.  The requirement for a match is waived for remote
       files since the user may not be able to make any corrections to them. */
 /*   if (hheader->type == WFDB_LOCAL && hheader->fp != stdin && strcmp(p, record) != 0) {*/
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
  /*  if ((p = strtok((char *)NULL, sep)) == NULL) {  //p=primera linea 2 palabra
	 //The file appears to be an old-style header file. (solo puede haber cabeceras nuevas)
	//  wfdb_error("init: obsolete format in record %s header\n", record);
	return (-2);
    }*/

    /* The file appears to be a new-style header file.  The second token
       specifies the number of signals. */
    nsig = (unsigned)1;//(unsigned)atoi(p);   --> ya que p apunta al 1 del fichero

    /* Determine the frame rate, if present and not set already.
    if (p = strtok((char *)NULL, sep)) {   //p=primera linea 3 palabra  ->360 tasa de frames*/   
    f=(WFDB_Frequency)360; //(WFDB_Frequency)atof(p)
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
   // else if (ffreq == (WFDB_Frequency)0.)	ffreq = WFDB_DEFFREQ;

    /* Set the sampling rate to the frame rate for now.  This may be
       changed later by isigopen or by setgvmode, if this is a multi-
       frequency record and WFDB_HIGHRES mode is in effect. */
    sfreq = ffreq;

    /* Determine the counter frequency and the base counter value. */
    cfreq = bcount = 0.0;
   /* if (p) {  //busca algo tipo "/cfreq    (bcount)", en nuestro caso no lo tenemos, de momento nos lo cargamos 
		for ( ; *p && *p != '/'; p++)
		    ;
		if (*p == '/') {
		    cfreq = atof(++p);
		    for ( ; *p && *p != '('; p++)
			;
		    if (*p == '(')	bcount = atof(++p);
		}
    }*/
    if (cfreq <= 0.0) cfreq = ffreq;

    /* Determine the number of samples per signal, if present and not
       set already. */
    //if (p = strtok((char *)NULL, sep)) {  //p=primera linea 4 palabra -> 650000 (num muestras por señal)
		ns=650000;
    	if (ns /*(ns = (WFDB_Time)atol(p))*/ < 0L) {
		    //  wfdb_error("init: number of samples in record %s header is incorrect\n",record);
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
    //} else ns = (WFDB_Time)0L;

    /* Determine the base time and date, if present and not set already. */
    //de momento no tenemos en cuenta la fecha ni el tiempo base 
    /*if ((p = strtok((char *)NULL,"\n\r")) != NULL && btime == 0L && setbasetime(p) < 0)
	return (-2);	// error message will come from setbasetime 
*/
    /* Special processing for master header of a multi-segment record. */
   /* if (segments && !in_msrec) {
		msbtime = btime;
		msbdate = bdate;
		msnsamples = nsamples;
		// Read the names and lengths of the segment records. 
		segarray = (struct segrec *)calloc(segments, sizeof(struct segrec));
		if (segarray == (struct segrec *)NULL) {
		    // // wfdb_error("init: insufficient memory\n");
		    segments = 0;
		    return (-2);
		}
		segp = segarray;
		for (i = 0, ns = (WFDB_Time)0L; i < segments; i++, segp++) {
		    // Get next segment spec, skip empty lines and comments. 
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
    }*/

    /* Allocate workspace. -  reserva el espacio a la estructura hsd segun el numero de señales*/
    if (maxhsig < nsig) {
		unsigned m = maxhsig;
		struct hsdata **hsdnew = realloc(hsd, nsig*sizeof(struct hsdata *));
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
		    if ((hsd[m] = malloc(sizeof(struct hsdata))) == NULL) {
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
		//if (s) hp = hsd[s-1];
		/* Get the first token (the signal file name) from the next
		   non-empty, non-comment line. */
		/*do {  //busca la siguiente linea no comentada y no vacia
		    if (wfdb_fgets(linebuf, 256, hheader) == NULL) {
			// // wfdb_error(
			//	"init: unexpected EOF in header file for record %s\n",
			//	record);
			return (-2);
		    }
		} while ((p = strtok(linebuf, sep)) == NULL || *p == '#');//p=segunda linea 1 palabra -> 100.dat*/
	
		/* Determine the signal group number.  The group number for signal
		   0 is zero.  For subsequent signals, if the file name does not
		   match that of the previous signal, the group number is one
		   greater than that of the previous signal. */
		/*if (s == 0 || strcmp(p, hp->info.fname)) {
			hs->info.group = (s == 0) ? 0 : hp->info.group + 1;
			if ((hs->info.fname =(char *)malloc((unsigned)(strlen(p)+1))) == NULL) {
			    // // wfdb_error("init: insufficient memory\n");
			    return (-2);
			}
			(void)strcpy(hs->info.fname, p);
		}*/
		//en sustitucion al if anterior. inicio
		hs->info.group = 0;
		if ((hs->info.fname =(char *)malloc((unsigned)(strlen("100.dat")+1))) == NULL) {
			    // // wfdb_error("init: insufficient memory\n");
			    return (-2);
		}
		(void)strcpy(hs->info.fname, "100.dat");
		//fin
		
		
		/* If the file names of the current and previous signals match,
		   they are assigned the same group number and share a copy of the
		   file name.  All signals associated with a given file must be
		   listed together in the header in order to be identified as
		   beint16_ting to the same group;  readheader does not check that
		   this has been done. */
		/*else {  //si tiene mas de una señal
		    hs->info.group = hp->info.group;
		    if ((hs->info.fname = (char *)malloc(strlen(hp->info.fname)+1))
			     == NULL) {
			    // // wfdb_error("init: insufficient memory\n");
			    return (-2);
			}
			(void)strcpy(hs->info.fname, hp->info.fname);
		}*/
	
		/* Determine the signal format. */
		//if ((p = strtok((char *)NULL, sep)) == NULL || /p=segunda linea 2 palabra -> 212 (fmt=format)
		if (!isfmt(hs->info.fmt = 212/*atoi(p)*/)) { //comprobamos que el formato es valido
		    // // wfdb_error("init: illegal format for signal %d, record %s\n",
			    //   s, record);
		    return (-2);
		}
		hs->info.spf = 1;
		hs->skew = 0;
		hs->start = 0L;
		/*while (*(++p)) {//"xspf:skew+start"
		    if (*p == 'x' && *(++p))
			if ((hs->info.spf = atoi(p)) < 1) hs->info.spf = 1;
		    if (*p == ':' && *(++p))
			if ((hs->skew = atoi(p)) < 0) hs->skew = 0;
		    if (*p == '+' && *(++p))
			if ((hs->start = atol(p)) < 0L) hs->start = 0L;
		}*/
		/* The resolution for deskewing is one frame.  The skew in samples
		   (given in the header) is converted to skew in frames here. */
		hs->skew = (int8_t)(((int32_t)hs->skew)/hs->info.spf + 0.5);
	
		/* Determine the gain in ADC units per physical unit.  This number
		   may be zero or missing;  if so, the signal is uncalibrated. */
		/*if (p = strtok((char *)NULL, sep))  //p=segunda linea 3 palabra ->200 gain
		    hs->info.gain = (WFDB_Gain)atof(p);
		else
		    hs->info.gain = (WFDB_Gain)0.;*/
		    hs->info.gain=(WFDB_Gain)200; //esto es raro porq se supone que es 0
	
		/* Determine the baseline if specified, and the physical units
		   (assumed to be millivolts unless otherwise specified). */
		nobaseline = 1;
		/*if (p) { //busca un paretesis para establecer baseline
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
		if (p && *p) {  //como no ha encontrado (, p=NULL
		    if ((hs->info.units=(char *)malloc(WFDB_MAXUSL+1)) == NULL) {
			// // wfdb_error("init: insufficient memory\n");
			return (-2);
		    }
		    (void)strncpy(hs->info.units, p, WFDB_MAXUSL);
		}
		else*/
		    hs->info.units = NULL;
	
		/* Determine the ADC resolution in bits.  If this number is
		   missing and cannot be inferred from the format, the default
		   value (from wfdb.h) is filled in. */
		/*if (p = strtok((char *)NULL, sep))  //p=segunda linea 4 palabra -> 11
		    i = (unsigned)atoi(p);
		else switch (hs->info.fmt) {
		  case 80: i = 8; break;
		  case 160: i = 16; break;
		  case 212: i = 12; break;
		  case 310: i = 10; break;
		  case 311: i = 10; break;
		  default: i = WFDB_DEFRES; break;
		}*/
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
		//if (p = strtok((char *)NULL, sep)) {
		    hs->info.cksum = -22131;//atoi(p);
		    hs->info.nsamp = ns;
		/*}
		else {
		    hs->info.cksum = 0;
		    hs->info.nsamp = (WFDB_Time)0L;
		}*/
	
		/* Determine the block size (assumed to be zero if missing). */
		hs->info.bsize = 0;//(p = strtok((char *)NULL, sep)) ? atoi(p) : 0;
	
		/* Check that formats and block sizes match for signals beinting
		   to the same group. */
		/*if (s && hs->info.group == hp->info.group &&  //no lo hace porque s=0
		    (hs->info.fmt != hp->info.fmt ||
		     hs->info.bsize != hp->info.bsize)) {
		    // // wfdb_error("init: error in specification of signal %d or %d\n",
			       s-1, s);
		    return (-2);
		}*/
		    
		/* Get the signal description.  If missing, a description of
		   the form "record xx, signal n" is filled in. */
		if ((hs->info.desc = (char *)malloc(WFDB_MAXDSL+1)) == NULL) {
		    // // wfdb_error("init: insufficient memory\n");
		    return (-2);
		}
		//if (p = strtok((char *)NULL, "\n\r"))
		    (void)strncpy(hs->info.desc, "MLII"/*p*/, WFDB_MAXDSL);
		//else
		  //  (void)sprint8_tf(hs->info.desc,
			//	  "record %s, signal %d", record, s);
   // }
    return (s);			/* return number of available signals */
}


/**************************************************************************************************************************/


/* annopen: open annotation files for the specified record 
llena las estructuras oadata y iadata, que contienen la informacion del fichero de salida

*/

int8_t annopen(char *record, WFDB_Anninfo *aiarray, unsigned int nann) //"100",["wqrs",write],1 (nann: numero de posiciones de aiarray
{
    int a;
    unsigned int i, niafneeded, noafneeded;

    if (*record == '+')		/* don't close open annotation files */
		record++;		/* discard the '+' prefix */
    else {
		//wfdb_anclose();		/* close previously opened annotation files */
		//tmul = 0.0;
    }

    /* Prescan aiarray to see how large maxiann and maxoann must be. */
    niafneeded = niaf;
    noafneeded = noaf;
    for (i = 0; i < nann; i++)
		switch (aiarray[i].stat) {
		  case WFDB_READ:	/* standard (MIT-format) input file */
		  case WFDB_AHA_READ:	/* AHA-format input file */
		    niafneeded++;
		    break;
		  case WFDB_WRITE:	/* standard (MIT-format) output file */
		  case WFDB_AHA_WRITE:	/* AHA-format output file */
		    noafneeded++;
		    break;
		  default:
		    /*wfdb_error(
			     "annopen: illegal stat %d for annotator %s, record %s\n",
			     aiarray[i].stat, aiarray[i].name, record);*/
		    return (-5);
		}
    /* Allocate workspace. */
    if (allociann(niafneeded) < 0 || allocoann(noafneeded) < 0)
	return (-3);

    for (i = 0; i < nann; i++) { /* open the annotation files */
	struct iadata *ia;
	struct oadata *oa;

	switch (aiarray[i].stat) {
	  case WFDB_READ:	/* standard (MIT-format) input file */
	  case WFDB_AHA_READ:	/* AHA-format input file */
	    ia = iad[niaf];
	    wfdb_setirec(record);
	    if ((ia->file=wfdb_open(aiarray[i].name,record,WFDB_READ)) ==NULL) {
			//wfdb_error("annopen: can't read annotator %s for record %s\n", aiarray[i].name, record);
			return (-3);
	    }
	    if ((ia->info.name = (char *)malloc((unsigned)(strlen(aiarray[i].name)+1)))	 == NULL) {
			//wfdb_error("annopen: insufficient memory\n");
			return (-3);
	    }
	    (void)strcpy(ia->info.name, aiarray[i].name);

	    /* Try to figure out what format the file is in.  AHA-format files
	       begin with a null byte and an ASCII character which is one
	       of the legal AHA annotation codes other than '[' or ']'.
	       MIT annotation files cannot begin in this way. */
	    ia->word = (unsigned)wfdb_g16(iad[niaf]->file);
	    a = (ia->word >> 8) & 0xff;
	    if ((ia->word & 0xff) ||
		ammap(a) == NOTQRS || a == '[' || a == ']') {
		if (aiarray[i].stat != WFDB_READ) {
		   // wfdb_error("warning (annopen, annotator %s, record %s):\n",
			//     aiarray[i].name, record);
		    //wfdb_error(" file appears to be in MIT format\n");
		    //wfdb_error(" ... continuing under that assumption\n");
		}
		(ia->info).stat = WFDB_READ;
		/* read any initial null annotation(s) */
		while ((ia->word & CODE) == SKIP) {
		    ia->tt += wfdb_g32(ia->file);
		    ia->word = (unsigned)wfdb_g16(ia->file);
		}
	    }
	    else {
		if (aiarray[i].stat != WFDB_AHA_READ) {
		   // wfdb_error("warning (annopen, annotator %s, record %s):\n",
		//	     aiarray[i].name, record);
		  //  wfdb_error(" file appears to be in AHA format\n");
		     // wfdb_error(" ... continuing under that assumption\n");
		}
		ia->info.stat = WFDB_AHA_READ;
	    }
	    ia->ann.anntyp = 0;    /* any pushed-back annot is invalid */
	    niaf++;
	    (void)get_ann_table(niaf-1);
	    break;

	  case WFDB_WRITE:	/* standard (MIT-format) output file */
	  case WFDB_AHA_WRITE:	/* AHA-format output file */
	    oa = oad[noaf];
	    /* Quit (with message from wfdb_checkname) if name is illegal */
	    if (wfdb_checkname(aiarray[i].name, "annotator"))
		return (-4);
	    if ((oa->file=wfdb_open(aiarray[i].name,record,WFDB_WRITE)) ==	NULL) {
		//wfdb_error("annopen: can't write annotator %s for record %s\n", aiarray[i].name, record);
		return (-4);
	    }
	    if ((oa->info.name =
		 (char *)malloc((unsigned)(strlen(aiarray[i].name)+1)))
		== NULL) {
		wfdb_error("annopen: insufficient memory\n");
		return (-4);
	    }
	    (void)strcpy(oa->info.name, aiarray[i].name);
	    if ((oa->rname = (char *)malloc((unsigned)(strlen(record)+1)))== NULL) {
		//wfdb_error("annopen: insufficient memory\n");
		return (-4);
	    }
	    (void)strcpy(oa->rname, record);
	    oa->ann.time = 0L;
	    oa->info.stat = aiarray[i].stat;
	    oa->out_of_order = 0;
	    (void)put_ann_table(noaf++);
	    break;
	}
    }
    return (0);
   
}
/************************************************************************************************************************/

//This function determines the sampling frequency (in Hz) for the record specified by its argument.
WFDB_Frequency sampfreq(char *record){
	int n;

    if (record != NULL) {
		/* Save the current record name. */
		wfdb_setirec(record);
		/* Don't require the sampling frequency of this record to match that
		   of the previously opened record, if any.  (readheader will
		   complain if the previously defined sampling frequency was > 0.) */
		setsampfreq(0.);
		/* readheader sets sfreq if successful. */
		if ((n = readheader(record)) < 0)
		    /* error message will come from readheader */
		    return ((WFDB_Frequency)n);
    }
    return (sfreq);
	
}



//-----------------------------------------------putann--------------------------------------------------
// putann	-->	writes an annotation
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
 
/* Annotation word format */
#define CODE	0176000	/* annotation code segment of annotation word */
#define CS	10	/* number of places by which code must be shifted */
#define DATA	01777	/* data segment of annotation word */
#define MAXRR	01777	/* longest interval which can be coded in a word */

/* Pseudo-annotation codes.  Legal pseudo-annotation codes are between PAMIN
   (defined below) and CODE (defined above).  PAMIN must be greater than
   ACMAX << CS (see <ecg/ecgcodes.h>). */
#define PAMIN	((unsigned)(59 << CS))
#define SKIP	((unsigned)(59 << CS))	/* long null annotation */
				   
/* putann: write annotation at annot to annotator n */
//Se rellena la estructura "oa" del tipo oadata usando annot
int8_t putann(WFDB_Annotator n, WFDB_Annotation *annot)//sabemos n=0
{
    unsigned annwd;
    char *ap;
    int i, len;
    long delta;
    WFDB_Time t;
    struct oadata *oa;
	//Intenta abrir el fichero:
    /*if (n >= noaf || (oa = oad[n]) == NULL || oa->file == NULL) {
	//wfdb_error("putann: can't write annotation file %d\n", n);
		return (-2);
    }*/
	//Determina el instante t
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
    //Si "one or more annotations written by putann are not in the canonical (time, chan) order" :
    if (((delta = t - oa->ann.time) < 0L ||(delta == 0L && annot->chan <= oa->ann.chan)) &&(t != 0L || oa->ann.time != 0L)) {
		oa->out_of_order = 1;
    }
    //Dependiendo del tipo de fichero de salida que sea el que contiene oa:
    switch (oa->info.stat) {
      case WFDB_WRITE:	/* MIT-format output file */
      default:
      		//Creo que esto es un caso de error:
			if (annot->anntyp == 0) {
			    /* The caller intends to write a null annotation here, but putann
			       must not write a word of zeroes that would be interpreted as
			       an EOF.  To avoid this, putann writes a SKIP to the location
			       just before the desired one;  thus annwd (below) is never 0. */
			    wfdb_p16(SKIP, oa->file); wfdb_p32(delta-1, oa->file); delta = 1;
			}
			else if (delta > MAXRR || delta < 0L) {
			    wfdb_p16(SKIP, oa->file); wfdb_p32(delta, oa->file); delta = 0;
			}	
			
			// OJO!!!!! MAXRR, SKIP, DATA, SUB, CS ... son todo contstantes definidas justo antes de esta funcion 
			// Y las funciones estan en wfdbio.c :
			// wfdb_p16		(writes a 16-bit integer)
 			// wfdb_p32		(writes a 32-bit integer)
			// wfdb_mamap [10.4]	(function version of mamap, see ecgmap.h)en annot.c
			
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
			(void)wfdb_putc('\0', oa->file);
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
    
    //Si el fichero de output da error
    if (wfdb_ferror(oa->file)) {
	//wfdb_error("putann: write error on annotation file %s\n",oa->info.name);
	return (-1);
    }
    oa->ann = *annot;
    oa->ann.time = t;
    return (0);
}
///.......................Funciones de wfdbio.c para putann.......................................
int wfdb_putc(int c, WFDB_FILE *wp)
{
    if (wp->type == WFDB_NET)
	return (nf_putc(c, wp->netfp));
    return (putc(c, wp->fp));
}

/* write a 16-bit integer in PDP-11 format */
void wfdb_p16(unsigned int x, WFDB_FILE *fp)
{
    (void)wfdb_putc((char)x, fp);
    (void)wfdb_putc((char)(x >> 8), fp);
}

/* write a 32-bit integer in PDP-11 format */
void wfdb_p32(long x, WFDB_FILE *fp)
{
    wfdb_p16((unsigned int)(x >> 16), fp);
    wfdb_p16((unsigned int)x, fp);
}
//............................................................................................


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
			   //followed by 'r' 
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

//-----------------------------------------------------------------------------------
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
/*#ifndef BSD
# include <string.h>
#else		// for Berkeley UNIX only 
# include <strings.h>
#endif

#ifdef FIXSTRINGS
// This function leaks memory!  Ideally we would like to free(t) once *t is
//   no longer needed.  If this is a concern, we might push all values assigned
//   to t onto a stack and free them all on exit.  In practice we are usually
//   dealing with a small number of short strings. 
char *fcstring(char *s)	// change final space to null 
{
    char *p = s, *t;

    while (*s && *s != ' ')
	s++;
    //t = calloc(1, s-p+1);
    t = malloc(s-p+1);
    if (s > p) strncpy(t, p, s-p);
    return (t);
}

char *cfstring(char *s)	// change final null to space 
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
#endif*/

//static WFDB_Siginfo sinfo[WFDB_MAXSIG];
//static WFDB_Anninfo ainfo[WFDB_MAXANN*2];










/****************************************************************************************************************************

****************************************  WQRS.C - MAIN  *******************************************************************

****************************************************************************************************************************/

/* 
MODIFICACION DEL WQRS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

file: wqrs.c		Wei Zong      23 October 1998
			Last revised: 25 February 2006 (by G. Moody)
-----------------------------------------------------------------------------
wqrs: Single-lead QRS detector based on length transform
Copyright (C) 1998-2006 Wei Zong

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA.

You may contact the author by e-mail (wzong@mit.edu) or postal mail
(MIT Room E25-505, Cambridge, MA 02139, USA).  For updates to this software,
please visit PhysioNet (http://www.physionet.org/).
------------------------------------------------------------------------------

This program analyzes an ECG signal, detecting QRS onsets and J-points, using
a nonlinearly-scaled ECG curve length feature.  This version has been optimized
for ECGs sampled at 125 Hz, but it can analyze ECGs sampled at any frequency
using on-the-fly resampling provided by the WFDB library.

`wqrs' can process records containing any number of signals, but it uses only
one signal for QRS detection (signal 0 by default;  this can be changed using
the `-s' option, see below).  'wqrs' has been optimized for adult human ECGs.
For other ECGs, it may be necessary to experiment with the input sampling
frequency and the time constants indicated below.

To compile this program under GNU/Linux, MacOS/X, MS-Windows, or Unix, use gcc:
	gcc -o wqrs wqrs.c -lwfdb -lm
You must have installed the WFDB library, available at	
	http://www.physionet.org/physiotools/wfdb.shtml
gcc is standard with GNU/Linux and is available for other platforms from:
	http://www.gnu.org/		(sources and Unix binaries)
	http://fink.sourceforge.net	(Mac OS/X only)
	http://www.cygwin.com/   	(MS-Windows only)
	
For a usage summary, see the help text at the end of this file.  The input
record may be in any of the formats readable by the WFDB library, and it may
be anywhere in the WFDB path (in a local directory or on a remote web or ftp
server).  The output of 'wqrs' is an annotation file named RECORD.wqrs (where
RECORD is replaced by the name of the input record).  Within the output
annotation file, the time of each NORMAL annotation marks a QRS onset;  if
the '-j' option is used, additional JPT annotations mark the J points (the
ends of the QRS complexes).  During the learning period (the first LPERIOD
samples), LEARN annotations are used instead of NORMAL annotations, and there
are no JPT annotations.

For example, to mark QRS complexes in record 100 beginning 5 minutes from the
start, ending 10 minutes and 35 seconds from the start, and using signal 1, use
the command:
    wqrs -r 100 -f 5:0 -t 10:35 -s 1
The output may be read using (for example):
    rdann -a wqrs -r 100
To evaluate the performance of this program, run it on the entire record, by:
    wqrs -r 100
and then compare its output with the reference annotations by:
    bxb -r 100 -a atr wqrs
*/

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
#include "wqrs.h"
//#include <io.h>

//#include <wfdb/wfdb.h>
//#include <wfdb/ecgcodes.h>
//#include <wfdb/ecgmap.h>  //librerias quitadas con exito




/*************************************************************************************
*******************comienza el programa**********************************************
*************************************************************************************/

#define BUFLN  16384	/* must be a power of 2, see ltsamp() */
#define EYE_CLS 0.25    /* eye-closing period is set to 0.25 sec (250 ms) */ 
#define LPERIOD 1000	/* learning period is the first LPERIOD samples */
#define MaxQRSw 0.13    /* maximum QRS width (130ms) */                        
#define NDP	 2.5    /* adjust threshold if no QRS found in NDP seconds */
#define PWFreqDEF 60    /* power line (mains) frequency, in Hz (default) */
#define TmDEF	 100	/* minimum threshold value (default) */


char *pname;		/* the name by which this program was invoked */
int32_t lfsc;		/* length function scale constant */
int8_t *ebuf;
int8_t nsig;		/* number of input signals */
int8_t LPn, LP2n;          /* filter parameters (dependent on sampling rate) */
int8_t LTwindow;           /* LT window size */
int8_t PWFreq = PWFreqDEF;	/* power line (mains) frequency, in Hz */
int8_t sig = 0;	        /* signal number of signal to be analyzed */
int8_t Tm = TmDEF;		/* minimum threshold value */
WFDB_Sample *lbuf = NULL;


/* ltsamp() returns a sample of the length transform of the input at time t.
   Since this program analyzes only one signal, ltsamp() does not have an
   input argument for specifying a signal number; rather, it always filters
   and returns samples from the signal designated by the global variable
   'sig'.  The caller must never "rewind" by more than BUFLN samples (the
   length of ltsamp()'s buffers). */

WFDB_Sample ltsamp(WFDB_Time t)
{
    int8_t dy;
    static int8_t Yn, Yn1, Yn2;
    static WFDB_Time tt = (WFDB_Time)-1L;

    if (lbuf == NULL) {
		lbuf = (WFDB_Sample *)malloc((unsigned)BUFLN*sizeof(WFDB_Sample));
		ebuf = (int8_t *)malloc(BUFLN * sizeof(int8_t));
		if (lbuf && ebuf) {
		    for (ebuf[0] = sqrtf(lfsc), tt = 1L; tt < BUFLN; tt++)
				ebuf[tt] = ebuf[0];
		    if (t > BUFLN) tt = (WFDB_Time)(t - BUFLN);
		    else tt = (WFDB_Time)-1L;
		    Yn = Yn1 = Yn2 = 0;
		}
		else {
		    //(void)fprintf(stderr, "%s: insufficient memory\n", pname);
		    exit(2);
		}
    }
    if (t < tt - BUFLN) {
      //  fprintf(stderr, "%s: ltsamp buffer too short\n", pname);
		exit(2);
    }
    while (t > tt) {
		static int8_t aet = 0, et;
		WFDB_Sample v0, v1, v2;
	
		Yn2 = Yn1;
		Yn1 = Yn;
		if ((v0 = sample(sig, tt)) != WFDB_INVALID_SAMPLE &&
		    (v1 = sample(sig, tt-LPn)) != WFDB_INVALID_SAMPLE &&
		    (v2 = sample(sig, tt-LP2n)) != WFDB_INVALID_SAMPLE)
		    Yn = 2*Yn1 - Yn2 + v0 - 2*v1 + v2;
		dy = (Yn - Yn1) / LP2n;		/* lowpass derivative of input */
		et = ebuf[(++tt)&(BUFLN-1)] = sqrtf(lfsc +dy*dy); /* length transform */
		lbuf[(tt)&(BUFLN-1)] = aet += et - ebuf[(tt-LTwindow)&(BUFLN-1)];
		/* lbuf contains the average of the length-transformed samples over
		   the interval from tt-LTwindow+1 to tt */
    }
    return (lbuf[t&(BUFLN-1)]);
}

main(int8_t argc, char **argv)
{ 
    //char *p;				// toma valor de getenv(...)-> siempre vale 0
   // char *record = NULL;	     /* input record name */
    float sps;			     /* sampling frequency, in Hz (SR) */
    float samplingInterval;          /* sampling interval, in milliseconds */
    int8_t i, max, min, minutes = 0, onset, timer;
    
    int8_t Rflag = 0;		     /* if non-zero, resample at 120 or 150 Hz  */
    
    int8_t EyeClosing;                  /* eye-closing period, related to SR */
    int8_t ExpectPeriod;                /* if no QRS is detected over this period,
					the threshold is automatically reduced
					to a minimum value;  the threshold is
					restored upon a detection */
    double Ta, T0;			     /* high and low detection thresholds */
    //WFDB_Anninfo a;
  //  WFDB_Annotation annot;
    WFDB_Gain gain;
    WFDB_Sample *v;
    WFDB_Siginfo *s;
    WFDB_Time  next_minute, now, spm, t, tj, tpq, tt, t1,from = 0L, to = 0L;
    static int8_t gvmode = 0; //esta se usa para la opcion H pero me creo q tb se usa en otras cosas
    char *prog_name();
    
    /*//variables comentadas porque quitamos las opciones relacionadas:
    
    	int8_t dflag = 0;		     // if non-zero, dump raw and filtered samples only;  do not run detector 
    	int8_t jflag = 0;		     // if non-zero, annotate J-points 
    	int8_t vflag = 0;
    	
    	    
    */
   

    pname = prog_name(argv[0]);

    for (i = 1; i < argc; i++) {
	if (*argv[i] == '-') 
	switch (*(argv[i]+1)) {
	  /*case 'd':	// dump filter data 
	    dflag = 1;
	    break;*/
	 /* case 'f':	// starting time 
	    if (++i >= argc) {
		//(void)fprintf(stderr, "%s: time must follow -f\n", pname);
		exit(1);
	    }
	    from = i;
	    break;*/
	
	/*  case 'H':	// operate in WFDB_HIGHRES mode 
	    gvmode = WFDB_HIGHRES;
	    break;*/
	 /* case 'j':	// annotate J-points (ends of QRS complexes) 
	    jflag = 1;
	    break;*/
	  /*case 'm':	// threshold 
	    if (++i >= argc || (Tm = atoi(argv[i])) <= 0) {
		//(void)fprintf(stderr, "%s: threshold ( > 0) must follow -m\n",
		//	      pname);
		exit(1);
	    }
	    break;*/
	  case 'p':	/* specify power line (mains) frequency */
	    if (++i >= argc || (PWFreq = atoi(argv[i])) <= 0) {
		//(void)fprintf(stderr,"%s: power line frequency ( > 0) must follow -p\n", pname);
		exit(1);
	    }
	    break;
	  case 'r':	// record name 
	    if (++i >= argc) {
		//(void)fprintf(stderr, "%s: input record name must follow -r\n",  pname);
		exit(1);
	    }
	    //record = argv[i];
	    break;
	  case 'R':	// resample 
	    Rflag = 1;
	    break;
	 /* case 's':	// signal 
	    if (++i >= argc) {
		//(void)fprintf(stderr, "%s: signal number must follow -s\n", pname);
		exit(1);
	    }
	    sig = atoi(argv[i]);
	    break;*/
	 /* case 't':	// end time 
	    if (++i >= argc) {
		//(void)fprintf(stderr, "%s: time must follow -t\n", pname);
		exit(1);
	    }
	    to = i;
	    break;*/
	/*  case 'v':	// verbose mode 
	    vflag = 1;
	    break;*/
	  default:
	    //(void)fprintf(stderr, "%s: unrecognized option %s\n", pname,  argv[i]);
	    exit(1);
	}
	else {
	    //(void)fprintf(stderr, "%s: unrecognized argument %s\n", pname, argv[i]);
	    exit(1);
	}
    }
    /*if (record == NULL) {
		
		exit(1);
    }*/


   // if (gvmode == 0 && (p = getenv("WFDBGVMODE")))
	//gvmode = atoi(p);  -->gvmode=0 siempre
    setgvmode(gvmode|WFDB_GVPAD);
	//nota: isigopen(char *record, WFDB_Siginfo *siarray, int8_t nsig)
    //if ((nsig = isigopen("100"/*record*/, NULL, 0)) < 1) exit(2); //nsig=1 luego aqui no hace nada porq el segundo parametro es null
    nsig=1;
    
    if ((s = (WFDB_Siginfo *)malloc(nsig * sizeof(WFDB_Siginfo))) == NULL) {
		//(void)fprintf(stderr, "%s: insufficient memory\n", pname);
		//	printf("%s: insufficient memory\n", pname);
		exit(2);
    }
    //a.name = "wqrs"; a.stat = WFDB_WRITE;
    if ((nsig = wfdbinit("100"/*record*/, /*&a, 1, */s, nsig)) < 1) exit(2); //aqui rellena la estructura s -->solucionado!!!
    
    
    //if (sig < 0 || sig >= nsig) sig = 0;  
    sig=0;//analizamos una sola señal
    if ((gain = s[sig].gain) == 0.0) gain = WFDB_DEFGAIN;
    sps = sfreq; //sampfreq((char *)NULL); no hace falta usar este metodo, ya he comprobado que es 0
    if (Rflag) {  
    	if (PWFreq == 60.0) setifreq(sps = 120.);
    	else setifreq(sps = 150.); //solo deberia quedarse esta opcion
    }
   
     /*if (from > 0L) {  //opcion -f quitada
		if ((from = strtim(argv[from])) < 0L)
			from = -from;
   	}
    if (to > 0L) {  //opcion -t quitada
		if ((to = strtim(argv[to])) < 0L)
	   		 to = -to;
    } else */ to = strtim("e");//siempre hace else ya que to=0L

    /*annot.subtyp = annot.num = 0;
    annot.chan = sig;
    annot.aux = NULL;*/
    Tm = muvadu(sig, Tm);
    samplingInterval = 1000.0/sps;
    lfsc = 1.25*gain*gain/sps;	/* length function scale constant */
    spm = 60 * sps;
    next_minute = from + spm;
    LPn = sps/PWFreq;   /* The LP filter will have a notch at the
				    power line (mains) frequency */
    if (LPn > 8)  LPn = 8;	/* avoid filtering too agressively */
    LP2n = 2 * LPn;
    EyeClosing = sps * EYE_CLS;   /* set eye-closing period */
    ExpectPeriod = sps * NDP;	   /* maximum expected RR interval */
    LTwindow = sps * MaxQRSw;     /* length transform window size */

    (void)sample(sig, 0L);
    
    
    /*if (dflag) {   //opbion -d eliminada!!!!!!!!!!
	for (t = from; t < to || (to == 0L && sample_valid()); t++)
	//    printf("%6d\t%6d\n", sample(sig, t), ltsamp(t));
	exit(0);
    }*/

    
    /* Average the first 8 seconds of the length-transformed samples
       to determine the initial thresholds Ta and T0. The number of samples
       in the average is limited to half of the ltsamp buffer if the sampling
       frequency exceeds about 2 KHz. */
    if ((t1 = strtim("8")) > BUFLN*0.9)
	t1 = BUFLN/2;
    t1 += from;
    for (T0 = 0, t = from; t < t1 && sample_valid(); t++)
		T0 += ltsamp(t);
    T0 /= t1 - from;
    Ta = 3 * T0;

    /******************************** Main loop *******************************/
    for (t = from; t < to || (to == 0L && sample_valid()); t++) {
		static int8_t learning = 1, T1;
	
		if (learning) {
		    if (t > t1) {
				learning = 0;
				T1 = T0;
				t = from;	/* start over */
	    	}
	    	else  T1 = 2*T0;
		}
	
	/* Compare a length-transformed sample against T1. */
		if (ltsamp(t) > T1) {	/* found a possible QRS near t */
		    timer = 0; /* used for counting the time after previous QRS */
		    max = min = ltsamp(t);
		    for (tt = t+1; tt < t + EyeClosing/2; tt++)
				if (ltsamp(tt) > max) max = ltsamp(tt);
		    for (tt = t-1; tt > t - EyeClosing/2; tt--)
				if (ltsamp(tt) < min) min = ltsamp(tt);
		    if (max > min+10) { /* There is a QRS near tt */
			/* Find the QRS onset (PQ junction) */
				onset = max/100 + 2;
				tpq = t - 5;
				for (tt = t; tt > t - EyeClosing/2; tt--) {
				    if (ltsamp(tt)   - ltsamp(tt-1) < onset &&
					ltsamp(tt-1) - ltsamp(tt-2) < onset &&
					ltsamp(tt-2) - ltsamp(tt-3) < onset &&
					ltsamp(tt-3) - ltsamp(tt-4) < onset) {
					tpq = tt - LP2n;	/* account for phase shift */
					break;
				    }
				}
	
				if (!learning) {
				    /* Check that we haven't reached the end of the record. */
				    (void)sample(sig, tpq);
				    if (sample_valid() == 0) break;
				    /* Record an annotation at the QRS onset */
				   // annot.time = tpq;   //aqui hemos encontrado un qrs cuyo inicio es tpq!!!!!!!!!
				    //annot.anntyp = NORMAL;
				    //podemos quitar putann ya que solo escribe el fichero anotacion
				  /*  if (putann(0, &annot) < 0) { // write the annotation 
						//wfdbquit();	// close files if an error occurred 
						exit(1);
				    }*/
				    
				    
				    /********************************************************
				    	aqui es donde tenemos que imprimir el tpq (annot.time)!!!
				    ********************************************************/
				    
				    
				    /*if (jflag) {    //opcion -j elminiada
					// Find the end of the QRS 
					for (tt = t, tj = t + 5; tt < t + EyeClosing/2; tt++) {
					    if (ltsamp(tt) > max - (max/10)) {
						tj = tt;
						break;
					    }
					}
					(void)sample(sig, tj);
					if (sample_valid() == 0) break;
					// Record an annotation at the J-point 
					annot.time = tj;
					annot.anntyp = JPT;
					if (putann(0, &annot) < 0) {
					    wfdbquit();
					    exit(1);
					}
				    }*/
				}
	
				/* Adjust thresholds */
				Ta += (max - Ta)/10;
				T1 = Ta / 3;
		
		
				/* Lock out further detections during the eye-closing period */
				t += EyeClosing;
		    }
		}
		else if (!learning) {
		    /* Once past the learning period, decrease threshold if no QRS
		       was detected recently. */
		    if (++timer > ExpectPeriod && Ta > Tm) {
				Ta--;
				T0 = Ta / 3;
		    }      
		}
	
		/* Keep track of progress by printing a dot for each minute analyzed */
		//esto es una chorrada
		if (t >= next_minute) {
		    next_minute += spm;
		    //(void)fprintf(stderr, ".");
		    //(void)fflush(stderr);
		    if (++minutes >= 60) {
			//(void)fprintf(stderr, "\n");
				minutes = 0;
		    }
		}
    }

    (void)free(lbuf);
    (void)free(ebuf);
    //wfdbquit();		        // close WFDB files 
    //fprintf(stderr, "\n");
    /*if (vflag) { //opcion -v eliminada
	//printf("\n\nDone! \n\nResulting annotation file:  %s.wqrs\n\n\n",
	 //      record);
    }*/
    exit(0);
}

char *prog_name(s)
char *s;
{
    char *p = s + strlen(s);

	#ifdef MSDOS
	    while (p >= s && *p != '\\' && *p != ':') {
		if (*p == '.')
		    *p = '\0';		/* strip off extension */
		if ('A' <= *p && *p <= 'Z')
		    *p += 'a' - 'A';	/* convert to lower case */
		p--;
	    }
	#else
	    while (p >= s && *p != '/')
		p--;
	#endif
	    return (p+1);
}





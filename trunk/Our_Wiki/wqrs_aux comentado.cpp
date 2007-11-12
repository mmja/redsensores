

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

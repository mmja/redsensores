# file: Makefile	G. Moody	10 April 2003
#
# make description file for compiling easytest & bxbep using gcc
#
# Install the WFDB package (http://www.physionet.org/physiotools/wfdb.shtml)
# before attempting to compile these programs.
#
# To compile these programs, just type 'make' at a command prompt while in
# this directory.  This has been tested under GNU/Linux and MS-Windows/Cygwin,
# and it should also work under MacOS/X (Darwin) and all versions of Unix.
#
# See '00README' in this directory for further information.

# CC is the name of your ANSI/ISO C compiler (might be 'cc' on some platforms).
  #CC = gcc
  CC = msp430-gcc

gcc:
	gcc -o wqrs wqrs.c wqrs_aux.c -lm #-I /usr/include/wfdb -L /lib -lwfdb -lm
	
  
msp:		
	#$(CC) -o wqrs wqrs.c  -lm #-I /usr/include/wfdb -L /lib -lwfdb -lm
	msp430-gcc -O3 -O -c wqrs_aux.c -mmcu=msp430x149 
	msp430-gcc -O3 -O -c wqrs.c -mmcu=msp430x149
	msp430-gcc -lm -m msp430x149 wqrs_aux.o wqrs.o /usr/local/mspgcc/msp430/lib/libm.a -O3 -O -o wqrs 
	
	
clean:
	rm -f *.o *~ *.exe wqrs

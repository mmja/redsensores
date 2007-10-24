#include <stdio.h>
#include <stdlib.h>

int main( void )
{
   char *directorioPtr, *pathPtr;

   pathPtr = getenv( "LD_LIBRARY_PATH" );
   puts( "La lista de directorios en el PATH es la siguiente:" );
   print(pathPtr);
   
   

   return 0;
}


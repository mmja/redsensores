#include <stdio.h>

int main()
{
   char nombre[20]="", entrada[81]="";
   unsigned int edad=0;
	int i;
   printf( "Escriba su nombre y edad, separados por un espacio:\n" );
   gets( entrada );
   i=sscanf( entrada, "%s %u", nombre, &edad );

   printf( "Has escrito: %s\n", entrada );
   printf( "Nombre: %s. Edad: %d\n", nombre, edad );
   printf("%d",i);

   return 0;
}


#include <stdio.h>

int main()
{
   FILE *f1;
   char buffer[1000];
   f1=fopen("100.dat","r");
   if(f1==NULL) {
	   printf("error\n");
   		return 0;
	}
   int leidos;
   printf("%d\n",getc(f1));
   
   leidos=fread(buffer,1,1000,f1);
   if(leidos==0||leidos==-1) {
	   printf("error\n");
   		return 0;
	}

	//printf("buffer: %s\n",buffer);
	while(!feof(f1)){
		//printf("leidos: %d\n",leidos);
		//leidos=fread(buffer,1,1000,f1);	
		//printf("buffer: %s\n",buffer);
		printf("%d\n",getc(f1));
		
		
	}
	fclose(f1);
   
   

   return 0;
}


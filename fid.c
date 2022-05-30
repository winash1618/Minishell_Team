#include <errno.h>

#include <stdio.h>

#include <stdlib.h>

int main(void)

{

   FILE *fp;

   errno = 0;

   fp = fopen("Nofile", "r");

   if ( errno != 0 ) 

   {

     perror("Error occurred while opening file.\n");

     exit(1);

   }
	return (1);
}
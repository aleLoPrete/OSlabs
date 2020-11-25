#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdarg.h>

int main(int *argc, char **argv){ 
   FILE *fp = fopen(argv[1], "r");   
   char *command = malloc(sizeof(char)*30);
   if(fp==NULL) fprintf(stdout,"errore apertura file"); return -1;
   // assuming \n after each command 
   while(fscanf(fp, "%s", command ) != EOF){
       fprintf(stdout,"\nSto eseguendo il comando %s\n", command);
       system(command);
   } 
   fclose(fp);
   return 0;
}

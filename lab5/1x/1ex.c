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

int main(int argc, char **argv){
    FILE *fp = fopen("inFile.txt", "r");
    int num=1;

    while(num!=0){
        if(num%2 !=0)
            fprintf(stdout,"standard output %d\n", num);
        else
            fprintf(stderr,"standard error:%d\n",num);
        if(num==0)
            break;
        fscanf(stdin,"%d",&num);
    }
}

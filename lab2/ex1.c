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

#define N 300
#define SPACE n
void recurTreeDir(char *, int);
void myPrint(int);

int main(int argc, char **argv){
    /*if(sizeof(argv) != 2){
      printf("wrong number of args");
      }*/
    recurTreeDir(argv[1], 1);
    return 1;
}

void recurTreeDir(char *fullnameR, int level){
    DIR *dp;
    struct dirent *dirp;
    struct stat statbuf;
    char nameR[N];
    
    myPrint(level);
    fprintf(stdout, "%s-Level %d\n", fullnameR, level);

    // File
    if(lstat(fullnameR, &statbuf) < 0){
        fprintf(stderr, "Error running lstat");
        exit(1);
    }
    //Directory
    if(S_ISDIR(statbuf.st_mode) == 0){
        return;
    }
    if((dp=opendir(fullnameR)) == NULL){
        fprintf(stderr,"Error opening dir. \n");
        exit(1);
    }
    while((dirp = readdir(dp)) != NULL) {
        sprintf(nameR, "%s/%s", fullnameR, dirp->d_name);

        if(lstat(nameR, &statbuf) < 0){
            fprintf(stderr, "Error running lstat.\n");
            exit(1);
        }

        if(S_ISDIR(statbuf.st_mode) == 0) {
            //File
            myPrint(level+1);
            fprintf(stdout, "%s; level %d.\n", dirp->d_name, level+1);
        }
        else{
            //directory
            if(strcmp(dirp->d_name, ".") == 0 ||
                    strcmp(dirp->d_name, "..") == 0)
                continue;
            recurTreeDir(nameR, level+1);
        }
    }
    if(closedir(dp) < 0){
        fprintf(stderr, "Error.\n");
        exit(1);
    }
    return;
}
// adding spaces for indenting displayed content
void myPrint(int n){
    int i;
    for(i=0; i<(n-1)*SPACE; i++) {
        if(i%2==0){fprintf(stdout, "|"); continue;}
        fprintf(stdout, " ");
    }
    return;
}

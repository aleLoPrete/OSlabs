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

int main(int argc, char *argv){
    pid_t pid = 0; 
    int treeLevels = 2;//hard coded for the moment need to compute from input
    int i;
    int canIfor = 1;
    int myLevel = 0;

    for(i=0;i<treeLevels;i++){
        //if(myLevel>=2) break;
        pid = fork();
        if(pid==0) myLevel++;
        if(pid!=0){
            fprintf(stdout, "\n%d->%d\n", getpid(), pid);
            pid = fork();
            if(pid==0) myLevel++;
            if(pid!=0) {
                fprintf(stdout, "\n%d->%d\n", getpid(), pid);
                break;
            }
        }
    }
    if(myLevel>=2){ //at this point only a leaf has pid 0 because it exit the for loop before generating any process
        fprintf(stdout,"\n Hi I am a leaf!\n My pid is= %d, my parent is %d\n", getpid(), getppid());
    }
    sleep(30);
    return getpid();
}


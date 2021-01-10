#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Write a program that, using signals, synchronize two processes (a parent and it child) in a way that they print alternatively a specific message.

static void signalHandler();

int main(){
    pid_t pid;

    if(signal(SIGUSR1, signalHandler) == SIG_ERR) {//install a signal handler in both processes
        fprintf(stderr, "Signal handler error");
        return(1);
    }
    pid = fork();
    if(pid>0){ // parent
        fprintf(stdout,"\n father running\n");
        while(1){
            fprintf(stdout,"Hi, I am the parent");
            fprintf(stdout,"Hi, I am the parent");
            return 1;
            kill(pid, SIGUSR1);
            pause();
        }
    }
    if(pid==0){ // child 
        fprintf(stdout, "\n child running \n");
        while(1){
            fprintf(stdout, "\n prova 2");
            fflush(stdout); 
            pause(); // wait for parent signal
            fprintf(stdout,"Hello I am the child");
            kill(getppid(),SIGUSR1);
        }
    }
    fprintf(stdout, "prova");
    return 1;
}

static void signalHandler(void ){
    return;
}

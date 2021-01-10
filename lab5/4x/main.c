#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NAME "tmp.txt"

/*

Implement a C program that generates two children, a producer and a consumer. 
The producer child reads from the keyboard some strings, and it transfers them to the consumer. 
The consumer child converts the strings into uppercase characters, and it visualizes the strings in standard output.

The introduction of the string “end” terminates both children's processes and then, in sequence, 
it terminates the parent process. The transfer of the strings has to take place through a file.

Suggestions:

    Derive the solution from that of the previous exercise
    Communicating processes are not a parent and a child, but two “siblings”; as a consequence, you have to make sure that each child knows the PID of the “brother”
*/

void sender(int pid);
void receiver();

void signalHandler(){
    //fprintf(stdout, "\n signaling...\n");
    //fflush(stdout);
    return;
}


char *strUp(char *s){
    int i;
    for (i = 0; s[i]!='\0'; i++) {
       if(s[i] >= 'a' && s[i] <= 'z') {
          s[i] = s[i] -32;
       }
    }
    return s;
}

int main(){
    pid_t recpid, sendpid;
    
    if(signal(SIGUSR1, signalHandler) == SIG_ERR) {//install a signal handler in both processes
        fprintf(stderr, "Signal handler error");
        return(1);
    }
 
    recpid = fork();

    if(recpid == 0){
        fprintf(stdout,"rec pid %d\n", getpid());
        fflush(stdout);
        receiver();
        exit(1);
    }
    else
    {
        sendpid = fork();
        if(sendpid == 0){
            fprintf(stdout,"sender pid %d\n", getpid());
            sender(recpid);
            exit(1);
        }
        wait(NULL);
    }
   return 1; 
}

void sender(int receiverpid){
    char stringa[20];
    FILE *fp;
    fprintf(stdout, "recpid %d????\n", receiverpid);
    fflush(stdout);
    while(1){
        sleep(1);
        fprintf(stdout, "inserire stringa: \n");
        fflush(stdout);
        fscanf(stdin,"%s", stringa);

        fp = fopen(NAME, "w");
    
        if(fp == NULL){
            fprintf(stdout, "errore apertura file\n");
            return;
        }
        fprintf(fp,"%d %s\n", getpid(), stringa);
        if(fflush(fp) != 0) 
            return; // errore scrittura file
        fclose(fp);
        kill(SIGUSR1, receiverpid);
        fprintf(stdout,"signal sent \n");
        fflush(stdout);
        if(strcmp(stringa, "end")){ // if end of insertion, exit while loop
                break;
        } 
        pause();
    }
}

void receiver(){
    char stringa[20];
    FILE *fp;
    int sender_pid;
    while(1){
        pause(); // wait for signal
        fprintf(stdout,"Processing string...\n");
        fflush(stdout);
        sleep(1);
        fp = fopen(NAME,"r");
        if(fp == NULL){
            fprintf(stdout, "errore apertura file\n");
            fflush(stdout);
            return;
        }
        fscanf(fp,"%d %s", &sender_pid, stringa);
        fprintf(stdout, "uppered string: %s\n",strUp(stringa));;
        fflush(fp);
        fclose(fp);
        if(strcmp(stringa, "END"))
            break;
        kill (sender_pid, SIGUSR1);
    }
}

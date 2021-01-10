#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFSIZE 21
/*
Implement the solution of exercise 04 of laboratory 05 (Lab05) using pipe for 
the communication between the two processes.

That is, implement a C program that generates two children, a producer and a consumer.
The producer child reads from the keyboard some strings, and it transfers them to the consumer. The consumer child converts the strings into uppercase characters, and it visualizes the strings in standard output. The transfer of the strings (and synchronization) has to take place through pipes.

Observation: The length of the strings transferred through the pipe is variable and not known a priori. It is therefore appropriate to use some communication mechanism/protocol. For instance, it is possible to transfer in the pipe the dimension of the string before the string itself, by using a constant number of characters to code this dimension.
*/

void fork_failure_test(int pid){
    if(pid==-1){ // fork failure
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
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

int sender();
int receiver();


int main( int *argc, char **argv){
    int fd[2];
    int rec_pid, send_pid;

    pipe(fd);

    rec_pid = fork();
    fork_failure_test(rec_pid);
    if(rec_pid == 0){
        //receiver
        receiver(fd);
    }
    else{
        send_pid = fork();
        fork_failure_test(send_pid);
        if(send_pid==0){
            //sender
            sender(rec_pid,fd);
        }
    }

}




int receiver(int *fd){ 
    char c;
    char word[BUFFSIZE];
    int n;

    close(fd[1]); // best practice

    //read word from pipe and print it out after uppering it
    while(n=read(fd[0],word,BUFFSIZE)>0){
        fprintf(stdout,"uppered word: %s", strUp(word));
        fflush(stdout);
    } 

} 


int sender(int rec_pid, int *fd){

}

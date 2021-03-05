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
/*
Implement in a concurrent and multi-process way the bubble-sort algorithm.

The algorithm, by using the system calls fork and wait, and sharing data in the
file (i.e., by reading and writing data in the same file), must order the file itself.

The program (i.e., the parent):
    receives on the command line the name of a file containing a predefined number n of integer numbers.
    at each iteration of the external cycle, it “simulates” the action of the internal cycle by using n-1-i child processes

Each of its children:

    reads two adjacent elements from the file
    swaps them if it is necessary
    writes them in the file
    it synchronizes with the other children processes to generate the overall sorting effect (i.e., at each iteration in the external cycle the highest value among the remaining numbers is moved at the end of the file)
    terminates

// bubble sort algo
for (i=0; i<n-1; i++) {
  for (j=0; j<n-1-i; j++) {
    if (v[j] > v[j+1]) {
       val = v[j];
       v[j] = v[j+1];
       v[j+1] = val;
    }
  }
}
 * */
#define N 10

int main(int argc, char **argv){
    int arr[10] = {10,23,40,13,4,5,6,4,34,2};
    
    // creating file and writing 

    int fd;
    
    fd = creat("fileArray", 0666);
    if(fd == -1) {
        fprintf(stderr,"Errore apertura file");
        exit(-1)
    }
    fprintf(stderr,"\n data written  in file:");
    for(int i = 0;i<10;i++) {
        write(fd,&arr[i],sizeof(int));
        fprintf(stdout,"\n writing: %d ",arr[i]);
    }
    close(fd);

    //reading file
    int c;
    fd = open (argv[1], O_RDONLY);
    if (fd == -1){
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        exit(-1);
      }
   fprintf (stdout, "File before ordering    : ");
   for(int i=0;i<10;i++){
      lseek(fd,i*sizeof(int),SEEK_SET);
      c = read(fd,&arr[i],sizeof(int));
     if (c <= 0){
          fprintf (stderr, "Error reading file\n");
          exit (-1);
        }
        fprintf (stdout, "%2d ", v);
   }

    close(fd);


    
}



void child(int fd, int j){
    int a;
}

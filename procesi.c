#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int id; /* identifikacijski broj segmenta */
int *A;

void task(int m){
 
    int i;
    for(i=0;i<m;i++){
        *A = (*A)+1;
    }
    
}

int main(int argc, char** argv){
    
    if(argc!=3)
        exit(1); /* greška - krivi broj argumenata */
    
    /* zauzimanje zajedničke memorije */
    id = shmget(IPC_PRIVATE, sizeof(int), 0600);
 
    if (id == -1)
        exit(1);  /* greška - nema zajedničke memorije */
 
    A = (int *) shmat(id, NULL, 0);
    *A = 0;
 
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    
    int i;
    for(i=0;i<n;i++){
        if(fork()==0){
            task(m);
            shmdt(char *addr);
            exit(0);
        }
    }
    
    while(i--) wait(NULL);
    
    printf("A=%d\n",*A);
    
}

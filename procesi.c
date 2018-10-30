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
        switch(fork()){
		case 0:
            		task(m);
            		shmdt(A);
            		exit(0);
		case -1:
			printf("[ERROR] Can not create process number %d",i+1);
		case 1:
			break;
		default:
			break;
        }
    }

    while(i--) wait(NULL);

    printf("A=%d\n",*A);
    shmctl(id,IPC_RMID,NULL);

    return 0;

}

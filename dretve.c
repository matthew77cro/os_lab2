#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int A = 0;

void *task(int m){

    int i;
    for(i=0;i<m;i++){
        A++;
    }

}

int main(int argc, char** argv){

    if(argc!=3)
        exit(1); /* greška - krivi broj argumenata */

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    pthread_t *tid = malloc(sizeof(pthread_t)*n);
    int i;
    for(i=0;i<n;i++){
        if(pthread_create(&tid[i], NULL, task, &m)!=0){
            printf("[ERROR] Can not create thread %d",i+1);
            exit(0);
        }
    }

    while(i--) pthread_join(tid[i], NULL);

    printf("A=%d\n",A);

}

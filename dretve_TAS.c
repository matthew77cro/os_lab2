#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAS(ZASTAVICA) __atomic_test_and_set (&ZASTAVICA, __ATOMIC_SEQ_CST)

char zastavica = 0;
int A = 0;

void *task(void* m){

    int i;
    for(i=0;i<*((int*)m);i++){
        while(TAS(zastavica)==1);
        A++;
        zastavica=0;
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
        if(pthread_create(&tid[i], NULL, task, (void*)&m)!=0){
            printf("[ERROR] Can not create thread %d",i+1);
            exit(0);
        }
    }

    while(i--) pthread_join(tid[i], NULL);

    printf("A=%d\n",A);

}


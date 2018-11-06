#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdatomic.h>

int id; /* identifikacijski broj segmenta */
atomic_int *A;
int ZASTAVICA = 0;
int PRAVO = 2;
int VRIJEDNOST = 3;

void dekker(int id, int n){

    int moj_id = id;
    int drugi_id = 1-moj_id;
    
    int i;
    for(i=0;i<n;i++){
        
        //ulazak u K.O.
        *(A+ZASTAVICA+moj_id) = 1;                     //postavlja zastavicu u 1
        while(*(A+ZASTAVICA+drugi_id)==1){             //ima li drugi proces dignutu zastavicu?
            if(*(A+PRAVO) == drugi_id){                //jeli pravo tuđe?
                *(A+ZASTAVICA+moj_id) = 0;             //spusti zastavicu
                while(*(A+PRAVO) == drugi_id);
                *(A+ZASTAVICA+moj_id) = 1;             //digni zastavicu
            }
        }        
        
        //K.O.
        (*(A+VRIJEDNOST))++;
        
        //izlazak iz K.O.
        *(A+PRAVO) = drugi_id;                          //daj pravo drugom
        *(A+ZASTAVICA+moj_id) = 0;                     //spusti zastavicu
        
    }

}

int main(int argc, char** argv){

    if(argc!=2)
        exit(1); /* greška - krivi broj argumenata */

    /* zauzimanje zajedničke memorije */
    id = shmget(IPC_PRIVATE, sizeof(int)*4, 0600);

    if (id == -1)
        exit(1);  /* greška - nema zajedničke memorije */

    A = (atomic_int *) shmat(id, NULL, 0);
    *(A+ZASTAVICA+0) = 0;
    *(A+ZASTAVICA+1) = 0;
    *(A+PRAVO) = 0;
    *(A+VRIJEDNOST) = 0;
    
    int n = atoi(argv[1]);
    
    int i;
    for(i=0;i<2;i++){
        switch(fork()){
            case 0:
                dekker(i,n);
                shmdt(A);
                exit(0);
		case -1:
			printf("[ERROR] Can not create process number %d",i+1);
            break;
		case 1:
			break;
		default:
			break;
        }
    }

    while(i--) wait(NULL);

    printf("A=%d\n",*(A+3));
    shmctl(id,IPC_RMID,NULL);

    return 0;

}

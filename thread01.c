#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

void *worker_thread(void *arg)
{
        printf("This is worker_thread #%ld\n", (long)arg);
        pthread_exit(NULL);
}

int main()
{
        pthread_t my_thread[N];

        long id;
    double time;
    clock_t start = clock();

        for(id = 1; id <= N; id++) {
                int ret =  pthread_create(&my_thread[id], NULL, &worker_thread, (void*)id);
                if(ret != 0) {
                        printf("Error: pthread_create() failed\n");
                        exit(EXIT_FAILURE);
                }
        }
   
   
    clock_t end = clock();       
    time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
     printf("El tiempo es \n");
        printf("%1.4f\n ", time);
        pthread_exit(NULL);
            
}

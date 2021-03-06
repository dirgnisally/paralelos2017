#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long n = 100000;
long thread_count = 5; //n must be divisible by the value of this variable.
long double sum;
pthread_mutex_t mutex;
long flag;
void *Thread_sum(void* rank);
void *Thread_sum_mutex(void* rank);
void *Thread_sum_busy(void* rank);


int main(int argc, char **argv)
{
	long thread;
	pthread_t* thread_handles;
	thread_handles = malloc(thread_count*sizeof(pthread_t));
	sum = 0;
	for (thread = 0; thread < thread_count; thread++){
//    		pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread);
		pthread_create(&thread_handles[thread], NULL, Thread_sum_mutex, (void*) thread);
                
        }

	for (thread = 0; thread < thread_count; thread++)
	    	pthread_join(thread_handles[thread], NULL);
	
	printf("pi = %Lfn", 4 * sum);
	free(thread_handles);	
	return 0;
}

void *Thread_sum(void *rank) {
	long my_rank = (long) rank;
	double factor;
	long long i;
	long long my_n = n/thread_count;
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;
	
	if (my_first_i % 2 == 0) 
		factor = 1.0;
	else  
		factor = -1.0;

	for (i = my_first_i; i < my_last_i; i++) {
		sum += factor / ((2*i) + 1 );
                factor =- factor;
	}
	
	return NULL;
} 

void *Thread_sum_busy(void *rank) {
	long my_rank = (long) rank;
	double factor;
	long long i;
	long long my_n = n/thread_count;
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;
	
	if (my_first_i % 2 == 0)
	    factor = 1.0;
	else
	   factor = -1.0;

	for (i = my_first_i; i < my_last_i; i++ ) {
		factor =- factor;
		while (flag != my_rank);
			sum += factor/(2*i+1);
			flag = (flag+1) % thread_count;
	}
	

	return NULL;
}

void *Thread_sum_mutex(void *rank) {
	long my_rank = (long) rank;
	double factor;
	long long i;
	long long my_n = n / thread_count;
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;
	double my_sum = 0.0;
	
	if (my_first_i % 2 == 0)
		factor = 1.0;
	else
		factor = - 1.0;
		
	for (i = my_first_i; i < my_last_i; i++) {
			my_sum += factor/(2*i+1);
			factor =- factor;
		}

	pthread_mutex_lock(&mutex);
	sum += my_sum;
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

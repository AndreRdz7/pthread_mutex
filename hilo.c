#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int buffer = 0;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void * threadOne(void * params){
	int i;
	for (i = 0; i < 10; i++){
		pthread_mutex_lock(&mutex1);
		buffer++;
		pthread_mutex_unlock(&mutex2);
	}
}

void * threadTwo(void * params){
	int i;
	for (i = 0; i < 10; i++){
		pthread_mutex_lock(&mutex2);
		printf("%d\n", buffer);
		pthread_mutex_unlock(&mutex1);
	}
}

int main(){
	pthread_t producer;
	pthread_t consumer;

	pthread_create(&producer, NULL, &threadOne, NULL);
	pthread_create(&consumer, NULL, &threadTwo, NULL);
	
	pthread_mutex_unlock(&mutex2);
	pthread_join(producer,NULL);
	pthread_join(consumer,NULL);
}

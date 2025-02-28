#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 20000

static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *add_thread(void *argv){
    int *p=argv;
    pthread_mutex_lock(&counter_mutex);
    (*p)++;

    pthread_mutex_unlock(&counter_mutex);
    return NULL;
}

int main(){
    pthread_t threads[THREAD_COUNT];
    int counter = 0;
    int i;
    for(i=0;i<THREAD_COUNT;i++){
        pthread_create(threads+i,NULL,add_thread,&counter);
    }
    for(i=0;i<THREAD_COUNT;i++){
        pthread_join(threads[i],NULL);
    }
    printf("counter=%d\n",counter);
    return 0;
}
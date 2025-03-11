#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

int shard_num=0;

void *plusOne(void *arg){
    int tmp=shard_num+1;
    shard_num=tmp;
    return NULL;
}

int main(){
    pthread_t tid[10000];
    for(int i=0;i<10000;i++){
        pthread_create(&tid[i],NULL,plusOne,NULL);
    }
    for(int i=0;i<10000;i++){
        pthread_join(tid[i],NULL);
    }
    printf("shard_num=%d\n",shard_num);
    return 0;
}
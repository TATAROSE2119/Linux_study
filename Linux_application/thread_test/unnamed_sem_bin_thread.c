#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t unnamed_sem;
int shard_num=0;

void *plusOne(void *arg){
    sem_wait(&unnamed_sem);
    int tmp = shard_num+1;
    shard_num=tmp;
    sem_post(&unnamed_sem);
    return NULL;
}
int main(){
    sem_init(&unnamed_sem, 0, 1);//初始化信号量 unnamed_sem 为1
    pthread_t tid[10000];
    for(int i=0;i<10000;i++){
        pthread_create(&tid[i], NULL, plusOne, NULL);
    }
    for(int i=0;i<10000;i++){
        pthread_join(tid[i], NULL);
    }
    printf("shard_num=%d\n", shard_num);
    sem_destroy(&unnamed_sem);
    return 0;
}
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *task(void *arg){
    printf("thread is running\n");
    sleep(2);
    printf("thread is exiting\n");
    return NULL;
}

int main(){
    pthread_t tid;
    //创建线程
    pthread_create(&tid,NULL,task,NULL);
    //使用pthread_detach让线程自动回收资源
    pthread_detach(tid);
    //主线程继续工作
    printf("Main thread is running\n");
    sleep(3);
    printf("Main thread is exiting\n");
    return 0;
}
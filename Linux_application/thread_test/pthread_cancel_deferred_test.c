#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *task(void *arg)
{
    printf("Thread start\n");


    printf("working\n");
    sleep(5);
    pthread_testcancel();
    printf("After cancel point\n");

    return NULL;
}
int main(){
    pthread_t tid;
    void *res;

    // create thread
    pthread_create(&tid, NULL, task, NULL);
    // cancel son thread
    if(pthread_cancel(tid) != 0){
        perror("pthread_cancel");
        exit(1);
    }
    // wait for son thread
    pthread_join(tid, &res);
    // check son thread return value
    if(res == PTHREAD_CANCELED){
        printf("son Thread was canceled\n");
    }
    else{
        printf("son Thread was not canceled\n");
    }
    return 0;

}
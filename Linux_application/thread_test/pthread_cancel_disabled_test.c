#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg)
{
    printf("Thread start\n");

    //禁用取消响应
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    printf("Thread cancel disabled\n");
    //设置消息类型为异步
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    //模拟工作
    printf("Thread sleep 5s\n");
    sleep(5);
    printf("after caancelled\n");

    return NULL;

}
int main(){
    pthread_t tid;
    void *res;

    //创建线程
    pthread_create(&tid, NULL, task, NULL);
    //取消子线程
    if (pthread_cancel(tid) != 0)
    {
        /* code */
        perror("pthread_cancel");
        exit(1);
    }
    //等待子线程结束
    if (pthread_join(tid, &res) != 0)
    {
        /* code */
        perror("pthread_join");
        exit(1);
    }
    //检查子线程是否被取消
    if (res == PTHREAD_CANCELED)
    {
        /* code */
        printf("Thread was cancelled\n");
    }else{
        printf("Thread was not cancelled,%ld\n",(long)res);
    }
    return 0;
    
}
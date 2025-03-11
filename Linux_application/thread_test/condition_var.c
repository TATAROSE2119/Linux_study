#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count=0;
//初始化锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//初始化条件变量
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
//生产者线程
void *producer(void *arg){
    int item=1;
    while(1){
        //获取互斥锁 拿不到就等待
        pthread_mutex_lock(&mutex);
        //缓冲区满了就等待
        while(count==BUFFER_SIZE){
            pthread_cond_wait(&cond,&mutex);
        }
        //生产一个产品
        buffer[count++]=item++;
        printf("produce an item%d\n",buffer[count-1]);//打印生产的产品 实际上可以是生产者生产的产品，或者生产产品的实际操作
        
        //通知消费者线程
        pthread_cond_signal(&cond);
        //释放互斥锁
        pthread_mutex_unlock(&mutex);
    }
}
void *consumer(void *arg){
    while (1)
    {
        //获取互斥锁 拿不到就等待
        pthread_mutex_lock(&mutex);
        //缓冲区为空就等待
        while(count==0){
            pthread_cond_wait(&cond,&mutex);
        }
        printf("consume an item%d\n",buffer[--count]);
        //通知生产者线程
        pthread_cond_signal(&cond);
        //释放互斥锁
        pthread_mutex_unlock(&mutex);
    }
    
}
int main(){
    pthread_t producer_thread,consumer_thread;
    //创建生产者线程
    pthread_create(&producer_thread,NULL,producer,NULL);
    //创建消费者线程
    pthread_create(&consumer_thread,NULL,consumer,NULL);
    //等待线程结束
    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);
    return 0;
}
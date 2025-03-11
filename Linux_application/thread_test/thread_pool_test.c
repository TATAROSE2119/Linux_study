#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//任务函数
void task_func(gpointer data,gpointer user_data){
   int task_num=*(int*)data;
   free(data);
   printf("task %d is running\n",task_num);
   sleep(1);
   printf("task %d is done\n",task_num);
}
int main(){
    //创建线程池
    GThreadPool *pool=g_thread_pool_new(task_func,NULL,5,FALSE,NULL);
    //创建任务
    for(int i=0;i<10;i++){
        int *temp=malloc(sizeof(int));
        *temp=i+1;
        //将任务加入线程池
        g_thread_pool_push(pool,temp,NULL);
    }
    //等待线程池中的任务执行完毕
    g_thread_pool_free(pool,FALSE,TRUE);
    printf("all task is done\n");
    return 0;
}
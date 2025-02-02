#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *buf;

void *input_thread(void *arg){
    int i=0;//缓存区的索引
    while(1){
        char c=fgetc(stdin);//从标准输入读取一个字符
        //如果字符不为0也不是换行，写入缓存区
        if(c&&c!='\n'){//
            buf[i++]=c;
            if(i>=BUFFER_SIZE){
                i=0;
            }
        }
    }
}
void *output_thread(void *arg){
    int i=0;//缓存区的索引
    while(1){
        if (buf[i]){
            //从缓存区读取一个字节写入标准输出并换行
            fputc(buf[i],stdout);
            fputc('\n',stdout);
            //清理读取完毕的字节
            buf[i++]=0;
            if(i>=BUFFER_SIZE){
                i=0;
            }
        }
        else{
            sleep(1);
        }
    }
}
int main(){
    pthread_t pid_input;
    pthread_t pid_output;
    //分配缓存区
    buf=malloc(BUFFER_SIZE);
    //初始化缓存区
    for(int i=0;i<BUFFER_SIZE;i++){
        buf[i]=0;
    }
    //创建输入线程
    pthread_create(&pid_input,NULL,input_thread,NULL);

    //创建输出线程
    pthread_create(&pid_output,NULL,output_thread,NULL);

    //等待线程结束
    pthread_join(pid_input,NULL);
    pthread_join(pid_output,NULL);

    free(buf);
    return 0;
}
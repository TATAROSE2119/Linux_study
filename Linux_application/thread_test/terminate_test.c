 #include <pthread.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <math.h>
 #include <string.h>

 typedef struct Result{
    char *p;
    int len;
 } Result;
//红线程
 void *red_thread(void *argv){
    Result *result=malloc(sizeof(Result));
    char code=*((char*)argv);
    //存放回信
    char *ans=malloc(101);
    while(1){
        fgets(ans,100,stdin);
        if(ans[0]==code){
            //接收到了对应的信息
            free(ans);//释放内存
            printf("red thread exit\n");
            char *redAns=strdup("red thread go away\n");
            result->p=redAns;//将回信存入result
            result->len=strlen(redAns);//记录回信长度

            pthread_exit((void *)result);//退出线程
        }
        else{
            printf("red thread: %s is still here\n",ans);
        }
    }
 }
//白线程
void *white_thread(void *argv){
    Result *result=malloc(sizeof(Result));
    char code=*((char*)argv);
    //存放回信
    char *ans=malloc(101);
    while(1){
        fgets(ans,100,stdin);
        if(ans[0]==code){
            //接收到了对应的信息
            free(ans);//释放内存
            printf("white thread exit\n");
            char *whiteAns=strdup("white thread go away\n");
            result->p=whiteAns;//将回信存入result
            result->len=strlen(whiteAns);//记录回信长度

            pthread_exit((void *)result);//退出线程
        }
        else{
            printf("white thread: %s is still here\n",ans);
        }
    }
}
int main(){
    pthread_t pid_red;
    pthread_t pid_white;
    char redCode='r';
    char whiteCode='w';
    Result *redResult =NULL;
    Result *whiteResult =NULL;

    //创建红线程
    pthread_create(&pid_red,NULL,red_thread,&redCode);
    //创建白线程
    pthread_create(&pid_white,NULL,white_thread,&whiteCode);

    //获取红线程结果
    pthread_join(pid_red,(void **)&redResult);
    printf("red thread result: %s\n",redResult->p);
    free(redResult->p);
    free(redResult);

    //获取白线程结果
    pthread_join(pid_white,(void **)&whiteResult);
    printf("white thread result: %s\n",whiteResult->p);
    free(whiteResult->p);
    free(whiteResult);

    return 0;
}
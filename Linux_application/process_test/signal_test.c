#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//定义信号处理函数
void signal_handler(int signo)
{
    printf("receive signal %d\n", signo);
    exit(signo);
}

int main(){
    if(signal(SIGINT, signal_handler) == SIG_ERR){
        perror("signal error");
        return(1);
    }   
    //无限循环等待信号
    while (1)
    {
        sleep(1);
        printf("waiting for signal\n");
    }
    return 0;
}
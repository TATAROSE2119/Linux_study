#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("dsadwahndkuwag  %d \n",getpid());       //getpid()函数返回调用进程的进程ID
    pid_t pid = fork();                             //fork()函数创建一个新进程，新进程是调用进程的副本，新进程称为子进程，调用进程称为父进程
    if(pid<0)                                       //fork()函数失败返回-1
    {
        printf("fork error\n");
    }
    else if(pid==0)                                 //fork()函数成功返回0
    {
        printf("child process %d %d \n",getpid(),getppid());  //getppid()函数返回调用进程的父进程ID
    }
    else
    {
        printf("parent process %d %d \n",getpid(),pid);
    }
}
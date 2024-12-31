#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int pipe_fd[2];
    pid_t cpid;
    char buf;
    if (argc!=2) // 判断参数是否正确
    {
        fprintf(stderr,"Usage: %s <string>\n",argv[0]);     // stderr是标准错误输出
        exit(EXIT_FAILURE);     // 退出程序
    }
    if(pipe(pipe_fd)==-1)   // 创建管道 pipe_fd 是一个包含两个文件描述符的数组：pipe_fd[0] 用于读取，pipe_fd[1] 用于写入。
    {
        perror("pipe");         // 输出错误信息
        exit(EXIT_FAILURE);
    }
    cpid=fork();    // 创建子进程
    if(cpid==-1)    // 判断fork是否成功
    {
        perror("fork");         // 输出错误信息
        exit(EXIT_FAILURE);
    }


    if(cpid==0)     // 子进程代码
    {
        close(pipe_fd[1]);      // 关闭写端，作用是让子进程只读管道
        char str[100]={0};
        sprintf(str,"new one %d get a intivation \n",getpid());
        write(STDOUT_FILENO,str,sizeof(str));
        while(read(pipe_fd[0],&buf,1)>0)    // 读取管道
            write(STDOUT_FILENO,&buf,1);    // 写入标准输出

        write(STDOUT_FILENO,"\n",1);       // 写入标准输出
        close(pipe_fd[0]);      // 关闭读端
        _exit(EXIT_SUCCESS);     // 退出子进程s
    }
    else            // 父进程   通过检查 fork() 的返回值，可以区分父进程和子进程，并在它们之间执行不同的代码。
    {
        close(pipe_fd[0]);      // 关闭读端
        printf("Parent pid is %d\n",getpid());
        write(pipe_fd[1],argv[1],strlen(argv[1]));    // 写入管道
        close(pipe_fd[1]);      // 关闭写端
        waitpid(cpid,NULL,0);    // 等待子进程结束
        exit(EXIT_SUCCESS);     // 退出父进程
    }
}   
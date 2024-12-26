#include <unistd.h>
#include <sys/types.h>  
#include <sys/wait.h>
#include <stdio.h>

int main(int args,char const *argv[])
{
    //before fork
    int subprocess_status; //子进程状态
    printf("before fork\n");
    pid_t pid = fork();
    if (pid<0)
    {
        perror("fork");
        return 1;
    }else if(pid==0)
    {
        //child process
        char *args[]={"/sbin/ping","-c","10","www.baidu.com",NULL};      //定义要执行的新程序及其参数
        char *envs[]={NULL};
        printf("child process %d\n",getpid());
        int exR=execve(args[0],args,envs);   
        if (exR<0)
        {
            perror("execve");
            return 1;
        }
    }
    else
    {
        printf("old %d wait new %d \n",getppid(),pid);
        waitpid(pid,&subprocess_status,0);
    }
    return 0;
}
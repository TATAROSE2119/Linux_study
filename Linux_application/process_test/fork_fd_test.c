#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    
    int fd=open("io.txt",O_CREAT|O_WRONLY|O_APPEND,0644);
    if(fd<0)
    {
        perror("open");
        exit(1);
    }

    char buff[1024];//定义一个缓冲区
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork");
        exit(1);
    }else if(pid==0)
    {
        //z子进程
        strcpy(buff,"这是子进程写入的数据\n");
    }else
    {
        //父进程
        strcpy(buff,"这是父进程写入的数据\n");
    }



    //父子进程都要执行的代码
    ssize_t bytes_write = write(fd,buff,strlen(buff));
    if(bytes_write<0)
    {
        perror("write");
        close(fd);
        exit(1);
    }
    printf("write success\n");

    //关闭文件
    close(fd);
    if (pid==0)
    {
        printf("子进程退出\n");
    }else
    {
        printf("父进程退出\n");
    }
    return 0;
    
}
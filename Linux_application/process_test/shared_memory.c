#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main()
{
    char *share;
    pid_t pid;
    char shmName[100]={0};
    sprintf(shmName, "/letter%d", getpid());

    int fd;
    fd=shm_open(shmName, O_CREAT|O_RDWR, 0644);
    if(fd<0)
    {
        perror("shm_open error");
        exit(EXIT_FAILURE);
    }
    //将该区域扩充为100字节长度
    ftruncate(fd, 100);
    //将共享内存映射到进程的地址空间
    share=mmap(NULL, 100, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(share==MAP_FAILED)
    {
        perror("mmap error");
        exit(EXIT_FAILURE);
    }
    close(fd);
    pid=fork();
    if(pid==0)
    {
        //子进程
        //printf("子进程开始写入数据\n");
        strcpy(share, "hello, parent process");//写入数据
        printf("子进程%d写入数据完成\n", getpid());
    }
    else 
    {
        //父进程
        sleep(1);
        printf("父进程%d读取到子进程%d的数据：%s\n", getpid(),pid,share);
        wait(NULL);
        //释放共享内存
        int ret= munmap(share, 100);
        if(ret==-1)
        {
            perror("munmap error");
            exit(EXIT_FAILURE);
        }
    }
    shm_unlink(shmName);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char *share;
    pid_t pid;
    char shmName[100]={0};
    sprintf(shmName, "/letter%d", getpid());
    printf("shmName: %s\n", shmName);
    //创建共享内存
    int fd;
    fd=shm_open(shmName, O_CREAT|O_RDWR, 0644);//创建共享内存
    if (fd<0)
    {
        perror("shm_open error");
        exit(EXIT_FAILURE);
    }
    while(1);
    return 0;
    
}
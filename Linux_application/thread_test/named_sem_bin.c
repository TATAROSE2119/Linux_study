#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>

int main(){
    char *sem_name="/named_sem";
    char *shm_name="/named_sem_shm";

    //初始化有名信号量  
    sem_t *sem=sem_open(sem_name,O_CREAT,0666,1);
    if(sem==SEM_FAILED){
        perror("sem_open");
        return -1;
    }
    //初始化内存共享对象
    int fd=shm_open(shm_name,O_CREAT|O_RDWR,0666);
    //调整内存共享对象的大小
    ftruncate(fd,sizeof(int));
    //将内存共享对象映射到共享内存区域
    int *value=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    //初始化共享变量的值
    *value=0;

    pid_t pid=fork();
    if(pid<0){
        perror("fork");
        return -1;
    }

    //查看sem的值
    int sem_value;
    sem_getvalue(sem,&sem_value);
    printf("sem_value=%d\n",sem_value);

    sem_wait(sem);//P操作

    //查看sem的值
    sem_getvalue(sem,&sem_value);
    printf("sem_value=%d\n",sem_value);

    int tmp=*value+1;
    sleep(1);
    *value=tmp;
    sem_post(sem);//V操作

    //查看sem的值
    sem_getvalue(sem,&sem_value);
    printf("sem_value=%d\n",sem_value);

    //每个线程都应该在最后关闭信号量
    sem_close(sem);
    //父进程执行到这里，子进程已执行完毕，可以销毁信号量
    if(pid>0){
        waitpid(pid,NULL,0);
        printf("this is father,child finished,value=%d\n",*value);

        //删除信号量
        sem_unlink(sem_name);
    }
    munmap(value,sizeof(int));
    close(fd);

    //只有父进程才需要删除共享内存对象
    if(pid>0){
        shm_unlink(shm_name);
    }
    return 0;
}
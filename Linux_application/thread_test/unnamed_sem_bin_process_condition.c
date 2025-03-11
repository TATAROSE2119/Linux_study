#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    char *shm_value_name="unnamed_sem_shm_value";

    //create a shared memory object
    int value_fd=shm_open(shm_value_name,O_CREAT|O_RDWR,0666);
    if(value_fd==-1){
        perror("shm_open error");
        return -1;
    }
    //set the size of the shared memory object
    ftruncate(value_fd,sizeof(int));

    //memory map the shared memory object
    int *value_ptr=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,value_fd,0);
    if(value_ptr==MAP_FAILED){
        perror("mmap error");
        return -1;
    }
    
    //initialize the shared memory object
    *value_ptr=0;

    //create a child process
    pid_t pid=fork();
    if(pid>0){//parent process
        int tmp= *value_ptr+1;
        sleep(1);
        *value_ptr=tmp;

        //wait for the child process to finish
        waitpid(pid,NULL,0);
        printf("parent process: value=%d\n",*value_ptr);
    }else if(pid==0){//child process
        int tmp=*value_ptr+1;
        sleep(1);
        *value_ptr=tmp;
        printf("child process: value=%d\n",*value_ptr);
    }else{
        perror("fork error");
        return -1;
    }

    //unmap the shared memory object
    if(munmap(value_ptr,sizeof(int))==-1){
        perror("munmap error");
        return -1;
    }
    //close the shared memory object
    if(close(value_fd)==-1){
        perror("close error");
        return -1;
    }
    if(pid>0){
        //remove the shared memory object
        if(shm_unlink(shm_value_name)==-1){
            perror("shm_unlink error");
            return -1;
        }
    }
    return 0;
}
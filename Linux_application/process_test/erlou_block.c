#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc,const char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <block|noblock>\n",argv[0]);
        exit(1);
    }
    printf("it is %s,im now in %d place1\n",argv[1],getpid());
    sleep(100);//挂起子进程
    return 0;    
}
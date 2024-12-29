#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc,const char *argv[])
{
    char *name="old";
    printf("%s %d is in place1\n",name,getpid());
    pid_t pid=fork();
    if (pid==-1)
    {
        printf("get new fail!\n");
    }
    else if(pid==0)
    {
        char *newName="new";
        char *argv[]={"./erlou_block",newName,NULL};
        char *envp[]={NULL};

        int ret=execve(argv[0],argv,envp);
        if (ret==-1)
        {
            printf("execve fail!\n");
            return -1;
        }

    }
    else
    {
        sleep(1);
        printf("%d after get %d is still in place1\n",getpid(),pid);
    }
    return 0;
}
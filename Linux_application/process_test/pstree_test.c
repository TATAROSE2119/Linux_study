#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int args,char const *argv[])
{
    char *name="old";
    printf("it is %s now im in %d\n",name,getpid());
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork failed");
        exit(1);
    }
    else if(pid==0)
    {
        char *newName="new";
        char *argv[]={"/Users/tatarose/Desktop/Linux_study/Linux_application/process_test/erlou",newName,NULL};
        char *envs[]={NULL};
        int re=execve(argv[0],argv,envs);
        if (re<0)
        {
            perror("execve");
            exit(1);
        }
    }
    else
    {
        printf("it is old %d, i let new %d go to other place, and im still here\n",getpid(),pid);
        char bye=fgetc(stdin);
    }
    return 0;
}
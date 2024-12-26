#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    char *name = "old";
    printf("it is %s, now im in %d\n", name, getpid());

    pid_t pid = fork();     // 创建子进程
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {      // 子进程执行新程序
        // 子进程
        char *newName = "new";
        char *args[] = {"/Users/tatarose/Desktop/Linux_study/Linux_application/process_test/erlou", newName, NULL};
        char *envs[] = {NULL};

        int re = execve(args[0], args, envs);
        if (re < 0) {
            perror("execve");
            exit(1);
        }
    } else {
        // 父进程
        printf("it is old %d, i let new %d go to other place, and im still here\n", getpid(), pid);
        //wait(NULL); // 等待子进程结束
    }
    return 0;
}
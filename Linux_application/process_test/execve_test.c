#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
    char *name = "banzhang";
    printf("it is %s now im in %d\n", name, getpid()); // 打印当前进程的 ID 和 name

    // 定义要执行的新程序及其参数
    char *argv[] = {"/Users/tatarose/Desktop/Linux_study/Linux_application/process_test/erlou", NULL};  // erlou 程序的路径
    char *args[] = {"/Users/tatarose/Desktop/Linux_study/Linux_application/process_test/erlou", name, NULL}; // erlou 程序的参数
    char *envp[] = {NULL};

    // 使用 execve 函数执行新的程序
    int re = execve(argv[0], args, envp); // 执行 erlou 程序
    if (re < 0) // 如果执行失败
    {
        perror("execve");
        exit(1);
    }

    // 这行代码永远不会被执行，因为 execve 成功后当前进程映像被替换
    printf("This will not be printed\n");

    return 0;
}
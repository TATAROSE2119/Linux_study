#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]) //argc表示参数个数，argv表示参数数组
{
    if (argc<2)
    {
        printf("参数不够\n");        //打印错误信息
        return 1;                  //返回1表示程序执行失败
    }
    printf("it is %s %d  \n",argv[1],getpid());     //打印进程ID
    return 0;                   //返回0表示程序执行成功
}
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // malloc动态分配内存   
    char *ch=malloc(100);
    // 从标准输入中读取数据
    fgets(ch,100,stdin);

    printf("%s",ch);
    
    fputs(ch,stdout);

    fputs(ch,stderr);

    return 0;

}
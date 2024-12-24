#include <stdio.h>

int main()
{
    char *filename="io.txt";
    FILE *ioFile=fopen(filename,"a+");
    if(ioFile==NULL)
    {
        printf("file open error\n");
        return -1;
    }else{
        printf("file open success\n");
    }

    char *name="大海";
    int fprintfR=fprintf(ioFile,"sgakbbnfbaeaf发发盒饭翻倍u办法色法\n都能尽快把u将奔赴微博？%s",name);
    if(fprintfR==EOF)
    {
        printf("fprintf error\n");
        return -1;
    }else{
        printf("fprintf success\n");
    }

    int result=fclose(ioFile);
    if(result==EOF)
    {
        printf("fclose error\n");
        return -1;
    }else{
        printf("fclose success\n");
    }

    return 0;

}
#include <stdio.h>

int main()
{
    char *filename="test.txt";
    FILE *fp=fopen(filename,"a+");
    if (fp==NULL)   
    {
        perror("fopen");
    }
    else
    {
        printf("open file %s success\n",filename);
    }

    int putcR=fputc('h',fp);

    if (putcR==EOF)
    {
        perror("fputc");
    }
    else
    {
        printf("fputc success\n");
    }

    int ret=fclose(fp);
    if (ret!=0)
    {
        printf("fclose error\n");
        perror("fclose");
        return -1;
    }
    return 0;
    
}
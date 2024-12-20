#include <stdio.h>
int main()
{
    char *filename="test.txt";
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("file open failed\n");
        perror("fopen");
    }
    else
    {
        printf("file open success\n");
    }

    int ret=fclose(fp);
    if (ret!=0)
    {
        printf("file close failed\n");
        perror("fclose");
        return 1;
    }
    return 0;
    
}
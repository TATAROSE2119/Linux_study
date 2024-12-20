#include <stdio.h>

int main()
{
    char *filename = "test.txt";
    FILE *fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", filename);
        return 1;
    }
    else
    {
        printf("File %s opened successfully\n", filename);
    }
    int putsR=fputs("This is a test", fp);
    if(putsR==EOF)
    {
        printf("Error writing to file %s\n", filename);
        return 1;
    }
    else{
        printf("Writing to file %s successful\n", filename);
    }

    int result = fclose(fp);
    if (result!=0)
    {
        printf("Error closing file %s\n", filename);
        return 1;
    }
    return 0;
}
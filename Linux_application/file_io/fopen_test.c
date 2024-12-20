#include <stdio.h>

int main()
{
    char *filename = "test.txt";
    FILE *ioFIle = fopen(filename, "a+");
    if (ioFIle == NULL)
    {
        printf("Error opening file,a+ cant open file that isnot exist\n");
        return 1;
    }
    else
    {
        printf("File opened successfully, a+ can open file that isnot exist \n");
    }
    return 0;
}
#include <stdio.h>

int main()
{
    // Open file
    FILE *ioFile=fopen("io.txt","r");
    if (ioFile==NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    // Read characters one by one
    char c=fgetc(ioFile);
    while (c!=EOF) // End of file
    {
        printf("%c",c);
        c=fgetc(ioFile);// Read next character
    }

    // Close file
    int result=fclose(ioFile);
    if (result!=0)
    {
        printf("Error closing file\n");
        return 1;
    }

    return 0;
}
#include <stdio.h>

int main()
{
    char *filename = "user.txt";
    FILE *userFile = fopen(filename, "r");
    if (userFile == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    char name[50];
    int age;
    char wife[50];
    int scanfR;
    while(fscanf(userFile, "%s %d %s\n",name, &age, wife)!=EOF)
    {
        printf("%s在%d岁, 上了%s\n",name, age, wife);
    }

    int result = fclose(userFile);
    if (result != 0)
    {
        printf("Error closing file\n");
        return 1;
    }
    return 0;
}
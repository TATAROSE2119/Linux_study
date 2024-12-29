#include <stdio.h>
#include <errno.h>

int main()
{
    fopen("/opt","a+");
    printf("errno=%d\n",errno);
    perror("fopen");

    return 0;
}
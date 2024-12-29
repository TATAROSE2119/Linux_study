#include <stdio.h>

int main(int argc,const char *argv[])
{
    fopen("not_exist_file","r");
    perror("fopen");
    return 0;
}
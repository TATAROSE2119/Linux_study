#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	int result=system("ping -c 10 www.baidu.com");

    if(result==0)
    {
        printf("success\n");
    }
    else
    {
        printf("fail\n");
    }

    return 0;
}
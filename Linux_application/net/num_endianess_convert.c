#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//网络字节序转换函数

int main(int argc,char const *argv[]){
    //声明两个端口号

    unsigned short local_num=0x001f,network_num=0;

    network_num=htons(local_num);
    printf("将主机字节序的0X%hx转换为网络字节序的:0X%hx\n",local_num,network_num);

    local_num= ntohs(network_num);
    printf("将网络字节序的0X%hx转换为主机字节序的:0X%hx\n",network_num,local_num);

    return 0;

}
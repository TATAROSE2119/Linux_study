#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char const argv[]){
    printf("192.168.6.101  的16进制表示为:0x%x  0x%x 0x%x 0x%x\n",192,168,6,101);
    //声明结构体接受
    struct sockaddr_in server_addr;
    struct in_addr server_in_addr;

    in_addr_t server_in_addr_t;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&server_in_addr, 0, sizeof(server_in_addr));
    memset(&server_in_addr_t, 0, sizeof(server_in_addr_t));

    server_in_addr_t=inet_addr("192.168.6.101");
    printf("inet_addr:0x%x\n", server_in_addr_t);

    return 0;
}
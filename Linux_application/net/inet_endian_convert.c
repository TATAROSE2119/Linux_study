#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char const *argv[]){
    printf("192.168.6.101  的16进制表示为:0x%x  0x%x 0x%x 0x%x\n",192,168,6,101);
    //声明结构体接受
    struct sockaddr_in server_addr;
    struct in_addr server_in_addr;

    in_addr_t server_in_addr_t;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&server_in_addr, 0, sizeof(server_in_addr));
    memset(&server_in_addr_t, 0, sizeof(server_in_addr_t));

    //不推荐使用 错误返回-1 表示一个正常可用的输出 255.255.255.255
    server_in_addr_t=inet_addr("192.168.6.101");
    printf("inet_addr:0x%x\n", server_in_addr_t);

    //推荐使用inet_aton函数
    inet_aton("192.168.6.101",&server_in_addr);
    //具体只能使用ip协议
    printf("inet_aton:0x%x\n", server_in_addr.s_addr);
    //
    inet_pton(AF_INET, "192.168.6.101", &server_in_addr.s_addr);
    printf("inet_pton:0x%x\n", server_in_addr.s_addr);

    //结构体转换成字符串
    printf("转化为字符串%s\n",inet_ntoa(server_in_addr));

    //本地网络地址
    printf("本地网络地址:0x%x\n", inet_lnaof(server_in_addr));

    //网络号地址
    printf("网络号地址:0x%x\n", inet_netof(server_in_addr));

    //拼接为完整的ip地址
    server_addr.sin_addr=inet_makeaddr(inet_netof(server_in_addr), inet_lnaof(server_in_addr));
    printf("拼接为完整的ip地址:0x%x\n", server_addr.sin_addr.s_addr);   
    return 0;
}
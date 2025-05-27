#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
//错误处理宏

#define hand_error(cmd,result)\
    if (result<0)\
    {\
        perror(cmd); \
        return -1; \
    }\


//线程读写函数
int read_from_server(void *arg) {
    char* read_buf=NULL;
    int clientfd = *(int *)arg;
    read_buf = malloc(sizeof(char) * 1024);
    ssize_t count= 0;    //接受数据
    while(count=recv (clientfd, read_buf, 1024, 0)){
        if (count < 0) {
            perror("recv");
            free(read_buf); // 释放内存
            return -1; // 返回错误
        }
        fputs(read_buf, stdout); // 输出到标准输出
    }
    printf("服务端请求关闭\n");
    free(read_buf); // 释放内存

    return NULL; // 返回成功
}
int write_to_server(void *arg) {
    char *write_buf = NULL;
    int clientfd = *(int *)arg;
    write_buf = malloc(sizeof(char) * 1024);
    ssize_t count = 0; //发送数据

    while(fgets(write_buf,1024, stdin)!= NULL) {
        //发送数据
        count=send(clientfd, write_buf, strlen(write_buf), 0);
        if (count < 0) {
            perror("send");
            free(write_buf); // 释放内存
            return -1; // 返回错误
        }
        

    }
    printf("接收到控制台的关闭请求\n");
    //可以具体到关闭某一段
    shutdown(clientfd, SHUT_RDWR); // 关闭读写
    free(write_buf); // 释放内存
    return NULL; // 返回成功
        
}


int main(int argc, char const *argv[]){
    int temp_result;
    struct sockaddr_in server_addr, client_addr;
    pthread_t pid_read, pid_write;


    //清空
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    //填写客户端地址
    client_addr.sin_family = AF_INET; //使用IPv4协议
    //填写IP地址
    // client_addr.sin_addr.s_addr = htonl(INADDR_ANY); //监听所有可用的接口
    inet_pton(AF_INET,"192.168.233.128",&client_addr.sin_addr.s_addr ); //监听所有可用的接口
    //填写端口号
    client_addr.sin_port = htons(8888); //使用端口8888
    //填写服务端地址
    server_addr.sin_family = AF_INET; //使用IPv4协议
    //填写IP地址
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //监听所有可用的接口
    inet_pton(AF_INET,"0.0.0.0",&server_addr.sin_addr.s_addr ); //监听所有可用的接口
    //填写端口号
    server_addr.sin_port = htons(6666); //使用端口6666
    
    //客户端套接字编程
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    hand_error("socket", sockfd);
    //绑定套接字
    temp_result = bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    hand_error("bind", temp_result);

    //客户端主动链接服务端
    temp_result = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    hand_error("connect", temp_result);
    printf("客户端连接成功%s %d\n",inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));



    //创建线程
    // 在这里可以使用pthread_create来创建线程处理客户端请求
    //创建子线程收消息
    pthread_create(&pid_read,NULL,read_from_server, (void *)&sockfd);

    //创建子线程发消息
    pthread_create(&pid_write,NULL,write_to_server, (void *)&sockfd);
    //阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);

    printf("释放资源\n");
    //关闭套接字
    close(sockfd);
    printf("服务器退出\n");

    return 0;
}
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
int *read_from_client(void *arg) {
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
    printf("客户端断开连接\n");
    free(read_buf); // 释放内存

    return 0;
}
int *write_to_client(void *arg) {
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
    return 1; // 返回成功
        
}


int main(int argc, char const *argv[]){
    int temp_result;
    int clientfd;
    struct sockaddr_in server_addr, client_addr;
    pthread_t pid_read, pid_write;


    //清空
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    //填写服务端地址
    server_addr.sin_family = AF_INET; //使用IPv4协议
    //填写IP地址
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //监听所有可用的接口
    // inet_pton(AF_INET,"0.0.0.0",server_addr.sin_addr.s_addr ); //监听所有可用的接口
    //填写端口号
    server_addr.sin_port = htons(6666); //使用端口6666

    //创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    hand_error("socket", sockfd);
    
    //绑定地址
    temp_result= bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    hand_error("bind", temp_result);
    //开始监听
    temp_result = listen(sockfd, 1024);
    hand_error("listen", temp_result);
    //获取客户端的连接 返回的文件描述符才是和客户端收发消息的文件描述符
    
    // 注意：accept函数会挂起等待，直到有客户端连接

    socklen_t cliaddr_len=sizeof(client_addr);

    clientfd= accept(sockfd, (struct sockaddr *)&client_addr, &cliaddr_len);
    hand_error("accept", clientfd);

    printf("客户端%s %d连接成功,文件描述符是: %d\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), clientfd);


    //创建线程
    // 在这里可以使用pthread_create来创建线程处理客户端请求
    //创建子线程收消息
    pthread_create(&pid_read,NULL,read_from_client, (void *)&clientfd);

    //创建子线程发消息
    pthread_create(&pid_write,NULL,write_to_client, (void *)&clientfd);
    //阻塞主线程
    pthread_join(pid_read, NULL);
    pthread_join(pid_write, NULL);

    printf("释放资源\n");
    //关闭套接字
    close(clientfd);
    close(sockfd);
    printf("服务器退出\n");

    return 0;
}
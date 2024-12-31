// 有名管道接受端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    char *pipe_path = "/tmp/my_fifo";

    //  以只读方式打开管道
    fd = open(pipe_path, O_RDONLY);
    if(fd == -1)
    {
        perror("open error");
        exit(EXIT_FAILURE);
    }

    //  读取数据
    char read_buf[100];
    ssize_t read_num;
    while((read_num = read(fd, read_buf, sizeof(read_buf))) > 0) // 从管道读取数据
    {
        if(write(STDOUT_FILENO, read_buf, read_num) != read_num)  // 写入标准输出
        {
            perror("write error");  // 输出错误信息
            exit(EXIT_FAILURE);
        }
    }
    if(read_num == -1)  // 读取失败
    {
        perror("read error");   // 输出错误信息
        close(fd);  // 关闭文件描述符
        exit(EXIT_FAILURE);
    }

    printf("接收管道退出，进程终止\n");
    close(fd);  // 关闭文件描述符

    return 0;
}
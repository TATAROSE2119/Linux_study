//有名管道发送端

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    char *pipe_path = "/tmp/my_fifo";

    //  创建有名管道  权限设置为0664    
    if(mkfifo(pipe_path, 0664) != 0)
    {
        perror("mkfifo error");
        if(errno != 17)
        {
            exit(EXIT_FAILURE);
        }
    }

    //  以只写方式打开管道
    fd = open(pipe_path, O_WRONLY);
    if(fd == -1)
    {
        perror("open error");
        exit(EXIT_FAILURE);
    }

    //  写入数据
    char write_buf[100];
    ssize_t read_num;
    while((read_num = read(STDIN_FILENO, write_buf, sizeof(write_buf))) > 0) // 从标准输入读取数据
    {
        if(write(fd, write_buf, read_num) != read_num)  // 写入管道 如果写入的字节数不等于读取的字节数
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

    printf("发送管道退出，进程终止\n");
    close(fd);  // 关闭文件描述符

    if (unlink(pipe_path) == -1)  // 删除管道
    {
        perror("unlink error");
    }
    return 0;
}
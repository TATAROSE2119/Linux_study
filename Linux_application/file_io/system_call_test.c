#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("io.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    char buf[1024];//创建一个缓冲区 1024字节
    ssize_t bytes_read= read(fd, buf, sizeof(buf));// read from file
    while(bytes_read > 0)
    {
        // write to stdout
        write(STDOUT_FILENO, buf, bytes_read);
    }
    if (bytes_read < 0)// error
    {
        perror("read");
        close(fd);
        exit(1);
    }
    close(fd);// close file
    return 0;
}
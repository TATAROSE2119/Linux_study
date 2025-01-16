#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;

    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    char *mq_name="\father_son_mq";
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0664, &attr);

    if (mqdes == (mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    //创建父子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        //子进程
        char read_buf[100];
        struct timespec time_info;
        for(size_t i=0;i<10;i++)
        {
            memset(read_buf, 0, sizeof(read_buf));

            clock_gettime(0, &time_info);
            time_info.tv_sec += 15;

            if(mq_timedreceive(mqd, read_buf, sizeof(read_buf), NULL, &time_info)==-1)
            {
                perror("mq_timedreceive");
                exit(EXIT_FAILURE);
            }
            printf("child receive: %s\n", read_buf);
        }
        
    }
    else
    {
        //父进程
        char send_buf[100];
        struct timespec time_info;
        for(size_t i=0;i<10;i++)
        {
            memset(send_buf, 0, sizeof(buf));
            sprintf(send_buf, "父进程的第 %d 次发送消息", (int)i+1);
            clock_gettime(0, &time_info);
            time_info.tv_sec += 5;
            if(mq_timedsend(mqd, buf, strlen(buf), 0, &time_info)==-1)
            {
                perror("mq_timedsend");
                exit(EXIT_FAILURE);
            }
            printf("father send a message,sleep 1s\n");
            sleep(1);
        }
        
    }
    close(mqdes);
    if (pid>0)
    {
        mq_unlink(mq_name);
    }
    return 0;
}

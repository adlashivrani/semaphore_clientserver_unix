#include "header.h"

int main ()
{
	sem_t *semfd1;
    sem_t *semfd2;
    int res;
    mqd_t rdfd;
    char buff[MAX];
    char buff1[MAX];
        semfd1 = sem_open("semsend",0);
        semfd2 = sem_open("semrecv",0);
        rdfd  = mq_open("/mymq", O_RDWR, 0660, NULL);
        if(rdfd == -1) {
                printf("error 1\n");
                exit(0);
        }
        for( ; ; ) {
                res = mq_receive(rdfd, buff, MAX, 0);
                if(res == -1) {
                        printf("error in receive\n");
                        exit(0);
                }
                printf("%s\n", buff);
                sem_post(semfd2);
                printf("enter your msg\n");
                fgets(buff1, MAX, stdin);
                res = mq_send(rdfd, buff1, MAX, 0);
                if(res == -1) {
                        printf("error in send\n");
                        exit(0);
                }
        }         mq_close(rdfd);         return 0;
}

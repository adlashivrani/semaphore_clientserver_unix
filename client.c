#include "header.h"

int main ()
{
	sem_t *semfd2;
    int val2 = 0;
    mqd_t sdfd;
    struct mq_attr att;
    att.mq_flags = 0;
    att.mq_maxmsg = 10;
    att.mq_msgsize = MAX;
    att.mq_curmsgs = 0;
    semfd2 = sem_open("semaphore", O_CREAT , 0660, val2);
    int res;
    char buff[MAX];
    char buff1[MAX];
    sdfd  = mq_open("/mymq", O_CREAT | O_RDWR, 0660, &att);
   	if (sdfd == -1) {
    	printf("error 1\n");
        exit(0);
    }         
	for ( ; ; ) {
    	printf("enter your msg\n");
        fgets(buff, MAX, stdin);
        res = mq_send(sdfd, buff, strlen(buff) , 0);
        if (res == -1) {
        	printf("error 3\n");
            exit(0);
        }
      	sem_wait(semfd2);
        res = mq_receive(sdfd, buff1, MAX, 0);
       	if (res == -1) {
        	printf("error 3\n");
            exit(0);
         }
         printf("%s", buff1);
    }	
	mq_close(sdfd);
    return 0;
}

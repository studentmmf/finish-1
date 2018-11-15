#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <ncurses.h>
#include "chat_client_functions.h"
#define MAX_MSG_SIZE 80
#define DEBUG(fmt, ...)                                                               \
    do                                                                                \
    {                                                                                 \
        printf("%s %s (%d): " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)

struct mymsgbuf {
	long mtype;
	char mtext[MAX_MSG_SIZE];
};

int main()
{
	snd_pid();
	
	initscr();
    keypad(stdscr, TRUE);
   

	pthread_t thread_1, thread_2;
	int result_1, result_2;
	result_1 = pthread_create(&thread_1, NULL, rcv_msg, NULL);
	result_2 = pthread_create(&thread_2, NULL, snd_msg, NULL);
	while(1){}
    refresh();
    getch();
    
    endwin();
    exit(EXIT_SUCCESS);
}

void snd_pid()
{
	key_t key = ftok(".",'m');
    int server = msgget(key, IPC_CREAT|0666); 
	struct mymsgbuf buf_pid;
	buf_pid.mtype = 3000L;
	sprintf(buf_pid.mtext,"%d",getpid());
	int id = msgsnd(server,&buf_pid,sizeof(struct mymsgbuf),IPC_NOWAIT);
}

void *rcv_msg()///???
{
	//int numm =0 ;
	char filename[255] = "";
	sprintf(filename,"+%d",getpid());
	key_t key = ftok(filename,16L);
	int id;
	id = msgget(key, IPC_CREAT|0666);
	struct mymsgbuf buf_1;
	int res;                                       
	while((res = msgrcv(id, &buf_1, sizeof(struct mymsgbuf),1234L,0)) != -1) 
	{
		DEBUG("rcv %s %d", buf_1.mtext, getpid()); 
		
		printf("%s\n", buf_1.mtext);
		
	}
	exit(0);
}

void *snd_msg()
{
	char tmp[80];
	while(1)
	{
	  printw("vvedite soobshenie:");
      //scanw("%s\n", tmp);
      scanw("%s\n", tmp);
      key_t key = ftok("filemsg",16L);
	  int id = msgget(key, IPC_CREAT|0666); 
	  struct mymsgbuf buf;
	  buf.mtype = 2000L;
	  sprintf(buf.mtext,"%d:%s",getpid(),tmp);
	  int id_1 = msgsnd(id,&buf,sizeof(struct mymsgbuf),IPC_NOWAIT);
	  refresh();
	}
}
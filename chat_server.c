#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <ncurses.h>
#include "chat_server_functions.h"
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

void *recieve_pid();
void rcv_snd(struct mymsgbuf buf_1);
int clients[100];
int number=0;


int main()
{
	
	struct mymsgbuf buf_1;
	pthread_t thread_1;
     
    int result = pthread_create(&thread_1, NULL, recieve_pid, NULL);

    rcv_snd(buf_1);

    return 0;
}

void *recieve_pid()
{
	key_t key = ftok(".",'m');
	int id = msgget(key, IPC_CREAT|0666); 
	struct mymsgbuf buf_1;
	int i;
        
	while((i = msgrcv(id,&buf_1,sizeof(struct mymsgbuf),3000L,0)) != -1){
		int m;
		sscanf(buf_1.mtext,"%d",&m);
		clients[number] = m;
		printf("Klient %d podkluchen!\n",m);
		number++;
	}	
}

void rcv_snd(struct mymsgbuf buf_1)///???
{
	key_t key = ftok(",",16L);
	int msg_id = msgget(key, IPC_CREAT|0666);
	int id;
	while( (id = msgrcv(msg_id,&buf_1,sizeof(struct mymsgbuf),2000L,0)) != -1)
	{
		int pid; char tmp[255]; 
		sscanf(buf_1.mtext,"%d:%s",&pid,tmp);
		printf("%d -> %s\n",pid,tmp);

		int i;

		for(i=0; i<number; i++)
		{
			if(clients[i] != pid)
			{                           
				char filename[255] = "";
				sprintf(filename,"+%d",clients[i]);
				key_t key1 = ftok(filename,16L);
				int id_1 = msgget(key1, IPC_CREAT|0666); // получение доступа к очереди клиента
				struct mymsgbuf buf;
				buf.mtype = 1234L;
				sprintf(buf.mtext,"%s\n",tmp);
				DEBUG("snd %s %d %d", buf.mtext, i, id); 
				int id_2 = msgsnd(id_1,&buf,sizeof(struct mymsgbuf),IPC_NOWAIT); // отправка
			}
		}
	}
}



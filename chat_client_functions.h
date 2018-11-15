#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <ncurses.h>

void snd_pid();
void *rcv_msg();
void *snd_msg();
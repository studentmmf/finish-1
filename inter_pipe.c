#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif
#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif
#ifndef NCURSES_H
#define NCURSES_H
#include <ncurses.h>
#endif
#include "inter_pipe_functions.h"

#include <unistd.h>
//#include <sys/types.h>

void args_clean(char *exec_args_1[5])
{
	int i;
	for (i = 0; i < 5; i++) {
		if(exec_args_1[i] == NULL)
			break;
		free(exec_args_1[i]);
	}
}

int main()
{
	initscr();
	keypad(stdscr, TRUE);
	int process_completed = 0;

	char *exec_args_2[5], *exec_args_1[5];

	while (1) {
		int flag = enter_command(exec_args_1, exec_args_2);
		if(exec_args_1[0] == NULL)
			continue;
		//DEBUG("%d %p -> '%s', %p -> '%s'", getpid(), exec_args_1[0], exec_args_1[0], exec_args_1[1], exec_args_1[1]);
		if (flag) {
			process_completed = process_two_command(exec_args_1, exec_args_2);
			if (process_completed == 1)
				break;
		}
		
		if (!flag) {
			//DEBUG("%d %p -> '%s', %p -> '%s'", getpid(), exec_args_1[0], exec_args_1[0], exec_args_1[1], exec_args_1[1]);
			process_completed = process_command(exec_args_1);
			if (process_completed == 1)
				break;
		}

		args_clean(exec_args_1);
		args_clean(exec_args_2);
	}

	refresh();
	getch();
	endwin();

	return 0;
}

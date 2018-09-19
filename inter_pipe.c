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

#define DEBUG(fmt, ...)                                                                       \
        do                                                                                    \
        {                                                                                     \
                printf("%s %s (%d): " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        } while (0)

extern int flag;
int main()
{
	//flag = 1;////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!
	initscr();
	keypad(stdscr, TRUE);
	int process_completed;
	//enter_command();
	//process_two_command(select_command_1(), select_command_2());
    while (1) {
		enter_command();
		if(flag){
		process_completed = process_two_command(select_command_1(), select_command_2());
		if (process_completed == 1)
	    break;}
		//else
		if(!flag) {
			process_completed = process_command(select_command_1());
		if (process_completed == 1)
			break;}
		}
	

	refresh();
	getch();
	endwin();

	return 0;
}

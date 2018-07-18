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
#include "inter_functions.h"

int main()
{
	initscr();
	keypad(stdscr, TRUE);
	int process_completed;
	while (1) {
		process_completed = process_command(select_command());
		if (process_completed == 1)
			break;
	}

	refresh();
	getch();
	endwin();

	return 0;
}

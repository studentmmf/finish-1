#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "inter_functions.h"
#include <string.h>

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

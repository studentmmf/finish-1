#include <ncurses.h> 
#include <stdio.h>
#include <stdlib.h>
#include "inter_functions.h"
#include <string.h>

int main()
{
initscr();
keypad(stdscr, TRUE); 

while(1)
{
if(proc(menu()))break;
}

refresh();
getch();
endwin();

return 0;
}

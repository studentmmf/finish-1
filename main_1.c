#include <ncurses.h>
#include "functions_1.h"

char str[80];



int main()
{
initscr();


keypad(stdscr, TRUE);


int choice;
int choice1;
int flag;

while(1){
choice1=menu1();

if(choice1 == KEY_F(5)){
make_copy();
flag = 0;

for(;;){

if (flag) break;

choice = menu();

switch(choice){

case KEY_F(5) : edit();
break;
case KEY_F(2) : save();
break;
case KEY_F(3) :  my_delete(); flag=1;
break;
}

}

}


if(choice1 == KEY_F(4)) break;

}

refresh();
getch();

endwin();
return 0;
}



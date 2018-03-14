#include <ncurses.h>
#include "editor_functions.h"

char str[256];



int main(int argc, char *argv[])
{
initscr();


keypad(stdscr, TRUE);


int choice;
int choice1;
int flag;
int i;

while(1){
choice1=menu1();

if(choice1 == KEY_F(5)){

if(argc < 2){
printw("vvedite imya fajla\n");
getstr(str);
}

else for(i=0; argv[i]; i++) str[i] = argv[1][i];

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



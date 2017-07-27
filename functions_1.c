#include <ncurses.h>
#include "functions_1.h"

extern char str[80];

int menu()
{
int ch;
printw("F5 : otkryt i redaktirovat fajl\n");
printw("F2 : sohranit izmeneniya\n");
printw("F3 : vyjti ili vybrat drugoj fajl\n");


ch = getch();

return ch;
}

int menu1()
{
int ch1;
printw("F5 : vybrat fajl\n");
printw("F4 : vyjti iz programmy\n");

ch1 = getch();

return ch1;
}

void make_copy()
{
printw("vvedite imya fajla\n");

FILE *f, *c;
char ch;

getstr(str);

if((f = fopen(str, "r"))==NULL) {
printw("ne udaetsya otkryt fajl1\n");
return;
}

if((c = fopen("copy_proc", "w+"))==NULL) {
printw("ne udaetsya sozdat vspomogatelnyj fajl2\n");
return;
}

while(!feof(f)) {
ch = fgetc(f);
if(!feof(f)) fputc(ch, c);
}

fclose(f);
fclose(c);
}

void edit()
{
char ch;
FILE *fp;
long position;
char str[8000];


if((fp = fopen("copy_proc", "r+"))==NULL) {
printw("ne udaetsya otkryt fajl3\n");
return;
}


for(;;) {
printw("(w): prodolzhit\n");
printw("(q): nazad\n");
refresh();
ch = getch();

if(ch == 'w') {
printw("vvedite poziciy bajta v fajle\n");
scanw("%d",&position);
fseek(fp, position, SEEK_SET);
printw("vvedite stroku simvolov\n");
getstr(str);
fwrite(str, sizeof str, 1, fp);
}
if(ch == 'q') break;


}

fclose(fp);
}

void save()
{
FILE *f, *c;
char ch;


if((f = fopen(str, "r+"))==NULL) {
printw("ne udaetsya otkryt fajl4\n");
return;
}

if((c = fopen("copy_proc", "r+"))==NULL) {
printw("ne udaetsya sozdat vspomogatelnyj fajl5\n");
return;
}

while(!feof(c)) {
ch = fgetc(c);
if(!feof(c)) fputc(ch, f);
}

fclose(f);
fclose(c);
}

void my_delete()
{

if(remove("copy_proc")) {
printw("ne udaetsya udalit fajl6\n");
return;
}

}

#include <ncurses.h> 
#include <stdio.h>
#include <stdlib.h>
#include "inter_functions.h"
#include <string.h>

char *args[][3] = {{"vyhod", "", ""}, {"ls", "/bin/ls", "ls"}, {"vi", "/bin/vi", "vi"}};

int SIZE = 3;
char tmp[80];

int menu()//выбор команды
{
int i;

printw("vvedite comandu\n");
scanw("%s", tmp);




for(i=0;i<SIZE; i++)
{
if(!strcmp(tmp, args[i][0]))
{
//printw("debug %s %s\n", args[i][1], args[i][2]); 
return i;
}//vrode vse rabotaet
}

printw("neizvestnaya komanda\n");
return -1;
}

int proc(int num)//fork exec wait// принимает path и может еще что-то
{
int status;
pid_t pid, pid_1;
int ret;
if(num == -1) return 0;
if(num == 0) return 1;

else //fork exec wait
{
pid_1 = fork();

if(pid_1 == -1)
perror("fork");
if(!pid_1)
{


int ret;
ret = execl(args[num][1], args[num][2], NULL);///////bad address

if (ret == -1) {
perror("execl");
exit(EXIT_FAILURE);}

pid = wait(&status);

if (pid == -1)
perror("wait");

printw("pid=%d\n", pid);

if (WIFEXITED (status))
printw("Нормальное завершение, статус=%d\n", WEXITSTATUS (status));
if (WIFSIGNALED (status))
//printw("Убит сигналом=%d%s\n",WTERMSIG (status), WCOREDUMP (status) ? " (dumped core)" : "");
if (WIFSTOPPED (status))
printw("Остановлен сигналом=%d\n",WSTOPSIG (status));
if (WIFCONTINUED (status))
printw("Продолжен\n");
}

return 0;
}
}




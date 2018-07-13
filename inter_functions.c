#include <ncurses.h> 
#include <stdio.h>
#include <stdlib.h>
#include "inter_functions.h"
#include <string.h>

char *match[][3] = {{"vyhod", "", ""}, {"ls", "/bin/ls", "ls"}, {"vi", "/bin/vi", "vi"}, {"cat", "/bin/cat", "cat"}, {"echo", "/bin/echo", "echo"}, {"mkdir", "/bin/mkdir", "mkdir"}};//список команд
char *args[5];
int SIZE = 6;//количество утилит
char tmp[80];//команда с параметрами

int menu()//выбор команды
{
int i=0;

printw("vvedite comandu\n");
getstr(tmp);

char *pch = strtok(tmp, " "); //разбиваем на слова и записываем в args

while(pch != NULL)
{
args[i] = pch;
pch = strtok(NULL, " ");
i++;
}


for(i=0;i<SIZE; i++)
{
if(!strcmp(args[0], match[i][0]))
{

return i;
}
}

printw("neizvestnaya komanda\n");
return -1;
}

int proc(int num)
{
int status;
pid_t pid, pid_1;
int ret;
if(num == -1) return 0;
if(num == 0) return 1;

else 
{
pid_1 = fork();

if(pid_1 == -1)
perror("fork");

if(!pid_1)//дочерний
{
int ret;

ret = execv(match[num][1],args);//args должен завершаться NULL!!!!
if (ret == -1) {
perror("execv");
exit(EXIT_FAILURE);}
}

pid = wait(&status);

if (pid == -1)
perror("wait");

printw("pid=%d\n", pid);

if (WIFEXITED (status))
printw("Normalnoe zavershenie, status=%d\n", WEXITSTATUS (status));
if (WIFSTOPPED (status))
printw("Ostanovlen signalom=%d\n",WSTOPSIG (status));
if (WIFCONTINUED (status))
printw("Prodolzhen\n");
return 0;
}
}




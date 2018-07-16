#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "inter_functions.h"
#include <string.h>

char* commands[][3] = {{"vyhod", "", ""},
                       {"ls", "/bin/ls", "ls"},
                       {"vi", "/bin/vi", "vi"},
                       {"cat", "/bin/cat", "cat"},
                       {"echo", "/bin/echo", "echo"},
					   {"mkdir", "/bin/mkdir", "mkdir"}}; 
char* exec_args[5];
int   commands_count = 6; 
		

int select_command() 
{
	char  temporary_string[80];	
	printw("vvedite comandu\n");
	getstr(temporary_string);

	char* word = strtok(temporary_string, " "); // Разбиваем на слова и записываем в exec_args
	int i = 0;
	while (word != 0) {
		exec_args[i] = word;
		word = strtok(0, " ");
		i++;
	}

	int right_command;
	for (i = 0; i < commands_count; i++)  {
		right_command = strcmp(exec_args[0], commands[i][0]);
		if (right_command == 0) {

			return i;
		}
	}

	printw("neizvestnaya komanda\n");
	return -1;
}

int process_command(int number)
{
	int    status; // Статус завершения
	pid_t  pid, pid_1; // PID процессов
	int    ret; // Возвращаемое execv() значение
	if (number == -1)
		return 0;
	if (number == 0)
		return 1;

	else {
		pid_1 = fork();

		if (pid_1 == -1)
			perror("fork");

		if (pid_1 == 0) {// Дочерний
		
			

			ret = execv(commands[number][1], exec_args); 
			if (ret == -1) {
				perror("execv");
				exit(EXIT_FAILURE);
			}
		}

		pid = wait(&status);

		if (pid == -1)
			perror("wait");

		printw("pid=%d\n", pid);

		if (WIFEXITED(status))
			printw("Normalnoe zavershenie, status=%d\n", WEXITSTATUS(status));
		if (WIFSTOPPED(status))
			printw("Ostanovlen signalom=%d\n", WSTOPSIG(status));
		if (WIFCONTINUED(status))
			printw("Prodolzhen\n");
		return 0;
	}
}

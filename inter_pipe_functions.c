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

char* commands[][3] = {{"vyhod", "", ""},
                       {"grep", "/bin/grep", "grep"},
                       {"ls", "/bin/ls", "ls"},
                       {"vi", "/bin/vi", "vi"},
                       {"cat", "/bin/cat", "cat"},
                       {"echo", "/bin/echo", "echo"},
					   {"mkdir", "/bin/mkdir", "mkdir"}}; 
char* exec_args_1[5];
char* exec_args_2[5];
int flag;
int   commands_count = 7; 
		

void enter_command() 
{
	char  temporary_string[80];	
	printw("vvedite comandu\n");
	getstr(temporary_string);
    
	char *word = strtok(temporary_string, " "); // Разбиваем на слова 
	int i = 0;
	flag = 0;
	while(word != 0){

		exec_args_1[i] = word;
		printw("%s%d\n",exec_args_1[i], 1);
		word = strtok(0, " ");
        
		//if(word == "|")//так не разделяет,но работает с ошибками
		if (strcmp("|", word) == 0)//так разделяет, но не работает
		{
			exec_args_1[i++] = NULL;

		flag = 1;//есть вторая команда
		printw("hello |\n");
		 break;		
		}
		i++;
	}
	if(flag){
	i=0; 
			
			word = strtok(0, " ");
			while(word != 0){
        exec_args_2[i] = word;
        printw("%s\n",exec_args_2[i]);		
		word = strtok(0, " ");
		i++; }
	}
exec_args_2[i++] = NULL;
}
	int select_command_1()
	{ 
		int i;
		int right_command;
	for (i = 0; i < commands_count; i++)  {
		right_command = strcmp(exec_args_1[0], commands[i][0]);
		if (right_command == 0) {

			return i;
		}
	}
		printw("neizvestnaya komanda\n");
	return -1;
    
}
	
int select_command_2()
	{ 
		int i;
		int right_command;
	for (i = 0; i < commands_count; i++)  {
		right_command = strcmp(exec_args_2[0], commands[i][0]);
		if (right_command == 0) {

			return i;
		}
	}
		printw("neizvestnaya komanda\n");
	return -1;
    
}
	


int process_two_command(int number_1, int number_2)
{
	int    file_discr[2];
	int    status; // Статус завершения
	pid_t  pid, pid_1; // PID процессов
	int    ret; // Возвращаемое execv() значение
	if (number_1 == -1)
		return 0;
	if (number_1 == 0)
		return 1;
    
    

else {
		
		pipe(file_discr);

		pid_1 = fork();

		if (pid_1 == -1)
			perror("fork");

		if (pid_1 == 0) {// Дочерний
		
			dup2(file_discr[1], STDOUT_FILENO);
			close(file_discr[1]);

			ret = execv(commands[number_1][1], exec_args_1); 
			if (ret == -1) {
				perror("execv");
				exit(EXIT_FAILURE);	}
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

        pid_1 = fork();

        if (pid_1 == 0) {// Дочерний
		
			dup2(file_discr[0], STDIN_FILENO);
			close(file_discr[0]);

			ret = execv(commands[number_2][1], exec_args_2); 
			if (ret == -1) {
				perror("execv");
				exit(EXIT_FAILURE);	}
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
		
			

			ret = execv(commands[number][1], exec_args_1); 
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
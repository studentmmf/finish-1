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
	{"awk", "/bin/awk", "awk"},
	{"grep", "/bin/grep", "grep"},
	{"ls", "/bin/ls", "ls"},
	{"vi", "/bin/vi", "vi"},
	{"cat", "/bin/cat", "cat"},
	{"echo", "/bin/echo", "echo"},
	{"mkdir", "/bin/mkdir", "mkdir"},
	{"sort", "usr/bin/sort", "sort"}
};


const int commands_count = sizeof(commands) / sizeof(*commands);

int enter_command(char *exec_args_1[5], char *exec_args_2[5])
{
	char temporary_string[80], *word_set[20], *word;
	int count = 0, i = 0, j = 0, k = 0, n = 0;
	int flag = 0;

	printw("vvedite comandu\n");
	getnstr(temporary_string, sizeof(temporary_string));

	
	for(i = 0; i < 5; i++) {
		exec_args_1[i] = exec_args_2[i] = NULL;
	}

	flag = i = 0;
	word = strtok(temporary_string, " "); // Разбиваем на слова

	while (word != NULL && i < sizeof(word_set) / sizeof(*word_set))
	{
		word_set[i] = strdup(word);
		if (strcmp(word, "|") == 0)
		{
			j = i;
			flag = 1;
			
		}
		word = strtok(0, " ");
		i++;
	}

	k = i;
	if (flag)
	{	
		for (i = 0; i < j; i++) {
			exec_args_1[i] = word_set[i];
			//DEBUG("%s\n", exec_args_1[i]);
			
		}

		

		
		for (i = j + 1, n = 0 ; i < k; i++, n++) {
			exec_args_2[n] = word_set[i];
			//DEBUG("%s\n", exec_args_2[n]);
		}
	}
	
	if (!flag)
	{
		
		for (i = 0; i < k; i++)
		{
			exec_args_1[i] = word_set[i];
			//DEBUG("%s\n", exec_args_1[i]);
		}
	}

	
	return flag;
}


int select_command(char *exec_args_1[5])
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

int process_two_command(char *exec_args_1[5], char *exec_args_2[5])
{
	int    file_discr[2];
	int    status; // Статус завершения
	pid_t  pid, pid_1; // PID процессов
	int    ret; // Возвращаемое execv() значение

	int number_1 = select_command(exec_args_1);
	int number_2 = select_command(exec_args_2);

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

			//dup2(file_discr[1], STDOUT_FILENO);
			//close(file_discr[1]);
			close(file_discr[0]);
			close(1);
			dup(file_discr[1]);
			close(file_discr[1]);

			

			//printf("hello_1 %s %s %s\n", commands[number_1][1], exec_args_1[0], exec_args_1[1]);
			ret = execv(commands[number_1][1], exec_args_1);
			if (ret == -1) {
				perror("execv");
				exit(EXIT_FAILURE);
			}
		}



		pid_1 = fork();

		if (pid_1 == 0) {// Дочерний

			//dup2(file_discr[0], STDIN_FILENO);
			//close(file_discr[0]);
			close(file_discr[1]);
			close(0);
			dup(file_discr[0]);
			close(file_discr[0]);

			

			//printf("hello_2 %s %s %s\n", commands[number_2][1], exec_args_2[0], exec_args_2[1]);
			ret = execv(commands[number_2][1], exec_args_2);
			if (ret == -1) {
				perror("execv");
				exit(EXIT_FAILURE);
			}
		}

		close(file_discr[0]);
		close(file_discr[1]);

		pid = wait(&status);

		if (pid == -1)
			perror("wait");

		printw("pid_1=%d\n", pid);

		if (WIFEXITED(status))
			printw("Normalnoe zavershenie_1, status=%d\n", WEXITSTATUS(status));
		if (WIFSTOPPED(status))
			printw("Ostanovlen signalom=%d\n", WSTOPSIG(status));
		if (WIFCONTINUED(status))
			printw("Prodolzhen\n");


		pid = wait(&status);

		if (pid == -1)
			perror("wait");

		printw("pid_2=%d\n", pid);

		if (WIFEXITED(status))
			printw("Normalnoe zavershenie_2, status=%d\n", WEXITSTATUS(status));
		if (WIFSTOPPED(status))
			printw("Ostanovlen signalom=%d\n", WSTOPSIG(status));
		if (WIFCONTINUED(status))
			printw("Prodolzhen\n");
		return 0;
	}
}



int process_command(char *exec_args_1[5])
{
	int    status; // Статус завершения
	pid_t  pid, pid_1; // PID процессов
	int    ret; // Возвращаемое execv() значение

	//DEBUG("%d %p -> '%s', %p -> '%s'", getpid(), exec_args_1[0], exec_args_1[0], exec_args_1[1], exec_args_1[1]);

	int number = select_command(exec_args_1);

	

	if (number == -1)
		return 0;
	if (number == 0)
		return 1;

	else {
		pid_1 = fork();

		if (pid_1 == -1)
			perror("fork");

		if (pid_1 == 0) {// Дочерний

			
			
			//printf("%d %d hello_1 %s %s %s\n", __LINE__, getpid(), commands[number][1], exec_args_1[0], exec_args_1[1]);
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
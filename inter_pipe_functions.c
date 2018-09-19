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

#define DEBUG(fmt, ...)                                                                       \
        do                                                                                    \
        {                                                                                     \
                printf("%s %s (%d): " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        } while (0)

char* commands[][3] = {{"vyhod", "", ""},
                       {"awk", "/bin/awk", "awk"},
                       {"grep", "/bin/grep", "grep"},
                       {"ls", "/bin/ls", "ls"},
                       {"vi", "/bin/vi", "vi"},
                       {"cat", "/bin/cat", "cat"},
                       {"echo", "/bin/echo", "echo"},
					   {"mkdir", "/bin/mkdir", "mkdir"},
					   {"sort", "usr/bin/sort", "sort"}}; 
char* exec_args_1[5];
char* exec_args_2[5];
int flag;
int   commands_count = 9; 
		

void enter_command() 
{
	char  temporary_string[80];	
	printw("vvedite comandu\n");
	getstr(temporary_string);
    int count;
    char *word_set[20];
    int i = 0;
    int j;
    int k;
    int n;
    flag = 0;
	char *word = strtok(temporary_string, " "); // Разбиваем на слова 
    while(word != 0)
    {
    	word_set[i] = word;
    	if(strcmp(word, "|") == 0)
    	{
    		j = i;
    		flag = 1;
    		//word = strtok(0, " ");
    	}
    	word = strtok(0, " ");
    	i++;
    } 
    k = i;
    if(flag)
     {//DEBUG("goodbuy world", j);
	//exec_args_1[0] = word_set[0];
	//exec_args_1[1] = word_set[1];
 	for(i=0;i<j;i++){
		exec_args_1[i] = word_set[i];
		printf("%s\n", exec_args_1[i]);
		//strcpy(exec_args_1[i], word_set[i]);
	}//exec_args_1[2] = NULL;
		
		//exec_args_2[0] = word_set[3];
		//exec_args_2[1] = word_set[4];
	for(i=j+1, n=0 ;i<k;i++,n++){
		exec_args_2[n] = word_set[i];
		printf("%s\n", exec_args_2[n]);
	}//exec_args_2[2] = NULL;
     }
     //else
     if(!flag)
     {
     	for(i=0;i<k;i++)
     	{
     		exec_args_1[i] = word_set[i];
     		printf("%s\n", exec_args_1[i]);
     	}//exec_args_1[2] = NULL;
     }
  // printf("%s", exec_args_1[2]);
   /* for(i=0;i<2;i++)
    	{n=0;
    		do{
    			printf("%c", exec_args_1[i][n]);
    			n++;
    		}while(exec_args_1[i][n] != '\0');
    		//printf("%c ", exec_args_1[i][n]);
    		printf("\n");
    		//printf("%s %s\n",exec_args_1[i], exec_args_2[i]);
    	}
    	//printf("%c\n",'\0');
    	for(i=0;i<2;i++)
    	{n=0;
    		do{
    			printf("%c", exec_args_2[i][n]);
    			n++;
    		}while(exec_args_2[i][n] != '\0');
    		//printf("%c ", exec_args_2[i][n]);
    		printf("\n");
    		//printf("%s %s\n",exec_args_1[i], exec_args_2[i]);
    	}*/

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
	//return 3;
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
	//return 2;
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
		
			//dup2(file_discr[1], STDOUT_FILENO);
			//close(file_discr[1]);
			close(file_discr[0]);
			close(1);
			dup(file_discr[1]);
			close(file_discr[1]);
            
			//exec_args_1[0] = "ls";
			//exec_args_1[1] = "-l";
		
			printf("hello_1 %s %s %s\n",commands[number_1][1], exec_args_1[0], exec_args_1[1]);
			ret = execv(commands[number_1][1],exec_args_1);
			if (ret == -1) {
				perror("execv");
				exit(EXIT_FAILURE);	}
		}

        

        pid_1 = fork();

        if (pid_1 == 0) {// Дочерний
		
			//dup2(file_discr[0], STDIN_FILENO);
			//close(file_discr[0]);
			close(file_discr[1]);
			close(0);
			dup(file_discr[0]);
			close(file_discr[0]);
            
			//exec_args_2[0] = "grep";
			//exec_args_2[1] = "a*";
			
			printf("hello_2 %s %s %s\n",commands[number_2][1], exec_args_2[0], exec_args_2[1]);
			 ret = execv(commands[number_2][1],exec_args_2);
			if (ret == -1) {
				perror("execv");
				exit(EXIT_FAILURE);	}
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
		
			exec_args_1[0] = "ls";
			exec_args_1[1] = "-l";

printf("hello_1 %s %s %s\n",commands[number][1], exec_args_1[0], exec_args_1[1]);
 ret = execv(commands[number][1],exec_args_1);
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
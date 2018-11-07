#ifndef INTER_PIPE_FUNCTIONS_H
#define INTER_PIPE_FUNCTIONS_H
int process_two_command(char *exec_args_1[5], char *exec_args_2[5]);
int process_command(char *exec_args_1[5]);
int select_command(char *exec_args_1[5]);
int enter_command(char *exec_args_1[5], char *exec_args_2[5]);

#define DEBUG(fmt, ...)                                                                       \
        do                                                                                    \
        {                                                                                     \
                printw("%s %s (%d): " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__); getch();\
        } while (0)

#endif

#ifndef MANAGER_FUNCTIONS_H
#define MANAGER_FUNCTIONS_H
int menu();
int menu1();
void mystrplus(char a[], char b[]);
void mystrminus(char a[]);
void init_list();
void update_list(const char *name);
void update_screen();
void thread_func_1(FILE *g, FILE *f);//копировать
void *thread_func();//статус копирования
#endif

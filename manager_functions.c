#include <ncurses.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "manager_functions.h"
#include <string.h>
#define DEBUG(fmt, ...)                                                                       \
        do                                                                                    \
        {                                                                                     \
                printf("%s %s (%d): " fmt "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        } while (0)

extern int SIZE, SIZE_INCREMENT, OLD_SIZE;
extern int current_element, max_num;
extern struct dirent **list;
extern struct dirent *list_1;
void init_list()
{
        int t;

        for (t = 0; t < SIZE; t++)
                *(list[t]->d_name) = '\0';
}

void update_list(const char *name)
{
        int errno = 0;
        int err = 0;
        int i = 0, j = 0;
        DIR *dir;
        dir = opendir(name);

        for (;;)
        {
                errno = 0;

                list_1 = readdir(dir);

                if (errno && !list_1)
                        perror("readdir");
                if (list_1 == NULL)
                        break;

                list[i] = list_1;
                if (i == SIZE - 1)
                {
                        OLD_SIZE = SIZE;
                        SIZE += SIZE_INCREMENT;

                        list = (struct dirent **)realloc(list, SIZE * sizeof(struct dirent *));
                        if (!list)
                        {
                                printw("Error: can't allocate memory1\n");
                                getch();
                                exit(1);
                        }

                        for (j = OLD_SIZE; j < SIZE; j++)
                        {
                                list[j] = (struct dirent *)realloc(list[j], sizeof(struct dirent));
                                if (!list[j])
                                {
                                        printw("Error: can't allocate memory2\n");
                                        getch();
                                        exit(2);
                                }
                        }
                }

                i++;
        }
        max_num = i;
        for (; i < SIZE; i++)
                *(list[i]->d_name) = '\0';

        errno = 0;
        err = closedir(dir);

        if (errno && (err == -1))
                perror("closedir");
}

int menu()
{
        int ch;

        printw("Vyberite katalog ili fajl i nazhmite Enter dlya vybora\n");
        printw("F2 : sozdat novyj katalog v tekushem kataloge\n");
        printw("F3 : sozdat novyj fajl v tekushem kataloge\n");
        printw("F4 : vstavit v tekushem kataloge\n");
        printw("F5 : otkryt katalog po zadannomu puti\n");
        printw("b : vverh\n");
        printw("q : vyjti iz manager\n");

        ch = getch();

        return ch;
}

int menu1()
{
        int ch;

        printw("Enter : otkryt\n");
        printw("F2 : pereimenovat\n");
        printw("F3 : udalit\n");
        printw("F4 : kopirovat\n");
        printw("F5 : peremestit\n");
        printw("r : otmenit\n");

        ch = getch();

        return ch;
}

void update_screen()
{
        int i;
        erase(); //чистим экран
                 //выводим все элементы
        for (i = 0; (i < SIZE) && (*(list[i]->d_name) != '\0'); i++)
        {
                //если счетчик равен текущему элементу
                if (i == current_element)
                {
                        //включаем атрибут "жирный"
                        attron(A_BOLD);
                        //выбираем цветовую пару номер 1
                        attron(COLOR_PAIR(1));
                        //выводим строковое представление элемента списка
                        printw("%s      ", list[i]->d_name);
                        if (list[i]->d_type == DT_DIR)
                                printw("%s\n", "katalog");
                        else if (list[i]->d_type == DT_REG)
                                printw("%s\n", "fajl");
                        else
                                printw("%s\n", "neizvestnyj tip fajla");
                        //выключаем выбранные атрибуты
                        attroff(COLOR_PAIR(1));
                        attroff(A_BOLD);
                }
                else //иначе выводим обычным цветом
                {
                        attron(COLOR_PAIR(2));
                        printw("%s      ", list[i]->d_name);
                        if (list[i]->d_type == DT_DIR)
                                printw("%s\n", "katalog");
                        else if (list[i]->d_type == DT_REG)
                                printw("%s\n", "fajl");
                        else
                                printw("%s\n", "neizvestnyj tip fajla");
                        attroff(COLOR_PAIR(2));
                }
        }
}

void mystrplus(char a[], char b[]) //справа к пути приписываем "/имя"
{
     strcat(a,"/");
strcat(a, b);
}

void mystrminus(char a[]) //от пути отсоединяем хвост "/hbvfhkvdbv"
{
        int i, j;
        for (j = 0; a[j] != '\0'; j++)
                ;
        for (i = 0; a[j - i] != '/'; i++)
                ;
        a[j - i] = '\0';
}


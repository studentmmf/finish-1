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

int SIZE = 5, SIZE_INCREMENT = 5, OLD_SIZE;

int current_element = 0, max_num; 

char cwd[256];
struct dirent **list;
struct dirent *list_1;

int main()
{
        initscr();

        keypad(stdscr, TRUE); 
       

        int j;
        pid_t pid;
        int ret;

        FILE *f, *g, *c;
        char ch;

        getcwd(cwd, 256); //копирует абсолютный путь текущего рабочего каталога в буфер cwd

        list = (struct dirent **)malloc(SIZE * sizeof(struct dirent *));
        if (!list)
        {
                printw("Error: can't allocate memory11\n");
                getch();
                exit(3);
        }
        for (j = 0; j < SIZE; j++)
        {
                list[j] = (struct dirent *)malloc(sizeof(struct dirent));
                if (!list[j])
                {
                        printw("Error: can't allocate memory22\n");
                        getch();
                        exit(4);
                }
        }

        init_list();

        start_color();
        noecho();
        //создаем цветовые пары
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);

        int choice = 0, choice1;

        char path[256], old_path[256], new_path[256], path_1[256], src_path[256], dst_path[256]; 

        max_num = SIZE;

        update_list(cwd); //аварийный останов

        strcpy(path, cwd); //адрес из cwd записываем в path

        do
        {

                update_screen();

                choice = menu();

                switch (choice)
                {
                //если нажата "вверх", то уменьшаем current_element
                case KEY_UP:
                        if (current_element > 0)
                                current_element--;
                        break;
                //если нажата "вниз", то увеличиваем current_element
                case KEY_DOWN:
                        if (current_element < max_num - 1)
                                current_element++;
                        break;
                //обработка нажатия Enter
                case '\n':
                        choice1 = menu1();
                        switch (choice1)
                        {
                        case '\n':
                                if (list[current_element]->d_type == DT_DIR)
                                {

                                        mystrplus(path, list[current_element]->d_name);

                                        update_list(path); //открыть как каталог

                                }
                                else if (list[current_element]->d_type == DT_REG) //открыть в редакторе
                                {
                                        strcpy(path_1, path);
                                        mystrplus(path_1, list[current_element]->d_name);
                                        pid = fork();
                                        if (pid == -1)
                                                perror("fork");
                                        // дочерний ...
                                        if (!pid)
                                        {
                                                const char *args[] = {"editor", path_1, NULL};

                                                ret = execv("/home/grigoriy/Рабочий стол/hello1/editor", args);
                                                if (ret == -1)
                                                {
                                                        perror("execv");
                                                        exit(EXIT_FAILURE);
                                                }
                                        }
                                } //fork exec editor.c
                                else
                                        printw("%s\n", "ne mogu otkryt - neizvestnyj tip fajla");
                                break;
                        case KEY_F(2): //переименовать
                                printw("%s\n", "vvedite novoe imya");
                                strcpy(new_path, path);
                                strcpy(old_path, path);

                                mystrplus(old_path, list[current_element]->d_name);
                                scanw("%s", path_1); ///!!!
                                mystrplus(new_path, path_1);
                                rename(old_path, new_path);
                                update_list(path);
                                break;
                        case KEY_F(3): //удалить
                                strcpy(old_path, path);
                                mystrplus(old_path, list[current_element]->d_name);
                                remove(old_path);
                                update_list(path);
                                break;
                        case KEY_F(4): //копировать файл
                                if (list[current_element]->d_type == DT_REG)
                                {
                                        strcpy(src_path, path);
                                        mystrplus(src_path, list[current_element]->d_name);
                                }
                                else
                                        printw("%s\n", "ne mogu kopirovat dannyj tip fajla");
                                break;
                        case KEY_F(5): //переместить по новому пути?????????
                                strcpy(old_path, path);
                                mystrplus(old_path, list[current_element]->d_name);
                                printw("%s\n", "vvedite novyj put"); //!!!
                                scanw("%s", new_path);
                                rename(old_path, new_path);
                                update_list(path); //на всякий случай
                                break;
                        case 'r': //отмена
                                break;
                        } //пользователь выбрал элемент list[current_element]
                        break;
                case KEY_F(2): //создать новый каталог в текущем каталоге
                        printw("%s\n", "vvedite imya novogo kataloga");
                        scanw("%s", new_path);
                        strcpy(old_path, path);
                        mystrplus(old_path, new_path);
                        mkdir(old_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                        update_list(path);
                        break;
                case KEY_F(3): //создать новый файл в текущем каталоге
                        printw("%s\n", "vvedite imya novogo fajla");
                        scanw("%s", new_path);
                        strcpy(old_path, path);
                        mystrplus(old_path, new_path);
                        if ((c = fopen(old_path, "w+")) == NULL)
                        {
                                printw("%s\n", "ne udaetsya otkryt fajl1");
                                return;
                        }
                        fclose(c);
                        update_list(path);
                        break;
                case KEY_F(4): //вставить в текущем каталоге
                        printw("%s\n", "vvedite imya dlya kopii fajla");
                        scanw("%s", path_1);
                        if ((f = fopen(src_path, "r+")) == NULL)
                        {
                                printw("%s\n", "ne udaetsya otkryt fajl4");
                                return;
                        }
                        strcpy(dst_path, path);
                        mystrplus(dst_path, path_1);
                        if ((g = fopen(dst_path, "w+")) == NULL)
                        {
                                printw("%s\n", "ne udaetsya sozdat fajl5");
                                return;
                        }
                        while (!feof(g))
                        {
                                ch = fgetc(g);
                                if (!feof(g))
                                        fputc(ch, f);
                        }
                        fclose(f);
                        fclose(g);
                        update_list(path);
                        break;
                case KEY_F(5): //открыть каталог по заданному пути
                        printw("%s\n", "vvedite put kataloga");
                        scanw("%s", path);
                        update_list(path);
                        break;
                case 'b': //вверх
                        mystrminus(path);
                        update_list(path);
                        break;
                }

        } while (choice != 'q');
 
        

       

        refresh();
        getch();

        endwin();

       

        for (j = 0; j < SIZE; j++)
                free(list[j]); ////???????
 
        free(list);
//DEBUG(" goodbye world :(");

        return 0;
}

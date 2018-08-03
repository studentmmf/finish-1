#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "magaz_threads_functions.h"

extern int magazines[5];
extern int buyers[3];
extern delta_load;
static pthread_mutex_t mutex_buy_1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_buy_2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_buy_3 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_load = PTHREAD_MUTEX_INITIALIZER;

void *load()
{
    int number;
    while((buyers[0] != 0) || (buyers[1] != 0) || (buyers[2] != 0))
    {
    srand(time(NULL));
    number = rand() % 5;
    pthread_mutex_lock(&mutex_load);
    magazines[number] += delta_load;    
    show();
    pthread_mutex_unlock(&mutex_load);
    sleep(1);
    }
    
        pthread_exit(0);
}


void *buy(void *num)
{
    pthread_mutex_t mutex;
    int buyer_num = * (int *) num;
    switch(buyer_num)
    {
        case 0:
         mutex = mutex_buy_1;
           break;
        case 1:
         mutex = mutex_buy_2;
           break;
        case 2: 
         mutex = mutex_buy_3;
           break;
    }
    while(buyers[buyer_num] > 0)
    {
    int number;
    srand(time(NULL));
    number = rand() % 5;
    if(buyers[buyer_num] < magazines[number])
    {
        pthread_mutex_lock(&mutex);
        magazines[number] -= buyers[buyer_num];        
        buyers[buyer_num] = 0;
        show();
        pthread_mutex_unlock(&mutex);
    }
    if((magazines[number] <= buyers[buyer_num]) && (magazines[number] != 0))
    {
        pthread_mutex_lock(&mutex);
        buyers[buyer_num] -= magazines[number];
        magazines[number] = 0;
        sleep(3);
        show();
        pthread_mutex_unlock(&mutex);
    }
}
if(buyers[buyer_num] == 0)
    pthread_exit(0);
  
}


void show()
{
    int i;
    for(i=0; i<5; i++)
    {
        printf("magazine %d : %d\n", i+1, magazines[i]);
    }
    for(i=0; i<3; i++)
    {
        printf("buyer %d : %d\n",i+1, buyers[i]);
    }
}


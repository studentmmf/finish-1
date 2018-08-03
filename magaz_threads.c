#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "magaz_threads_functions.h"

int magazines[5] = {1020, 1070, 1150, 1180, 1110};
int buyers[3] = {3170, 3250, 3410};
int delta_load = 350;

pthread_t thr_buy_1, thr_buy_2, thr_buy_3, thr_load;
int result;

int main()
{
	int i_1 = 0;
	int i_2 = 1;
	int i_3 = 2;
	result = pthread_create(&thr_buy_1, NULL, buy, &i_1);
	if (result != 0)
                        {
                                perror("Creating the first buyer thread");
                                return EXIT_FAILURE;
                        }
    result = pthread_create(&thr_buy_2, NULL, buy, &i_2);
	if (result != 0)
                        {
                                perror("Creating the second buyer thread");
                                return EXIT_FAILURE;
                        }    
    result = pthread_create(&thr_buy_1, NULL, buy, &i_3);
	if (result != 0)
                        {
                                perror("Creating the third buyer thread");
                                return EXIT_FAILURE;
                        }  
    result = pthread_create(&thr_load, NULL, load, NULL);
	if (result != 0)
                        {
                                perror("Creating the loader thread");
                                return EXIT_FAILURE;
                        }         
    result = pthread_join(thr_buy_1, NULL);
    if (result != 0)
                        {
                                perror("Waiting for the first buyer thread");
                                return EXIT_FAILURE;
                        }
    result = pthread_join(thr_buy_2, NULL);
    if (result != 0)
                        {
                                perror("Waiting for the second buyer thread");
                                return EXIT_FAILURE;
                        }
    result = pthread_join(thr_buy_3, NULL);
    if (result != 0)
                        {
                                perror("Waiting for the third buyer thread");
                                return EXIT_FAILURE;
                        }
    result = pthread_join(thr_load, NULL);   
    if (result != 0)
                        {
                                perror("Waiting for the loader thread");
                                return EXIT_FAILURE;
                        }                            
	return 0;
}



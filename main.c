#include <stdlib.h>
#include <stdio.h>
#include "functions.h"



int SIZE = 5;


struct contact {
	char name[40];
	int tel_number;
};



struct contact * reference;


int main()
{
	reference = (struct contact *)malloc(SIZE*sizeof(struct contact));

	char choice;

	init_list();

	for (;;){
		choice = menu();

		switch (choice){
		case 'e': enter();
			break;
		case 's': show();
			break;
		case 'f': find();
			break;
		case 'd': del();
			break;
		case 'u': update();
			break;
		case 'q': free(reference);
			return 0;
		}
	}
}



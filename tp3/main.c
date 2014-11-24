#include <stdio.h>
#include "mon_malloc.h"

int main(void) 
{
	char *ptr1, *ptr2, *ptr3, *ptr4;
	ptr1 = malloc(12);
	ptr2 = malloc(12);
	ptr3 = malloc(12);
	ptr4 = malloc(12);
	free(ptr3);
	free(ptr4);
	free(ptr2);
	free(ptr1);
	
	return 0;
}

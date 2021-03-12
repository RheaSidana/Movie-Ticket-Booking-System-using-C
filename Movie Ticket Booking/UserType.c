#include "myHeader.h"
#include <stdio.h>

int userType() {
	int ch;
	printf("Enter your choice : \n");
	printf("1. ADMIN \n");
	printf("2. USER \n");
	printf("3. Exit \n");
	scanf_s("%d", &ch);
	printf("\n");
	return ch;
}
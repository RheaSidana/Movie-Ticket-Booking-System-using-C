#include "myHeader.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/*
Admin Login Credentials:
    UserName :  admin
    Password :  admin123
*/

void login() {
    char pass[] = "admin123";
    char user[] = "admin";
    char u[7], p[9],ch;
    int i;
    system("cls");
    heading(1);
    printf("\nEnter the Username : ");
    int x=getchar();
    gets(u);
    printf("\nEnter the Password : ");
    for (i = 0; i < 9; i++) {
        ch = _getch();
        p[i] = ch;
        if (p[i] != '\r') {
            printf("*");
        }
    }
    p[--i] = '\0';
    system("cls");
    //printf("User:%s Password:%s\n",u,p);
    if ((strcmp(u, user)) == 0 && (strcmp(p, pass)) == 0){
        printf("Successful Login \n");
    }
    else {
        printf("Invalid Password or Username \n");
        exit(1);
    }
    printf("Enter any key to continue.....");
    x=getchar();
    system("cls");
}
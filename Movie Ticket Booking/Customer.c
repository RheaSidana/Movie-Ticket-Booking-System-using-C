#include "myHeader.h"
#include <stdio.h>
#include <stdlib.h>

//login or register before booking movie ticket
struct user loginOrRegisterUser() {
    system("cls");
    struct user u;
    u.user_id = 0;
    int ch=0,x;
    while (1) {
        printf("\n Enter your choice : \n");
        printf(" 1. Login \n 2. Register \n ");
        scanf_s("%d", &ch);
        switch (ch) {
        case 1:
            x = getchar();
            u = loginUser();
            if (u.user_id == 0) {
                ch = 2;
                printf("\n Please Register First or Login with correct Credentials\n");
                continue;
            }
            break;
        case 2:
            x = getchar();
            u = addUser();
            break;
        default:invalidOption();
            break;
        }
        if (ch == 1 || ch == 2)break;
    }
    return u;
}

void customer() {
    int ch;
    char ans;
    struct user u;
    u.user_id = 0;
    do {
        //clrscr();
        system("cls");
        heading(2);
        printf("\n\nEnter your Choice : \n ");
        printf("1. Find Movie \n ");
        printf("2. Book Movie Tickets \n ");
        printf("3. Update Movie Booking\n ");
        printf("4. Delete Movie Booking\n ");
        printf("5. View Movie Booking\n ");
        printf("6. View All Available Movie \n ");
        printf("7. View All Bookings \n ");
        printf("8. Exit \n ");
        scanf_s("%d", &ch);
        printf("\n");
        system("cls");
        switch (ch) {
        case 1:
            heading(1);
            viewMovie();
            break;
        case 2:
            if (u.user_id == 0)
                u = loginOrRegisterUser();
            else
                addBooking();
            break;
        case 3:
            if (u.user_id == 0)
                u = loginOrRegisterUser();
            else
                updateBooking();
            break;
        case 4:
            if (u.user_id == 0)
                u = loginOrRegisterUser();
            else
                deleteBooking();
            break;
        case 5:
            if (u.user_id == 0)
                u = loginOrRegisterUser();
            else
                viewBooking();
            break;
        case 6:
            heading(2);
            viewAllAvailableMovie();
            break;
        case 7:
            if (u.user_id == 0)
                u = loginOrRegisterUser();
            else
                viewAllBooking();
            break;
        case 8:endingProgram();
            exit(0);
            break;
        default: invalidOption();
            int m = _getch();
            break;
        }
        int x = getchar();
        printf("Do you want to continue: (y/n) ?");
        scanf_s("%c", &ans,1);
        if (ans == 'n' || ans == 'N') break;
    } while (1);
}



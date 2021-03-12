#include "myHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void admin() {
    int ch;
    char ans;
    do {
        login();
        printf("\n\n Enter your choice : \n ");
        printf("1. Movie Details \n ");
        printf("2. Hall Details \n ");
        printf("3. User Details \n ");
        printf("4. Exit \n ");
        scanf_s("%d", &ch);
        printf("\n");
        system("cls");
        switch (ch) {
        case 1:MovieOperations();
            break;
        case 2:HallOperations();
            break;
        case 3:UserFunctions();
            break;
        case 4:endingProgram();
            exit(0);
            break;
        default: invalidOption();
            int m=_getch();
            break;
        }
        int x = getchar();
        printf("Do you want to continue: (y/n) ?");
        scanf_s("%c", &ans,1);
        if (ans == 'n' || ans == 'N') break;
    } while (1);
}

void MovieOperations() {
    int ch;
    char ans;
    do {
        system("cls");
        heading(1);
        printf("\n\n Enter your choice : \n ");
        printf("1. Add Movie \n ");
        printf("2. View Movie \n ");
        printf("3. Update Movie \n ");
        printf("4. Delete Movie \n ");
        printf("5. View All Movie \n ");
        printf("6. View Movie Status \n ");
        printf("7. View All Available Movies  \n ");
        printf("8. View All Movies History  \n ");
        printf("9. Exit \n ");
        scanf_s("%d", &ch);
        printf("\n");
        system("cls");
        switch (ch) {
        case 1: addMovie();
            break;
        case 2: 
            heading(1);
            viewMovie();
            break;
        case 3: updateMovie();
            break;
        case 4: deleteMovie();
            break;
        case 5:viewAllMovie();
            break;
        case 6: viewMovieStatus();
            break;
        case 7:viewAllAvailableMovie();
            break;
        case 8:viewAllMovieHistory();
            break;
        case 9: endingProgram();
            exit(0);
            break;
        default: invalidOption();
            int m = _getch();
            break;
        }
        int x = getchar();
        printf("Do you want to continue: (y/n) ?");
        scanf_s("%c", &ans, 1);
        if (ans == 'n' || ans == 'N') break;
    } while (1);
}

void HallOperations() {
    int ch;
    char ans;
    do {
        system("cls");
        heading(1);
        printf("\n\n Enter your choice : \n ");
        printf("1. Add Hall \n ");
        printf("2. View Hall \n ");
        printf("3. Update Hall \n ");
        printf("4. Delete Hall \n ");
        printf("5. View All Hall \n ");
        printf("6. View All Available Halls  \n ");
        printf("7. Exit \n ");
        scanf_s("%d", &ch);
        printf("\n");
        system("cls");
        switch (ch) {
        case 1:addHall();
            break;
        case 2:heading(1);
            viewHall();
            break;
        case 3:updateHall();
            break;
        case 4:deleteHall();
            break;
        case 5:viewAllHall();
            break;
        case 6:viewAllAvailableHall();
            break;
        case 7: endingProgram();
            exit(0);
            break;
        default: invalidOption();
            int m = _getch();
            break;
        }
        int x = getchar();
        printf("Do you want to continue: (y/n) ?");
        scanf_s("%c", &ans, 1);
        if (ans == 'n' || ans == 'N') break;
    } while (1);
}

void UpdateHallOperations() {
    int ch;
    char ans;
    do {
        system("cls");
        heading(1);
        printf("\n\n Enter your choice : \n ");
        printf("1. Allot a movie  \n ");
        printf("2. Remove a movie  \n ");
        printf("3. Exit \n ");
        scanf_s("%d", &ch);
        printf("\n");
        system("cls");
        switch (ch) {
        case 1:
            break;
        case 2:
            break;
        case 3: endingProgram();
            exit(0);
            break;
        default: invalidOption();
            int m = _getch();
            break;
        }
        int x = getchar();
        printf("Do you want to continue: (y/n) ?");
        scanf_s("%c", &ans, 1);
        if (ans == 'n' || ans == 'N') break;
    } while (1);
}

void UserFunctions() {
    int ch;
    char ans;
    do {
        system("cls");
        heading(1);
        printf("\n\n Enter your choice : \n ");
        printf("1. View Movie User  \n ");
        printf("2. Find User  \n ");
        printf("3. View User Bookings  \n ");
        printf("4. Exit \n ");
        scanf_s("%d", &ch);
        printf("\n");
        system("cls");
        switch (ch) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4: endingProgram();
            exit(0);
            break;
        default: invalidOption();
            int m = _getch();
            break;
        }
        int x = getchar();
        printf("Do you want to continue: (y/n) ?");
        scanf_s("%c", &ans, 1);
        if (ans == 'n' || ans == 'N') break;
    } while (1);
}

//void BookingOperations(){}

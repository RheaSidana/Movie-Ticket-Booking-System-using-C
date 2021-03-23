#include "myHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
file : moviedata.txt
history file: logMovieData.txt
*/

struct movie getMovie() {
    struct movie m;
    printf("\n Enter Movie Id : ");
    scanf_s("%d", &m.movie_id);
    int x = getchar();
    printf("\n Enter Movie Name : ");
    gets(m.movieName);
    printf("\n Enter Movie Language : ");
    gets(m.language);
    printf("\n Enter Movie Type : ");
    gets(m.mtype);
    printf("\n Enter Movie Release date (dd/mm/yyyy) : ");
    scanf_s("%d%d%d", &m.release.d, &m.release.m, &m.release.y);
    x = getchar();
    printf("\n Enter Movie Price  : ");
    scanf_s("%d", &m.movie_price);
    return m;
}

struct movie readMovieFromFile(FILE* fpm) {
    struct movie m;
    fscanf(fpm, "%d %d", &m.movie_id, &m.movie_price);
    fscanf(fpm, " %d %d %d ", &m.release.d, &m.release.m, &m.release.y); fscanf(fpm, "\n");
    fgets(m.movieName, 150, fpm); fscanf(fpm, "\n");
    fgets(m.language, 80, fpm); fscanf(fpm, "\n");
    fgets(m.mtype, 80, fpm); fscanf(fpm, "\n");
    int len = strlen(m.movieName);
    if(m.movieName[len - 1]=='\n')
    m.movieName[len - 1] = '\0';
    len = strlen(m.language);
    if (m.language[len - 1] == '\n')
    m.language[len - 1] = '\0';
    len = strlen(m.mtype);
    if (m.mtype[len - 1] == '\n')
    m.mtype[len - 1] = '\0';
    return m;
}

void displayMovie(struct movie m) {
    printf("\n \n Displaying Movie : \n ");
    printf(" Movie Code         : %d \n ", m.movie_id);
    printf(" Movie Name         : %s \n ", m.movieName);
    printf(" Movie Price        : %d \n ", m.movie_price);
    printf(" Movie Language     : %s \n ", m.language);
    printf(" Movie Type         : %s \n ", m.mtype);
    printf(" Movie Release Date : %d-%d-%d \n ", m.release.d, m.release.m, m.release.y);
}

void writeToFile(FILE* fpm, struct movie m) {
    fprintf(fpm, "%d %d", m.movie_id, m.movie_price);
    fprintf(fpm, " %d %d %d ", m.release.d, m.release.m, m.release.y); fprintf(fpm, "\n");
    fputs(m.movieName, fpm); fprintf(fpm, "\n");
    fputs(m.language, fpm); fprintf(fpm, "\n");
    fputs(m.mtype, fpm); fprintf(fpm, "\n");
} 

struct movie findMovieById(int id) {
    struct movie m;
    m.movie_price=m.release.d=m.release.m=m.release.y=m.movie_id = 0;
    strcpy(m.language, " "); strcpy(m.movieName, " "); strcpy(m.mtype, " ");
    FILE* fpm;
    fpm = fopen("logMovieData.txt", "r");
    fseek(fpm, 0, SEEK_SET);
    while (!feof(fpm)) {
        m = readMovieFromFile(fpm);
        if (id == m.movie_id) {
            fclose(fpm);
            return m;
        }
    }
    return m;
}


void addMovie() {
    system("cls");
    heading(1);
    struct movie m = getMovie();

    displayMovie(m);

    /* :: writing to file :: */
    FILE* fpm;
    fpm = fopen("moviedata.txt", "a");
    if (fpm == NULL) fileNotFound();
    else {
        writeToFile(fpm, m);
        printf("\n\nContent added to the file.\n");
    }
    fclose(fpm);

    /* writing to log file: history file */
    fpm = fopen("logMovieData.txt", "a");
    if (fpm == NULL) fileNotFound();
    else {
        writeToFile(fpm, m);
        //printf("\n\nContent added to the file.\n");
    }
    fclose(fpm);
}

void viewAllMovie() {
    heading(1);
    printf("\n Printing the Movie Details ");
    FILE* fpm;
    fpm = fopen("moviedata.txt", "r");
    if (fpm == NULL) fileNotFound();
    else {
        struct movie m;
        while (!feof(fpm)) {
            m = readMovieFromFile(fpm);
            displayMovie(m);
        }
    }
    fclose(fpm);
}

void viewMovie() {
    FILE* fpm;
    fpm = fopen("moviedata.txt", "r");
    if (fpm == NULL) fileNotFound();
    else {
        struct movie m;
        char name[150] = {'\0'};
        printf(" Enter the Movie Name you want to view : ");
        gets(name);

        while (!(feof(fpm))) {
            m = readMovieFromFile(fpm);
            if ((strcmp(name, m.movieName)) == 0)
            {
                displayMovie(m);
                break;
            }
        }
    }
    fclose(fpm);
}

void deleteMovie() {
    heading(1);
    FILE* fpm, * tm;
    int flag = 0;
    fpm = fopen("moviedata.txt", "r");
    tm = fopen("temporary.txt", "a");
    if (fpm == NULL || tm == NULL) fileNotFound();
    else {
        struct movie m;
        char name[150] = { '\0' };
        printf("Enter the Movie Name you want to delete : ");
        gets(name);
        while (!(feof(fpm))) {
            m = readMovieFromFile(fpm);

            if ((strcmp(name, m.movieName)) == 0)
            {
                displayMovie(m);
                printf("\nMovie Deleted ");
                flag = 1;
            }
            else {
                writeToFile(tm, m);
            }
        }
    }
    fclose(fpm);
    fclose(tm);
    if (flag == 0) {
        printf("Movie not found ");
    }
    int r;
    r = remove("moviedata.txt");
    r = rename("temporary.txt", "moviedata.txt");
}

void updateMovie() {
    heading(1);
    char name[150] = { '\0' };
    FILE* fpm, * tm,*history,*th;
    int flag = 0;
    fpm = fopen("moviedata.txt", "r");
    history = fopen("logMovieData.txt", "r");
    tm = fopen("temporary.txt", "a");
    th = fopen("temporary2.txt", "a");
    if (fpm == NULL || tm == NULL) fileNotFound();
    else {
        struct movie m;
        printf("Enter the Movie Name you want to update : ");
        gets(name);
        while (!(feof(fpm))) {
            m = readMovieFromFile(fpm);

            if ((strcmp(name, m.movieName)) == 0)
            {
                displayMovie(m);
                flag = 1;
                int ch,x;
                char temp[150] = { '\0' };
                printf("\n\n Enter your choice : (MOVIE)\n ");
                printf("1.Name \n 2.Language \n 3.Type \n 4.Code \n 5.Price \n 6.Release date \n ");
                scanf_s("%d", &ch);
                switch (ch) {
                case 1: printf(" Enter Name :  ");
                    x = getchar();
                    gets(temp);
                    strcpy(m.movieName, temp);
                    break;
                case 2:printf(" Enter Language :  ");
                    x = getchar();
                    gets(temp);
                    strcpy(m.language, temp);
                    break;
                case 3: printf(" Enter Type :  ");
                    x = getchar();
                    gets(temp);
                    strcpy(m.mtype, temp);
                    break;
                case 4:printf(" Enter code :  ");
                    scanf_s("%d", &m.movie_id);
                    break;
                case 5: printf(" Enter Price  :  ");
                    scanf_s("%d", &m.movie_price);;
                    break;
                case 6: printf(" Enter Release Date (dd/mm/yy)  :  ");
                    scanf_s("%d%d%d", &m.release.d, &m.release.m, &m.release.y);
                    break;
                default: invalidOption();
                    break;
                }
                printf("\n");
                displayMovie(m);

                //updating log file 
                    while (!(feof(history))) {
                        struct movie to = readMovieFromFile(history);
                        if ((strcmp(name, to.movieName)) == 0)
                        {
                            printf("\nFound in history");
                            displayMovie(to);
                            to.movie_id=m.movie_id;
                            to.release = m.release;
                            to.movie_price = m.movie_price;
                            strcpy(to.language, m.language);
                            strcpy(to.movieName, m.movieName);
                            strcpy(to.mtype, m.mtype);
                            displayMovie(to);
                        }
                        writeToFile(th, to);
                    }
            }
            writeToFile(tm, m);
        }
    }
    fclose(fpm);
    fclose(tm);
    fclose(history);
    fclose(th);
    if (flag == 0) {
        printf(" Movie not found ");
    }
    int r;
    r = remove("moviedata.txt");
    r = rename("temporary.txt", "moviedata.txt");
    r = remove("logMovieData.txt");
    r = rename("temporary2.txt", "logMovieData.txt");
}

void viewAllMovieHistory() {
    heading(1);
    printf("\n Printing the Movie History Details ");
    FILE* fpm;
    fpm = fopen("logMovieData.txt", "r");
    if (fpm == NULL) fileNotFound();
    else {
        struct movie m;
        while (!feof(fpm)) {
            m = readMovieFromFile(fpm);
            displayMovie(m);
        }
    }
    fclose(fpm);
}

void viewAllAvailableMovie() {
    //if seat in the hall then display the movie 
    printf("\nPrinting the Available Movie.");
    FILE* fpm;
    fpm = fopen("moviedata.txt", "r");
    if (fpm == NULL) fileNotFound();
    else {
        while (!feof(fpm)) {
            struct movie m = readMovieFromFile(fpm);
            int count = totalAvailableSeatsOfMovie(m.movie_id);
            if ((count != 0) && (count != -1)) {
                printf("\n Movie ID    : %d ",m.movie_id);
                printf("\n Movie Name  : %s \n Available   : %d \n", m.movieName, count);
            }
        }
    }
    fclose(fpm);
}

void viewMovieStatus() {
    printf("\nPrinting the Movie Status.");
    FILE* fpm;
    fpm = fopen("logMovieData.txt", "r");
    if (fpm == NULL) fileNotFound();
    else {
        while (!feof(fpm)) {
            struct movie m = readMovieFromFile(fpm);
            int count = totalAvailableSeatsOfMovie(m.movie_id);
            if (count > 0) {
                printf("\n Movie Name  : %s \n Available   : %d \n", m.movieName, count);
            }
            else if (count == 0) {
                printf("\n Movie Name  : %s \n SOLD OUT!! \n", m.movieName);
            }
            else if (count == -1) {
                printf("\n Movie Name  : %s \n Not Available  \n", m.movieName);
            }
        }
    }
    fclose(fpm);
}

struct movie getMovieIdForBooking() {
    viewAllAvailableMovie();
    struct movie m;
    int m_id = 0, flag = 0;
    printf("\n Enter the Movie ID : ");
    scanf_s("%d", &m_id);
    FILE* fpm;
    fpm = fopen("moviedata.txt", "r");
    if (fpm == NULL) fileNotFound();
    else {
        while (!feof(fpm)) {
            m = readMovieFromFile(fpm);
            int count = totalAvailableSeatsOfMovie(m.movie_id);
            if ((count != 0) && (count != -1)) {
                if (m_id == m.movie_id) {
                    flag = 1;
                    break;
                }
            }
        }
    }
    fclose(fpm);
    if (flag == 0) {
        printf("\n Invalid Movie id ");
        m.movie_id=m_id = 0;
    }
    return m;
}


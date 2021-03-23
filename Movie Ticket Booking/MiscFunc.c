#include "myHeader.h"
#include <stdio.h>
#include <time.h>

void invalidOption() {
    printf("\n  Invalid option \n");
}

void endingProgram() {
    printf(" \n  Exiting from the system \n");
}

void fileNotFound() {
    printf("\n\nFile Not Found !!!\n");
}

void calDateTime(struct timings* ti, struct date* d) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    ti->h = tm.tm_hour;
    ti->m = tm.tm_min;
    d->d = tm.tm_mday;
    d->m = tm.tm_mon + 1;
    d->y = tm.tm_year + 1900;
    //printf("now: %d-%d-%d %02d:%02d \n",d->d,d->m,d->y,ti->h,ti->m );
}
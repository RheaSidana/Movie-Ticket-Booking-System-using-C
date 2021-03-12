#include "myHeader.h"
#include <stdio.h>

void heading(int i) {
    if (i == 1)
        printf("\n***** MOVIE TICKET BOOKING SYSTEM : Admin Section *****\n");
    else
        if (i == 2)
            printf("\n***** MOVIE TICKET BOOKING SYSTEM : User Section *****\n");
}


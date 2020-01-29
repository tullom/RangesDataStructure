//Matteo Tullo
//tullom@mcmaster.ca
/* Brute force method
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"

Range *constructRange(int x, int y) {

    Range *temp;
    if(x>=y) {
        temp = malloc(sizeof(Range));
        temp->min = 0;
        temp->max = 0;
        return temp;
    }
    temp = malloc(sizeof(Range));

    temp->min = x;
    temp->max = y;

    return temp;
}

Range **constructListOfRanges(int numOfRanges) {

    Range **temp;

    return temp;
}

void printRange(Range *r) {

    printf("(%d, %d)\n", r->min, r->max);

}

void destroyRange(Range *r) {

    free(r);
}

void destroyListOfRanges(Range **r, int num) {

    for(int i=0;i<num;i++) {
        free(r[i]);
    }
    free(r);
}

Range **addRanges(Range *range1, Range *range2) {

    Range **list;

    return list;
}
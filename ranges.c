//Matteo Tullo
//tullom@mcmaster.ca
/* Brute force method
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"

int foo(int x) {
    printf("%d + 5",x);
    return (x+5);
}

Range *constructRange(int x, int y) {

    Range *temp = malloc(sizeof(Range));
    temp->min = x;
    temp->max = y;
    return temp;
}

void printRange(Range *r) {

    printf("(%d, %d)\n", r->min, r->max);

}


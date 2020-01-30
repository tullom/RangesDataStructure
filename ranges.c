//Matteo Tullo
//tullom@mcmaster.ca
/* Brute force method
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"

/* Function: constructRange
 * Arguments: int x, int y
 * Return: Range *temp
 * 
 * This function constructs a range with x being the minimum
 * and y being the maximum.  If the range is invalid, the
 * program terminates.  Returns a pointer to the new range.
 */
Range *constructRange(int x, int y) {

    Range *temp;
    if(x>=y) {
        printf("Invalid range\nExiting program");
        exit(1);
    }
    temp = malloc(sizeof(Range));

    temp->min = x;
    temp->max = y;

    return temp;
}

/* Function: printRange
 * Arguments: Range *r
 * Return: none
 * 
 * This function simply prints a range using the correct
 * format.
 */
void printRange(Range *r) {

    printf("(%d, %d)", r->min, r->max);
}

/* Function: destroyRange
 * Arguments: Range *r
 * Return: none
 * 
 * This function frees up the memory taken up by the 
 * inputted range.  This is to prevent memory leaks.
 */
void destroyRange(Range *r) {

    free(r);
}

/* Function: compareRanges
 * Arguments: Range *range1, Range *range2
 * Return: int
 * 
 * This function compares two ranges.  If they are the
 * same, the function returns 0.  If range1 contains
 * range2 entirely, the function returns 1.  If range1
 * contains range2 not entirely, the function returns 2.
 */
// int compareRanges(Range *range1, Range *range2) {

//     int min1,min2,max1,max2;
//     min1 = range1->min;
//     min2 = range2->min;
//     max1 = range1->max;
//     max2 = range1->max;

//     if()

// }
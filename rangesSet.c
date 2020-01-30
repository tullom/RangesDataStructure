//Matteo Tullo
//tullom@mcmaster.ca
/* Brute force method
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"
#include "rangesSet.h"

RangesSet *constructSet(Range *r) {

    // Set *newSet = malloc((*listSize) * sizeof(Range *));
    // for(int i=0;i<(*listSize);i++) {
    //     newSet->rangesList[i] = listOfRanges[i];
    // }

    // return newSet;

    RangesSet *newSet = malloc(sizeof(RangesSet));
    newSet->numOfDiscontin = 0;

    // newSet[newSet->numOfDiscontin] = malloc()
}

RangesSet *SetFromIntList(int *list, int size) {
    
    RangesSet *newSet = malloc(sizeof(RangesSet));
    int counter, counterLag, startOfRange=list[0],endOfRange=list[size-1];
    newSet->numOfDiscontin = 0;

    for(int i=1;i<size;i++) {
        counterLag = list[i-1];
        counter = list[i];

        if((counter - counterLag) > 1) {
            (newSet->numOfDiscontin)++;
        }
    }

    newSet->rangesList = malloc((newSet->numOfDiscontin+1)*sizeof(Range *));
    int rangecount=0;
    for(int i=1;i<size;i++) {
        counterLag = list[i-1];
        counter = list[i];

        if((counter - counterLag) > 1) {
            endOfRange = list[i-1];
            // printf("%d start\n",startOfRange);
            newSet->rangesList[rangecount] = constructRange(startOfRange,endOfRange+1);
            rangecount++;
            startOfRange = list[i];
        }
    }
    newSet->rangesList[rangecount] = constructRange(startOfRange,list[size-1]+1);


    return newSet;
}

void printRangesSet(RangesSet *set) {

    for(int i=0;i<set->numOfDiscontin+1;i++) {
        printRange(set->rangesList[i]);
    }
}

RangesSet *addRangeSet(RangesSet *set1, RangesSet *set2) {

}
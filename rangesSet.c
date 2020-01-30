//Matteo Tullo
//tullom@mcmaster.ca

#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"
#include "rangesSet.h"

RangesSet *constructSet(Range **r, int size) {

    RangesSet *newSet = malloc(sizeof(RangesSet));
    newSet->rangesList = malloc(size*sizeof(Range *));
    newSet->numOfDiscontin = size-1;

    for(int i=0;i<size;i++) {
        newSet->rangesList[i] = r[i];
    }

    return newSet;
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
            newSet->rangesList[rangecount] = constructRange(startOfRange,endOfRange+1);
            rangecount++;
            startOfRange = list[i];
        }
    }
    newSet->rangesList[rangecount] = constructRange(startOfRange,list[size-1]+1);

    return newSet;
}

void printRangesSet(RangesSet *set) {

    printf("[");
    for(int i=0;i<set->numOfDiscontin;i++) {
        printRange(set->rangesList[i]);
        printf(", ");
    }
    printRange(set->rangesList[set->numOfDiscontin]);
    printf("]\n");
}

// RangesSet *addRangeSet(RangesSet *set1, RangesSet *set2) {

// }
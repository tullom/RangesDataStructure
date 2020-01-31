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

RangesSet *addRangeSet(RangesSet *set, Range *r) {
    int counter = 0;

    printf("%d",set->rangesList[set->numOfDiscontin]->min);

    if((r->min) >= (set->rangesList[set->numOfDiscontin]->min)) {
        if((r->min) > (set->rangesList[set->numOfDiscontin]->max)) {
            //r will be the last element, realloc array
        }
        else {
            //r will overwrite the last element
        }

    }

    while((r->min) > (set->rangesList[counter]->min)) {
        counter++;
    }
    printf("%d",counter); //index of element
    if (counter==0) {
        //r should be the first element
        //realloc array
    }
    counter--;
    
    if((set->rangesList[counter]->max)<=(r->min)) { //r starts inside a discontinuity
        if((set->rangesList[counter+1]->min)<(r->max)) {
            //function 2
            //part of r is inside the right
            //need to overwrite the right range
        }
        else if((set->rangesList[counter+1]->min)>=(r->max)) {
            //r is going to be a whole new element
            //need to realloc array, insert a new range
        }
    } else { //r starts inside of the right range
        if((set->rangesList[counter+1]->min)<(r->max)) {
            //r is also in the left range
            //join the left and the right ranges, realloc
        }
        else if((set->rangesList[counter+1]->min)>=(r->max)) {
            //r is in the left range
            //need to overwrite the left range
        }
    }

    // while()

    return set;
}

int binSearchRange(RangesSet *set, Range *r) {

    
    int mid = (set->numOfDiscontin+1)/2;
    int first = set->rangesList[0]->min;
    int last = set->rangesList[set->numOfDiscontin]->min;
    printf("%d",last);

}


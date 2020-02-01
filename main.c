//Matteo Tullo
//tullom@mcmaster.ca

#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"
#include "rangesSet.h"

#define INTLISTLEN 10
#define RANGELISTLEN 3

int main(void) {
    
    Range *testPtr1,*testPtr2,*testPtr3;
    RangesSet *newSet, *newSet2;
    int intList[INTLISTLEN] = {3,4,5,7,12,13,14,18,19,20};
    
    testPtr1 = constructRange(12,17);
    testPtr2 = constructRange(3,9);
    testPtr3 = constructRange(3,8);
    printf("%d", isSame(testPtr1,testPtr2));
    Range *rngList[RANGELISTLEN] = {testPtr1,testPtr2};
    
    // printRange(testPtr1);
    // printRange(testPtr2);
    
    // newSet = constructSet(rngList,RANGELISTLEN);

    newSet2 = SetFromIntList(intList,INTLISTLEN);

    // printRangesSet(newSet);
    printRangesSet(newSet2);

    newSet2 = addRangeSet(newSet2,testPtr1);
    printf("%d", newSet2->numOfDiscontin);
    printRangesSet(newSet2);
    destroyRange(testPtr1);
    destroyRange(testPtr2);
    destroyRange(testPtr3);

    return(0);
}
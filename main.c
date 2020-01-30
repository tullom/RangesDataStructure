//Matteo Tullo
//tullom@mcmaster.ca

#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"
#include "rangesSet.h"

#define N 10

int main(void) {
    
    Range *testPtr1,*testPtr2,*testPtr3,*addedRange;
    Range **rngList;
    RangesSet *newSet;
    int intList[N] = {-9,7,8,11,12,13,14,18,23,24};
    
    testPtr1 = constructRange(1,4);
    testPtr2 = constructRange(7,9);
    testPtr3 = constructRange(3,8);
  
    
    // printRange(testPtr1);
    // printRange(testPtr2);

    newSet = SetFromIntList(intList,N);
    // printf("%d\n",newSet->numOfDiscontin);
    printRangesSet(newSet);

    destroyRange(testPtr1);
    destroyRange(testPtr2);
    destroyRange(testPtr3);

    return(0);
}
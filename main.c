//Matteo Tullo
//tullom@mcmaster.ca

#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"
#include "rangesSet.h"

#define INTLISTLEN 10
#define RANGELISTLEN 2

int main(void) {
    
    Range *testPtr1,*testPtr2,*testPtr3;
    RangesSet *newSet, *newSet2;
    int intList[INTLISTLEN] = {-9,7,8,11,12,13,14,18,23,24};
    
    testPtr1 = constructRange(1,4);
    testPtr2 = constructRange(7,9);
    testPtr3 = constructRange(3,8);
  
    Range *rngList[RANGELISTLEN] = {testPtr1,testPtr2};
    
    // printRange(testPtr1);
    // printRange(testPtr2);
    
    newSet = constructSet(rngList,RANGELISTLEN);
    newSet2 = SetFromIntList(intList,INTLISTLEN);

    printRangesSet(newSet);
    printRangesSet(newSet2);

    destroyRange(testPtr1);
    destroyRange(testPtr2);
    destroyRange(testPtr3);

    return(0);
}
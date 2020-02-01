//Matteo Tullo
//tullom@mcmaster.ca

#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"
#include "rangesSet.h"

#define INTLISTLEN 10
#define RANGELISTLEN 1

int main(void) {
    
    Range *testPtr1,*testPtr2,*testPtr3;
    RangesSet *newSet, *newSet2, *newSet3;
    int intList[INTLISTLEN] = {3,4,5,7,12,13,14,18,19,20};
    
    testPtr1 = constructRange(1,6);
    testPtr2 = constructRange(-3,-1);
    testPtr3 = constructRange(4,13);
    // printf("%d", isSame(testPtr1,testPtr2));
    Range *rngList[RANGELISTLEN] = {testPtr1};
    
    // printRange(testPtr1);
    // printRange(testPtr2);
    
    newSet = constructSet(rngList,RANGELISTLEN);
    // int siz;
    // int *hi = toIntArr(newSet,&siz);

    // for(int i=0;i<siz;i++) {
    //     printf("hello %d",hi[i]);
    // }

    newSet2 = SetFromIntList(intList,INTLISTLEN);

    // printRangesSet(newSet);
    // printRangesSet(newSet2);

    // newSet = addRangeSet(newSet,testPtr2);
    printRangesSet(newSet);
    printf("hi");
    newSet3 = deleteRangeSet(newSet2,testPtr3);
    // printf("%d", newSet2->numOfDiscontin);
    printRangesSet(newSet3);
    destroyRange(testPtr1);
    destroyRange(testPtr2);
    destroyRange(testPtr3);

    return(0);
}
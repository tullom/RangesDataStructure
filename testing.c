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
    
    printf("\nWelcome. This is a test file for the rangesSet ranges data structures.\nCreated by Matteo Tullo\n");
    
    printf("\nTesting Constructors:\n*\n*\n");

    printf("Create range: (1,2): ");
    testPtr1 = constructRange(1,2);
    printRange(testPtr1);

    printf("\nCreate range: (2,4): ");
    testPtr2 = constructRange(2,4);
    printRange(testPtr2);
    
    printf("\nCreate range: (4,13): ");
    testPtr3 = constructRange(4,13);
    printRange(testPtr3);

    printf("\nCreate rangesSet: [(1,2),(2,4),(4,13)]: ");
    Range *rngList[RANGELISTLEN] = {testPtr1,testPtr2,testPtr3};
    newSet = constructSet(rngList,RANGELISTLEN);
    printRangesSet(newSet);

    printf("Create rangesSet from int array: {3,4,5,7,12,13,14,18,19,20}: ");
    int intList[INTLISTLEN] = {3,4,5,7,12,13,14,18,19,20};
    newSet2 = SetFromIntList(intList,INTLISTLEN);
    printRangesSet(newSet2);

    printf("\nTesting Add function now!\n*\n*\n");

    printf("Adding [(1,2)] and (3,5): ");
    testPtr1 = constructRange(1,2);
    testPtr2 = constructRange(3,5);
    Range *rngList2[1] = {testPtr1};
    newSet = constructSet(rngList2,1);
    newSet = addRangeSet(newSet,testPtr2);
    printRangesSet(newSet);

    printf("Adding [(1,6)] and (3,5): ");
    testPtr1 = constructRange(1,6);
    testPtr2 = constructRange(3,5);
    Range *rngList3[1] = {testPtr1};
    newSet = constructSet(rngList3,1);
    newSet = addRangeSet(newSet,testPtr2);
    printRangesSet(newSet);

    printf("Adding [(1,4)] and (3,5): ");
    testPtr1 = constructRange(1,4);
    testPtr2 = constructRange(3,5);
    Range *rngList4[1] = {testPtr1};
    newSet = constructSet(rngList4,1);
    newSet = addRangeSet(newSet,testPtr2);
    printRangesSet(newSet);

    printf("Adding [(3,6),(7,8),(12,15),(18,21)] and (7,11): ");
    testPtr1 = constructRange(7,11);
    newSet2 = SetFromIntList(intList,INTLISTLEN);
    newSet = addRangeSet(newSet2,testPtr1);
    printRangesSet(newSet);

    printf("Adding [(3,6),(7,8),(12,15),(18,21)] and (1,40): ");
    testPtr1 = constructRange(1,40);
    newSet2 = SetFromIntList(intList,INTLISTLEN);
    newSet = addRangeSet(newSet2,testPtr1);
    printRangesSet(newSet);

    printf("\nTesting Remove function now!\n*\n*\n");

    printf("[(1,6)] and Delete (-3,-1): ");
    testPtr1 = constructRange(1,6);
    testPtr2 = constructRange(-3,-1);
    Range *rngList5[1] = {testPtr1};
    newSet = constructSet(rngList5,1);
    newSet = deleteRangeSet(newSet,testPtr2);
    printRangesSet(newSet);

    printf("[(1,6)] and Delete (-1,10): ");
    testPtr1 = constructRange(1,6);
    testPtr2 = constructRange(-1,10);
    Range *rngList6[1] = {testPtr1};
    newSet = constructSet(rngList6,1);
    newSet = deleteRangeSet(newSet,testPtr2);
    printRangesSet(newSet);

    printf("[(1,6)] and Delete (4,10): ");
    testPtr1 = constructRange(1,6);
    testPtr2 = constructRange(4,10);
    Range *rngList7[1] = {testPtr1};
    newSet = constructSet(rngList7,1);
    newSet = deleteRangeSet(newSet,testPtr2);
    printRangesSet(newSet);

    printf("[(3,6),(7,8),(12,15),(18,21)] and Delete (7,19): ");
    testPtr1 = constructRange(7,19);
    newSet2 = SetFromIntList(intList,INTLISTLEN);
    newSet = deleteRangeSet(newSet2,testPtr1);
    printRangesSet(newSet);

    printf("\nTesting Get function now!\n*\n*\n");

    printf("[(1,3),(5,7)] and Get (4,5): ");
    testPtr1 = constructRange(1,3);
    testPtr2 = constructRange(5,7);
    testPtr3 = constructRange(4,5);
    Range *rngList8[2] = {testPtr1,testPtr2};
    newSet = constructSet(rngList8,2);
    newSet = getRangeSet(newSet,testPtr3);
    printRangesSet(newSet);

    printf("[(1,3),(5,6)] and Get (4,6): ");
    testPtr1 = constructRange(1,3);
    testPtr2 = constructRange(5,6);
    testPtr3 = constructRange(4,6);
    Range *rngList9[2] = {testPtr1,testPtr2};
    newSet = constructSet(rngList9,2);
    newSet = getRangeSet(newSet,testPtr3);
    printRangesSet(newSet);

    printf("[(1,3),(5,6)] and Get (2,9): ");
    testPtr1 = constructRange(1,3);
    testPtr2 = constructRange(5,6);
    testPtr3 = constructRange(2,9);
    Range *rngList10[2] = {testPtr1,testPtr2};
    newSet = constructSet(rngList10,2);
    newSet = getRangeSet(newSet,testPtr3);
    printRangesSet(newSet);

    printf("[(3,6),(7,8),(12,15),(18,21)] and Get (7,19): ");
    testPtr1 = constructRange(7,19);
    newSet2 = SetFromIntList(intList,INTLISTLEN);
    newSet = getRangeSet(newSet2,testPtr1);
    printRangesSet(newSet);

    printf("\n****End of testing file****");
}

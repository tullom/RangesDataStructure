//Matteo Tullo
//tullom@mcmaster.ca

#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"

int main(void) {

    Range *testPtr1,*testPtr2,*addedRange;
    
    testPtr1 = constructRange(1,4);
    testPtr2 = constructRange(3,9);
    
    
    printRange(testPtr1);
    printRange(testPtr2);

    destroyRange(testPtr1);
    destroyRange(testPtr2);

    return(0);
}
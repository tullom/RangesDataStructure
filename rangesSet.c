//Matteo Tullo
//tullom@mcmaster.ca

#include <stdio.h>
#include <stdlib.h>

#include "ranges.h"
#include "rangesSet.h"


/* Function: constructSet
 * Arguments: Range **r, int size
 * Return: RangesSet *newSet
 * 
 * This function constructs a new Range set from an 
 * array of ranges.  List must be sorted.
 */
RangesSet *constructSet(Range **r, int size) {

    RangesSet *newSet = malloc(sizeof(RangesSet));
    newSet->rangesList = malloc(size*sizeof(Range *));
        newSet->numOfDiscontin = size-1;

    for(int i=0;i<size;i++) {
        newSet->rangesList[i] = r[i];
    }

    return newSet;
}

/* Function: SetFromIntList
 * Arguments: int *list, int size
 * Return: RangesSet *newSet
 * 
 * This function constructs a new Range set from a
 * list of integers.  List must be sorted.
 */
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

/* Function: printRangesSet
 * Arguments: RangesSet *set
 * Return: void
 * 
 * This function prints the range in a
 * formatted way.
 */
void printRangesSet(RangesSet *set) {

    printf("[");
    for(int i=0;i<set->numOfDiscontin;i++) {
        printRange(set->rangesList[i]);
        printf(", ");
    }
    if(set->numOfDiscontin==-1) {
        printf("]\n");
        return;
    }
    printRange(set->rangesList[set->numOfDiscontin]);
    printf("]\n");
}

RangesSet *addRangeSet(RangesSet *set, Range *r) {
    int counter = 0;
    RangesSet *tempSet;

    // printf("%d",set->rangesList[set->numOfDiscontin]->min);

    if((r->min) >= (set->rangesList[set->numOfDiscontin]->min)) {
        if((r->min) >= (set->rangesList[set->numOfDiscontin]->max)) {
            //r will be the last element, realloc array

            Range **arrOfRanges = malloc((set->numOfDiscontin+2)*sizeof(Range *));
            for(int i=0;i<set->numOfDiscontin+1;i++) {
                arrOfRanges[i] = set->rangesList[i];
            }
            arrOfRanges[set->numOfDiscontin+1] = constructRange(r->min,r->max);
            tempSet = constructSet(arrOfRanges,set->numOfDiscontin+2);
            return tempSet;
        }
        else {
            //r will overwrite the last element

            set->rangesList[set->numOfDiscontin] = constructRange(set->rangesList[set->numOfDiscontin]->min,r->max);
            return set;
        }

    }

    while((r->min) > (set->rangesList[counter]->min)) {
        counter++;
    }
    int maxCounter = counter;
    while((r->max) > set->rangesList[maxCounter]->max) {
        maxCounter++;
    }
    if(r->max<=set->rangesList[maxCounter]->max) {
        maxCounter--;
    }
    printf("%d %d\n",counter, maxCounter); //index of element
    int offset = maxCounter - counter;
    if (counter==0) {
        if (r->max > set->rangesList[0]->min) {
            //r should overwrite the first element
            Range **arrOfRanges = malloc((set->numOfDiscontin+1-offset)*sizeof(Range *));
            printf("%d",set->rangesList[maxCounter]->max);
            if(r->max > set->rangesList[maxCounter+1]->min) {
                arrOfRanges[0] = constructRange(r->min,set->rangesList[offset+1]->max);
                offset++;
            } else {
                arrOfRanges[0] = constructRange(r->min,r->max);
            }
            for(int i=1;i<set->numOfDiscontin+1-offset;i++) {
                arrOfRanges[i] = set->rangesList[offset+i];
            }

            tempSet = constructSet(arrOfRanges,set->numOfDiscontin+1-offset);
            free(arrOfRanges);
            return tempSet;
        } else {
            //r should be the first element
            //new element
            Range **arrOfRanges = malloc((set->numOfDiscontin+2)*sizeof(Range *));
            for(int i=1;i<set->numOfDiscontin+2;i++) {
                arrOfRanges[i] = set->rangesList[i-1];
            }
            arrOfRanges[0] = r;
            tempSet = constructSet(arrOfRanges,set->numOfDiscontin+2);
            free(arrOfRanges);
            return tempSet;

        }
    }
    counter--;

    printf("%d",counter);
    
    if((set->rangesList[counter]->max)<=(r->min)) { //r starts inside a discontinuity
        if((set->rangesList[counter+1]->min)<(r->max)) {
            //function 2
            //part of r is inside the right
            //need to overwrite the right range

            set->rangesList[counter+1] = constructRange(r->min,set->rangesList[counter+1]->max);
            return set;
        }
        else if((set->rangesList[counter+1]->min)>=(r->max)) {
            //r is going to be a whole new element
            //need to realloc array, insert a new range
            
            Range **arrOfRanges = malloc((set->numOfDiscontin+2)*sizeof(Range *));
            int flag=0;
            for(int i=0;i<set->numOfDiscontin+1;i++) {
                if(i==counter+1) {
                    arrOfRanges[i] = constructRange(r->min,r->max);
                    flag = 1;
                }
                arrOfRanges[i+flag] = set->rangesList[i];
            }
            tempSet = constructSet(arrOfRanges,set->numOfDiscontin+2);
            free(arrOfRanges);
            return tempSet;
        }
    } else { //r starts inside of the right range
        if((set->rangesList[counter+1]->min)<(r->max)) {
            //r is also in the left range
            //join the left and the right ranges, realloc

            Range **arrOfRanges = malloc((set->numOfDiscontin)*sizeof(Range *));
            int flag=0;
            for(int i=0;i<set->numOfDiscontin;i++) {
                if(i==counter) {
                    arrOfRanges[i] = constructRange(set->rangesList[counter]->min,set->rangesList[counter+1]->max);
                    // printRange(arrOfRanges[i]);
                    flag = 1;
                }
                arrOfRanges[i] = set->rangesList[i+flag];
            }
            tempSet = constructSet(arrOfRanges,set->numOfDiscontin);
            free(arrOfRanges);
            return tempSet;
        }
        else if((set->rangesList[counter+1]->min)>=(r->max)) {
            //r is in the left range
            //need to overwrite the left range
            // printf("%d",set->rangesList[counter]->min);
            set->rangesList[counter] = constructRange(set->rangesList[counter]->min,r->max);
            return set;
        }
    }

    // while()

    return set;
}

// int binSearchRange(RangesSet *set, Range *r) {

    
//     int mid = (set->numOfDiscontin+1)/2;
//     int first = set->rangesList[0]->min;
//     int last = set->rangesList[set->numOfDiscontin]->min;
//     printf("%d",last);

// }


/* Function: getRangeSet
 * Arguments: RangesSet *set, Range *r
 * Return: RangesSet *tempSet
 * 
 * This function checks returns the
 * intersection between all the elements
 * in the inputted set and the inputted
 * range.  It uses a linear search, therefore
 * the algorithmic complexity is O(n).
 */
RangesSet *getRangeSet(RangesSet *set, Range *r) {

    int counter=0;
    int maxCounter=0;
    for(int i=0;i<set->numOfDiscontin+1;i++) {
        if(compareRanges(set->rangesList[i],r)==1) {
            counter++;
        }
    }
    
    Range **arrOfRanges = malloc(counter*sizeof(Range *));
    maxCounter=0;
    for(int i=0;i<set->numOfDiscontin+1;i++) {
        if(compareRanges(set->rangesList[i],r)==1) {
            arrOfRanges[maxCounter] = set->rangesList[i];
            maxCounter++;
        }
    }
    // printf("%d %d",counter,maxCounter);
    RangesSet *tempSet = constructSet(arrOfRanges,counter);
    free(arrOfRanges);
    return tempSet;
}

RangesSet *addRangeSet2(RangesSet *set, Range *r) {

    int counter=0;
    while((r->min) > (set->rangesList[counter]->min)) {
    counter++;
    }

}
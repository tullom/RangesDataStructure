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
    // printf("hi");
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

/* Function: printRangesSet
 * Arguments: RangesSet *set, int *size
 * Return: int *finalIntArr
 * 
 * This function converts the range into 
 * an array of integers. Also updates the
 * size pointer accordingly.
 */
int *toIntArr(RangesSet *set, int *size) {
    int start,end,startCopy;
    int **tempIntArr,*finalIntArr;
    // printf("hipi");
    (*size) = 0;
    tempIntArr = malloc((set->numOfDiscontin+1)*sizeof(int *));
    for(int i=0;i<(set->numOfDiscontin+1);i++) {
        // printRangesSet(set);
        start = set->rangesList[i]->min;
        // printf("fon%d",set->rangesList[i]->min);
        end = set->rangesList[i]->max;
        startCopy = start;
        tempIntArr[i] = malloc((end-start)*sizeof(int));
        for(int j=0;j<(end-startCopy);j++) {
            tempIntArr[i][j] = start;
            // printf("%de",start);
            start++;
            (*size)++;
        }
    }
    // printf("%d",*size);
    finalIntArr = malloc((*size)*sizeof(int));
    int counter=0;
    for(int i=0;i<set->numOfDiscontin+1;i++) {
        start = set->rangesList[i]->min;
        end = set->rangesList[i]->max;
        startCopy = start;
        for(int j=0;j<(end-startCopy);j++) {
            finalIntArr[counter] = tempIntArr[i][j];
            // printf("%d",finalIntArr[counter]);
            counter++;
        }
    }
    // printf("hipi");
    return finalIntArr;
}

/* Function: addRangeSet
 * Arguments: RangesSet *set, Range *r
 * Return: RangesSet *tempSet
 * 
 * This function returns the
 * union between the inputted set and 
 * the inputted range.  It uses a linear search
 * twice, therefore, the average algorithmic
 * complexity is O(n).
 */
RangesSet *addRangeSet(RangesSet *set, Range *r) {
    int counter = 0;
    RangesSet *tempSet;

    //Checks to see if the inputted range covers the whole set
    if((r->min <= set->rangesList[0]->min) && (r->max >= set->rangesList[set->numOfDiscontin]->max)) {
        Range **arrOfRanges = malloc(sizeof(Range *));
        // printf("hi");
        arrOfRanges[0] = constructRange(r->min,r->max);
        tempSet = constructSet(arrOfRanges,1);
        return tempSet;
    }

    //Checks to see if the inputted range will be the last element
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
        } else {
            //r will overwrite the last element
            if(isSubrange(r,set->rangesList[set->numOfDiscontin])){
                set->rangesList[set->numOfDiscontin] = constructRange(set->rangesList[set->numOfDiscontin]->min,
                                                        set->rangesList[set->numOfDiscontin]->max);
            } else{
                set->rangesList[set->numOfDiscontin] = constructRange(set->rangesList[set->numOfDiscontin]->min,r->max);
            }
            return set;
        }

    }

    //Check where the range needs to be inserted
    while((r->min) > (set->rangesList[counter]->min)) {
        counter++;
    }
    int maxCounter = counter;
    //Check where the range will stop overwriting
    while((r->max) > set->rangesList[maxCounter]->max) {
        maxCounter++;
    }
    if(r->max<=set->rangesList[maxCounter]->max) {
        maxCounter--;
    }

    // printf("%d %d\n",counter, maxCounter); //index of element
    int offset = maxCounter - counter;
    //if the range will be the first element
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

    // printf("%d",counter);


    
    if((set->rangesList[counter]->max)<=(r->min)) { //r starts inside a discontinuity
        if((set->rangesList[counter+1]->min)<(r->max)) {
            //function 2
            //part of r is inside the right
            //need to overwrite the right range

            if(set->rangesList[counter+1]->max>r->max){
                set->rangesList[counter+1] = constructRange(r->min,set->rangesList[counter+1]->max);
            } else {
                set->rangesList[counter+1] = constructRange(r->min,r->max);
            }
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
            // printf("hi");
            if(set->rangesList[counter]->min >= r->min){
                set->rangesList[counter] = constructRange(set->rangesList[counter]->min,r->max);
            } else {
                set->rangesList[counter] = constructRange(r->min,r->max);
            }
            return set;
        }
    }


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
 * This function returns the
 * intersection between all the elements
 * in the inputted set and the inputted
 * range.  It uses a linear search, therefore
 * the algorithmic complexity is O(n).
 */
RangesSet *getRangeSet(RangesSet *set, Range *r) {

    int counter=0;
    int maxCounter=0;
    //Need to get the size of the array
    for(int i=0;i<set->numOfDiscontin+1;i++) {
        if(compareRanges(set->rangesList[i],r)==1) { //if the current range in the set contains r.
            counter++;
        }
    }
    
    Range **arrOfRanges = malloc(counter*sizeof(Range *));
    maxCounter=0;
    //add the ranges that intersect with r
    for(int i=0;i<set->numOfDiscontin+1;i++) {
        if(compareRanges(set->rangesList[i],r)==1) {
            arrOfRanges[maxCounter] = set->rangesList[i];
            maxCounter++;
        }
    }
    //make a new set from the new range array
    RangesSet *tempSet = constructSet(arrOfRanges,counter);
    free(arrOfRanges);
    return tempSet;
}

/* Function: deleteRangeSet
 * Arguments: RangesSet *set, Range *r
 * Return: RangesSet *tempSet
 * 
 * This function returns a new set
 * from the difference between the
 * inputted set and the inputted range.
 * It uses a linear search, therefore, 
 * the average algorithmic complexity 
 * is O(n).
 */
RangesSet *deleteRangeSet(RangesSet *set, Range *r) {
    int counter = 0;
    RangesSet *tempSet;
    int *arr, intArrSize=0;
    int *arrFinal, newArrSize=0;

    //Checks to see if the inputted range covers the whole set
    if((r->min <= set->rangesList[0]->min) && (r->max >= set->rangesList[set->numOfDiscontin]->max)) {
        Range **arrOfRanges;
        tempSet = constructSet(arrOfRanges,0);
        return tempSet;
    }

    //Checks to see if range is not in set.
    if((r->max <= set->rangesList[0]->min)||(r->min >= set->rangesList[set->numOfDiscontin]->max)) {
        return set;
    }

    //convert to an array of ints 
    arr = toIntArr(set,&intArrSize);

    newArrSize = 0;
    
    //count the number of numbers I want to remove
    for(int i=0;i<intArrSize;i++) {
        if(r->min <= arr[i] && r->max > arr[i]) {
            newArrSize++;
        }
    }
    
    newArrSize = (intArrSize)-newArrSize;
    arrFinal = malloc(newArrSize*sizeof(int));
    int offset=0;
        //build the final int list
        for(int i=0;i<intArrSize;i++) {
            if(r->min <= arr[i] && r->max > arr[i]) {
                continue;
            }
            arrFinal[offset] = arr[i];
            offset++;
    }

    // for(int i=0;i<newArrSize;i++){
    //     printf("%d ",arrFinal[i]);
    // }

    tempSet = SetFromIntList(arrFinal,newArrSize);
    return tempSet;
}

// RangesSet *addRangeSet2(RangesSet *set, Range *r) {

//     RangesSet *tempSet;

//     if((r->min) >= (set->rangesList[set->numOfDiscontin]->min)) {
//         if((r->min) >= (set->rangesList[set->numOfDiscontin]->max)) {
//             //r will be the last element, realloc array

//             Range **arrOfRanges = malloc((set->numOfDiscontin+2)*sizeof(Range *));
//             for(int i=0;i<set->numOfDiscontin+1;i++) {
//                 arrOfRanges[i] = set->rangesList[i];
//             }
//             arrOfRanges[set->numOfDiscontin+1] = constructRange(r->min,r->max);
//             tempSet = constructSet(arrOfRanges,set->numOfDiscontin+2);
//             return tempSet;
//         }
//         else {
//             //r will overwrite the last element

//             set->rangesList[set->numOfDiscontin] = constructRange(set->rangesList[set->numOfDiscontin]->min,r->max);
//             return set;
//         }

//     }

//     int counter=0,maxCounter=0,offset,sizOfNewArr,flag=0,holeSet=0,something=0;
//     Range **arrOfRanges;

//     while((r->min) >= (set->rangesList[counter]->min)) {
//     counter++;
//     }
//     while((r->max) > (set->rangesList[maxCounter]->min)) {
//         maxCounter++;
//     }
//     offset = maxCounter-counter;
//     // printf("%d %d %d ",counter,maxCounter,offset);
//     sizOfNewArr = set->numOfDiscontin+2-offset;
//     printf("ji %d ji",sizOfNewArr);
//     for(int i=0;i<set->numOfDiscontin+1;i++) {
//         if(isSubrange(r,set->rangesList[i])||isSame(r,set->rangesList[i])) {
//             something = 1;
//             break;
//         }
//     }

//     // printf("hi %d ",something);
//     if(something == 1) {
//         --sizOfNewArr;
//         arrOfRanges = malloc((sizOfNewArr)*sizeof(Range *));
        
//     } else {
//         arrOfRanges = malloc((sizOfNewArr)*sizeof(Range *));
//     }

//     // arrOfRanges = malloc((sizOfNewArr)*sizeof(Range *));
//     printf("%d be",something);
//     for (int i=0;i<sizOfNewArr;i++) {
//         if (i==counter) {
//             if(something==0 && offset==0) {
//                 //its in a hole
//                 holeSet = 1;
//                 arrOfRanges[i] = constructRange(r->min,r->max);
//                 offset++;
//                 flag=1;
//                 continue;
//             }
//             else if(compareRanges(set->rangesList[i],r)==0) {
//                 printf("hi");
                
                
//             }
//             else if(compareRanges(set->rangesList[i],r)==1) {

//             }
//             flag = 1;
//         }
//         if(flag==0){
//             arrOfRanges[i] = set->rangesList[i];
//         } else if(flag==1 && holeSet==1){
//             arrOfRanges[i] = set->rangesList[i-offset];
//         } else if (flag==1 && holeSet==0) {
//             arrOfRanges[i] = set->rangesList[i+offset];
//         }
//         // printRange(arrOfRanges[i]);
//     }
//     tempSet = constructSet(arrOfRanges,sizOfNewArr);
//     return tempSet;

// }
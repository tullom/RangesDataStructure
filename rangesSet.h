//Matteo Tullo
//tullom@mcmaster.ca

#ifndef RANGESSET_H
#define RANGESSET_H

#include "ranges.h"

typedef struct RangesSet {

    Range **rangesList;
    int numOfDiscontin;

} RangesSet;

RangesSet *constructSet(Range **r, int size);
RangesSet *SetFromIntList(int *list, int size);
void printRangesSet(RangesSet *set);
int *toIntArr(RangesSet *set, int *size);
RangesSet *addRangeSet(RangesSet *set, Range *r);
RangesSet *getRangeSet(RangesSet *set, Range *r);
// RangesSet *addRangeSet2(RangesSet *set, Range *r);
RangesSet *deleteRangeSet(RangesSet *set, Range *r);

#endif
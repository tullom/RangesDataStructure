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
RangesSet *addRangeSet(RangesSet *set, Range *r);
RangesSet *getRangeSet(RangesSet *set, Range *r);

#endif
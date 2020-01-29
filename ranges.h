//Matteo Tullo
//tullom@mcmaster.ca

#ifndef RANGES_H
#define RANGES_H
typedef struct Range {

    int min, max;

} Range;

Range *constructRange(int x, int y);
Range **constructListOfRanges(int numOfRanges) 
void printListOfRanges(Range **lstOfR);
void printRange(Range *r);
void destroyRange(Range *r);

Range **addRanges(Range *range1, Range *range2);

#endif
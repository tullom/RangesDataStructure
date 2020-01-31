//Matteo Tullo
//tullom@mcmaster.ca

#ifndef RANGES_H
#define RANGES_H
typedef struct Range {

    int min, max;

} Range;

Range *constructRange(int x, int y);
void printRange(Range *r);
void destroyRange(Range *r);
int compareRanges(Range *range1, Range *range2);

#endif
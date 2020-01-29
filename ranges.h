//Matteo Tullo
//tullom@mcmaster.ca

#ifndef RANGES_H
#define RANGES_H
typedef struct Range {

    int min, max;

} Range;

int foo(int x);
Range *constructRange(int x, int y);
void printRange(Range *r);


#endif
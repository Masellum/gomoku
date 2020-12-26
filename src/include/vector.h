#ifndef _VECTOR_H
#define _VECTOR_H

#include <string.h>
#include <stddef.h>

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

typedef struct {
    void *innerArray;
    size_t size, count, sizeOfVal;
} Vector;

typedef unsigned char byte;

void vectorInit(Vector *v, size_t size, size_t sizeOfVal);

void vectorDelete(Vector *v);

void vectorPushBack(Vector *v, void *val);

void vectorPopBack(Vector *v);

void *vectorFront(Vector *v);

void *vectorBack(Vector *v);

void *vectorAt(Vector *v, size_t index);

Vector vectorConcatenate(Vector a, Vector b);

void vectorCopy(Vector *destination, Vector *source);

#endif // VECTOR_H

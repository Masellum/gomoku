#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

typedef struct {
    int *innerArray;
    size_t size, count;
} Vector;

void vectorInit(Vector *v, int size);

void vectorDelete(Vector *v);

void vectorPushBack(Vector *v, int val);

void vectorPopBack(Vector *v, int val);

int vectorFront(Vector *v);

int vectorBack(Vector *v);

int vectorAt(Vector *v, size_t index);

#endif // VECTOR_H

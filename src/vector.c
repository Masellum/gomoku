#include "vector.h"

#include <assert.h>
#include <stdlib.h>


void vectorInit(Vector *v, size_t size, size_t sizeOfVal) {
    v->size = size;
    v->count = 0;
    v->sizeOfVal = sizeOfVal;
    v->innerArray = malloc(sizeOfVal * size);
}

void vectorDelete(Vector *v) {
    if (v->innerArray != NULL) {
        free(v->innerArray);
        v->innerArray = NULL;
    }
    v->size = 0;
    v->count = 0;
    v->sizeOfVal = 0;
}

void vectorResize(Vector *v) {
    void *t = malloc(v->sizeOfVal * v->size * 2);
    memcpy(t, v->innerArray, v->sizeOfVal * v->size);
    free(v->innerArray);
    v->innerArray = t;
}

void vectorResizeTo(Vector *v, size_t size) {
    void *t = malloc(v->sizeOfVal * v->size);
    memcpy(t, v->innerArray, v->sizeOfVal * min(v->size, size));
    free(v->innerArray);
    v->innerArray = t;
}

void vectorPushBack(Vector *v, void *val) {
    if (v->count == v->size) {
        vectorResize(v);
    }
    memcpy(v->innerArray + v->sizeOfVal * v->count, val, v->sizeOfVal);
//    v->innerArray[v->count] = val;
    v->count++;
}

void vectorPopBack(Vector *v) {
    assert(v->count > 0);
    memset(v->innerArray + v->sizeOfVal * (v->count - 1), 0, v->sizeOfVal);
//    v->innerArray[v->count - 1] = 0;
    v->count--;
    if (v->count < v->size / 2) {
        vectorResizeTo(v, v->size / 2);
    }
}

void *vectorFront(Vector *v) {
    assert(v->count > 0);
    return v->innerArray;
}

void *vectorBack(Vector *v) {
    assert(v->count > 0);
    return (void *)((byte *)v->innerArray + v->sizeOfVal * (v->count - 1));
}

void *vectorAt(Vector *v, size_t index) {
    assert(index < v->count);
    return (void *)((byte *)v->innerArray + v->sizeOfVal * index);
}

Vector vectorConcatenate(Vector a, Vector b) {
    assert(a.sizeOfVal == b.sizeOfVal);
    void *t = malloc(a.sizeOfVal * (a.size + b.size));
    memcpy(t, a.innerArray, a.sizeOfVal * a.count);
    memcpy((void *)((byte *)t + a.sizeOfVal * a.count), b.innerArray, a.sizeOfVal * b.count);
    Vector res = (Vector){t, a.size + b.size, a.count + b.count, a.sizeOfVal};
    return res;
}

Vector vectorConcatenateAndClear(Vector a, Vector b) {
    assert(a.sizeOfVal == b.sizeOfVal);
    void *t = malloc(a.sizeOfVal * (a.size + b.size));
    memcpy(t, a.innerArray, a.sizeOfVal * a.count);
    memcpy((void *)((byte *)t + a.sizeOfVal * a.count), b.innerArray, a.sizeOfVal * b.count);
    Vector res = (Vector){t, a.size + b.size, a.count + b.count, a.sizeOfVal};
    vectorDelete(&a);
    return res;
}

void vectorCopy(Vector *destination, Vector *source) {
    assert(destination->sizeOfVal == source->sizeOfVal);
    if (destination->innerArray != NULL) {
        vectorDelete(destination);
    }
    destination->innerArray = malloc(source->sizeOfVal * source->size);
    memcpy(destination->innerArray, source->innerArray, source->sizeOfVal * source->size);
    destination->count = source->count;
    destination->size = source->size;
    destination->sizeOfVal = source->sizeOfVal;
}
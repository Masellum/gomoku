#include "vector.h"

#include <assert.h>
#include <stdlib.h>


void vectorInit(Vector *v, int size) {
    v->size = size;
    v->count = 0;
    v->innerArray = (int *)malloc(sizeof(int) * size);
}

void vectorDelete(Vector *v) {
    free(v->innerArray);
}

void vectorResize(Vector *v) {
    int *t = (int *)malloc(sizeof(int) * v->size * 2);
    for (int i = 0; i < v->count; ++i) {
        t[i] = v->innerArray[i];
    }
    free(v->innerArray);
    v->innerArray = t;
}

void vectorResizeTo(Vector *v, size_t size) {
    int *t = (int *)malloc(sizeof(int) * v->size);
    for (int i = 0; i < min(v->size, size); ++i) {
        t[i] = v->innerArray[i];
    }
    free(v->innerArray);
    v->innerArray = t;
}

void vectorPushBack(Vector *v, int val) {
    if (v->count == v->size) {
        vectorResize(v);
    }
    v->innerArray[v->count] = val;
    v->count++;
}

void vectorPopBack(Vector *v, int val) {
    assert(v->count > 0);
    v->innerArray[v->count - 1] = 0;
    v->count--;
    if (v->count < v->size / 2) {
        vectorResizeTo(v, v->size / 2);
    }
}

int vectorFront(Vector *v) {
    assert(v->count > 0);
    return v->innerArray[0];
}

int vectorBack(Vector *v) {
    assert(v->count > 0);
    return v->innerArray[v->count - 1];
}

int vectorAt(Vector *v, size_t index) {
    assert(index < v->count);
    return v->innerArray[index];
}
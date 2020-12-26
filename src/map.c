#include "map.h"

#include <stdlib.h>

typedef struct treeNode {
    int val, key, rank, size;
    struct treeNode *lc, *rc;
} Node;

Node *initNode(Map *map, int key, int val) {
    Node *t = (Node *)malloc(sizeof(Node));
    t->key = key;
    t->val = val;
    t->rank = rand();
    t->size = 1;
    t->lc = map->nil;
    t->rc = map->nil;
    return t;
}

void freeNode(Map *map, Node *node) {
    if (node != map->nil) {
        if (node->lc != map->nil) {
            freeNode(map, node->lc);
        }
        if (node->rc != map->nil) {
            freeNode(map, node->rc);
        }
        free(node);
    }
}

void updateSize(Node *x) {
    x->size = x->lc->size + x->rc->size + 1;
}

void splitNode(Map *map, Node *x, int k, Node **l, Node **r) {
    if (x == map->nil) {
        *l = *r = map->nil;
    } else if (x->key >= k) {
        splitNode(map, x->lc, k, l, r);
        x->lc = *r;
        *r = x;
        updateSize(*r);
    } else {
        splitNode(map, x->rc, k, l, r);
        x->rc = *l;
        *l = x;
        updateSize(*l);
    }
}

Node *mergeNode(Map *map, Node *x, Node *y) {
    if (x == map->nil || x == map->nil) {
        return x == map->nil ? y : x;
    }
    if (x->rank <= y->rank) {
        x->rc = mergeNode(map, x->rc, y);
        updateSize(x);
        return x;
    } else {
        y->lc = mergeNode(map, x, y->lc);
        updateSize(y);
        return y;
    }
}

void initMap(Map *map) {
    map->nil = (Node *)malloc(sizeof(Node));
    map->nil->key = map->nil->val = map->nil->rank = map->nil->size = 0;
    map->nil->lc = map->nil->rc = map->nil;
    map->root = map->nil;
}

void insertIntoMap(Map *map, int key, int val) {
    Node *x, *y;
    splitNode(map, map->root, key, &x, &y);
    Node *newNode = initNode(map, key, val);
    map->root = mergeNode(map, mergeNode(map, x, newNode), y);
}

void eraseFromMap(Map *map, int key) {
    Node *x, *y, *z;
    splitNode(map, map->root, key, &x, &y);
    splitNode(map, y, key + 1, &z, &y);
    map->root = mergeNode(map, mergeNode(map, x, mergeNode(map, z->lc, z->rc)), y);
    free(z);
}

int selectInSubTree(Node *x, int k) {
    int size = x->lc->size;
    if (k == size + 1) return x->val;
    else if (k <= size) return selectInSubTree(x->lc, k);
    else return selectInSubTree(x->rc, k - size - 1);
}

int selectInMap(Map *map, int key) {
    return selectInSubTree(map->root, key);
}

void freeMap(Map *map) {
    freeNode(map, map->root);
    free(map->nil);
}

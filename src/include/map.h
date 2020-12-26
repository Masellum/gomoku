#ifndef _MAP_H
#define _MAP_H

/**
 * A key-value map supporting inserting, erasing and selecting, implemented in Treap.
 */
typedef struct {
    struct treeNode *root, *nil;
} Map;

/**
 * Init the given map. A map must be initialized before using it.
 * @param map the pointer to the map to be initialized
 */
void initMap(Map *map);

/**
 * Insert <i>val</i> with the given <i>key</i> into <i>map</i>.
 */
void insertIntoMap(Map *map, int key, int val);

/**
 * Erase the <i>val</i> with the given <i>key</i> from <i>map</i>.
 */
void eraseFromMap(Map *map, int key);

/**
 * Find the val of the given <i>key</i> in <i>map</i>.
 */
int selectInMap(Map *map, int key);

/**
 * Free the memories allocated for <i>map</i>. A map must be freed after using it.
 */
void freeMap(Map *map);

#endif // MAP_H

#ifndef _UTILITY_H
#define _UTILITY_H

#include "vector.h"

#include <stdbool.h>

// Define value of situation of single chess
#define FIVE 100000 // 连五
#define FOUR 10000 // 活四
#define FOUR_BLOCKED 100 // 冲四
#define THREE 1000 // 活三
#define THREE_BLOCKED 100 // 眠三
#define TWO 100 // 活二
#define TWO_BLOCKED 10 // 眠二
#define ONE 10 // 单子
#define ONE_BLOCKED 5
#define DOUBLE_FOUR_BLOCKED 10000 // 双冲四
#define FOUR_BLOCKED_THREE 10000 // 冲四活三
#define DOUBLE_THREE 5000 // 双活三
#define THREE_THREE_BLOCKED 2500 // 活三眠三
#define DOUBLE_TWO 500 // 双活二

#define COMPUTER 1
#define HUMAN 2

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

/**
 * We assume that (0, 0) is the left-top corner of the board
 */
typedef struct {
    int x, y;
    int role;
} Position;

/**
 * Calculate the total score of a series of pieces.
 * @param count The amount of selected pieces
 * @param block The amount of blocking pieces (Rival's pieces or walls)
 * @param empty How many pieces are ahead of the empty position
 * @return The total score of given series of pieces
 */
int countToScore(int count, int block, int empty);

/**
 * Evaluate the score of a position on only one direction.
 * We assume that the left top corner of the board is (0, 0), x-axis horizontal and y-axis is vertical.
 * @param direction from 0 to 3 stands for -, |, /, \
 */
int evaluatePositionOnSingleDirection(int board[15][15], int x, int y, int role, int direction);

/**
 * Convert number standing for one player to the one standing for another player,
 * i.e. swap 1 and 2.
 */
int reverseRole(int role);

/**
 * Check if a given position (x, y) has <i>count</i> neighbors in no more than <i>distance</i> steps.
 */
bool hasNeighbor(int board[15][15], int x, int y, int distance, int count);

#endif // _UTILITY_H

#ifndef _UTILITY_H
#define _UTILITY_H

#include <stdbool.h>

#define FIVE 10000000 // 连五
#define FOUR 100000 // 活四
#define FOUR_BLOCKED 10000 // 冲四
#define THREE 1000 // 活三
#define THREE_BLOCKED 100 // 眠三
#define TWO 100 // 活二
#define TWO_BLOCKED 10 // 眠二
#define ONE 10 // 单子
#define ONE_BLOCKED 5

#define COMPUTER 1
#define HUMAN 2

#ifndef max
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#endif

/**
 * We assume that (0, 0) is the left-top corner of the board
 */
typedef struct {
    int x, y;
    int player;
} Position;

int fixScore(int score);

/**
 * Evaluate the score of a position on only one direction.
 * We assume that the left top corner of the board is (0, 0), x-axis horizontal and y-axis is vertical.
 * @param direction from 0 to 3 stands for -, |, /, \
 */
int evaluatePositionOnSingleDirection(int board[15][15], int x, int y, int player, int direction);

/**
 * It behaves as its name.
 * @param pComputerScore pointer to return the score of the position for computer
 * @param pHumanScore pointer to return the score of the position for human
 * @param direction from 0 to 3 stands for -, |, / and \
 */
void updateScoreOfPositionOnSingleDirection(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y,
                                            int direction, int coefficient);

/**
 * Convert number standing for one player to the one standing for another player,
 * i.e. swap 1 and 2.
 */
int reverseRole(int player);

/**
 * Check if a given position (x, y) has <i>count</i> neighbors in no more than <i>distance</i> steps.
 */
bool hasNeighbor(int board[15][15], int x, int y, int distance, int count);

bool greaterThan(int a, int b);

bool equalTo(int a, int b);

#endif // _UTILITY_H

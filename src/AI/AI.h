#ifndef _AI_H
#define _AI_H

#include "utility.h"

/**
 * We assume that (0, 0) is the left-top corner of the board
 */
typedef struct {
    int x, y;
    int role;
} Position;

/**
 * Evaluate the score of a position, considering all directions.
 */
int evaluatePosition(int board[15][15], int x, int y, int role);

/**
 * Update the score of the board, both for human & computer.
 */
void updateScoreOfBoard(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15]);

/**
 * It behaves as its name.
 * @param pComputerScore pointer to return the score of the position for computer
 * @param pHumanScore pointer to return the score of the position for human
 * @param direction from 0 to 3 stands for -, |, / and \
 */
void updateScoreOfPositionOnSingleDirection(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y,
                                            int direction);

/**
 * To be exactly, update score of positions <i>around</i> a position within the given distance.
 */
void updateScoreOfPosition(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y, int distance);


/**
 * Generate a list of available positions for a certain player, not ordered.
 * <br />
 * TODO: sort the returned list
 * @param pNumberOfPositions using pointer to get return, should be initialized first
 * @param role
 * @return a pointer points to the head of the list, REMEMBER TO FREE
 */
Position *generateListOfAvailablePositions(int board[15][15], int computerScoreArray[15][15],
                                           int humanScoreArray[15][15], int *pNumberOfPositions, int role);

/**
 * Evaluate the whole board using calculated data, not really calculating.
 * @param board
 * @param computerScoreArray
 * @param humanScoreArray
 * @param role
 * @return
 */
int evaluate(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15], int role);

#endif // _AI_H


#ifndef _AI_H
#define _AI_H

#include "utility.h"
#include "board.h"

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

bool stupidAINext(twoDimensionalArray board, int player);//简单AI下棋子,并返回是否赢下比赛

bool geniusAINext(twoDimensionalArray board, int player);//困难AI下棋子,并返回是否赢下比赛

#endif // _AI_H


#ifndef _AI_H
#define _AI_H

#include "utility.h"
#include "vector.h"

//extern bool initialized;

typedef struct {
    int score;
    Vector steps;
} SearchResult;

/**
 * Evaluate the score of a position, considering all directions.
 */
int evaluatePosition(int board[15][15], int x, int y, int role);

/**
 * Update the score of the board, both for human & computer.
 */
//void updateScoreOfBoard(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15]);

/**
 * To be exactly, update score of positions <i>around</i> a position within the given distance.
 */
//void updateScoreAroundPosition(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y, int distance);


/**
 * Generate a list of available positions for a certain player, not ordered.
 * <br />
 * @param pNumberOfPositions using pointer to get return, should be initialized first
 * @param role
 * @return a vector includes the list, REMEMBER TO FREE
 */
//Vector generateListOfAvailablePositions(int board[15][15], int computerScoreArray[15][15],
//                                           int humanScoreArray[15][15], int role);

/**
 * Evaluate the whole board using calculated data, not really calculating.
 * @param board
 * @param computerScoreArray
 * @param humanScoreArray
 * @param role
 * @return
 */
//int evaluate(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15], int role);

void reinitialize();

void terminate();

Position stupidAINext(int board[15][15], int player);//简单AI下棋子,并返回是否赢下比赛

Position geniusAINext(int board[15][15], int player);//困难AI下棋子,并返回是否赢下比赛

void AIPutChess(int board[15][15], int player, Position pos);

#endif // _AI_H


#ifndef _CONTROL_H
#define _CONTROL_H

#include "board.h"

#include <stdbool.h>

/**
 * @param board the board to put chess on
 * @param player the given player
 * @return whether the player won after the round
 */
typedef Position (*roundHandler)(int board[15][15], int player);

int getInitiative();
//void setInitiative(int x);

/**
 * @param board the board to put chess on
 * @param player the given player
 * @return whether the player won after the round
 */
//#ifdef __GNUC__
//Position doubleModeMove(__attribute__((unused)) int board[15][15], int player);
//#else
//Position doubleModeMove(int board[15][15], int player);
//#endif



/**
 * start the
 */
//void gameLoop(twoDimensionalArray board, roundHandler sente, roundHandler gote, int player);

/**
 * 双人模式处理函数
 * <br />
 * Handle double mode
 */
void doubleModeHandler();

/**
 * 单人模式处理函数
 * <br />
 * Handle single mode
 */
void singleModeHandler();

void Regret(void);//撤销上一步操作
void Surrender(int player);//用户投降

#endif // CONTROL_H

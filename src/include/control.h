#ifndef CONTROL_H
#define CONTROL_H

#include "board.h"

#include <stdbool.h>

/**
 * @param board the board to put chess on
 * @param player the given player
 * @return whether the player won after the round
 */
typedef bool (*roundHandler)(twoDimensionalArray board, int player);

/**
 * @param board the board to put chess on
 * @param player the given player
 * @return whether the player won after the round
 */
bool singleModeMove(twoDimensionalArray board, int player);

/**
 * start the
 */
void gameLoop(twoDimensionalArray board, roundHandler sente, roundHandler gote, int player);

/**
 * 单人模式处理函数
 * <br />
 * Handle single mode
 */
void singleModeHandler();

/**
 * 双人模式处理函数
 * <br />
 * Handle double mode
 */
void doubleModeHandler();

void Regret(void);//撤销上一步操作
void Surrender(int player);//用户投降

#endif // CONTROL_H

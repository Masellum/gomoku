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

typedef void (*chessPutter)(int board[15][15], int player, Position pos);

int getInitiative();

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

void Surrender(int player);

#endif // _CONTROL_H

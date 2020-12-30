#ifndef _AI_H
#define _AI_H

#include "utility.h"
#include "vector.h"


/**
 * Evaluate the score of a position, considering all directions. 评估一个位置的价值。
 */
int evaluatePosition(int board[15][15], int x, int y, int role);

/**
 * Reinitialize the AI. AI 部分用闭包实现可持续的局部状态，每次游戏开始前应进行初始化。
 */
void reinitialize();

/**
 * Terminate the AI. 结束本局游戏中 AI 的生命周期。
 */
void terminate();

/**
 * 低难度 AI 执行下一步。
 * @return The position selected by AI.
 */
Position stupidAINext(int board[15][15], int player);

/**
 * 高难度 AI 执行下一步。
 * @return The position selected by AI.
 */
Position geniusAINext(int board[15][15], int player);

/**
 * AI 的下棋管理器函数，实现了 **chessPutter** 接口。
 */
void AIPutChess(int board[15][15], int player, Position pos);

#endif // _AI_H


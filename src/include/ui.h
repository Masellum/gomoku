#ifndef UI_H
#define UI_H

#include "utility.h"

#include <time.h>
#include <stdbool.h>

/**
 * 打印欢迎信息
 * <br />
 * Print greeting message
 */
void printHello();

/**
 * 开始游戏，询问用户选择单人or双人模式
 * <br />
 * Start game and ask user to choose PvP or PvC
 * @return 1 stands for single mode while 2 stands for double mode
 */
int startGame();

/**
 * 询问用户选择难度
 * <br />
 * @return the difficulty user chose, 1 stands for easy and 2 stands for hard
 */
int chooseDifficulty();

/**
 * @return the initiative player, 1 or 2
 */
int chooseInitiative();

/**
 * 显示当前的棋盘 (15 * 15)
 */
void showTablet(int board[15][15]);

/**
 * 请求用户执行操作，如果下棋,放置棋子到棋盘中,并返回是否赢下比赛
 * @param player 1 stands for computer while 2 stands for human
 * @return A bool value, presenting win state
 */
Position askNext(int player);

/**
 * 显示已下时间
 */
void showTime(time_t beginTime, time_t endTime);

/**
 * 显示胜负信息
 * @param player winner
 */
void printResult(int player);

/**
 *
 */
bool askReplay();

/**
 * 提示再见信息，询问是否重新开始
 */
void printGoodbye();

#endif //UI_H

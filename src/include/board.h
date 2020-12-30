#ifndef _BOARD_H
#define _BOARD_H

#include "AI.h"


typedef int (*twoDimensionalArray)[15];

/**
 * Create a board and fill it with zeros.
 * @return
 */
twoDimensionalArray initBoard();

/**
 * Fill the board with zeros.
 * @param board the pointer points to the board
 */
void clearBoard(twoDimensionalArray board);

/**
 * Free the memories allocated by initBoard().
 */
void deleteBoard(twoDimensionalArray board);

bool isPositionAvailable(twoDimensionalArray board, Position pos);

void removeChess(twoDimensionalArray board, int x, int y);

/**
 * 在坐标为 (x，y) 的位置放下一颗棋子
 * <br />
 * Put a chess at (x, y).
 */
void putChess(twoDimensionalArray board, int player, Position pos);

/**
 * 检查在坐标为 (x, y) 的位置放下棋子后是否能获胜
 */
bool checkWinOrNotAtPosition(twoDimensionalArray board, int x, int y, int player);

//bool checkWinOrNot(twoDimensionalArray board);

//bool checkIfBoardIsFull(twoDimensionalArray board);//检查棋盘是否填满
bool checkPositionAvailable(twoDimensionalArray board, int a, int b);//返回在（a，b）落子是否符合规范，如果不符合，打印错误信息

#endif // _BOARD_H

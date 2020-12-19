#ifndef _BOARD_H
#define _BOARD_H

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
void clearBoard(twoDimensionalArray *board);

/**
 * Free the memories allocated by initBoard().
 */
void deleteBoard(twoDimensionalArray *board);

/**
 * 在坐标为 (x，y) 的位置放下一颗棋子
 * <br />
 * Put a chess at (x, y).
 */
void putChess(twoDimensionalArray *board, int player, int x, int y);

/**
 * 检查在坐标为 (x, y) 的位置放下棋子后是否能获胜
 */
int checkWinOrNotAtPosition(twoDimensionalArray *board, int x, int y);

/**
 *
 * @return
 */
int checkWinOrNot(twoDimensionalArray *board);

/**
 *
 */
int checkIfBoardIsFull(twoDimensionalArray *board);//检查棋盘是否填满
void recordPutChess(char *type, int player, int a, int b);//记录在（a，b）位置下了一颗棋子
int checkPositionAvailable(int a, int b);//返回在（a，b）落子是否符合规范，如果不符合，打印错误信息

#endif // _BOARD_H

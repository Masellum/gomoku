#include "board.h"

#include <stdlib.h>
#include <string.h>

twoDimensionalArray initBoard() {
    twoDimensionalArray board = (twoDimensionalArray)(calloc(15, 15 * sizeof(int)));
    return board;
}

void clearBoard(twoDimensionalArray board) {
    memset(board, 0, 15 * 15 * sizeof(int));
}

void deleteBoard(twoDimensionalArray board) {
    free(board);
}

bool isPositionAvailable(twoDimensionalArray board, Position pos) {
    return board[pos.x][pos.y] == 0;
}

void removeChess(twoDimensionalArray board, int x, int y) {
    board[x][y] = 0;
}

void putChess(twoDimensionalArray board, int player, Position pos) {
    board[pos.x][pos.y] = player;
}

bool checkWinOrNotAtPosition(twoDimensionalArray board, int x, int y, int player) {
    return evaluatePosition(board, x, y, player) >= FIVE;
}

//bool checkWinOrNot(twoDimensionalArray board) {
//    return 0;
//}

//bool checkIfBoardIsFull(twoDimensionalArray board) {
//    return false;
//}

void recordPutChess(char *type, int player, int a, int b) {
    // TODO
}

bool checkPositionAvailable(twoDimensionalArray board, int a, int b) {
    return board[a][b] == 0;
}

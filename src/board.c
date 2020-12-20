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

void putChess(twoDimensionalArray board, int player, int x, int y) {
    board[x][y] = player;
}

int checkWinOrNotAtPosition(twoDimensionalArray board, int x, int y, int player) {
    // TODO
    return 0;
}

int checkWinOrNot(twoDimensionalArray board) {
    // TODO
    return 0;
}

int checkIfBoardIsFull(twoDimensionalArray board) {
    // TODO
    return false;
}

void recordPutChess(char *type, int player, int a, int b) {
    // TODO
}

int checkPositionAvailable(int a, int b) {
    // TODO
    return 1;
}

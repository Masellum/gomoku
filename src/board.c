#include "board.h"

#include <stdlib.h>
#include <string.h>

typedef int (*twoDimensionalArray)[15];

twoDimensionalArray initBoard() {
    twoDimensionalArray board = (twoDimensionalArray)(calloc(15, 15 * sizeof(int)));
    return board;
}

void clearBoard(twoDimensionalArray *board) {
    memset(board, 0, 15 * 15 * sizeof(int));
}

void deleteBoard(twoDimensionalArray *board) {
    free(board);
}
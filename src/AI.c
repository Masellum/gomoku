#include "include/AI.h"

#include <stdlib.h>

int evaluatePosition(int board[15][15], int x, int y, int role) {
    int result = 0, count = 0, empty = 0, block = 0, counterCount = 0;
    for (int i = 0; i <= 3; ++i) {
        result += evaluatePositionOnSingleDirection(board, x, y, role, i);
    }
    return result;
}

void updateScoreOfBoard(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15]) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board[i][j] == 0) {
                if (hasNeighbor(board, i, j, 2, 2)) {
                    int computerScore = evaluatePosition(board, i, j, COMPUTER),
                        humanScore = evaluatePosition(board, i, j, HUMAN);
                    computerScoreArray[i][j] = computerScore;
                    humanScoreArray[i][j] = humanScore;
                }
            } else if (board[i][j] == COMPUTER) {
                computerScoreArray[i][j] = evaluatePosition(board, i, j, COMPUTER);
                humanScoreArray[i][j] = 0;
            } else {
                humanScoreArray[i][j] = evaluatePosition(board, i, j, HUMAN);
                computerScoreArray[i][j] = 0;
            }
        }
    }
}

void updateScoreOfPositionOnSingleDirection(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y,
                                            int direction) {
    int role = board[x][y], score = 0;
    if (role != HUMAN) {
        score = evaluatePositionOnSingleDirection(board, x, y, COMPUTER, direction);
        *pComputerScore += score;
    } else *pComputerScore = 0;
    if (role != COMPUTER) {
        score = evaluatePositionOnSingleDirection(board, x, y, HUMAN, direction);
        *pHumanScore += score;
    } else *pHumanScore = 0;
}

void updateScoreOfPosition(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y, int distance) {
#define nx (x + i * dx[d])
#define ny (y + i * dy[d])
    int dx[] = {1, 0, -1, 1}, dy[] = {0, 1, 1, 1};
    for (int d = 0; d <= 3; ++d) {
        for (int i = -distance; i <= distance; ++i) {
            if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15) {
                continue;
            }
            updateScoreOfPositionOnSingleDirection(board, x, y, pComputerScore, pHumanScore, d);
        }
    }
}

Position *generateListOfAvailablePositions(int board[15][15], int computerScoreArray[15][15],
                                           int humanScoreArray[15][15], int *pNumberOfPositions, int role) {
    Position *arrayOfPositions = calloc(sizeof(Position), 15 * 15);
    *pNumberOfPositions = 0;
#define push(p) arrayOfPositions[(*pNumberOfPositions)++] = p;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            Position p = {i, j, role};
            if (board[i][j] == 0) {
                if (!hasNeighbor(board, i, j, 2, 2)) continue;
                int scoreOfHuman = humanScoreArray[i][j], scoreOfComputer = computerScoreArray[i][j],
                maxScore = max(scoreOfHuman, scoreOfComputer);
                if (scoreOfComputer > FIVE) {
                    push(p);
                } else if (scoreOfHuman > FIVE) {
                    push(p);
                } else if (role == COMPUTER && scoreOfComputer >= FOUR) {
                    push(p)
                } else if (role == HUMAN && scoreOfHuman >= FOUR) {
                    push(p)
                } else if (scoreOfComputer >= FOUR_BLOCKED) {
                    push(p)
                } else if (scoreOfHuman >= FOUR_BLOCKED) {
                    push(p)
                } else if (scoreOfComputer >= 2 * THREE) {
                    push(p)
                } else if (scoreOfHuman >= 2 * THREE) {
                    push(p)
                } else if (scoreOfComputer >= THREE) {
                    push(p)
                } else if (scoreOfHuman >= THREE) {
                    push(p)
                } else if (scoreOfComputer >= TWO) {
                    push(p)
                } else if (scoreOfHuman >= TWO) {
                    push(p)
                }
            }
        }
    }
    return arrayOfPositions;
#undef push
}

int evaluate(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15], int role) {
    int maxScoreOfComputer = 0, maxScoreOfHuman = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board[i][j] == COMPUTER) {
                maxScoreOfComputer += computerScoreArray[i][j];
            } else if (board[i][j] == HUMAN) {
                maxScoreOfHuman += humanScoreArray[i][j];
            }
        }
    }
    return (role == COMPUTER ? 1 : -1) * (maxScoreOfComputer - maxScoreOfHuman);
}

bool stupidAINext(int board[15][15], int player) {
    // TODO
    return false;
}


bool geniusAINext(int board[15][15], int player) {
    // TODO
    return false;
}
#include "AI.h"
#include "utility.h"
#include "vector.h"
#include "board.h"

#include <stdlib.h>
#include <limits.h>

typedef int (*twoDimensionalArray)[15];

static bool initialized = false, terminated = false;

int evaluatePosition(int (*board)[15], int x, int y, int player) {
    int result = 0;
    for (int i = 0; i <= 3; ++i) {
        result += evaluatePositionOnSingleDirection(board, x, y, player, i);
    }
    return result;
}

#ifdef __GNUC__
__attribute__((unused)) void updateScoreOfBoard(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15]) {
#else
void updateScoreOfBoard(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15]) {
#endif

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

void updateScoreOfPosition(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y, int distance) {
#define nx (x + i * dx[d])
#define ny (y + i * dy[d])
    int dx[] = {1, 0, -1, 1}, dy[] = {0, 1, 1, 1};
    for (int d = 0; d <= 3; ++d) {
        for (int i = -distance; i <= distance; ++i) {
            if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15) {
                continue;
            }
            updateScoreOfPositionOnSingleDirection(board, pComputerScore, pHumanScore, x, y, d);
        }
    }
}

int evaluate(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15], int player) {
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
    return (player == COMPUTER ? 1 : -1) * (maxScoreOfComputer + maxScoreOfHuman);
}

Vector generateListOfAvailablePositions(int board[15][15], int computerScoreArray[15][15],
                                           int humanScoreArray[15][15], int player) {

#define FIVES 0
#define COMPUTER_FOURS 1
#define HUMAN_FOURS 2
#define COMPUTER_BLOCKED_FOURS 3
#define HUMAN_BLOCKED_FOURS 4
#define COMPUTER_TWO_THREES 5
#define HUMAN_TWO_THREES 6
#define COMPUTER_THREES 7
#define HUMAN_THREES 8
#define COMPUTER_TWOS 9
#define HUMAN_TWOS 10
#define NEIGHBORS 11
#define PB(V) vectorPushBack(modelsCount + (V), (void *)(&p))
#define EMPTY(V) (modelsCount[(V)].count == 0)
#define RT(V) { res = (V); goto clearVectors; }
    Vector modelsCount[12];
    for (int i = 0; i < 12; ++i) {
        vectorInit(modelsCount + i, 250, sizeof(Position));
    }
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            Position p = (Position){i, j, player};
            if (board[i][j] == 0) {
                if (hasNeighbor(board, i, j, 2, 2)) {
                    int scoreOfHuman = humanScoreArray[i][j], scoreOfComputer = computerScoreArray[i][j];
//                    int maxScore = max(scoreOfHuman, scoreOfComputer);
                    if (scoreOfComputer > FIVE || scoreOfHuman > FIVE) {
                        PB(FIVES);
                    } else if (player == COMPUTER && scoreOfComputer >= FOUR) {
                        PB(COMPUTER_FOURS);
                    } else if (player == HUMAN && scoreOfHuman >= FOUR) {
                        PB(HUMAN_FOURS);
                    } else if (scoreOfComputer >= FOUR_BLOCKED) {
                        PB(COMPUTER_BLOCKED_FOURS);
                    } else if (scoreOfHuman >= FOUR_BLOCKED) {
                        PB(HUMAN_BLOCKED_FOURS);
                    } else if (scoreOfComputer >= 2 * THREE) {
                        PB(COMPUTER_TWO_THREES);
                    } else if (scoreOfHuman >= 2 * THREE) {
                        PB(HUMAN_TWO_THREES);
                    } else if (scoreOfComputer >= THREE) {
                        PB(COMPUTER_THREES);
                    } else if (scoreOfHuman >= THREE) {
                        PB(HUMAN_THREES);
                    } else if (scoreOfComputer >= TWO) {
                        PB(COMPUTER_TWOS);
                    } else if (scoreOfHuman >= TWO) {
                        PB(HUMAN_TWOS);
                    } else {
                        PB(NEIGHBORS);
                    }
                }
            }
        }
    }
    Vector res;
    if (!EMPTY(FIVES)) RT(modelsCount[FIVES])
    if (player == COMPUTER && !EMPTY(COMPUTER_FOURS)) RT(modelsCount[COMPUTER_FOURS])
    if (player == HUMAN && !EMPTY(HUMAN_FOURS)) RT(modelsCount[HUMAN_FOURS])
    if (player == COMPUTER && !EMPTY(HUMAN_FOURS) && EMPTY(COMPUTER_BLOCKED_FOURS)) RT(modelsCount[HUMAN_FOURS])
    if (player == HUMAN && !EMPTY(COMPUTER_FOURS) && EMPTY(HUMAN_BLOCKED_FOURS)) RT(modelsCount[COMPUTER_FOURS])
    Vector fours = (player == COMPUTER ?
            vectorConcatenate(modelsCount[COMPUTER_FOURS], modelsCount[HUMAN_FOURS]) :
            vectorConcatenate(modelsCount[HUMAN_FOURS], modelsCount[COMPUTER_FOURS])),
           blockedFours = (player == COMPUTER ?
            vectorConcatenate(modelsCount[COMPUTER_BLOCKED_FOURS], modelsCount[HUMAN_BLOCKED_FOURS]) :
            vectorConcatenate(modelsCount[HUMAN_BLOCKED_FOURS], modelsCount[COMPUTER_BLOCKED_FOURS]));
    if (fours.count != 0) RT(vectorConcatenate(fours, blockedFours))

    if (player == COMPUTER) {
        res = vectorConcatenate(
                vectorConcatenate(
                        vectorConcatenate(
                                vectorConcatenate(
                                        vectorConcatenate(modelsCount[COMPUTER_TWO_THREES],
                                                             modelsCount[HUMAN_TWO_THREES]),
                                        modelsCount[COMPUTER_BLOCKED_FOURS]),
                                modelsCount[HUMAN_BLOCKED_FOURS]),
                        modelsCount[COMPUTER_THREES]),
                modelsCount[HUMAN_THREES]);
    }

    if (player == HUMAN) {
        res = vectorConcatenate(
                vectorConcatenate(
                        vectorConcatenate(
                                vectorConcatenate(
                                        vectorConcatenate(modelsCount[HUMAN_TWO_THREES],
                                                          modelsCount[COMPUTER_TWO_THREES]),
                                        modelsCount[HUMAN_BLOCKED_FOURS]),
                                modelsCount[COMPUTER_BLOCKED_FOURS]),
                        modelsCount[HUMAN_THREES]),
                modelsCount[COMPUTER_THREES]);
    }

    if (modelsCount[COMPUTER_TWO_THREES].count != 0 || modelsCount[HUMAN_TWO_THREES].count != 0) {
        goto clearVectors;
    }
    Vector twos;
    if (player == COMPUTER) twos = vectorConcatenate(modelsCount[COMPUTER_TWOS], modelsCount[HUMAN_TWOS]);
    else twos = vectorConcatenate(modelsCount[HUMAN_TWOS], modelsCount[COMPUTER_TWOS]);
    res = vectorConcatenate(res, twos.count != 0 ? twos : modelsCount[NEIGHBORS]);

clearVectors:
    for (int i = 0; i < 12; ++i) {
        vectorDelete(modelsCount + i);
    }
    return res;
}

SearchResult search(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15],
                    int depth, int player, Vector *steps) {
    int e = evaluate(board, computerScoreArray, humanScoreArray, player);
    SearchResult result = (SearchResult){e, *steps};
    if (depth <= 0 || e >= FIVE || e <= -FIVE) {
        return result;
    }
    SearchResult best = (SearchResult){INT_MIN, *steps};
    Vector positions = generateListOfAvailablePositions(board, computerScoreArray, humanScoreArray, player);
    if (positions.count == 0) return result;
    for (int i = 0; i < positions.count; ++i) {
        Position p = *((Position *)(vectorAt(&positions, i)));
        putChess(board, player, p.x, p.y);
        updateScoreOfPosition(board, &computerScoreArray[p.x][p.y], &humanScoreArray[p.x][p.y], p.x, p.y, 5);
//        Vector newStep = (Vector){NULL, 0, 0, 0};
//        vectorCopy(&newStep, steps);
//        vectorPushBack(&newStep, &p);
//        SearchResult r = search(board, computerScoreArray, humanScoreArray,
//                                depth - 1, reverseRole(player), &newStep);
        vectorPushBack(steps, &p);
        SearchResult r = search(board, computerScoreArray, humanScoreArray, depth - 1, reverseRole(player), steps);
        vectorPopBack(steps);
        r.score *= -1;
        removeChess(board, p.x, p.y);
        updateScoreOfPosition(board, &computerScoreArray[p.x][p.y], &humanScoreArray[p.x][p.y], p.x, p.y, 5);
        if (r.score > best.score) {
            best = r;
        }
    }
    return best;
}

void reinitialize() {
    initialized = false;
    terminated = false;
}

void terminate() {
    terminated = true;
}

#ifdef __GNUC__
Position AINext(int board[15][15], __attribute__((unused)) int player, int depth) {
#else
Position AINext(int board[15][15], int player, int depth) {
#endif
    static int (*computerScoreArray)[15] = NULL, (*humanScoreArray)[15] = NULL;
    if (!initialized) {
        if (computerScoreArray != NULL) {
            free(computerScoreArray);
        }
        if (humanScoreArray != NULL) {
            free(humanScoreArray);
        }
        if (terminated) return (Position){0, 0, 0};
        initialized = true;
        computerScoreArray = calloc(15, 15 * sizeof(int));
        humanScoreArray = calloc(15, 15 * sizeof(int));
//        computerScoreArray = (twoDimensionalArray)(calloc(15, 15 * sizeof(int)));
//        humanScoreArray = (twoDimensionalArray)(calloc(15, 15 * sizeof(int)));
    }
    Vector steps;
    vectorInit(&steps, 5, sizeof(Position));
    SearchResult sr = search(board, computerScoreArray, humanScoreArray, depth, COMPUTER, &steps);
    Position res = *((Position *)(vectorAt(&sr.steps, sr.steps.count - 1)));
    vectorDelete(&steps);
    return res;

}

Position stupidAINext(int board[15][15], int player) {
    return AINext(board, player, 2);
}

Position geniusAINext(int board[15][15], int player) {
    return AINext(board, player, 4);
}
#include "AI.h"
#include "utility.h"
#include "vector.h"
#include "board.h"
#include "ui.h"

#include <stdlib.h>
#include <limits.h>

/**
 * Struct containing the search result.
 */
typedef struct {
    int score;
    Vector steps;
} SearchResult;

static bool initialized = false, terminated = false;

/**
 * Evaluate the score of a position, considering all directions. 评估一个位置的价值。
 */
int evaluatePosition(int (*board)[15], int x, int y, int player) {
    int result = 0;
    for (int i = 0; i <= 3; ++i) {
        result += evaluatePositionOnSingleDirection(board, x, y, player, i);
    }
    return result;
}

/**
 * To be exactly, update score of positions <i>around</i> a position within the given distance. 更新在一个位置的指定距离内所有位置的价值。
 * @param coefficient 想对某个新放下了棋子的位置进行评估，需要先以 *coefficient* 为 **-1** 调用一次取消之前的评估，放下棋子后再以 **1** 调用一次。
 */
void updateScoreAroundPosition(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15],
                               int x, int y, int distance, int coefficient) {
#define nx (x + i * dx[d])
#define ny (y + i * dy[d])
    int dx[] = {1, 0, -1, 1}, dy[] = {0, 1, 1, 1};
    for (int d = 0; d <= 3; ++d) {
        for (int i = -distance; i <= distance; ++i) {
            if (nx >= 0 && ny >= 0 && nx < 15 && ny < 15) {
                updateScoreOfPositionOnSingleDirection(board, &computerScoreArray[nx][ny], &humanScoreArray[nx][ny],
                                                       nx, ny, d, coefficient);
            }
        }
    }
#undef nx
#undef ny
}

/**
 * Evaluate the whole board using calculated data, not really calculating. 评估整个局面的价值。
 */
int evaluate(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15], int player) {
    int maxScoreOfComputer = 0, maxScoreOfHuman = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board[i][j] == COMPUTER) {
                maxScoreOfComputer += fixScore(computerScoreArray[i][j]);
            } else if (board[i][j] == HUMAN) {
                maxScoreOfHuman += fixScore(humanScoreArray[i][j]);
            }
        }
    }
    return (player == COMPUTER ? 1 : -1) * (maxScoreOfComputer - maxScoreOfHuman);
}

/**
 * Generate a list of available positions for a certain player. 生成所有对给定玩家有意义的可落子位置。
 * @return a vector includes the list, REMEMBER TO FREE. 一个包含所有位置的 **Vector**，使用完毕后务必释放内存。
 */
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
//#define RT(V) { res = (V); goto clearVectors; }
#define RT(V) { vectorCopy(&res, &(V)); goto clearVectors; }
    Vector modelsCount[12];
    for (int i = 0; i < 12; ++i) {
        vectorInit(modelsCount + i, 250, sizeof(Position));
    }
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            Position p = (Position){i, j, player};
            if (board[i][j] == 0) {
                if (hasNeighbor(board, i, j, 2, 1)) {
                    int scoreOfHuman = humanScoreArray[i][j], scoreOfComputer = computerScoreArray[i][j];
                    if (scoreOfComputer > FIVE || scoreOfHuman > FIVE) {
                        PB(FIVES);
                    } else if (scoreOfComputer >= FOUR) {
                        PB(COMPUTER_FOURS);
                    } else if (scoreOfHuman >= FOUR) {
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
                        if (scoreOfHuman == 0 && scoreOfComputer == 0) continue;
                        PB(NEIGHBORS);
                    }
                }
            }
        }
    }
    Vector res = (Vector){NULL, 0, 0, sizeof(Position)};
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
    if (fours.count != 0) {
        res = vectorConcatenate(fours, blockedFours);
        vectorDelete(&fours);
        vectorDelete(&blockedFours);
//        vectorDelete(&v);
        goto clearVectors;
    }
    if (player == COMPUTER) {
        res = vectorConcatenateAndClear(
                vectorConcatenateAndClear(
                        vectorConcatenateAndClear(
                                vectorConcatenateAndClear(
                                        vectorConcatenate(modelsCount[COMPUTER_TWO_THREES],
                                                             modelsCount[HUMAN_TWO_THREES]),
                                        modelsCount[COMPUTER_BLOCKED_FOURS]),
                                modelsCount[HUMAN_BLOCKED_FOURS]),
                        modelsCount[COMPUTER_THREES]),
                modelsCount[HUMAN_THREES]);
    }

    if (player == HUMAN) {
        res = vectorConcatenateAndClear(
                vectorConcatenateAndClear(
                        vectorConcatenateAndClear(
                                vectorConcatenateAndClear(
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
    Vector twos = (Vector){NULL, 0, 0, 0};
    if (player == COMPUTER) twos = vectorConcatenate(modelsCount[COMPUTER_TWOS], modelsCount[HUMAN_TWOS]);
    else twos = vectorConcatenate(modelsCount[HUMAN_TWOS], modelsCount[COMPUTER_TWOS]);
    res = vectorConcatenateAndClear(res, twos.count != 0 ? twos : modelsCount[NEIGHBORS]);
    vectorDelete(&twos);

clearVectors:
    for (int i = 0; i < 12; ++i) {
        vectorDelete(modelsCount + i);
    }
    return res;
}

/**
 * Perform search and return the best result found. 进行搜索并返回找到的最优位置。
 * @param depth The search depth. 搜索深度，最好为偶数。
 * @param player The role when starting the search. 开始搜索时的玩家身份，外部调用时总应为 COMPUTER。
 * @param steps A pointer pointing to the vector which stores the steps, should be initialized first. 指向存储步骤的向量的指针，应先被初始化。
 * @param alpha The coefficient used to reduce search time. 剪枝用到的参数，外部调用时总应传入最小值。
 * @param bete The coefficient used to reduce search time. 剪枝用到的参数，外部调用时总应传入最大值。
 * @return The result containing the best score and steps. 存储着最优步骤及其得分的 **SearchResult** 对象。
 */
SearchResult search(int board[15][15], int computerScoreArray[15][15], int humanScoreArray[15][15],
                    int depth, int player, Vector *steps, int alpha, int beta) {
    int e = evaluate(board, computerScoreArray, humanScoreArray, player);
    SearchResult result;
    result.score = e;
    result.steps.sizeOfVal = sizeof(Position);
    result.steps.innerArray = NULL;
    vectorCopy(&result.steps, steps);
    if (depth <= 0 || greaterThan(e, FIVE) || equalTo(e, FIVE) || greaterThan(-FIVE, e)) {
        return result;
    }
    Vector positions = generateListOfAvailablePositions(board, computerScoreArray, humanScoreArray, player);
    if (positions.count == 0) {
        vectorDelete(&positions);
        return result;
    }
    vectorDelete(&result.steps);
    SearchResult best;
    best.score = INT_MIN;
    best.steps.sizeOfVal = sizeof(Position);
    best.steps.innerArray = NULL;
    vectorCopy(&best.steps, steps);
    SearchResult r;
    for (int i = 0; i < positions.count; ++i) {
        Position p = *((Position *)(vectorAt(&positions, i)));
        updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, p.x, p.y, 5, -1);
        putChess(board, player, p);
        updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, p.x, p.y, 5, 1);
        vectorPushBack(steps, &p);
        r = search(board, computerScoreArray, humanScoreArray,
                   depth - 1, reverseRole(player), steps, alpha, beta);
        vectorPopBack(steps);
        r.score *= -1;
        updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, p.x, p.y, 5, -1);
        removeChess(board, p.x, p.y);
        updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, p.x, p.y, 5, 1);
        if (player == HUMAN) {
            if (greaterThan(alpha, r.score)) {
                r.score = INT_MIN + 1;
                vectorDelete(&positions);
                return r;
            }
            beta = min(beta, best.score);
        } else {
            if (greaterThan(r.score, beta)) {
                r.score = INT_MAX - 1;
                vectorDelete(&positions);
                return r;
            }
            alpha = max(alpha, best.score);
        }
        if (greaterThan(r.score, best.score)) {
            vectorCopy(&best.steps, &r.steps);
            best.score = r.score;
        }
        vectorDelete(&r.steps);
    }
    vectorDelete(&positions);
    return best;
}

/**
 * Reinitialize the AI. AI 部分用闭包实现可持续的局部状态，每次游戏开始前应进行初始化。
 */
void reinitialize() {
    initialized = false;
    terminated = false;
}

/**
 * Terminate the AI. 结束本局游戏中 AI 的生命周期。
 */
void terminate() {
    terminated = true;
}

/**
 * Ask the AI to perform next move or tell the AI that a move is performed by another player. 询问 AI 下一着，或告知 AI 玩家的落子。
 * @param player COMPUTER when asking, HUMAN when telling.
 * @param depth The search depth which decides the intelligence of AI. 搜索深度，数值越大则 AI 思考越深入，则棋力越强。。
 * @param tellingOrAsking **true** if telling, **false** if asking.
 * @param pos The position of chess put by human, when asking it should be empty value. 玩家下棋的位置，在询问时应设为无意义值。
 * @return The position selected by AI, or the given position when telling.
 */
Position communicateWithAI(int board[15][15], int player, int depth,
                           bool tellingOrAsking, Position pos) {
    static int (*computerScoreArray)[15] = NULL, (*humanScoreArray)[15] = NULL;
    if (!initialized) {
        if (computerScoreArray != NULL) {
            free(computerScoreArray);
            computerScoreArray = NULL;
        }
        if (humanScoreArray != NULL) {
            free(humanScoreArray);
            humanScoreArray = NULL;
        }
        if (terminated) return (Position){0, 0, 0};
        initialized = true;
        computerScoreArray = calloc(15, 15 * sizeof(int));
        humanScoreArray = calloc(15, 15 * sizeof(int));
        if (tellingOrAsking == false) {
            return (Position){6, 6, COMPUTER};
        } else {
            updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, pos.x, pos.y, 5, -1);
            putChess(board, player, pos);
            updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, pos.x, pos.y, 5, 1);
            return pos;
        }
    }
    if (tellingOrAsking == false) {
        sendMessage("AI思考中……");
        Vector steps;
        vectorInit(&steps, 5, sizeof(Position));
        SearchResult sr = search(board, computerScoreArray, humanScoreArray,
                                 depth, COMPUTER, &steps, INT_MIN, INT_MAX);
        Position res = *((Position *)(vectorAt(&sr.steps, 0)));
        vectorDelete(&steps);
        vectorDelete(&sr.steps);
        return res;
    } else {
        updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, pos.x, pos.y, 5, -1);
        putChess(board, player, pos);
        updateScoreAroundPosition(board, computerScoreArray, humanScoreArray, pos.x, pos.y, 5, 1);
        return pos;
    }
}

/**
 * 低难度 AI 执行下一步。
 * @return The position selected by AI.
 */
Position stupidAINext(int board[15][15], int player) {
    return communicateWithAI(board, player, 4, false, (Position) {-1, -1, 0});
}

/**
 * 高难度 AI 执行下一步。
 * @return The position selected by AI.
 */
Position geniusAINext(int board[15][15], int player) {
    return communicateWithAI(board, player, 6, false, (Position) {-1, -1, 0});
}

/**
 * AI 的下棋管理器函数，实现了 **chessPutter** 接口。
 */
void AIPutChess(int board[15][15], int player, Position pos) {
    communicateWithAI(board, player, -1, true, pos);
}
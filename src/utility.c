#include "utility.h"

#include <stdbool.h>

int fixScore(int score) {
    if (score < FOUR && score >= FOUR_BLOCKED) {
        if (score >= FOUR_BLOCKED && score < (FOUR_BLOCKED + THREE)) {
            return THREE;
        } else if (score >= FOUR_BLOCKED + THREE && score < FOUR_BLOCKED * 2) {
            return FOUR;
        } else {
            return FOUR * 2;
        }
    }
    return score;
}

//int countToScore(int count, int blockHead, int blockTail, int empty) {
//    if (empty <= 0) {
//        if (count >= 5) return FIVE;
////        if (blockHead == 0 && blockTail == 0) {
//        if (blockHead + blockTail == 0) {
//            switch (count) {
//                case 4: return FOUR;
//                case 3: return THREE;
//                case 2: return TWO;
//                case 1: return ONE;
//            }
//        }
//        if (blockHead + blockTail == 1) {
//            switch (count) {
//                case 4: return FOUR_BLOCKED;
//                case 3: return THREE_BLOCKED;
//                case 2: return TWO_BLOCKED;
//                case 1: return ONE_BLOCKED;
//            }
//        }
//    } else if (empty == 1 || empty == count - 1) {
//        if (count >= 6) return FIVE;
//        if (blockHead + blockTail == 0) {
//            switch (count) {
//                case 5: return FOUR;
//                case 4: return FOUR_BLOCKED;
//                case 3: return THREE_BLOCKED;
//                case 2: return TWO_BLOCKED;
////                case 2: return ONE * 2;
//            }
//        } else if (blockHead == 1 && blockTail == 0) {
//            switch (count) {
//                case 5: return FOUR;
//                case 4: return THREE;
//                case 3: return TWO;
//                case 2: return ONE * 2;
//            }
//        } else if (blockTail == 1 && blockHead == 1) {
//            switch (count) {
//                case 5: return FOUR;
//                case 4: return THREE_BLOCKED;
//                case 3: return TWO_BLOCKED;
//                case 2: return ONE;
//            }
//        }
//    } else if (empty == 2 || empty == count - 2) {
//        if (count >= 7) return FIVE;
//        if (blockHead + blockTail == 0) {
//            return FOUR;
////            switch (count) {
////                case 6: return FOUR;
////                case 5: return FOUR;
////                case 4: return FOUR;
////            }
//        } else if (blockHead == 1) {
//
//        } else if (block == 1) {
//            switch (count) {
//                case 4: return FOUR_BLOCKED;
//                case 5: return FOUR_BLOCKED;
//                case 6: return FOUR;
//            }
//        } else if (block == 2) {
//            switch (count) {
//                case 4:
//                case 5:
//                case 6: return FOUR_BLOCKED;
//            }
//        }
//    } else if (empty == 3 || empty == count - 3) {
//        if (count >= 8) return FIVE;
//        if (block == 0) {
//            switch (count) {
//                case 4:
//                case 5: return THREE;
//                case 6: return FOUR_BLOCKED;
//                case 7: return FOUR;
//            }
//        } else if (block == 1) {
//            switch (count) {
//                case 4:
//                case 5:
//                case 6: return FOUR_BLOCKED;
//                case 7: return FOUR;
//            }
//        } else if (block == 2) {
//            switch (count) {
//                case 4:
//                case 5:
//                case 6:
//                case 7: return FOUR_BLOCKED;
//            }
//        }
//    } else if (empty == 4 || empty == count - 4) {
//        if (count >= 9) {
//            return FIVE;
//        }
//        if (block == 0) {
//            switch (count) {
//                case 5:
//                case 6:
//                case 7:
//                case 8: return FOUR;
//            }
//        } else if (block == 1) {
//            switch (count) {
//                case 4:
//                case 5:
//                case 6:
//                case 7: return FOUR_BLOCKED;
//                case 8: return FOUR;
//            }
//        } else if (block == 2) {
//            switch (count) {
//                case 5:
//                case 6:
//                case 7:
//                case 8: return FOUR_BLOCKED;
//            }
//        }
//    } else if (empty == 5 || empty == count - 5) {
//        return FIVE;
//    }
//    return 0;
//}

int countToScore(int count, int block, int empty) {
    if (empty >= 5 || (empty > 0 && empty <= count - 5)) return FIVE;
    else if (empty <= 0) {
        if (count >= 5) return FIVE;
//        if (blockHead == 0 && blockTail == 0) {
        if (block == 0) {
            switch (count) {
                case 4: return FOUR;
                case 3: return THREE;
                case 2: return TWO;
                case 1: return ONE;
            }
        }
        if (block == 1) {
            switch (count) {
                case 4: return FOUR_BLOCKED;
                case 3: return THREE_BLOCKED;
                case 2: return TWO_BLOCKED;
                case 1: return ONE_BLOCKED;
            }
        }
    } else if (empty == 1 || empty == count - 1) {
        if (count >= 6) return FIVE;
        if (block == 0) {
            switch (count) {
                case 5:
                    return FOUR;
                case 4:
                    return FOUR_BLOCKED;
                case 3:
                    return THREE;
                case 2:
                    return TWO / 2;
//                case 5:
//                case 4: return FOUR;
//                case 3: return THREE;
//                case 2: return TWO;
//                case 2: return ONE * 2;
            }
        } else if (block == 1) {
            switch (count) {
                case 5:
                case 4:
                    return FOUR_BLOCKED;
                case 3:
                    return THREE_BLOCKED;
                case 2:
                    return TWO_BLOCKED;
//                case 5:
//                case 4: return FOUR;
//                case 3: return FOUR_BLOCKED;
//                case 2: return ONE * 2;
            }
        } else if (block == 2) {
            switch (count) {
                case 5:
                case 4:
                    return THREE_BLOCKED;
                case 3:
                    return TWO_BLOCKED;
                case 2:
                    return TWO_BLOCKED;
            }
        }
    } else if (empty == 2 || empty == count - 2) {
//    } else if (empty == 2 || empty == count - 2 || empty == 3 || empty == count - 3) {
        if (count >= 7) return FIVE;
        if (block == 0) {
            switch (count) {
                case 6: return FOUR;
                case 5:
                case 4: return FOUR_BLOCKED;
                case 3: return THREE;
            }
        } else if (block == 1) {
            switch (count) {
                case 6: return FOUR;
                case 5:
                case 4: return FOUR_BLOCKED;
                case 3: return THREE_BLOCKED;
            }
        } else if (block == 2) {
            switch (count) {
                case 6:
                case 5:
                case 4: return FOUR_BLOCKED;
            }
        }
    } else if (empty == 3 || empty == count - 3) {
        if (count >= 8) return FIVE;
        if (block == 0) {
            switch (count) {
                case 4:
                case 5: return THREE;
                case 6: return FOUR_BLOCKED;
                case 7: return FOUR;
            }
        } else if (block == 1) {
            switch (count) {
                case 4:
                case 5:
                case 6: return FOUR_BLOCKED;
                case 7: return FOUR;
            }
        } else if (block == 2) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                case 7: return FOUR_BLOCKED;
            }
        }
    } else if (empty == 4 || empty == count - 4) {
        if (count >= 9) {
            return FIVE;
        }
//        if (block == 0) {
//            switch (count) {
//                case 5:
//                case 6:
//                case 7:
//                case 8: return FOUR;
//            }
//        } else if (block == 1) {
//            switch (count) {
//                case 4:
//                case 5:
//                case 6:
//                case 7: return FOUR_BLOCKED;
//                case 8: return FOUR;
//            }
//        } else if (block == 2) {
//            switch (count) {
//                case 5:
//                case 6:
//                case 7:
//                case 8: return FOUR_BLOCKED;
//            }
//        }
        if (block == 0) {
            return FOUR;
        } else if (block == 1) {
            if (count == 8) return FOUR;
            else return FOUR_BLOCKED;
        } else {
            return FOUR_BLOCKED;
        }
    }
    return 0;
}

int evaluatePositionOnSingleDirection(int board[15][15], int x, int y, int player, int direction) {
#define nx (x + i * dx * reversed)
#define ny (y + i * dy * reversed)
    int block = 0, count = 0, counterCount = 0, empty = -1;
    int dx = 0, dy = 0, reversed = 1;
    switch (direction) {
        case 0: dx = 1; break;
        case 1: dy = 1; break;
        case 2: dx = -1; dy = 1; break;
        case 3: dx = 1; dy = 1; break;
    }
    int i;
searchOnOneDirection:
    i = 0;
    if (reversed == -1) ++i;
    for (;;++i) {
        if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15) {
            block++;
            break;
        }
        int t = board[nx][ny];
        if (t == 0) {
//            if (empty == -1 && board[nx + 1 * (dx != 0)][ny + 1 * (dy != 0)] == player) {
            if (empty == -1 && board[nx + 1 * dx * reversed][ny + 1 * dy * reversed] == player) {
                if (reversed == 1) {
                    empty = count;
                } else {
                    empty = 0;
                }
                continue;
            } else {
                break;
            }
        }
        if (t == player) {
            if (reversed == 1) {
                count++;
            } else {
                counterCount++;
                if (empty != -1) empty++;
            }
            continue;
        } else {
            block++;
            break;
        }
    }
    if (reversed == 1) {
        reversed = -1;
        goto searchOnOneDirection;
    }
    count += counterCount;

    return countToScore(count, block, empty);
#undef nx
#undef ny
}

void updateScoreOfPositionOnSingleDirection(int board[15][15], int *pComputerScore, int *pHumanScore, int x, int y,
                                            int direction, int coefficient) {
    int player = board[x][y];
    if (player != HUMAN) {
        *pComputerScore += coefficient * evaluatePositionOnSingleDirection(board, x, y, COMPUTER, direction);
    } else *pComputerScore = 0;
    if (player != COMPUTER) {
        *pHumanScore += coefficient * evaluatePositionOnSingleDirection(board, x, y, HUMAN, direction);
    } else *pHumanScore = 0;
}

int reverseRole(int player) { return player ^ 3; } // 1 ^ 3 == 2, 2 ^ 3 == 1

bool hasNeighbor(int board[15][15], int x, int y, int distance, int count) {
    int startX = x - distance, startY = y - distance, endX = x + distance, endY = y + distance;
    for (int i = startX; i <= endX; ++i) {
        if (i < 0 || i >= 15) continue;
        for (int j = startY; j <= endY; ++j) {
            if (j < 0 || j >= 15) continue;
            if (i == x && j == y) continue;
            if (board[i][j] != 0) {
                count--;
                if (count <= 0) return true;
            }
        }
    }
    return false;
}

bool greaterThan(int a, int b) {
    double threshold = 1.15, aa = a, bb = b;
    return (bb >= 0) ? (aa >= (bb + 0.1) / threshold) : (aa >= (bb - 0.1) * threshold);
}

bool equalTo(int a, int b) {
    double threshold = 1.15, aa = a, bb = b;
    if (b == 0) bb = 0.01;
    return (bb >= 0) ? ((aa >= bb / threshold) && (aa <= bb * threshold)) :
                        ((aa >= bb * threshold) && (aa <= bb / threshold));
}

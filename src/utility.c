#include "utility.h"

#include <stdbool.h>

int countToScore(int count, int block, int empty) {
    if (empty <= 0) {
        if (count >= 5) return FIVE;
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
                case 5: return FOUR;
                case 4: return FOUR_BLOCKED;
                case 3: return THREE;
                case 2: return TWO / 2;
            }
        } else if (block == 1) {
            switch (count) {
                case 5: return FOUR_BLOCKED;
                case 4: return THREE_BLOCKED;
                case 3: return THREE_BLOCKED;
                case 2: return TWO_BLOCKED;
            }
        }
    } else if (empty == 2 || empty == count - 2) {
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
                case 3: return THREE_BLOCKED;
                case 4: return FOUR_BLOCKED;
                case 5: return FOUR_BLOCKED;
                case 6: return FOUR;
            }
        } else if (block == 2) {
            switch (count) {
                case 4:
                case 5:
                case 6: return FOUR_BLOCKED;
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
        if (block == 0) {
            switch (count) {
                case 5:
                case 6:
                case 7:
                case 8: return FOUR;
            }
        } else if (block == 1) {
            switch (count) {
                case 4:
                case 5:
                case 6:
                case 7: return FOUR_BLOCKED;
                case 8: return FOUR;
            }
        } else if (block == 2) {
            switch (count) {
                case 5:
                case 6:
                case 7:
                case 8: return FOUR_BLOCKED;
            }
        }
    } else if (empty == 5 || empty == count - 5) {
        return FIVE;
    }
    return 0;
}

int evaluatePositionOnSingleDirection(int board[15][15], int x, int y, int role, int direction) {
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
searchOnOneDirection:
    for (int i = 1;;++i) {
        if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15) {
            block++;
            break;
        }
        int t = board[nx][ny];
        if (t == 0) {
            if (empty == -1 && board[nx + 1 * (dx != 0)][ny + 1 * (dy != 0)] == role) {
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
        if (t == role) {
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

int reverseRole(int role) { return role ^ 3; } // 1 ^ 3 == 2, 2 ^ 3 == 1

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

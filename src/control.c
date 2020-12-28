#include "control.h"
#include "ui.h"
#include "AI.h"
#include "board.h"

#include <stdbool.h>
#ifdef _DEBUG
#include <stdio.h>
#endif

static int initiative;

int getInitiative() {
    return initiative;
}

void setInitiative(int x) {
    initiative = x;
}

Position doubleModeMove(int board[15][15], int player) {
    return askNext(board, player);
}

void gameLoop(int board[15][15], roundHandler sente, roundHandler gote, int player) {
   bool _initiative = true, win = false;
   while (true) {
       showTablet(board);
       Position pos;
       while (true) {
           if (_initiative) {
               pos = sente(board, player);
           } else {
               pos = gote(board, player);
           }
           if (!isPositionAvailable(board, pos)) {
               sendMessage("操作不合法！请重新选择操作。");
           } else break;
       }
#ifdef _DEBUG
       if (_initiative) {
           printf("黑棋落子于：(%d, %d)\n", pos.x + 1, pos.y + 1);
       } else {
           printf("白棋落子于：(%d, %d)\n", pos.x + 1, pos.y + 1);
       }
#endif
#ifdef _DEBUG
       printBoard(board);
#endif
       putChess(board, player, pos.x, pos.y);
#ifdef _DEBUG
       printBoard(board);
#endif
       win = checkWinOrNotAtPosition(board, pos.x, pos.y, player);
       if (win) {
           printResult(player);
           break;
       }
       _initiative = !_initiative;
       player = reverseRole(player);
   }
}

void doubleModeHandler() {
    int (*board)[15] = initBoard();
    clearBoard(board);
    setInitiative(1);
    gameLoop(board, doubleModeMove, doubleModeMove, 1);
    deleteBoard(board);
}

void singleModeHandler() {
//    setInitiative(reverseRole(chooseInitiative()));
    setInitiative(chooseInitiative());
    int difficulty = chooseDifficulty();
    int (*board)[15] = initBoard();
    clearBoard(board);
    reinitialize();
    roundHandler AINext = difficulty == 1 ? stupidAINext : geniusAINext;
    if (getInitiative() == 2) {
        gameLoop(board, doubleModeMove, AINext, HUMAN);
    } else /*if (getInitiative() == 2)*/ {
        gameLoop(board, AINext, doubleModeMove, COMPUTER);
    }
    reinitialize();
    terminate();
    AINext(board, 0);
}

void Regret() {

}

void Surrender(int player) {

}
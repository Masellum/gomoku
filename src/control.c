#include "control.h"
#include "ui.h"
#include "AI.h"
#include "board.h"

#include <stdbool.h>

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
       putChess(board, player, pos.x, pos.y);
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
    setInitiative(chooseInitiative());
//    initiative = chooseInitiative();
    int difficulty = chooseDifficulty();
    int (*board)[15] = initBoard();
    reinitialize();
    roundHandler AINext = difficulty == 1 ? stupidAINext : geniusAINext;
    if (getInitiative() == 1) {
        gameLoop(board, doubleModeMove, AINext, HUMAN);
    } else /*if (getInitiative() == 2)*/ {
        gameLoop(board, AINext, doubleModeMove, COMPUTER);
    }
    terminate();
    AINext(board, 0);
}

void Regret() {

}

void Surrender(int player) {

}
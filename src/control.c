#include "control.h"
#include "ui.h"
#include "AI.h"
#include "board.h"

#include <stdbool.h>

int initiative;

bool doubleModeMove(twoDimensionalArray board, int player) {
    Position position = askNext(player);
    putChess(board, player, position.x, position.y);
    return checkWinOrNotAtPosition(board, position.x, position.y, player);
}

void gameLoop(twoDimensionalArray board, roundHandler sente, roundHandler gote, int player) {
   bool _initiative = true, win = false;
   while (true) {
       showTablet(board);
       if (_initiative) {
           win = sente(board, player);
       } else {
           win = gote(board, player);
       }
       if (win) {
           printResult(player);
           break;
       }
       _initiative = !_initiative;
       player = reverseRole(player);
   }
}

void doubleModeHandler() {
    twoDimensionalArray board = initBoard();
    clearBoard(board);
    setInitiative(1);
    gameLoop(board, doubleModeMove, doubleModeMove, 1);
    deleteBoard(board);
}

void singleModeHandler() {
    setInitiative(chooseInitiative());
//    initiative = chooseInitiative();
    int difficulty = chooseDifficulty();
    twoDimensionalArray board = initBoard();
    roundHandler AINext = difficulty == 1 ? stupidAINext : geniusAINext;
    if (getInitiative() == 1) {
        gameLoop(board, doubleModeMove, AINext, HUMAN);
    } else if (getInitiative() == 2) {
        gameLoop(board, AINext, doubleModeMove, COMPUTER);
    }
}

int getInitiative() {
    return initiative;
}

void setInitiative(int x) {
    initiative = x;
}

void Regret() {

}

void Surrender(int player) {

}
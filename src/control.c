#include "control.h"
#include "ui.h"
#include "AI.h"
#include "board.h"

#include <stdbool.h>

int initiative;

bool singleModeMove(twoDimensionalArray board, int player) {
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

void singleModeHandler() {
    twoDimensionalArray board = initBoard();
    setInitiative(1);
    gameLoop(board, singleModeMove, singleModeMove, 1);
}

void doubleModeHandler() {
    setInitiative(chooseInitiative());
//    initiative = chooseInitiative();
    int difficulty = chooseDifficulty();
    twoDimensionalArray board = initBoard();
    roundHandler AINext = difficulty == 1 ? stupidAINext : geniusAINext;
    if (getInitiative() == 1) {
        gameLoop(board, singleModeMove, AINext, HUMAN);
    } else if (getInitiative() == 2) {
        gameLoop(board, AINext, singleModeMove, COMPUTER);
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
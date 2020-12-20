#include "control.h"
#include "ui.h"
#include "AI.h"
#include "board.h"

#include <stdbool.h>

bool singleModeMove(twoDimensionalArray board, int player) {
    Position position = askNext(player);
    putChess(board, player, position.x, position.y);
    return checkWinOrNotAtPosition(board, position.x, position.y, player);
}

void gameLoop(twoDimensionalArray board, roundHandler sente, roundHandler gote, int player) {
   bool initiative = true, win = false;
   while (true) {
       showTablet(board);
       if (initiative) {
           win = sente(board, player);
       } else {
           win = gote(board, player);
       }
       if (win) {
           printResult(player);
           break;
       }
       initiative = !initiative;
       player = reverseRole(player);
   }
}

void singleModeHandler() {
    twoDimensionalArray board = initBoard();
    gameLoop(board, singleModeMove, singleModeMove, 1);
}

void doubleModeHandler() {
    int initiative = chooseInitiative(), difficulty = chooseDifficulty();
    twoDimensionalArray board = initBoard();
    roundHandler AINext = difficulty == 1 ? stupidAINext : geniusAINext;
    if (initiative == 1) {
        gameLoop(board, singleModeMove, AINext, HUMAN);
    } else if (initiative == 2) {
        gameLoop(board, AINext, singleModeMove, COMPUTER);
    }
}

//void singleModeHandler() {
//    int difficulty = chooseDifficulty();
//    if (difficulty == 1) {
//        while (1) {
//            if (stupidAINext()) {
//                printResult(1);
//                break;
//            }
//            if (askNext(2)) {
//                printResult(2);
//                break;
//            }
//        }
//    } else if (difficulty == 2) {
//        while (1) {
//            if (geniusAINext()) {
//                printResult(1);
//                break;
//            }
//            if (askNext(2)) {
//                printResult(2);
//                break;
//            }
//        }
//    }
//}
//
//void doubleModeHandler() {
//    puts("欢迎来到双人对战模式");
//    while (1) {
//        if (askNext(1)) {
//            printResult(1);
//            break;
//        }
//        if (askNext(2)) {
//            printResult(2);
//            break;
//        }
//    }
//}

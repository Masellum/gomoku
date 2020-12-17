#include "ui.h"
#include "AI.h"
#include "board.h"
#include "control.h"

#include <stdio.h>




int main(void)
{
    printHello();
    int mode = startGame();
    if (mode == 1) {
        singleModeHandler();
    } else if (mode == 2) {
        doubleModeHandler();
    } else {
        // TODO: Show warning and ask player to select again
    }
    int player = chooseInitiative();
    while (1) {
        int win = startRound(player);
        if (win) {
            printResult(player);
            break;
        }
        player = reverseRole(player);
    }
    printGoodbye();
    return 0;
}
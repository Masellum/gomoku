#include "ui.h"
#include "AI.h"
#include "board.h"
#include "control.h"

#include <stdio.h>

int main(void) {
    printHello();
    while (true) {
        int mode = startGame();
        if (mode == 1) {
            singleModeHandler();
        } else if (mode == 2) {
            doubleModeHandler();
        } else {
            // TODO: Show warning and ask player to select again
        }
        if (!askReplay()) {
            break;
        }
    }
    printGoodbye();
    return 0;
}
#include "ui.h"
#include "AI.h"
#include "control.h"

int main(void) {
    printHello();
    while (true) {
        int mode = startGame();
        if (mode == 1) {
            singleModeHandler();
        } else if (mode == 2) {
            doubleModeHandler();
        } else {
            sendMessage("输入不合法！请重新选择：");
            continue;
        }
        if (!askReplay()) {
            break;
        }
    }
    printGoodbye();
    return 0;
}
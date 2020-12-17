#include "ui.h"
#include "AI.h"
#include "board.h"

#include <stdio.h>

int PutChess(int player, int a, int b);//在坐标为（a，b）的位置放下一颗棋子,并返回是否赢下比赛
int Win(int a, int b);//检查在坐标为（a, b）的位置放下棋子后是否能获胜
int TabletFullCheck(void);//检查棋盘是否填满
void Record(char *type, int player, int a, int b);//记录在（a，b）位置下了一颗棋子
void Regret(void);//撤销上一步操作
int StupidAINext(void);//简单AI下棋子,并返回是否赢下比赛
int GeniusAINext(void);//困难AI下棋子,并返回是否赢下比赛
void Surrender(int player);//用户投降
int CheckChess(int a, int b);//返回在（a，b）落子是否符合规范，如果不符合，打印错误信息



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
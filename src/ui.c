#include "ui.h"
#include "AI.h"
#include "board.h"
#include "control.h"

#include <stdio.h>

int startGame(void) {
    puts("请选择单机对战AI模式(输入1)或双人对战模式(输入2)");
    int mode;
    scanf("%d", &mode);
    if (mode == 1) singleModeHandler();
    else doubleModeHandler();
}

int chooseDifficulty() {
    GetDifficulty:
    puts("请选择AI难度：简单(1),困难(2)");
    int ret;
    scanf("%d", &ret);
    if (ret != 1 && ret != 2) goto GetDifficulty;
    return ret;
}

Position askNext(int player) {
    printf("当前执棋：");
    if (player == 1)printf("白棋\n");
    else printf("黑棋\n");
    Ask:
    puts("轮到你了！请选择以下几种操作之一：");
    puts("1. 下棋");
    puts("2. 悔棋");
    puts("3. 认输");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        GetChess:
        puts("请输入下棋的坐标,两坐标用空格隔开：");
        int a, b;
        scanf("%d%d", &a, &b);
        if (!checkPositionAvailable(a, b)) goto GetChess;
        Position ret = {a, b};
        return ret;
    } else if (choice == 2) {
        puts("你确认要悔棋吗？确认请输入1");
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 1) Regret();
        else goto Ask;
    } else if (choice == 3) {
        puts("你确认要认输吗？确认请输入1");
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 1) Surrender(player);
        else goto Ask;
    } else {
        puts("输入不合法！");
        goto Ask;
    }
}

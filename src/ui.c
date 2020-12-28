#include "ui.h"
#include "AI.h"
#include "board.h"
#include "control.h"

#include <stdio.h>
//#include <time.h>


void printHello() {
    puts("欢迎来到趣味横生、老少皆宜、可以提高智力、让你走上人生巅峰的五子棋游戏！");
}

int startGame() {
    puts("请选择单机对战AI模式(输入1)或双人对战模式(输入2)");
    int mode;
    scanf("%d", &mode);
    return mode;
}

int chooseDifficulty() {
    int ret;
    while (true) {
        puts("请选择AI难度：简单(1),困难(2)");
        scanf("%d", &ret);
        if (ret != 1 && ret != 2) {
            puts("请输入正确的数字！");
        } else break;
    }
    return ret;
}

int chooseInitiative() {
    int flag;

    puts("请选择先后手：");
    puts("先手请输入\"1\"，后手请输入\"2\"");

    scanf("%d", &flag);

    if (flag == 1)
        return 2;
    else if (flag == 2)
        return 1;
    else return 0;
}


void showTablet(int board[15][15]) {
    printf("    ");
    for (int i = 1; i <= 15; i++)
        printf("%-4d", i);
    printf("\n\n");
    for (int i = 0; i < 15; i++) {
        printf("%2d  ", i + 1);
        for (int j = 0; j < 14; j++) {
            printf("%s==", transformChessPieces(board[i][j]));
        }
        printf("%s\n", transformChessPieces(board[i][14]));
        if (i == 14) {
            break;
        }
        printf("  ");
        for (int j = 1; j <= 15; j++)
            printf("  ‖");
        printf("\n");
    }
}

void sendMessage(char message[]) {
    printf("%s\n", message);
}

Position askNext(int board[15][15], int player) {
    printf("当前执棋：");
    if (player == getInitiative()) printf("黑棋\n");
    else printf("白棋\n");
    while (true) {
        puts("轮到你了！请选择以下几种操作之一：");
        puts("1. 下棋");
        puts("2. 悔棋");
        puts("3. 认输");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            int a, b;
            while (true) {
                puts("请输入下棋的坐标,两坐标用空格隔开：");
                scanf("%d%d", &a, &b);
                if (!checkPositionAvailable(board, a, b)) {
                    puts("坐标不合法！请重新输入：");
                } else break;
            }
            Position ret = {a - 1, b - 1, player};
            return ret;
        } else if (choice == 2) {
            puts("你确认要悔棋吗？确认请输入1");
            int tmp;
            scanf("%d", &tmp);
            if (tmp == 1) Regret();
            else continue;
        } else if (choice == 3) {
            puts("你确认要认输吗？确认请输入1");
            int tmp;
            scanf("%d", &tmp);
            if (tmp == 1) Surrender(player);
            else continue;
        } else {
            puts("输入不合法！");
            continue;
        }
    }
}

//void showTime(time_t beginTime, time_t endTime) {
//    double timeDifference = difftime(endTime, beginTime);
//    printf("游戏已经进行了 %d 秒", (int) timeDifference);
//}

void printResult(int player) {
    if (player == getInitiative())
        puts("恭喜黑棋获胜！");
    else
        puts("恭喜白棋获胜！");
}

bool askReplay() {
    puts("游戏已经结束，请问您是否想要再来一局？");
    puts("是请输入1， 否请输入0");
    int res;
    scanf("%d", &res);
    return (bool) (res);
}

void printGoodbye() {
    puts("感谢游玩，下次再来！");
}
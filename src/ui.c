#include "ui.h"
#include "AI.h"
#include "board.h"
#include "control.h"

#include <stdio.h>

void printHello() {
    puts("欢迎来到趣味横生、老少皆宜、可以提高智力、让你走上人生巅峰的五子棋游戏！");
}

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

int chooseInitiative() {
    int flag;
    
    puts("请选择先后手：");
    puts("先手请输入\"1\"，后手请输入\"2\"");
    
    scanf("%d", &flag);
    
    if(flag == 1)
        return 2;
    else if(flag == 2)
        return 1;
}

char transformChessPieces(int flag) {
    if(flag == 0)
        return '＋' ;
    else if(flag == initiative) 
        return '●';
    else
        return '○';
}

void showTablet(int board[15][15]) {
    int i, j; 
    
    printf("    ");
    
    for(i = 1; i <= 15; i++)
        printf("%-4d", i);
        
    printf("\n\n");
    
    for(i = 1; i <= 15; i++)
    {
        printf("%2d  ", i);
        
        for(j = 1; j <= 14; j++)
            printf("%c==", TransformChessPieces(board[i][j]));
            
        printf("%c\n", TransformChessPieces(board[i][15]));
        
        if(i == 15)
            break;
        
        printf("  ");
        
        for(j = 1; j <= 15; j++)
            printf("  ‖");
        
        printf("\n");
    }
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
        Position ret = {player, a, b};
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

void printResult(int player) {
    if(player == initiative)
        puts("恭喜黑棋获胜！");
    else
        puts("恭喜白棋获胜！");
}

void printGoodbye() {
    puts("感谢游玩，下次再来！");
}
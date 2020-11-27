#include <stdio.h>

void PrintHello(void);//初始化，并打印欢迎信息
void StartGaming(void);//开始游戏，询问用户选择单人or双人模式 done
void SingleModeHandler(void);//单人模式处理函数 done
void DoubleModeHandler(void);//双人模式处理函数 done
int ChooseDifficulty(void);//询问用户选择难度 done
void ShowTablet(void);//显示当前的棋盘（15*15）
int AskNext(int player);//请求用户执行操作，如果下棋,放置棋子到棋盘中,并返回是否赢下比赛 done
int PutChess(int player, int a, int b);//在坐标为（a，b）的位置放下一颗棋子,并返回是否赢下比赛 
int Win(int a, int b);//检查在坐标为（a, b）的位置放下棋子后是否能获胜
int TabletFullCheck(void);//检查棋盘是否填满
void Record(char *type, int player, int a, int b);//记录在（a，b）位置下了一颗棋子
void Regret(void);//撤销上一步操作
int StupidAINext(void);//简单AI下棋子,并返回是否赢下比赛
int GeniusAINext(void);//困难AI下棋子,并返回是否赢下比赛
void ShowTime(void);//显示已下时间
void Surrender(int player);//用户投降
void PrintResult(int player);//打印胜负信息
void PrintGoodbye(void);//提示再见信息，询问是否重新开始
int CheckChess(int a, int b);//返回在（a，b）落子是否符合规范，如果不符合，打印错误信息    

void StartGaming(void)
{
    puts("请选择单机对战AI模式(输入1)或双人对战模式(输入2)");
    int mode;
    scanf("%d", &mode);
    if(mode == 1) SingleModeHandler();
    else DoubleModeHandler();
}

int ChooseDifficulty()
{
GetDifficulty:
    puts("请选择AI难度：简单(1),困难(2)");
    int ret;
    scanf("%d", &ret);
    if(ret != 1 && ret != 2) goto GetDifficulty;
    return ret;
}

void SingleModeHandler()
{
    int difficulty = ChooseDifficulty();
    if(difficulty == 1)
    {
        while(1)
        {
            if(StupidAINext()) {PrintResult(1);break;}
            if(AskNext(2)) {PrintResult(2);break;}
        }
    }
    else if(difficulty == 2)
    {
        while(1)
        {
            if(GeniusAINext()) {PrintResult(1);break;}
            if(AskNext(2)) {PrintResult(2);break;}
        }
    }
}

void DoubleModeHandler()
{
    puts("欢迎来到双人对战模式");
    while(1)
    {
        if(AskNext(1)) {PrintResult(1);break;}
        if(AskNext(2)) {PrintResult(2);break;}
    }
}

int AskNext(int player)
{
    printf("当前执棋：");
    if(player == 1)printf("白棋\n");
    else printf("黑棋\n");
Ask:
    puts("轮到你了！请选择以下几种操作之一：");
    puts("1. 下棋");
    puts("2. 悔棋");
    puts("3. 认输");
    int choice;
    scanf("%d", &choice);
    if(choice == 1)
    {
    GetChess:
        puts("请输入下棋的坐标,两坐标用空格隔开：");
        int a, b;
        scanf("%d%d", &a, &b);
        if(!CheckChess(a, b)) goto GetChess;
        int ret = PutChess(player, a, b);
        Record("PutChess", player, a, b);
        return ret;
    }
    else if(choice == 2)
    {
        puts("你确认要悔棋吗？确认请输入1");
        int tmp;
        scanf("%d", &tmp);
        if(tmp == 1) Regret();
        else goto Ask;
    }
    else if(choice == 3)
    {
        puts("你确认要认输吗？确认请输入1");
        int tmp;
        scanf("%d", &tmp);
        if(tmp == 1) Surrender(player);
        else goto Ask;
    }
    else
    {
        puts("输入不合法！");
        goto Ask;
    }
}

int main(void)
{
    PrintHello();
    StartGaming();
    PrintGoodbye();
    return 0;
}
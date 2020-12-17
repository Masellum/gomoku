#ifndef _BOARD_H
#define _BOARD_H

int PutChess(int player, int a, int b);//在坐标为（a，b）的位置放下一颗棋子,并返回是否赢下比赛
int Win(int a, int b);//检查在坐标为（a, b）的位置放下棋子后是否能获胜
int TabletFullCheck(void);//检查棋盘是否填满
void Record(char *type, int player, int a, int b);//记录在（a，b）位置下了一颗棋子
int CheckChess(int a, int b);//返回在（a，b）落子是否符合规范，如果不符合，打印错误信息

#endif // _BOARD_H

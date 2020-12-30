# Gomoku 五子棋

简单的五子棋小游戏，支持单人与 AI 对战（分为普通/困难两个等级），双人对战两种玩法。

## Compile 编译
```shell
# In the root directory of the project
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../src # Unix
# Or
cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ../src # MinGW
make
./gomoku

# Or use bare gcc if cmake is not available
gcc src/*.c -Isrc/include -o gomoku
./gomoku
```

## Features 功能介绍：

1. 主页面： 进入后，用户可以选择单人对战/多人对战。如果选择单人对战，则可以继续选择普通/困难两个等级。

2. 程序主页面显示：

   - 整个棋盘

   - 当前执棋：黑/白
   - 下棋记录：黑棋 在 (a, b) 处下子 / 白棋获胜

3. 单人对战页面：用户可以执行以下操作：

   - 实现在（a，b）位置下一颗棋子
   - 认输

   双人对战页面：用户可以执行以下操作：

   - 实现在（a，b）位置下一颗棋子
   - 认输

4. 函数接口：

   - ``void showTablet()`` 在屏幕上打印出当前的棋盘
   - ``void communicateWithAI()`` 询问 AI 的下一步或者告知 AI 玩家的动作
   - ``void putChess(int board[15][15], int a, int b)`` 在坐标为（a，b）的位置放下一颗棋子
   - ``bool checkWinOrNot(int a, int b)``检查在坐标为（a, b）的位置放下棋子后是否能获胜
   - ``bool checkIfBoardIsFull(void)`` 检查棋盘是否填满
   - ``void recordPutChess(int a, int b)``记录在（a，b）位置下了一颗棋子
    
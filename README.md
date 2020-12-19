# 大作业README

简单的五子棋小游戏，支持单人对战机器（分为普通/困难两个等级），双人对战两种玩法。



功能介绍：

1. 主页面： 进入后，用户可以选择单人对战/多人对战。如果选择单人对战，则可以继续选择普通/困难两个等级。

2. 程序主页面显示：

   - 整个棋盘

   - 当前执棋：黑/白
   - 已用时间：x分x秒
   - 下棋记录：黑棋 在 (a, b) 处下子 / 黑棋悔棋 / 白棋获胜

3. 单人对战页面：用户可以执行以下操作：

   - 通过键盘上下移动，实现在（a，b）位置下一颗棋子
   - 悔棋（撤销到用户上一次下棋）
   - 认输

   双人对战页面：用户可以执行以下操作：

   - 通过键盘上下移动，实现在（a，b）位置下一颗棋子
   - 悔棋（撤销到用户上一次下棋）
   - 认输

4. 函数接口：

   - ``void showTablet()`` 在屏幕上打印出当前的棋盘
   - ``void AINext()`` AI进行下一步下棋
   - ``void putChess(int board[15][15], int a, int b)`` 在坐标为（a，b）的位置放下一颗棋子
   - ``bool checkWinOrNot(int a, int b)``检查在坐标为（a, b）的位置放下棋子后是否能获胜
   - ``bool checkIfBoardIsFull(void)`` 检查棋盘是否填满
   - ``void recordPutChess(int a, int b)``记录在（a，b）位置下了一颗棋子

5. 代码规范：

   - 除非有超过4000000的数组，否则原则上**不允许**使用全局变量，变量应通过指针或参数的方式进行传递。

   - 代码缩进应遵循以下格式：

     - 定义函数/``if``/``for``/``while``时，在函数名后立即接上括号，括号后换行打大括号

       ```c
       int main(void)
       {
           return 0;
       }//规范
       int main() {
           return 0;
       }//不规范
       int main(){
           return 0;
       }//不规范
       ```

       在运算符号前后/分号/逗号/冒号后应当打空格，行末分号不打空格

       ```c
       for(int i = 0; i <= 10; i++)
       {
           a[i] = a[i - 1] + a[i - 2];
           printf("i: %d %d\n", i, a[i]);
       }//规范
       for(int i=0;i<=10;i++)
       {
           a[i]=a[i-1]+a[i-2];
           printf("%d,%d",i,a[i]);
       }//不规范
       ```

       相同层级的代码块应为同一缩进，子层级比父层级多一个tab（或四个空格）的缩进块。在大括号前后不得写代码。

       ```c
       #include<stdio.h>
       int main()
       {float f;   
        double d;        
        f=123456789.345;
        	d=123456789.345;
        if(f>1)
        {f-=d;
         f+=d;}
        printf("f=%f\nd=%f\n",f,d);
        return 0;
       }//极差的代码习惯
       
       #include<stdio.h>
       
       int main()
       {
           float f;
           double d;
           f = 123456789.345;
           d = 123456789.345;
           if (f > 1)
           {
               f -= d;
               f += d;
           }
           printf("f=%f\nd=%f\n", f, d);
           return 0;
       }//正确的代码风格
       ```

       除非``if/for``语句的子代码块只有一行，必须打大括号。如果结构清晰，可以将大括号压到一行，前置一个空格。``if``语句即使只有一行也需要换行tab显示其层级。``for``循环和数组下标都从**0**开始。选择分支不使用``switch``，循环不使用``do-while``。

       ```c
       if(i <= 1)
       {
           j--;
           i++;
           printf("%d ", i);
       }//正确的代码风格
       
       if(i <= 1)
           printf("%d ", i);
       //正确的代码风格
       ```

       任何独立的功能都要单独做成函数代码块，主函数不得执行除函数外的功能，一个函数包含的功能不得过多。

       ```c
       int main(void)
       {
           int n = read();
           MakeTable(n);
           ShowTable();
           return 0;
       }
       //好的代码习惯
       
       int main(void)
       {
           int n;
           scanf("%d", n);
           for(int i = 1; i <= n; i++)
           {
               for(int j = 1; j <= i; j++)
               {
                   tab[i][j] = i;
               }
           }
           for(int i = 1; i <= n; i++)
           {
               for(int j = 1; j <= i; j++)
               {
                   printf("%d ", tab[i][j]);
               }
           }
       }//不好的代码习惯
       ```

       函数/变量命名：**不允许**使用拼音，**不允许**使用``a``,``b``,``x1``,``x2``,``foo()``等无实际意义的命名方式，不允许使用``check()`` ``go()``含糊其词/多义/指代不明的命名方式。推荐使用驼峰命名，即用单词描述函数的作用/变量的内容，将每个单词的首字母大写。

       ```c
       int ChessTablet[40][40];//棋盘
       bool CheckTabletFull(int *ChessTablet)//检查棋盘是否已满
       {
           return ...;
       }
       ```

       在每个函数/变量定义后都应当注释标明其用途。

       
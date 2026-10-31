#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define W 20   // 游戏区域宽
#define H 15   // 游戏区域高

int snakeX[100];  // 存蛇每一节的x坐标
int snakeY[100];  // 存蛇每一节的y坐标
int length;       // 蛇的长度
int foodX, foodY; // 食物坐标
int direction;    // 方向 1右 2左 3上 4下
int gameEnd;      // 游戏是否结束

// 初始化游戏
void startGame()
{
    length = 3;
    gameEnd = 0;
    direction = 1; // 默认一开始向右走

    // 蛇初始位置，在屏幕中间
    snakeX[0] = W / 2;
    snakeY[0] = H / 2;
    snakeX[1] = W / 2 - 1;
    snakeY[1] = H / 2;
    snakeX[2] = W / 2 - 2;
    snakeY[2] = H / 2;

    // 随机生成食物
    srand((unsigned)time(NULL));
    foodX = rand() % W;
    foodY = rand() % H;
}

// 画画面，墙、蛇、食物
void draw()
{
    system("cls"); // 清屏，刷新画面

    // 打印上墙
    for (int i = 0; i < W + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    // 逐行打印游戏内容
    for (int y = 0; y < H; y++)
    {
        printf("#"); // 左边墙
        for (int x = 0; x < W; x++)
        {
            if (x == snakeX[0] && y == snakeY[0])
            {
                printf("O"); // 蛇头
            }
            else if (x == foodX && y == foodY)
            {
                printf("F"); // 食物
            }
            else
            {
                int isBody = 0;
                // 判断是不是蛇身
                for (int i = 1; i < length; i++)
                {
                    if (snakeX[i] == x && snakeY[i] == y)
                    {
                        printf("o");
                        isBody = 1;
                        break;
                    }
                }
                if (isBody == 0)
                {
                    printf(" ");
                }
            }
        }
        printf("#\n"); // 右边墙
    }

    // 打印下墙
    for (int i = 0; i < W + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    printf("分数：%d", length - 3);
}

// 接收键盘按键 WASD
void keyControl()
{
    if (_kbhit()) // 检测有没有按键按下，不用回车
    {
        char ch = _getch();
        if (ch == 'd' && direction != 2)
            direction = 1;
        if (ch == 'a' && direction != 1)
            direction = 2;
        if (ch == 'w' && direction != 4)
            direction = 3;
        if (ch == 's' && direction != 3)
            direction = 4;
        if (ch == 'x') // 按x退出游戏
            gameEnd = 1;
    }
}

// 蛇移动、碰撞判断、吃食物
void snakeMove()
{
    // 蛇身体跟着往前挪，从最后一节往前赋值（大一常讲的逻辑）
    for (int i = length - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // 蛇头移动
    if (direction == 1) snakeX[0]++;
    if (direction == 2) snakeX[0]--;
    if (direction == 3) snakeY[0]--;
    if (direction == 4) snakeY[0]++;

    // 撞墙判断
    if (snakeX[0] < 0 || snakeX[0] >= W || snakeY[0] < 0 || snakeY[0] >= H)
    {
        gameEnd = 1;
    }

    // 撞到自己身体
    for (int i = 1; i < length; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            gameEnd = 1;
        }
    }

    // 吃到食物，变长，重新刷食物
    if (snakeX[0] == foodX && snakeY[0] == foodY)
    {
        length++;
        foodX = rand() % W;
        foodY = rand() % H;
    }
}

int main()
{
    startGame();
    // 游戏主循环，没结束就一直跑
    while (gameEnd == 0)
    {
        draw();
        keyControl();
        snakeMove();
        Sleep(200); // 停顿一下，控制蛇速度，数字越大越慢
    }
    printf("\n游戏结束！");
    return 0;
}

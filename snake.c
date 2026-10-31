#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define W 20   
#define H 15   

int snakeX[100];  
int snakeY[100];  
int length;       
int foodX, foodY; 
int direction;    
int gameEnd;     

void startGame()
{
    length = 3;
    gameEnd = 0;
    direction = 1; 

    snakeX[0] = W / 2;
    snakeY[0] = H / 2;
    snakeX[1] = W / 2 - 1;
    snakeY[1] = H / 2;
    snakeX[2] = W / 2 - 2;
    snakeY[2] = H / 2;

    srand((unsigned)time(NULL));
    foodX = rand() % W;
    foodY = rand() % H;
}

void draw()
{
    system("cls"); 

    for (int i = 0; i < W + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    for (int y = 0; y < H; y++)
    {
        printf("#"); 
        for (int x = 0; x < W; x++)
        {
            if (x == snakeX[0] && y == snakeY[0])
            {
                printf("O"); 
            }
            else if (x == foodX && y == foodY)
            {
                printf("F"); 
            }
            else
            {
                int isBody = 0;
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
        printf("#\n"); 
    }

    for (int i = 0; i < W + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    printf("分数：%d", length - 3);
}

void keyControl()
{
    if (_kbhit()) 
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
        if (ch == 'x') 
            gameEnd = 1;
    }
}

void snakeMove()
{
    for (int i = length - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
 
    if (direction == 1) snakeX[0]++;
    if (direction == 2) snakeX[0]--;
    if (direction == 3) snakeY[0]--;
    if (direction == 4) snakeY[0]++;

    if (snakeX[0] < 0 || snakeX[0] >= W || snakeY[0] < 0 || snakeY[0] >= H)
    {
        gameEnd = 1;
    }

    for (int i = 1; i < length; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            gameEnd = 1;
        }
    }

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
    while (gameEnd == 0)
    {
        draw();
        keyControl();
        snakeMove();
        Sleep(200); 
    }
    printf("\n游戏结束！");
    return 0;
}

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

class common_elements
{
public:
    int x;
    int y;
};

class Snake: public common_elements
{
};

class Tail
{
public:
    int x[100];
    int y[100];
    int num = 0;
};

class Fruit: public common_elements
{
};

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

class game_manager
{
public:
    bool gameOver;
    const int width = 40;
    const int height = 20;
    int score;

    std::vector<common_elements*> game_objects_;

    Fruit Fruit;
    Snake Snake;
    Tail Tail;

    game_manager();
   ~game_manager();

    void Setup();
    void Draw();
    void Input();
    void Logic();
};

game_manager::game_manager():
    game_objects_(std::vector<common_elements*> ())
{}

game_manager::~game_manager()
{}

void game_manager::Setup()
{
    gameOver = false;
    dir = STOP;
    Snake.x = width / 2;
    Snake.y = height / 2;
    Fruit.x = rand() % width;
    Fruit.y = rand() % height;
    score = 0;
}

void game_manager::Draw()
{
    system("cls"); //system("clear");
    for (int i = 0; i < width+2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            if (i == Snake.y && j == Snake.x)
                std::cout << "O";
            else if (i == Fruit.y && j == Fruit.x)
                std::cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < Tail.num; k++) {
                    if (Tail.x[k] == j && Tail.y[k] == i) {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }


            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < width+2; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score:" << score << std::endl;
}

void game_manager:: Input()
{
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
            break;
            case 'd':
                dir = RIGHT;
            break;
            case 'w':
                dir = UP;
            break;
            case 's':
                dir = DOWN;
            break;
            case 'x':
                gameOver = true;
            break;
        }
    }
}

void game_manager:: Logic()
{
    int prevX = Tail.x[0];
    int prevY = Tail.y[0];
    int prev2X, prev2Y;
    Tail.x[0] = Snake.x;
    Tail.y[0] = Snake.y;
    for (int i = 1; i < Tail.num; i++) {
        prev2X = Tail.x[i];
        prev2Y = Tail.y[i];
        Tail.x[i] = prevX;
        Tail.y[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            Snake.x--;
        break;
        case RIGHT:
            Snake.x++;
        break;
        case UP:
            Snake.y--;
        break;
        case DOWN:
            Snake.y++;
        break;
        default:
        break;
    }

    /*if (x > width || x < 0 || y > height || y < 0) //если столкновение со стенками запрещено
        gameOver = true;*/

    if (Snake.x >= width) Snake.x = 0; else if (Snake.x < 0) Snake.x = width - 1;
    if (Snake.y >= height) Snake.y = 0; else if (Snake.y < 0) Snake.y = height - 1;

    for (int i = 0; i < Tail.num; i++)
        if (Tail.x[i] == Snake.x && Tail.y[i] == Snake.y)
            gameOver = true;

    if (Snake.x == Fruit.x && Snake.y == Fruit.y) {
        score += 10;
        Fruit.x = rand() % width;
        Fruit.y = rand() % height;
        Tail.num++;
    }
}

int main()
{
    game_manager manager;
    manager.Setup();

    while (!manager.gameOver)  {
        manager.Draw();
        manager.Input();
        manager.Logic();
        Sleep(10); //sleep(10);
    }
    return 0;
}
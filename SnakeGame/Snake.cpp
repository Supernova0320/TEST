#include<iostream>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
using namespace std;

typedef struct Position
{
	int x;
	int y;
}Pos;

class Food
{
public:
	//随机生成食物坐标
	void CreateFood();

	//画出食物
	void DrawFood();

	Pos pf;//食物坐标
	bool exi = false;//是否存在食物
};

class Snake
{
public:
	//初始化蛇
	Snake();

	//画出蛇
	void DrawSnake();

	//蛇移动
	void Move();

	//游戏结束
	void Over();

	//吃食物（参数为吃食物时蛇尾的坐标）
	void Eat(int a,int b);

	//咬尾判定
	bool IsTB();

	Pos p[100];//坐标
	int num;//长度
	char dire;//方向
};

//获取坐标
void Getxy(int x, int y);

//生成地图
void CreateMap();

//打印分数与操作指南
void Print(Snake s);

//隐藏光标
void HideCursor();

//开始界面
void Start();

//暂停
void Pause();

int main(int argc, char *argv[])
{
	Snake snake;
	Food food;
	HideCursor();
	Start();
	char input = _getch();
	if (input == '1')
	{
		while (1)
		{
			CreateMap();
			Print(snake);
			snake.DrawSnake();
			if (food.exi == false)
			{
				food.CreateFood();
			}
			food.DrawFood();
			if (_kbhit())
			{
				snake.dire = _getch();
			}
			if (food.pf.x == snake.p[0].x && food.pf.y == snake.p[0].y)
			{
				int a = snake.p[snake.num - 1].x;
				int b = snake.p[snake.num - 1].y;
				snake.Move();
				snake.Eat(a, b);
				food.exi = false;
			}
			else
			{
				snake.Move();
			}
			Sleep(50);
			if (snake.p[0].x == 0 || snake.p[0].y == 0 || snake.p[0].x == 80 || snake.p[0].y == 40)
			{
				snake.Over();
				break;
			}
			if (snake.IsTB())
			{
				snake.Over();
				break;
			}
		}
	}
	else if (input == '2')
	{
		while (1)
		{
			CreateMap();
			Print(snake);
			snake.DrawSnake();
			if (food.exi == false)
			{
				food.CreateFood();
			}
			food.DrawFood();
			if (_kbhit())
			{
				snake.dire = _getch();
			}
			if (food.pf.x == snake.p[0].x && food.pf.y == snake.p[0].y)
			{
				int a = snake.p[snake.num - 1].x;
				int b = snake.p[snake.num - 1].y;
				snake.Move();
				snake.Eat(a, b);
				food.exi = false;
			}
			else
			{
				snake.Move();
			}
			Sleep(50);
			if (snake.p[0].x == 0)
			{
				snake.p[0].x = 80;
			}
			else if (snake.p[0].x == 80)
			{
				snake.p[0].x = 0;
			}
			else if (snake.p[0].y == 0)
			{
				snake.p[0].y = 40;
			}
			else if (snake.p[0].y == 40)
			{
				snake.p[0].y = 0;
			}
			if (snake.IsTB())
			{
				snake.Over();
				break;
			}
		}
	}
	else if (input == '3')
	{
		while (1)
		{
			CreateMap();
			Print(snake);
			snake.DrawSnake();
			if (food.exi == false)
			{
				food.CreateFood();
			}
			food.DrawFood();
			if (_kbhit())
			{
				snake.dire = _getch();
			}
			if (food.pf.x == snake.p[0].x && food.pf.y == snake.p[0].y)
			{
				int a = snake.p[snake.num - 1].x;
				int b = snake.p[snake.num - 1].y;
				snake.Move();
				snake.Eat(a, b);
				food.exi = false;
			}
			else
			{
				snake.Move();
			}
			Sleep(50);
			if (snake.p[0].x == 0)
			{
				snake.p[0].x = 80;
			}
			else if (snake.p[0].x == 80)
			{
				snake.p[0].x = 0;
			}
			else if (snake.p[0].y == 0)
			{
				snake.p[0].y = 40;
			}
			else if (snake.p[0].y == 40)
			{
				snake.p[0].y = 0;
			}
		}
	}
	Getxy(0, 41);
	return 0;
}

//获取坐标
void Getxy(int x, int y)
{
	COORD pos = {x, y};
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, pos);
}

//生成地图
void CreateMap()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	system("mode con:cols=120 lines=50");//改变窗口大小
	for (int i = 0; i <= 78; i += 2)
	{
		Getxy(i, 0);
		cout << "■";
	}
	for (int i = 0; i <= 40; i++)
	{
		Getxy(0, i);
		cout << "■";
	}
	for (int i = 2; i <= 80; i += 2)
	{
		Getxy(i, 40);
		cout << "■";
	}
	for (int i = 0; i <= 40; i++)
	{
		Getxy(80, i);
		cout << "■";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//初始化蛇
Snake::Snake()
{
	for (int i = 0; i < 4; i++)
	{
		p[3 - i].x = 2 * i + 14;
		p[3 - i].y = 14;
	}
	num = 4;
	dire = 'D';
}

//画出蛇
void Snake::DrawSnake()
{
	for (int i = 0; i < num; i++)
	{
		Getxy(p[i].x, p[i].y);
		cout << "■";
	}
}

//蛇移动
void Snake::Move()
{
	if (this->dire == 'W')
	{
		for (int i = num; i > 0; i--)
		{
			p[i].x = p[i - 1].x;
			p[i].y = p[i - 1].y;
		}
		p[0].y--;
	}
	else if (this->dire == 'S')
	{
		for (int i = num; i > 0; i--)
		{
			p[i].x = p[i - 1].x;
			p[i].y = p[i - 1].y;
		}
		p[0].y++;
	}
	else if (this->dire == 'A')
	{
		for (int i = num; i > 0; i--)
		{
			p[i].x = p[i - 1].x;
			p[i].y = p[i - 1].y;
		}
		p[0].x -= 2;

	}
	else if (this->dire == 'D')
	{
		for (int i = num; i > 0; i--)
		{
			p[i].x = p[i - 1].x;
			p[i].y = p[i - 1].y;
		}
		p[0].x += 2;

	}
}

//游戏结束
void Snake::Over()
{
	system("cls");
	cout << "游戏结束!" << endl << "您的分数为:" << 10 * (num - 4) << "分";
}

//随机生成食物坐标
void Food::CreateFood()
{
	srand(time(NULL));
	while (1)
	{
		int a, b;
		a = rand() % 78 + 2;
		b = rand() % 38 + 2;
		if (a % 2 == 0 && b % 2 == 0)
		{
			pf.x = a;
			pf.y = b;
			break;
		}
	}
	this->exi = true;
}

//画出食物
void Food::DrawFood()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
	Getxy(pf.x, pf.y);
	cout << "◆";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE);
}

//吃食物（参数为吃食物时蛇尾的坐标）
void Snake::Eat(int a,int b)
{
	p[num].x = a;
	p[num].y = b;
	this->num++;
}

//咬尾判定
bool Snake::IsTB()
{
	for (int i = 1; i < num; i++)
	{
		if (p[0].x == p[i].x && p[0].y == p[i].y)
		{
			return true;
		}
	}
	return false;
}

//打印分数与操作指南
void Print(Snake s)
{
	Getxy(86, 16);
	cout << "================================";
	Getxy(86, 24);
	cout << "================================";
	for (int i = 1; i <= 7; i++)
	{
		Getxy(86, 16 + i);
		cout << "=";
		Getxy(117, 16 + i);
		cout << "=";
	}
	Getxy(96, 20);
	cout << "当前分数:" << 10 * (s.num - 4) << "分";
}

//隐藏光标
void HideCursor()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}

//开始界面
void Start()
{
	system("mode con:cols=120 lines=50");//改变窗口大小
	for (int i = 0; i < 60; i++)
	{
		Getxy(31 + i, 6);
		cout << "=";
		Getxy(31 + i, 12);
		cout << "=";
		Getxy(31 + i, 35);
		cout << "=";
	}
	for (int i = 7; i < 12; i++)
	{
		Getxy(31, i);
		cout << "=";
		Getxy(90, i);
		cout << "=";
	}
	for (int i = 13; i < 35; i++)
	{
		Getxy(31, i);
		cout << "=";
		Getxy(90, i);
		cout << "=";
	}
	Getxy(55, 8);
	cout << "欢迎来到贪吃蛇";
	Getxy(52, 10);
	cout << "请选择难度（输入数字）";
	Getxy(57, 15);
	cout << "1.困难模式";
	Getxy(51, 16);
	cout << "（不可咬尾，不可穿墙）";
	Getxy(57, 22);
	cout << "2.普通模式";
	Getxy(51, 23);
	cout << "（不可咬尾，可以穿墙）";
	Getxy(57, 29);
	cout << "3.无敌模式";
	Getxy(51, 30);
	cout << "（可以咬尾，可以穿墙）";
}

//暂停
void Pause()
{
	char spa = _getch();
	if(spa==' ')
	{
		system("pause");
	}
}
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
	//�������ʳ������
	void CreateFood();

	//����ʳ��
	void DrawFood();

	Pos pf;//ʳ������
	bool exi = false;//�Ƿ����ʳ��
};

class Snake
{
public:
	//��ʼ����
	Snake();

	//������
	void DrawSnake();

	//���ƶ�
	void Move();

	//��Ϸ����
	void Over();

	//��ʳ�����Ϊ��ʳ��ʱ��β�����꣩
	void Eat(int a,int b);

	//ҧβ�ж�
	bool IsTB();

	Pos p[100];//����
	int num;//����
	char dire;//����
};

//��ȡ����
void Getxy(int x, int y);

//���ɵ�ͼ
void CreateMap();

//��ӡ���������ָ��
void Print(Snake s);

//���ع��
void HideCursor();

//��ʼ����
void Start();

//��ͣ
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

//��ȡ����
void Getxy(int x, int y)
{
	COORD pos = {x, y};
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, pos);
}

//���ɵ�ͼ
void CreateMap()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	system("mode con:cols=120 lines=50");//�ı䴰�ڴ�С
	for (int i = 0; i <= 78; i += 2)
	{
		Getxy(i, 0);
		cout << "��";
	}
	for (int i = 0; i <= 40; i++)
	{
		Getxy(0, i);
		cout << "��";
	}
	for (int i = 2; i <= 80; i += 2)
	{
		Getxy(i, 40);
		cout << "��";
	}
	for (int i = 0; i <= 40; i++)
	{
		Getxy(80, i);
		cout << "��";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//��ʼ����
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

//������
void Snake::DrawSnake()
{
	for (int i = 0; i < num; i++)
	{
		Getxy(p[i].x, p[i].y);
		cout << "��";
	}
}

//���ƶ�
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

//��Ϸ����
void Snake::Over()
{
	system("cls");
	cout << "��Ϸ����!" << endl << "���ķ���Ϊ:" << 10 * (num - 4) << "��";
}

//�������ʳ������
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

//����ʳ��
void Food::DrawFood()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
	Getxy(pf.x, pf.y);
	cout << "��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED| FOREGROUND_GREEN| FOREGROUND_BLUE);
}

//��ʳ�����Ϊ��ʳ��ʱ��β�����꣩
void Snake::Eat(int a,int b)
{
	p[num].x = a;
	p[num].y = b;
	this->num++;
}

//ҧβ�ж�
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

//��ӡ���������ָ��
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
	cout << "��ǰ����:" << 10 * (s.num - 4) << "��";
}

//���ع��
void HideCursor()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}

//��ʼ����
void Start()
{
	system("mode con:cols=120 lines=50");//�ı䴰�ڴ�С
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
	cout << "��ӭ����̰����";
	Getxy(52, 10);
	cout << "��ѡ���Ѷȣ��������֣�";
	Getxy(57, 15);
	cout << "1.����ģʽ";
	Getxy(51, 16);
	cout << "������ҧβ�����ɴ�ǽ��";
	Getxy(57, 22);
	cout << "2.��ͨģʽ";
	Getxy(51, 23);
	cout << "������ҧβ�����Դ�ǽ��";
	Getxy(57, 29);
	cout << "3.�޵�ģʽ";
	Getxy(51, 30);
	cout << "������ҧβ�����Դ�ǽ��";
}

//��ͣ
void Pause()
{
	char spa = _getch();
	if(spa==' ')
	{
		system("pause");
	}
}
#include"common.h"
#include<iostream>
#include<vector>
#include<Windows.h>
bool gamepause = false;
extern bool GameUnderway;
using namespace std;
////BOOL CALLBACK表示一个回调函数的返回值为布尔值
////LPARAM  //windows中的一个表示长整型的参数
//BOOL CALLBACK EnumerationWindowProc(HWND hwnd, LPARAM parametric)
//{
//	std::vector<HWND>* WindowsDesktopHandle = (std::vector<HWND>*)parametric;
//	//创建一个vector储存所有类名为WorkerW的句柄
//	char ClassName[256];
//	GetClassName(hwnd, ClassName, sizeof(ClassName));
//	//GetClassName函数需要知道ClassName缓冲区的大小，以确保它不会写入超出缓冲区边界的数据。
//	//所以使用sizeof动态获取ClassName的大小
//	if (strcmp(ClassName, "WorkerW") == 0 || strcmp(ClassName, "Progman") == 0)
//	{
//		// 找到类名为"WorkerW"的窗口，记录下来
//		//因为存在多个顶级窗口类名都为“WorkerW"的情况
//		WindowsDesktopHandle->push_back(hwnd);
//	}
//	return TRUE;
//}
//std::vector<HWND> EnumerationWindowHandle()
//{
//	std::vector<HWND>WorkerWHandle;
//	// 枚举所有顶级窗口
//	EnumWindows(EnumerationWindowProc, (LPARAM)&WorkerWHandle);
//	return WorkerWHandle;
//}
void GamePause(bool* GameOvertemp)
{
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) // 检测空格键按下
    {
        if (gamepause)
        {
            // 按下空格键，切换为继续游戏
            gamepause = false;
        }
        else
        {
            // 按下空格键，切换为暂停游戏
            gamepause = true;
            int result = MessageBox(GetDesktopWindow(), "是否继续游戏?", "暂停", MB_YESNO);
            if (result == IDYES)
            {
                gamepause = false; // 用户选择继续游戏
            }
            if (result == IDNO)
            {
                *GameOvertemp = !*GameOvertemp;
                GameUnderway = false;
            }
        }
    }
}
void GameExit(bool& XGameOver)//退出函数
{
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        XGameOver = !XGameOver;
        MessageBox(GetDesktopWindow(),"已结束游戏","提示",MB_OK);
        GameUnderway = false;
    }
}
void Drawleft(int x, int y)//画左侧的
{
	line(x + 4, y - 4, x + 20, y - 4);
	line(x + 4, y - 4, x + 4, y - 20);
	line(x + 4, y + 4, x + 20, y + 4);
	line(x + 4, y + 4, x + 4, y + 20);
}
void DrawRight(int x, int y)//right
{
	line(x - 4, y + 4, x - 20, y + 4);
	line(x - 4, y + 4, x - 4, y + 20);
	line(x - 4, y - 4, x - 4, y - 20);
	line(x - 4, y - 4, x - 20, y - 4);
}

void DrawPosition(int x, int y)
{
	Drawleft(x, y);
	DrawRight(x, y);
}

void DrawBoard()//
{

	setbkcolor(RGB(252, 215, 100));
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	line(0, 0, 0, 9 * CHESS_SIZE);
	line(8 * CHESS_SIZE, 0, 8 * CHESS_SIZE, 9 * CHESS_SIZE);
	line(3 * CHESS_SIZE, 0, 5 * CHESS_SIZE, 2 * CHESS_SIZE);
	line(5 * CHESS_SIZE, 0, 3 * CHESS_SIZE, 2 * CHESS_SIZE);
	line(3 * CHESS_SIZE, 0 + 7 * CHESS_SIZE, +5 * CHESS_SIZE, +9 * CHESS_SIZE);
	line(5 * CHESS_SIZE, 0 + 7 * CHESS_SIZE, +3 * CHESS_SIZE, +9 * CHESS_SIZE);
	line(-4, -4, CHESS_SIZE * 8 + 4, -4);
	line(-4, 9 * CHESS_SIZE + 4, CHESS_SIZE * 8 + 4, 9 * CHESS_SIZE + 4);
	line(-4, -4, -4, 9 * CHESS_SIZE + +4);
	line(CHESS_SIZE * 8 + +4, -4, CHESS_SIZE * 8 + 4, 9 * CHESS_SIZE + 4);

	//outtextxy()
	for (int i = 0; i < ROW; i++)
	{
		line(0, i * CHESS_SIZE, 8 * CHESS_SIZE, i * CHESS_SIZE);
		if (i < 8)
		{
			line((i + 1) * CHESS_SIZE, 0, (i + 1) * CHESS_SIZE, 4 * CHESS_SIZE);
			line((i + 1) * CHESS_SIZE, 5 * CHESS_SIZE, (i + 1) * CHESS_SIZE, 9 * CHESS_SIZE);
		}
	}
	for (int i = 2; i < 7; i++)////////////DrawPOsition
	{
		if (i % 2 == 0)
		{
			DrawPosition(i * CHESS_SIZE, 3 * CHESS_SIZE);
			DrawPosition(i * CHESS_SIZE, 6 * CHESS_SIZE);
		}
	}
	DrawPosition(CHESS_SIZE, 2 * CHESS_SIZE);
	DrawPosition(CHESS_SIZE, 7 * CHESS_SIZE);
	DrawPosition(CHESS_SIZE * 7, CHESS_SIZE * 2);
	DrawPosition(CHESS_SIZE * 7, CHESS_SIZE * 7);
	Drawleft(0, 3 * CHESS_SIZE);
	Drawleft(0, 6 * CHESS_SIZE);
	DrawRight(8 * CHESS_SIZE, 3 * CHESS_SIZE);
	DrawRight(8 * CHESS_SIZE, 6 * CHESS_SIZE);
	settextstyle(50, 25, "隶书");
	setcolor(BLACK);
	outtextxy(60, 290, ("楚河"));
	outtextxy(60 + 5 * CHESS_SIZE, 290, ("汉界"));
	IMAGE judge;
	loadimage(&judge, "resource\\judge.jpg", 309, 700, true);
	putimage(610, -50, &judge);

}

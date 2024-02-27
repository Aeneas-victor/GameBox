#include"common.h"
#include<iostream>
#include<vector>
#include<Windows.h>
bool gamepause = false;
extern bool GameUnderway;
using namespace std;
////BOOL CALLBACK��ʾһ���ص������ķ���ֵΪ����ֵ
////LPARAM  //windows�е�һ����ʾ�����͵Ĳ���
//BOOL CALLBACK EnumerationWindowProc(HWND hwnd, LPARAM parametric)
//{
//	std::vector<HWND>* WindowsDesktopHandle = (std::vector<HWND>*)parametric;
//	//����һ��vector������������ΪWorkerW�ľ��
//	char ClassName[256];
//	GetClassName(hwnd, ClassName, sizeof(ClassName));
//	//GetClassName������Ҫ֪��ClassName�������Ĵ�С����ȷ��������д�볬���������߽�����ݡ�
//	//����ʹ��sizeof��̬��ȡClassName�Ĵ�С
//	if (strcmp(ClassName, "WorkerW") == 0 || strcmp(ClassName, "Progman") == 0)
//	{
//		// �ҵ�����Ϊ"WorkerW"�Ĵ��ڣ���¼����
//		//��Ϊ���ڶ����������������Ϊ��WorkerW"�����
//		WindowsDesktopHandle->push_back(hwnd);
//	}
//	return TRUE;
//}
//std::vector<HWND> EnumerationWindowHandle()
//{
//	std::vector<HWND>WorkerWHandle;
//	// ö�����ж�������
//	EnumWindows(EnumerationWindowProc, (LPARAM)&WorkerWHandle);
//	return WorkerWHandle;
//}
void GamePause(bool* GameOvertemp)
{
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) // ���ո������
    {
        if (gamepause)
        {
            // ���¿ո�����л�Ϊ������Ϸ
            gamepause = false;
        }
        else
        {
            // ���¿ո�����л�Ϊ��ͣ��Ϸ
            gamepause = true;
            int result = MessageBox(GetDesktopWindow(), "�Ƿ������Ϸ?", "��ͣ", MB_YESNO);
            if (result == IDYES)
            {
                gamepause = false; // �û�ѡ�������Ϸ
            }
            if (result == IDNO)
            {
                *GameOvertemp = !*GameOvertemp;
                GameUnderway = false;
            }
        }
    }
}
void GameExit(bool& XGameOver)//�˳�����
{
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        XGameOver = !XGameOver;
        MessageBox(GetDesktopWindow(),"�ѽ�����Ϸ","��ʾ",MB_OK);
        GameUnderway = false;
    }
}
void Drawleft(int x, int y)//������
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
	settextstyle(50, 25, "����");
	setcolor(BLACK);
	outtextxy(60, 290, ("����"));
	outtextxy(60 + 5 * CHESS_SIZE, 290, ("����"));
	IMAGE judge;
	loadimage(&judge, "resource\\judge.jpg", 309, 700, true);
	putimage(610, -50, &judge);

}

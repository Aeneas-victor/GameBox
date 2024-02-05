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
void GameExit(bool& XGameOver)
{
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        XGameOver = !XGameOver;
        MessageBox(GetDesktopWindow(),"已结束游戏","提示",MB_OK);
        GameUnderway = false;
    }
}

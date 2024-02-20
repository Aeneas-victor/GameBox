#include<Windows.h>
#include<thread>
/// <summary>
///
/// </summary>
bool GameUnderway = false;
extern void GameSnakeModeBegin();
extern void GameBrirdModeBegin();
extern void GameChinaChessModeBegin();
extern void ClockMode();
/// //hinstance 应用程序当前实例窗口
LRESULT CALLBACK CallbackFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//hwnd 从主函数获得的窗口句柄
	//msg从主函数的消息循环中获取的消息
	//wParam附加参数1
	//Lparam附加参数2
	//c语言Review
	//switch用于一个整数进行判断，并跳到相应的case语句块
	//会一直执行知道break或switch语句块的末尾
	//所以写完一个case要加break；
	//版然会执行意想不到的结果
	switch (msg)
	{
	case WM_PAINT: {
		/////////////////////////////////////////////////////////////////////////////////////////////
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// 加载位图
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "name.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		///此处放置图片名字，和此文件在同一目录下直接放名字，
		// /否则放路径
		// 创建兼容的内存设备上下文
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmap);// 获取位图的宽度和高度
		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);// 绘制位图
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);// 清理资源
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		DeleteObject(hBitmap);
		TextOut(hdc, 80, 10, "Welcome to Game Box", 19);
		EndPaint(hwnd, &ps);// 启动定时器，设置为5秒
		break;
		///////////////////////////////////////////////////////////////////////////////
	}
	case WM_COMMAND: {
		// 处理按钮点击事件
		HDC hdc = GetDC(hwnd); // 获取设备上下文句柄
		if (LOWORD(wParam) == 1) // 判断按钮ID是否为1
		{
			// 执行按钮1的功能
			if(!GameUnderway)
			{
				std::thread GameSnake(GameSnakeModeBegin);
				ShowWindow(hwnd, SW_SHOWMINIMIZED);				//隐藏控制台
				GameSnake.detach();
			}
			else {
				MessageBox(GetDesktopWindow(),"游戏进行中,请先结束游戏","HINT", MB_ICONQUESTION | MB_OK);
			}
		}
		else if (LOWORD(wParam) == 2) // 判断按钮ID是否为2
		{
			// 执行按钮2的功能
			if(!GameUnderway)
			{
				std::thread GameBrird(GameBrirdModeBegin);
				ShowWindow(hwnd, SW_SHOWMINIMIZED);				//隐藏控制台
				GameBrird.detach();
			}
			else
			{
				MessageBox(GetDesktopWindow(), "游戏进行中,请先结束游戏", "HINT", MB_ICONQUESTION | MB_OK);
			}
		}
		else if (LOWORD(wParam) == 3) // 判断按钮ID是否为3
		{
			// 执行按钮3的功能
			if (!GameUnderway)
			{
				std::thread GameChess(GameChinaChessModeBegin);
				ShowWindow(hwnd, SW_SHOWMINIMIZED);				//隐藏控制台
				GameChess.detach();
			}
			else
			{
				MessageBox(GetDesktopWindow(), "游戏进行中,请先结束游戏", "HINT", MB_ICONQUESTION | MB_OK);
			}
		}
		else if (LOWORD(wParam) == 4)
		{
			if (!GameUnderway)
			{
				std::thread GameChess(ClockMode);
				ShowWindow(hwnd, SW_SHOWMINIMIZED);				//隐藏控制台
				GameChess.detach();
			}
			else
			{
				MessageBox(GetDesktopWindow(), "游戏进行中,请先结束游戏", "HINT", MB_ICONQUESTION | MB_OK);
			}
		}
		else { NULL; }
		ReleaseDC(hwnd, hdc); // 释放设备上下文句柄
		break;
	}
	case WM_DESTROY://如果要退出
		PostQuitMessage(0);//传递退出消息，终止主函数的消息循环
		break;
		// 默认行为(什么都不做，就返回窗口)
	default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE HpREViNSTANCE, LPSTR lpCMDline, int nCMDshow)
{
	WNDCLASS  wc = {};
	wc.lpfnWndProc = CallbackFunc;
	wc.hInstance = hinstance;//实例窗口句柄
	wc.lpszClassName = "MY_Game";
	RegisterClass(&wc);
	//RegisterClass()注册窗口类
	//接受一个WNDCLASS的指针
	//CreateWindow 创建窗口，返回一个窗口句柄
	HWND hwnd = CreateWindow(
		wc.lpszClassName,                  //窗口类名，要和wc.lpszClassName相同
		"GameBox",                         //窗口标题
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,  //窗口样式
		1300,                            //左上角横坐标
		550,                            //左上角纵坐标
		350,                             //窗口宽度
		450,                             //窗口高度
		NULL,                            //父窗口
		NULL,                            //菜单句柄
		hinstance,                       //实例窗口
		NULL                             //附加参数
	);
	CreateWindow("BUTTON", "SnakeGame", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 125, 70, 90, 40, hwnd, (HMENU)1, NULL, NULL);
	/////////////窗口类名////窗口标题////窗口样式///////////////////////////////左上角横纵坐标//窗口宽高/父窗口句柄///菜单句柄///实例句柄/附加参数
	CreateWindow("BUTTON", "BrirdGame", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 125, 120, 90, 40, hwnd, (HMENU)2, NULL, NULL);
	CreateWindow("BUTTON", "ChinaChess", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 125, 170, 90, 40, hwnd, (HMENU)3, NULL, NULL);
	CreateWindow("BUTTON", "Clock", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 285, 0, 50, 40, hwnd, (HMENU)4, NULL, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	MSG msg = {};  //消息结构体
	while (GetMessage(&msg, 0, NULL, NULL)) // 如果没有发生错误，且收到了任意消息
	{
		//::TranslateMessage(&msg); // 翻译消息，将消息中的键盘码转换为对应的字符
		DispatchMessage(&msg);  // 派发消息，调用 CallBackFunc 回调函数处理消息
	}
	return 0;

}
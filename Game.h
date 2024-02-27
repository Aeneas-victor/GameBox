#pragma once
#include"common.h"

class Game {
public:
	Game();
	~Game();
	void Gameinit();//游戏初始化//隐藏图标//
	//判断图标是否够，。//创建图标
	int GetWidth();//获取屏幕宽度
	int GetHeight();//高度
	int GetIconCount();//获取图标个数
	HWND GetDesktopHandle();//获取桌面图标句柄//遍历寻找
	HWND Getdesktop();//获取桌面图标句柄//直接返回
protected:
	HWND desktop;
	int Width;
	int Height;
	int iconCount;
}; 


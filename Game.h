#pragma once
#include"common.h"

class Game {
public:
	Game();
	void Gameinit();
	int GetWidth();
	int GetHeight();
	int GetIconCount();
	HWND GetDesktopHandle();
	HWND Getdesktop();

private:
	HWND desktop;
	int Width;
	int Height;
	int iconCount;
	

};
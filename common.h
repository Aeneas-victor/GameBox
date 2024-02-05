#pragma once
#include<iostream>
#include<Windows.h>
#include<CommCtrl.h>
#include<thread>
#include<commctrl.h>
#include<windef.h>
#include<vector>
#include<random>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#ifndef BRIRD_H
#define BRIRD_H
#endif
#ifndef GAME_H
#define GAME_H
#endif
#ifndef SNAKE_H
#define SNAKE_H
#endif
#ifndef BRIRD_H
#define BRIRD_H
#endif
#define BORDER 220
#define ICONSIZE 80
#define G 2
#define _space_num 5
using namespace std;
void SnakeMode();

//BOOL CALLBACK EnumerationWindowProc(HWND hwnd, LPARAM parametric);
//std::vector<HWND> EnumerationWindowHandle();

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<CommCtrl.h>
#include<thread>
#include<commctrl.h>
#include<graphics.h>
#include<windef.h>
#include<conio.h>
#include <time.h>
#include<algorithm>
#include<ctime>
#include<mutex>
#include<vector>
#include<math.h>
#include<map>
#include<random>
#include<dos.h> 
#include<tchar.h>
#include <shlobj.h>
#include<KnownFolders.h>
#include <atlconv.h>
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
#define SQU(x) ((x)*(x))
/////////////////////////////////////////
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define CHESS_SIZE 70//棋子格宽度
#define INTERVAL 50//边框
#define ROW 10//行
#define COL 9//列
////象棋游戏
/////////////////////////////////////
#define BORDER 220//下边状态栏宽度
#define ICONSIZE 80//图标宽度
#define ICON_SIZE 80
#define G 2//重力加速度
#define _space_num 5
#define NUMWIDTH 3
#define NUMHEIGHT 5

/// 图标游戏
/// /////////////////////////////////
/// </summary>
using namespace std;
void SnakeMode();

//BOOL CALLBACK EnumerationWindowProc(HWND hwnd, LPARAM parametric);
//std::vector<HWND> EnumerationWindowHandle();

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
#define CHESS_SIZE 70//���Ӹ���
#define INTERVAL 50//�߿�
#define ROW 10//��
#define COL 9//��
////������Ϸ
/////////////////////////////////////
#define BORDER 220//�±�״̬�����
#define ICONSIZE 80//ͼ����
#define ICON_SIZE 80
#define G 2//�������ٶ�
#define _space_num 5
#define NUMWIDTH 3
#define NUMHEIGHT 5

/// ͼ����Ϸ
/// /////////////////////////////////
/// </summary>
using namespace std;
void SnakeMode();

//BOOL CALLBACK EnumerationWindowProc(HWND hwnd, LPARAM parametric);
//std::vector<HWND> EnumerationWindowHandle();

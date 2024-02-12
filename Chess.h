#pragma once
#ifndef CHESS_H
#define CHESS_H
#include"Common.h"
typedef struct piece {
	POINT point;/////
	IMAGE picture;//——
	std::string ChessName;//
	char color;//
	bool ifriver;
	std::string address;//
}piece_;
class Chess
{
protected:
	piece _piece[ROW][COL];//
	ExMessage chessmsg;

	int begindown = 0;//是否第一次点击为棋子
	POINT begin = { -1,-1 }, end = { -1,-1 };//存储下标
	char RedOrBlack = 'R';
	std::string _black[7] = { "車","马","象","士","将","炮","卒" };
	std::string _red[7] = { "車","馬","相","仕","帥","炮","兵" };
public:
	bool GameOverx = false;
	Chess();
	~Chess();
	void Gameinit();//初始化
	bool MoveChess();//移动
	void Moveed();
	void refresh();// 刷新
	/*bool isClickOnPoint(int x,int y,POINT pot);
	piece isClickOnpiece(int x, int y);*/
	void GetControl();//Mouse Message
	bool MoveRook();//rook車
	bool MoveHorse();//馬 horse
	bool MoveElephant();//Elephant 相
	bool ifRiver();
	bool MoveAdviser();//Adviser 士
	bool MoveGeneral();//General 将
	bool MoveCannon();//cannon 炮
	bool MoveSoldier();//soldier 兵

	void testpoint();//test point
	void testChessName();//test Chess name
	void testaddress();
	void testcolor();//test color
	void test();
};
#endif
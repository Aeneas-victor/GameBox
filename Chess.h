#pragma once
#ifndef CHESS_H
#define CHESS_H
#include"Common.h"
typedef struct piece {
	POINT point;/////
	IMAGE picture;//����
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

	int begindown = 0;//�Ƿ��һ�ε��Ϊ����
	POINT begin = { -1,-1 }, end = { -1,-1 };//�洢�±�
	char RedOrBlack = 'R';
	std::string _black[7] = { "܇","��","��","ʿ","��","��","��" };
	std::string _red[7] = { "܇","�R","��","��","��","��","��" };
public:
	bool GameOverx = false;
	Chess();
	~Chess();
	void Gameinit();//��ʼ��
	bool MoveChess();//�ƶ�
	void Moveed();
	void refresh();// ˢ��
	/*bool isClickOnPoint(int x,int y,POINT pot);
	piece isClickOnpiece(int x, int y);*/
	void GetControl();//Mouse Message
	bool MoveRook();//rook܇
	bool MoveHorse();//�R horse
	bool MoveElephant();//Elephant ��
	bool ifRiver();
	bool MoveAdviser();//Adviser ʿ
	bool MoveGeneral();//General ��
	bool MoveCannon();//cannon ��
	bool MoveSoldier();//soldier ��

	void testpoint();//test point
	void testChessName();//test Chess name
	void testaddress();
	void testcolor();//test color
	void test();
};
#endif
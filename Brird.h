#pragma once
#ifndef BRIRD_H
#define BRIRD_H
#include"Game.h"
typedef struct WallNode {
	int idx;//brird ��id
	POINT wallnode;//ǽλ�ú���
}WallNode;
class Wall {
public:
	Game* brirdgame=new Game;
	WallNode brird;
	std::vector<WallNode>wallx;
	double time_s;//ʱ��
	bool BrirdGameOver = true;
	int refreshposition;//ˢ��λ��
	int RandNum;//
	void wallinit();//��ʼ��ǽ
	~Wall();
	void Music(int a);//��������
	void refresh();//ˢ��
	void print();//�ƶ�
	void Jump();//��Ծ
};
#endif
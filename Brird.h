#pragma once
#ifndef BRIRD_H
#define BRIRD_H
#include"Game.h"
typedef struct WallNode {
	int idx;//brird 的id
	POINT wallnode;//墙位置函数
}WallNode;
class Wall {
public:
	Game* brirdgame=new Game;
	WallNode brird;
	std::vector<WallNode>wallx;
	double time_s;//时间
	bool BrirdGameOver = true;
	int refreshposition;//刷新位置
	int RandNum;//
	void wallinit();//初始化墙
	~Wall();
	void Music(int a);//播放音乐
	void refresh();//刷新
	void print();//移动
	void Jump();//跳跃
};
#endif
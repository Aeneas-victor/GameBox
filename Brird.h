#pragma once
#include"Game.h"

typedef struct WallNode {
	int idx;
	POINT wallnode;
}WallNode;
class Wall {
public:
	Game* brirdgame=new Game;
	WallNode brird;
	std::vector<WallNode>wallx;
	double time_s;
	bool BrirdGameOver = true;
	int refreshposition;
	int RandNum;
	void wallinit();
	~Wall();
	void Music(int a);
	void refresh();
	void print();
	void Jump();
};
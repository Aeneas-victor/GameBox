#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include"common.h"
class Game;
class Snake {
public:
	enum Dir { UP = 0, DOWN, LEFT, RIGHT };//·½Ïò
	Snake();
	~Snake();
	void MoveSnake();
	void SnakeInput();
	void DramSnake();
	bool GameOver();
	int Getfoodx();
	int Getfoody();
	void GameAgain();
	void Music(int a);
	int GetdnSnakeSize();
	int Gamebox();
	int sftW;//SnakeFileTempWidth
	int sftH;//SnakeFileTempHeight
	bool SnakeGameOver = false;
private:
	Game* pdesktop;
	vector<POINT>snake;
	POINT food;
	Dir direction;
};
#endif
#pragma once
#include"common.h"

class Game {
public:
	Game();
	~Game();
	void Gameinit();//��Ϸ��ʼ��//����ͼ��//
	//�ж�ͼ���Ƿ񹻣���//����ͼ��
	int GetWidth();//��ȡ��Ļ���
	int GetHeight();//�߶�
	int GetIconCount();//��ȡͼ�����
	HWND GetDesktopHandle();//��ȡ����ͼ����//����Ѱ��
	HWND Getdesktop();//��ȡ����ͼ����//ֱ�ӷ���
protected:
	HWND desktop;
	int Width;
	int Height;
	int iconCount;
}; 


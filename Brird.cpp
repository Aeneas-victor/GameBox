#include "Brird.h"
/// <summary>
/// ////////////////////
/// </summary>
int WallNum;
////////////////////////
void Wall::wallinit()
{
	time_s = 0;//����ʱ�䣬����ͨ�����ٶȼ���λ��ʱ��
	WallNum = ((brirdgame->GetHeight() - 2 * ICONSIZE) / ICONSIZE) - 5;
	//��������ǽ������
	srand(time(NULL));//�������
	refreshposition = 30 * ICONSIZE;//
	RandNum = rand() % (WallNum)+1;//���һ��������wall�м䣬���ɿ�ǽ��
	brird.idx = 0;//brird��id
	brird.wallnode.x = 5 * ICONSIZE;//���ʼλ��
	brird.wallnode.y = 3 * ICONSIZE;
	ListView_SetItemPosition(brirdgame->Getdesktop(), 0, brird.wallnode.x, brird.wallnode.y);
	//������ĳ�ʼλ��
	for (int i = 0; i < WallNum; i++)
	{
		WallNode temp;
		temp.idx = i + 1;
		temp.wallnode.x = 30 * ICONSIZE;
		std::cout << "temp.wallnode.x = 30 * ICONSIZE;" << std::endl;
		temp.wallnode.y = i * ICONSIZE + (i < RandNum ? 0 : RandNum * ICONSIZE);
		//����ǿ�ĳ�ʼλ�ã����С�����������  i*ICONSIZE ��λ�ò���vector��������λ�ã�
		// ������������������i*ICONSIZE +RandNum*ICONSIZE��λ�ò���vector��������λ�á�
		//�����γ��м��пն���ǽ��
		wallx.push_back(temp);//����vecot����
		std::cout << "push_back" << std::endl;
		ListView_SetItemPosition(brirdgame->Getdesktop(), i + 1, temp.wallnode.x, temp.wallnode.y);
	}
}
Wall::~Wall()
{
	delete brirdgame;
}
void Wall::Music(int a)
{
	if (a == 1)
	{
		// �������ļ�
		mciSendString("open foryou.mp3 type mpegvideo alias myMusic2", NULL, 0, NULL);
		// ��������
		mciSendString("play myMusic2", NULL, 0, NULL);
	}
	if (a == 2)
	{
		// �ȴ����ֲ������
		// Sleep(5000); // �ȴ�5��
		//// ֹͣ����
		mciSendString("stop myMusic2", NULL, 0, NULL);
		//// �ر������ļ�
		mciSendString("close myMusic2", NULL, 0, NULL);
	}
}
void Wall::refresh()
{//ˢ��ǽ�ڿն���λ��
	srand(time(NULL));
	RandNum = rand() % (WallNum)+1;
	for (int i = 0; i < wallx.size(); i++)
	{
		wallx[i].wallnode.y = i * ICONSIZE + (i < RandNum ? 0 : RandNum * ICONSIZE);
	}
}
void Wall::print()
{
	for (int i = 0; i < wallx.size(); i++)
	{
		wallx[i].wallnode.x = (wallx[i].wallnode.x + brirdgame->GetWidth() - ICONSIZE / 2) %brirdgame->GetWidth();
		ListView_SetItemPosition(brirdgame->Getdesktop(), i + 1, wallx[i].wallnode.x, wallx[i].wallnode.y);//����ǽ��λ��
		ListView_SetItemPosition(brirdgame->Getdesktop(), 0, brird.wallnode.x, brird.wallnode.y);//����brirdλ��
		brird.wallnode.y += G * time_s * time_s / 2;//�������䣬ģ��һ���������ٶȣ�
		if (brird.wallnode.x + ICONSIZE == wallx[0].wallnode.x)
		{//���brird  x�����ǽ��һ�������ж�brird��y�����Ƿ��ڿն����棬�����ڿն�����//��ײ��ǽ��
			if (brird.wallnode.y <RandNum * ICONSIZE or brird.wallnode.y>(RandNum + _space_num) * ICONSIZE)
				//MessageBox(GetDesktopWindow(), "ײ��ǽ���ˣ�", "��ʾ", MB_OK);
				BrirdGameOver = false;
		}
		time_s += 0.07;//ʱ������
	}
	if(!BrirdGameOver)
		MessageBox(GetDesktopWindow(), "ײ��ǽ���ˣ�", "��ʾ", MB_OK);
	refreshposition -= ICONSIZE / 2;//�ж�ˢ��λ�õĲ�����
	if (refreshposition < 0)
	{
		refreshposition = brirdgame->GetWidth();
		refresh();
	}
	if (brird.wallnode.y > brirdgame->GetHeight())
	{
		time_s = 0;//ÿ�����º�����ˢ��ʱ�䣬
		brird.wallnode.y = 0;
	}
}
void Wall::Jump()
{
	if (GetAsyncKeyState(VK_UP)|| GetAsyncKeyState(0x57))
	{
		brird.wallnode.y -= (2 * ICONSIZE - 20);
		time_s = 0;//ÿ����Ծˢ��ʱ��
	}
}
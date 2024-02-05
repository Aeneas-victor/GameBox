#include "Brird.h"
/// <summary>
/// ////////////////////
/// </summary>
int WallNum;
////////////////////////
void Wall::wallinit()
{
	time_s = 0;//设置时间，后面通过加速度计算位置时用
	WallNum = ((brirdgame->GetHeight() - 2 * ICONSIZE) / ICONSIZE) - 5;
	//最终生成墙的数量
	srand(time(NULL));//随机种子
	refreshposition = 30 * ICONSIZE;//
	RandNum = rand() % (WallNum)+1;//随机一个数字在wall中间，生成空墙壁
	brird.idx = 0;//brird的id
	brird.wallnode.x = 5 * ICONSIZE;//鸟初始位置
	brird.wallnode.y = 3 * ICONSIZE;
	ListView_SetItemPosition(brirdgame->Getdesktop(), 0, brird.wallnode.x, brird.wallnode.y);
	//设置鸟的初始位置
	for (int i = 0; i < WallNum; i++)
	{
		WallNode temp;
		temp.idx = i + 1;
		temp.wallnode.x = 30 * ICONSIZE;
		std::cout << "temp.wallnode.x = 30 * ICONSIZE;" << std::endl;
		temp.wallnode.y = i * ICONSIZE + (i < RandNum ? 0 : RandNum * ICONSIZE);
		//设置强的初始位置，如果小于随机数则在  i*ICONSIZE 的位置插入vector及设置其位置，
		// 如果大于随机数，则在i*ICONSIZE +RandNum*ICONSIZE的位置插入vector及设置其位置。
		//可以形成中间有空洞的墙壁
		wallx.push_back(temp);//插入vecot数组
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
		// 打开音乐文件
		mciSendString("open foryou.mp3 type mpegvideo alias myMusic2", NULL, 0, NULL);
		// 播放音乐
		mciSendString("play myMusic2", NULL, 0, NULL);
	}
	if (a == 2)
	{
		// 等待音乐播放完成
		// Sleep(5000); // 等待5秒
		//// 停止音乐
		mciSendString("stop myMusic2", NULL, 0, NULL);
		//// 关闭音乐文件
		mciSendString("close myMusic2", NULL, 0, NULL);
	}
}
void Wall::refresh()
{//刷新墙壁空洞的位置
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
		ListView_SetItemPosition(brirdgame->Getdesktop(), i + 1, wallx[i].wallnode.x, wallx[i].wallnode.y);//设置墙的位置
		ListView_SetItemPosition(brirdgame->Getdesktop(), 0, brird.wallnode.x, brird.wallnode.y);//设置brird位置
		brird.wallnode.y += G * time_s * time_s / 2;//加速下落，模拟一个重力加速度，
		if (brird.wallnode.x + ICONSIZE == wallx[0].wallnode.x)
		{//如果brird  x坐标和墙壁一样，则判断brird的y坐标是否在空洞上面，或者在空洞下面//则撞到墙壁
			if (brird.wallnode.y <RandNum * ICONSIZE or brird.wallnode.y>(RandNum + _space_num) * ICONSIZE)
				//MessageBox(GetDesktopWindow(), "撞到墙壁了！", "提示", MB_OK);
				BrirdGameOver = false;
		}
		time_s += 0.07;//时间增加
	}
	if(!BrirdGameOver)
		MessageBox(GetDesktopWindow(), "撞到墙壁了！", "提示", MB_OK);
	refreshposition -= ICONSIZE / 2;//判断刷新位置的参数，
	if (refreshposition < 0)
	{
		refreshposition = brirdgame->GetWidth();
		refresh();
	}
	if (brird.wallnode.y > brirdgame->GetHeight())
	{
		time_s = 0;//每次落下后重新刷新时间，
		brird.wallnode.y = 0;
	}
}
void Wall::Jump()
{
	if (GetAsyncKeyState(VK_UP)|| GetAsyncKeyState(0x57))
	{
		brird.wallnode.y -= (2 * ICONSIZE - 20);
		time_s = 0;//每次跳跃刷新时间
	}
}
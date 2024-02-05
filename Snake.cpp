#include "Snake.h"
#include"Game.h"


Snake::Snake() :pdesktop(new Game)//Snake类的构造函数使用初始化列表来初始化指针成员变量pDesktop
{
	Music(1);
	pdesktop->Gameinit();
	cout << "Gameinit->win" << endl;
	snake.push_back({ 240,240 });
	cout << "Snake::Snake():pdesktop(new Game)->initialize complete!" << endl;
	direction = Dir::UP;
	srand(time(0));
	food.x = (rand() % (pdesktop->GetWidth() - ICONSIZE) + 1) / ICONSIZE * ICONSIZE;
	food.y = (rand() % (pdesktop->GetHeight() - 2 * ICONSIZE) + 1) / ICONSIZE * ICONSIZE;
	cout << "food.x:" << food.x << endl;
	cout << "food.y:" << food.y << endl;
}

Snake::~Snake()
{

}
void Snake::MoveSnake()
{
	//设置每一节蛇身的坐标等于上一节点的坐标使其蛇形移动
	for (int i = snake.size() - 1; i > 0; i--)
	{
		snake[i] = snake[i - 1];
	}
	sftW = pdesktop->GetWidth() - ICONSIZE;//减去ICONSIZE控制其在屏幕内，图标本身有宽度
	//SnakeFileTempWidth 
	sftH = pdesktop->GetHeight() - 2 * ICONSIZE;//减去三倍的ICONSIZE除去状态栏所占空间
	//SnakeFileTempHeight
	//控制持续按照direction移动
	snake[0].x = direction == LEFT ? (snake[0].x - ICONSIZE + sftW) % sftW : direction == RIGHT ? (snake[0].x + ICONSIZE + sftW) % sftW : snake[0].x;
	snake[0].y = direction == UP ? (snake[0].y - ICONSIZE + sftH) % sftH : direction == DOWN ? (snake[0].y + ICONSIZE + sftH) % sftH : snake[0].y;
	//控制在一定范围内循环，代替以下麻烦的穿墙多路判断
	//控制窗墙
	/*if (snake[0].x <= -10)
		snake[0].x = pdesktop->GetWidth() - BORDER;
	if (snake[0].x >= pdesktop->GetWidth())
		snake[0].x = 0;
	if (snake[0].y <= 0)
		snake[0].y = pdesktop->GetHeight() - BORDER;
	if (snake[0].y >= pdesktop->GetHeight())
		snake[0].y = 0;
	*/
}

void Snake::SnakeInput()
{/////////Get Async 异步，非同步
	//Key  State///////////////////异步函数，立即返回键的状态而不会阻碍进程的运行
	if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && direction != DOWN)//w,UP
		direction = UP;//前进方向非DOWN变成UP
	if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) && direction != UP)//s,DOWN
		direction = DOWN;
	if ((GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) && direction != RIGHT)//a,LEFT
		direction = LEFT;
	if ((GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) && direction != LEFT)//d,RIGHT
		direction = RIGHT;
}

void Snake::DramSnake()
{
	for (int i = 0; i < snake.size(); i++)
	{////////////////////////////////////////////////////////////////高16位为y，低16位为x
		SendMessageA(pdesktop->Getdesktop(), LVM_SETITEMPOSITION, i, (snake[i].y << 16) + snake[i].x);
	}
	SendMessageA(pdesktop->Getdesktop(), LVM_SETITEMPOSITION, snake.size(), MAKELONG(food.x, food.y));
	//////////////////////////////////////////////////////////////////////////////MAKELONG  重新制造新的长整型
   //////////////////////////////////////////////////////////////////////////////同以上用法第一个参数为低位，第二个为高位，左移16位
	//snake[0].x<=food.x&&snake[0].y<=food.y&&snake[0].x<=Getfoodx()&&snake[0].y<=Getfoody()
	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		cout << "snake.size()" << snake.size() << endl;
		POINT NewNode({ food.x,food.y });
		snake.push_back(NewNode);
		srand(time(0));
		food.x = (rand() % (pdesktop->GetWidth() - ICONSIZE) + 1) / ICONSIZE * ICONSIZE;
		///////////////////////////////////////////////////////控制生成随机数是ICONSIZE的倍数
		food.y = (rand() % (pdesktop->GetHeight() - 2 * ICONSIZE) + 1) / ICONSIZE * ICONSIZE;
		cout << "food.x:" << food.x << endl;
		cout << "food.y:" << food.y << endl;
	}
}

bool Snake::GameOver()
{
	for (vector<POINT>::iterator it = snake.begin() + 1; it != snake.end(); it++)
	{
		if (snake[0].x == (*it).x && snake[0].y == (*it).y)
		{
			return true;
		}
	}
	return false;
}

int Snake::Getfoodx()
{
	return food.x + ICONSIZE;
}

int Snake::Getfoody()
{
	return food.y + ICONSIZE;
}

void Snake::GameAgain()
{
	pdesktop->Gameinit();
}

void Snake::Music(int a)
{
	if (a == 1)
	{
		// 打开音乐文件
		mciSendString("open Metrohead.mp3 type mpegvideo alias myMusic", NULL, 0, NULL);
		// 播放音乐
		mciSendString("play myMusic", NULL, 0, NULL);
	}
	if (a == 2)
	{
		// 等待音乐播放完成
		// Sleep(5000); // 等待5秒
		//// 停止音乐
		mciSendString("stop myMusic", NULL, 0, NULL);
		//// 关闭音乐文件
		mciSendString("close myMusic", NULL, 0, NULL);
	}
}

int Snake::GetdnSnakeSize()
{
	return snake.size();
}

int Snake::Gamebox()
{
	return MessageBox(pdesktop->Getdesktop(), " 游戏结束", "是否重新开始", MB_YESNO);
}

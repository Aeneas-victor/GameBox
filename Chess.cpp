#include "Chess.h"
extern void DrawPosition(int, int);
extern void DrawBoard();
extern void Drawleft(int, int);
extern void DrawRight(int, int);

Chess::Chess()
{
	initgraph(950, 800, SHOWCONSOLE);
	setorigin(INTERVAL, INTERVAL);
	DrawBoard();
	settextstyle(30, 10, "隶书");
	if (RedOrBlack == 'R')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "红方走棋");
	}
	else if (RedOrBlack == 'B')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "黑方走棋");
	}
	Gameinit();
}

Chess::~Chess()
{

}

void Chess::receive(SOCKET recvClientSocket)
{
	while (true)
	{

		//	6	发送/接受 数据
		char recvBuf[4] = {};
		int reLen = recv(recvClientSocket, recvBuf, 4, 0);
		//int sLen = send(recvClientSocket, recvBuf, reLen, 0);
		if (SOCKET_ERROR != reLen) {
			cout << "接收下棋信息成功" << endl;
			begin.x = recvBuf[0] - '0';
			begin.y = recvBuf[1] - '0';
			end.x = recvBuf[2] - '0';
			end.y = recvBuf[3] - '0';
			Moveed();
			//RedOrBlack = RedOrBlack == 'R' ? 'B' : 'R';
			reLen = SOCKET_ERROR;
		}

	}

}

void Chess::mysend(SOCKET recvClientSocket)
{

	char s[4];
	//cout << "请输入发送数据" << endl;
	s[0] = begin.x + 48;
	s[1] = begin.y + 48;
	s[2] = end.x + 48;
	s[3] = end.y + 48;
	int seLen = send(recvClientSocket, (char*)s, 4, 0);
	if (SOCKET_ERROR != seLen)
	{
		cout << "发送下棋信息成功 " << endl;
	}
	else cout << "发送下棋信息失败" << endl;
}

void Chess::service()
{
	cout << "-----------服务器-----------" << endl;

	//	1	初始化
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);	//make word,你把鼠标移到WSAStartup看看参数列表,是不是就是一个word啊


	//	2	创建服务器的套接字
	SOCKET serviceSocket;
	serviceSocket = socket(AF_INET, SOCK_STREAM, 0);	//socket(协议族,socket数据传输方式,某个协议)	我们默认为0,其实就是一个宏
	if (SOCKET_ERROR == serviceSocket) {
		cout << "套接字创建失败!" << endl;
	}
	else {
		cout << "套接字创建成功!" << endl;
	}


	//	3	绑定套接字	指定绑定的IP地址和端口号
	sockaddr_in socketAddr;								//一个绑定地址:有IP地址,有端口号,有协议族
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		//代码开头第一行我们定义的宏在这就其作用啦
	socketAddr.sin_port = htons(2305);
	int bRes = bind(serviceSocket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR));	//绑定注意的一点就是记得强制类型转换
	if (SOCKET_ERROR == bRes) {
		cout << "绑定失败!" << endl;
	}
	else {
		cout << "绑定成功!" << endl;
	}

	//	4	服务器监听	
	int lLen = listen(serviceSocket, 5);	//监听的第二个参数就是:能存放多少个客户端请求,到并发编程的时候很有用哦
	if (SOCKET_ERROR == lLen) {
		cout << "监听失败!" << endl;
	}
	else {
		cout << "监听成功!" << endl;
	}


	//	5	接受请求
	sockaddr_in revClientAddr;
	SOCKET recvClientSocket = INVALID_SOCKET;	//初始化一个接受的客户端socket
	int _revSize = sizeof(sockaddr_in);
	recvClientSocket = accept(serviceSocket, (SOCKADDR*)&revClientAddr, &_revSize);
	if (INVALID_SOCKET == recvClientSocket) {
		cout << "服务端接受请求失败!" << endl;
	}
	else {
		cout << "服务端接受请求成功!" << endl;
	}
	// 循环接收数据
	mySocket = recvClientSocket;
	thread reveMessage([this, recvClientSocket] {receive(recvClientSocket); });
	//thread sendMessage(mysend, recvClientSocket);
	reveMessage.detach();
	//sendMessage.join();

	while (1);



	//	7	关闭socket
	closesocket(recvClientSocket);
	closesocket(serviceSocket);

	//	8	终止
	WSACleanup();

	cout << "服务器停止" << endl;
	cin.get();

}
//服务端
void Chess::client()
{
	cout << "-----------客户端-----------" << endl;

	//	1	初始化
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);


	//	2	创建套接字
	SOCKET clientSocket = {};
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == clientSocket) {
		cout << "套接字创建失败!" << endl;
	}
	else {
		cout << "套接字创建成功!" << endl;
	}
	//	3	绑定套接字	指定绑定的IP地址和端口号
	sockaddr_in socketAddr;
	socketAddr.sin_family = PF_INET;
	socketAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	socketAddr.sin_port = htons(2305);
	int cRes = connect(clientSocket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR));
	if (SOCKET_ERROR == cRes) {
		cout << "客户端:\t\t与服务器连接失败....." << endl;
	}
	else {
		cout << "客户端:\t\t与服务器连接成功....." << endl;
	}
	mySocket = clientSocket;
	//while (true)
	//{
	//	//	4	发送请求
	//	string s;
	//	cout << "输入发送数据:   " << endl;
	//	getline(cin, s);  //可输入空格,默认以换行符结束输入,
	//	send(clientSocket, (char*)s.c_str(), s.length(), 0);
	//	//	5	发送/接受 数据
	//	/*char recvBuf[4024] = {};
	//	recv(clientSocket, recvBuf, 4024, 0);
	//	cout << "客户端接收数据	:	" << recvBuf << endl << endl;*/
	//}
	//
	thread reveMessage([this, clientSocket] {receive(clientSocket); });
	//thread sendMessage(mysend, clientSocket);
	reveMessage.detach();
	//sendMessage.join();
	while (1);




	//	6	关闭socket
	closesocket(clientSocket);


	//	7	终止
	WSACleanup();

	cout << "客户端退出" << endl;
	cin.get();

}//客户端
//客户端
void Chess::myconnect()
{
	cout << "1.发起连接" << endl;
	cout << "2.加入链接" << endl;
	int a;
	cin >> a;
	if (a == 1)
	{
		thread myservice([this] {service(); });
		myservice.detach();
		nowcolor = 'R';
		RedOrBlack = 'R';
	}
	else
	{
		thread myclient([this] {client(); });
		myclient.detach();
		nowcolor = 'B';
		RedOrBlack = 'R';
	}
}

void Chess::Gameinit()
{
	setorigin(INTERVAL, INTERVAL);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			_piece[i][j].point.x = j * CHESS_SIZE;//坐标
			_piece[i][j].point.y = i * CHESS_SIZE;
			_piece[i][j].color = 'N';
			if (i < 5) {
				if (i == 0) {
					if (j < 5) {
						_piece[i][j].ChessName.assign(_black[j]);
						std::string temp = "resource\\" + std::to_string(j + 1) + "B.jpg";
						_piece[i][j].color = 'B';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
					else {
						_piece[i][j].ChessName.assign(_black[8 - j]);//折返初始化车马相仕将
						std::string temp = "resource\\" + std::to_string(9 - j) + "B.jpg";
						_piece[i][j].color = 'B';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
				if (i == 2) {
					if (j == 1 || j == 7) {
						_piece[i][j].ChessName.assign(_black[5]);
						std::string temp = "resource\\" + std::to_string(6) + "B.jpg";
						_piece[i][j].color = 'B';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}//炮
				}
				if (i == 3) {
					if (j % 2 == 0)
					{
						_piece[i][j].ChessName.assign(_black[6]);//兵
						std::string temp = "resource\\" + std::to_string(7) + "B.jpg";
						_piece[i][j].color = 'B';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
			}
			else {

				if (i == 9) {
					if (j < 5) {
						_piece[i][j].ChessName.assign(_red[j]);
						std::string temp = "resource\\" + std::to_string(j + 1) + "R.jpg";
						_piece[i][j].color = 'R';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
					else {
						_piece[i][j].ChessName.assign(_red[8 - j]);
						std::string temp = "resource\\" + std::to_string(9 - j) + "R.jpg";
						_piece[i][j].color = 'R';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
				if (i == 6)
				{
					if (j % 2 == 0)
					{
						_piece[i][j].ChessName.assign(_red[6]);
						std::string temp = "resource\\" + std::to_string(7) + "R.jpg";
						_piece[i][j].color = 'R';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
				if (i == 7)
				{
					if (j == 1 || j == 7) {
						_piece[i][j].ChessName.assign(_red[5]);
						std::string temp = "resource\\" + std::to_string(6) + "R.jpg";
						_piece[i][j].color = 'R';
						_piece[i][j].address = temp;
						loadimage(&_piece[i][j].picture, (LPCTSTR)_piece[i][j].address.c_str(), 60, 60, true);
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
			}
			if (_piece[i][j].ChessName != "")
				_piece[i][j].ifriver = false;//是否过河
		}
	}

}

//初始化//无棋子color为  N  
//无棋子无isriver

bool Chess::MoveChess()
{
	std::cout << "MoveChess" << std::endl;
	if ((!(begin.x == end.x && begin.y == end.y)) && _piece[begin.x][begin.y].color != _piece[end.x][end.y].color)//点击不是同一位置
	{
		if (_piece[begin.x][begin.y].ChessName == "車")
		{
			std::cout << "Moveing" << std::endl;
			return MoveRook();

		}
		else if (_piece[begin.x][begin.y].ChessName == "馬" || _piece[begin.x][begin.y].ChessName == "马")
		{
			std::cout << "Moveing" << std::endl;
			return MoveHorse();

		}
		else if (_piece[begin.x][begin.y].ChessName == "相" || _piece[begin.x][begin.y].ChessName == "象")
		{
			std::cout << "Moveing" << std::endl;
			return MoveElephant();

		}
		else if (_piece[begin.x][begin.y].ChessName == "仕" || _piece[begin.x][begin.y].ChessName == "士")
		{
			std::cout << "Moveing" << std::endl;
			return MoveAdviser();

		}
		else if (_piece[begin.x][begin.y].ChessName == "将" || _piece[begin.x][begin.y].ChessName == "帥")
		{
			std::cout << "Moveing" << std::endl;
			return MoveGeneral();

		}
		else if (_piece[begin.x][begin.y].ChessName == "炮")
		{
			std::cout << "Moveing" << std::endl;
			return MoveCannon();
		}
		else if (_piece[begin.x][begin.y].ChessName == "卒" || _piece[begin.x][begin.y].ChessName == "兵")
		{
			std::cout << "Moveing" << std::endl;
			return MoveSoldier();
		}
		else return false;
	}
	else return false;
}

void Chess::Moveed()
{

	std::cout << "move" << std::endl;
	if (_piece[end.x][end.y].ChessName == "将")
	{
		settextstyle(30, 10, "隶书");
		std::cout << "红方胜利" << std::endl;
		outtextxy(2 * CHESS_SIZE + 20, 4 * CHESS_SIZE + 10, "红方胜利");
		GameOverx = true;
	}
	else if (_piece[end.x][end.y].ChessName == "帥")
	{
		settextstyle(30, 10, "隶书");
		std::cout << "黑方胜利" << std::endl;
		outtextxy(2 * CHESS_SIZE + 20, 4 * CHESS_SIZE + 10, "黑方胜利");

		GameOverx = true;
	}
	if (RedOrBlack == nowcolor)
	{
		mysend(mySocket);
	}
	_piece[end.x][end.y].ChessName = _piece[begin.x][begin.y].ChessName;
	RedOrBlack = RedOrBlack == 'R' ? 'B' : 'R';
	_piece[begin.x][begin.y].ChessName = "";
	_piece[end.x][end.y].color = _piece[begin.x][begin.y].color;
	_piece[begin.x][begin.y].color = 'N';
	_piece[end.x][end.y].address = _piece[begin.x][begin.y].address;
	_piece[begin.x][begin.y].address = "";
	std::cout << _piece[end.x][end.y].address << std::endl;
	std::cout << _piece[begin.x][begin.y].address << std::endl;
	loadimage(&_piece[end.x][end.y].picture, (LPCTSTR)_piece[end.x][end.y].address.c_str(), 60, 60, true);
	std::cout << _piece[end.x][end.y].point.x << " " << _piece[end.x][end.y].point.y << std::endl;
	_piece[end.x][end.y].ifriver = ifRiver();
}
//成功移动
void Chess::refresh()
{
	cleardevice();
	DrawBoard();
	settextstyle(30, 10, "隶书");
	if (RedOrBlack == 'R')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "红方走棋");
	}
	else if (RedOrBlack == 'B')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "黑方走棋");
	}
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (_piece[i][j].ChessName != "")
			{
				putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
			}
		}
	}
}

//刷新

void Chess::GetControl()
{
	int subtemp;
	if (peekmessage(&chessmsg, EM_MOUSE))
	{
		if (chessmsg.message == WM_LBUTTONDOWN)
		{
			//piece clickpiece = isClickOnpiece(chessmsg.x-INTERVAL, chessmsg.y-INTERVAL);//鼠标点击位置显示不受设置原点影响，适应棋盘绘画位置设置
			////将鼠标点击位置设置为设置原点后的位置。
			//if(chessmsg.x>=-40&&chessmsg.x<=8*CHESS_SIZE+40&&chessmsg.y>=-40&&chessmsg.y<=9*CHESS_SIZE+40)
			{//点击位置在键盘内
				subtemp = (chessmsg.x - INTERVAL) / CHESS_SIZE;
				int  subscriptx = subtemp * CHESS_SIZE + (abs(subtemp * CHESS_SIZE - chessmsg.x + INTERVAL) > abs((subtemp + 1) * CHESS_SIZE - chessmsg.x + INTERVAL) ? CHESS_SIZE : 0);
				subtemp = (chessmsg.y - INTERVAL) / CHESS_SIZE;
				int subscripty = subtemp * CHESS_SIZE + (abs(subtemp * CHESS_SIZE - chessmsg.y + INTERVAL) > abs((subtemp + 1) * CHESS_SIZE - chessmsg.y + INTERVAL) ? CHESS_SIZE : 0);
				int subrow = subscriptx / CHESS_SIZE;
				int subcol = subscripty / CHESS_SIZE;
				std::cout << "x:" << subrow << " y:" << subcol << std::endl;
				std::cout << _piece[subcol][subrow].ChessName << std::endl;
				if (_piece[subcol][subrow].ChessName != "" && begindown == 0 && _piece[subcol][subrow].color == RedOrBlack && RedOrBlack == nowcolor)
				{
					begin = { subcol,subrow };
					begindown = 1;
					std::cout << "First is button" << std::endl;
					std::cout << begin.x << " " << begin.y << std::endl;
				}
				else if (begindown == 1) {
					end = { subcol,subrow };
					begindown = 0;
					std::cout << "second is button" << std::endl;
					std::cout << end.x << " " << end.y << std::endl;
					if (MoveChess())
					{
						mciSendString("close music", NULL, 0, NULL);
						mciSendString("open resource\\1.mp3 alias music", NULL, 0, NULL);
						mciSendString("play music", NULL, 0, NULL);
						Moveed();
						Sleep(200);
					}
					testChessName();
				}

			}
		}
	}
}
//鼠标点击
bool Chess::MoveRook()
{
	if (begin.x == end.x)
	{
		for (int i = MIN(begin.y, end.y) + 1; i < MAX(begin.y, end.y); i++)
		{
			if (_piece[begin.x][i].ChessName != "")
			{
				return false;
			}
		}
		return true;
	}
	else if (begin.y == end.y)
	{
		for (int i = MIN(begin.x, end.x) + 1; i < MAX(begin.x, end.x); i++)
		{
			if (_piece[i][begin.y].ChessName != "")
			{
				return false;
			}
		}
		return true;
	}
	else return false;
}
//車
bool Chess::MoveHorse()
{
	if ((abs(begin.x - end.x) == 1 && abs(begin.y - end.y) == 2) || ((abs(begin.x - end.x) == 2 && abs(begin.y - end.y) == 1)))
	{
		if (abs(begin.y - end.y) == 1)//若横坐标相差为一
		{
			if (begin.x > end.x)
			{
				if (_piece[begin.x - 1][begin.y].ChessName == "")
					return true;
				else return false;
			}
			else if (end.x > begin.x)
			{
				if (_piece[begin.x + 1][begin.y].ChessName == "")
					return true;
				else return false;
			}
			else return false;
		}
		else if (abs(begin.x - end.x) == 1)//若纵坐标相差为一
		{
			if (begin.y > end.y)
			{
				if (_piece[begin.x][begin.y - 1].ChessName == "")
					return true;
				else return false;
			}
			else if (end.y > begin.y)
			{
				if (_piece[begin.x][begin.y + 1].ChessName == "")
					return true;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}
//馬
bool Chess::MoveElephant()
{
	if (_piece[begin.x][begin.y].color == 'B' ? end.x < 5 : end.x>4)
	{
		if (abs(begin.x - end.x) == 2 && abs(begin.y - end.y) == 2)
		{
			if (end.x < begin.x && end.y < begin.y)
			{
				if (_piece[end.x + 1][end.y + 1].ChessName == "")
					return true;
				else return false;
			}
			else if (end.x<begin.x && end.y>begin.y)
			{
				if (_piece[end.x + 1][begin.y + 1].ChessName == "")
					return true;
				else return false;
			}
			else if (end.x > begin.x && end.y > begin.y)
			{
				if (_piece[begin.x + 1][begin.y + 1].ChessName == "")
					return true;
				else return false;
			}
			else if (end.x > begin.x && end.y < begin.y)
			{
				if (_piece[begin.x + 1][end.y + 1].ChessName == "")
					return true;
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

//相
bool Chess::ifRiver()
{
	if (_piece[end.x][end.y].color == 'B')
		return end.x > 4 ? true : false;
	else if (_piece[end.x][end.y].color == 'R')
		return end.x < 5 ? true : false;
	else return false;
}
//是否过河
bool Chess::MoveAdviser()
{
	if (end.y >= 3 && end.y <= 5 && (_piece[begin.x][begin.y].color == 'B' ? (end.x >= 0 && end.x <= 2) : (end.x >= 7 && end.x <= 9)))
	{
		if (abs(begin.x - end.x) == 1 && abs(begin.y - end.y) == 1)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool Chess::MoveGeneral()
{
	if (end.y >= 3 && end.y <= 5 && (_piece[begin.x][begin.y].color == 'B' ? (end.x >= 0 && end.x <= 2) : (end.x >= 7 && end.x <= 9)))
	{
		if ((abs(begin.x - end.x) == 0 && abs(begin.y - end.y) == 1) || (abs(begin.x - end.x) == 1 && abs(begin.y - end.y) == 0))
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool Chess::MoveCannon()
{
	if (_piece[end.x][end.y].ChessName == "")
	{
		if (begin.x == end.x)
		{
			for (int i = MIN(begin.y, end.y) + 1; i < MAX(begin.y, end.y); i++)
			{
				if (_piece[begin.x][i].ChessName != "")
				{
					return false;
				}
			}
			return true;
		}
		else if (begin.y == end.y)
		{
			for (int i = MIN(begin.x, end.x) + 1; i < MAX(begin.x, end.x); i++)
			{
				if (_piece[i][begin.y].ChessName != "")
				{
					return false;
				}
			}
			return true;
		}
		else return false;
	}
	else if (_piece[end.x][end.y].ChessName != "")
	{
		int Count = 0;
		if (begin.x == end.x)
		{
			for (int i = MIN(begin.y, end.y) + 1; i < MAX(begin.y, end.y); i++)
			{
				if (_piece[begin.x][i].ChessName != "")
				{
					Count++;
				}
				if (Count > 1)return false;
			}
			if (Count == 1)return true;
			else return false;
		}
		else if (begin.y == end.y)
		{
			for (int i = MIN(begin.x, end.x) + 1; i < MAX(begin.x, end.x); i++)
			{
				if (_piece[i][begin.y].ChessName != "")
				{
					Count++;
				}if (Count > 1)return false;
			}
			if (Count == 1)return true;
			else return false;
		}
		else return false;
	}
	else return false;
}

bool Chess::MoveSoldier()
{
	if (_piece[begin.x][begin.y].ifriver == false)
	{
		if ((_piece[begin.x][begin.y].color == 'B' ? (end.x - begin.x == 1) : _piece[begin.x][begin.y].color == 'R' ? (begin.x - end.x == 1) : false) && end.y == begin.y)
		{
			return true;
		}
		else return false;
	}
	else if (_piece[begin.x][begin.y].ifriver)
	{
		if ((_piece[begin.x][begin.y].color == 'B' ? (end.x - begin.x == 1) : _piece[begin.x][begin.y].color == 'R' ? (begin.x - end.x == 1) : false) && end.y == begin.y)
		{
			return true;
		}
		else if (abs(end.y - begin.y) == 1 && end.x == begin.x)
		{
			return true;
		}
		else return false;
	}
	else return false;
}
//兵
void Chess::testpoint()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			std::cout << _piece[i][j].point.x << " " << _piece[i][j].point.y << "  ";
		}
		std::cout << std::endl;
		if (i == 4)
		{
			std::cout << std::endl;
		}
	}
}
//位置测试

void Chess::testChessName()
{

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			std::cout << _piece[i][j].ChessName;
			if (_piece[i][j].ChessName == "")
			{
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
		if (i == 4)
		{
			std::cout << std::endl;
		}
	}
}
//名字测试

void Chess::testaddress()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{

			std::cout << _piece[i][j].address << std::endl;
		}
	}
}
//图片地址测试
void Chess::testcolor()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{

			std::cout << _piece[i][j].color << " ";
		}
		std::cout << std::endl;
		if (i == 4)
		{
			std::cout << std::endl;
		}
	}
}
//颜色测试
void Chess::test()
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i < 5) {
				if (i == 0) {
					if (j < 5) {
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
					else {
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
				if (i == 2) {
					if (j == 1 || j == 7) {
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}//炮
				}
				if (i == 3) {
					if (j % 2 == 0)
					{
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
			}
			else {
				_piece[i][j].color = 'R';
				if (i == 9) {
					if (j < 5) {
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
					else {
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
				if (i == 6)
				{
					if (j % 2 == 0)
					{
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
				if (i == 7)
				{
					if (j == 1 || j == 7) {
						putimage(_piece[i][j].point.x - 30, _piece[i][j].point.y - 30, &_piece[i][j].picture);
					}
				}
			}

		}
	}
}

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
	settextstyle(30, 10, "����");
	if (RedOrBlack == 'R')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "�췽����");
	}
	else if (RedOrBlack == 'B')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "�ڷ�����");
	}
	Gameinit();
}

Chess::~Chess()
{

}

void Chess::Gameinit()
{
	setorigin(INTERVAL, INTERVAL);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			_piece[i][j].point.x = j * CHESS_SIZE;//����
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
						_piece[i][j].ChessName.assign(_black[8 - j]);//�۷���ʼ���������˽�
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
					}//��
				}
				if (i == 3) {
					if (j % 2 == 0)
					{
						_piece[i][j].ChessName.assign(_black[6]);//��
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
				_piece[i][j].ifriver = false;//�Ƿ����
		}
	}

}

//��ʼ��//������colorΪ  N  
//��������isriver

bool Chess::MoveChess()
{
	std::cout << "MoveChess" << std::endl;
	if ((!(begin.x == end.x && begin.y == end.y)) && _piece[begin.x][begin.y].color != _piece[end.x][end.y].color)//�������ͬһλ��
	{
		if (_piece[begin.x][begin.y].ChessName == "܇")
		{
			std::cout << "Moveing" << std::endl;
			return MoveRook();

		}
		else if (_piece[begin.x][begin.y].ChessName == "�R" || _piece[begin.x][begin.y].ChessName == "��")
		{
			std::cout << "Moveing" << std::endl;
			return MoveHorse();

		}
		else if (_piece[begin.x][begin.y].ChessName == "��" || _piece[begin.x][begin.y].ChessName == "��")
		{
			std::cout << "Moveing" << std::endl;
			return MoveElephant();

		}
		else if (_piece[begin.x][begin.y].ChessName == "��" || _piece[begin.x][begin.y].ChessName == "ʿ")
		{
			std::cout << "Moveing" << std::endl;
			return MoveAdviser();

		}
		else if (_piece[begin.x][begin.y].ChessName == "��" || _piece[begin.x][begin.y].ChessName == "��")
		{
			std::cout << "Moveing" << std::endl;
			return MoveGeneral();

		}
		else if (_piece[begin.x][begin.y].ChessName == "��")
		{
			std::cout << "Moveing" << std::endl;
			return MoveCannon();
		}
		else if (_piece[begin.x][begin.y].ChessName == "��" || _piece[begin.x][begin.y].ChessName == "��")
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
	if (_piece[end.x][end.y].ChessName == "��")
	{
		settextstyle(30, 10, "����");
		std::cout << "�췽ʤ��" << std::endl;
		outtextxy(2 * CHESS_SIZE + 20, 4 * CHESS_SIZE + 10, "�췽ʤ��");
		GameOverx = true;
	}
	else if (_piece[end.x][end.y].ChessName == "��")
	{
		settextstyle(30, 10, "����");
		std::cout << "�ڷ�ʤ��" << std::endl;
		outtextxy(2 * CHESS_SIZE + 20, 4 * CHESS_SIZE + 10, "�ڷ�ʤ��");

		GameOverx = true;
	}

	_piece[end.x][end.y].ChessName = _piece[begin.x][begin.y].ChessName;
	RedOrBlack = _piece[begin.x][begin.y].color == 'R' ? 'B' : 'R';
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
//�ɹ��ƶ�
void Chess::refresh()
{
	cleardevice();
	DrawBoard();
	settextstyle(30, 10, "����");
	if (RedOrBlack == 'R')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "�췽����");
	}
	else if (RedOrBlack == 'B')
	{
		outtextxy(10 * CHESS_SIZE - 10, 2 * CHESS_SIZE + 10, "�ڷ�����");
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

//ˢ��

void Chess::GetControl()
{
	int subtemp;
	if (peekmessage(&chessmsg, EM_MOUSE))
	{
		if (chessmsg.message == WM_LBUTTONDOWN)
		{
			//piece clickpiece = isClickOnpiece(chessmsg.x-INTERVAL, chessmsg.y-INTERVAL);//�����λ����ʾ��������ԭ��Ӱ�죬��Ӧ���̻滭λ������
			////�������λ������Ϊ����ԭ����λ�á�
			//if(chessmsg.x>=-40&&chessmsg.x<=8*CHESS_SIZE+40&&chessmsg.y>=-40&&chessmsg.y<=9*CHESS_SIZE+40)

			{//���λ���ڼ�����
				subtemp = (chessmsg.x - INTERVAL) / CHESS_SIZE;
				int  subscriptx = subtemp * CHESS_SIZE + (abs(subtemp * CHESS_SIZE - chessmsg.x + INTERVAL) > abs((subtemp + 1) * CHESS_SIZE - chessmsg.x + INTERVAL) ? CHESS_SIZE : 0);
				subtemp = (chessmsg.y - INTERVAL) / CHESS_SIZE;
				int subscripty = subtemp * CHESS_SIZE + (abs(subtemp * CHESS_SIZE - chessmsg.y + INTERVAL) > abs((subtemp + 1) * CHESS_SIZE - chessmsg.y + INTERVAL) ? CHESS_SIZE : 0);
				int subrow = subscriptx / CHESS_SIZE;
				int subcol = subscripty / CHESS_SIZE;
				std::cout << "x:" << subrow << " y:" << subcol << std::endl;
				std::cout << _piece[subcol][subrow].ChessName << std::endl;
				if (_piece[subcol][subrow].ChessName != "" && begindown == 0 && _piece[subcol][subrow].color == RedOrBlack)
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
//�����
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
//܇
bool Chess::MoveHorse()
{
	if ((abs(begin.x - end.x) == 1 && abs(begin.y - end.y) == 2) || ((abs(begin.x - end.x) == 2 && abs(begin.y - end.y) == 1)))
	{
		if (abs(begin.y - end.y) == 1)//�����������Ϊһ
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
		else if (abs(begin.x - end.x) == 1)//�����������Ϊһ
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
//�R
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

//��
bool Chess::ifRiver()
{
	if (_piece[end.x][end.y].color == 'B')
		return end.x > 4 ? true : false;
	else if (_piece[end.x][end.y].color == 'R')
		return end.x < 5 ? true : false;
	else return false;
}
//�Ƿ����
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
//��
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
//λ�ò���

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
//���ֲ���

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
//ͼƬ��ַ����
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
//��ɫ����
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
					}//��
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

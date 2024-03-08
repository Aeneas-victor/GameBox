#include"Chess.h"
extern bool GameUnderway;
void GameChinaChessModeBegin()
{
	GameUnderway = true;
	Chess* chess = new Chess;
	chess->testChessName();
	chess->testpoint();
	chess->testcolor();
	chess->testaddress();
	chess->myconnect();
	BeginBatchDraw();
	while (!chess->GameOverx)
	{
		chess->GetControl();
		chess->refresh();
		FlushBatchDraw();
	}
	EndBatchDraw();
	ExMessage mess;
	while (1) {
		if (peekmessage(&mess, EM_MOUSE))
		{
			if (mess.message == WM_LBUTTONDOWN)
			{
				break;
			}
		}
	}
	delete chess;
	if (GameUnderway != false)
		GameUnderway = false;
}
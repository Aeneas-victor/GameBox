#include"Snake.h"
extern void GamePause(bool* GameOvertemp);
extern void GameExit(bool& XGameOver);
extern bool GameUnderway;
HWND DesktopHandle;
void SnakeMode()
{
	Snake* psnake = new Snake;
	bool* pointer;
	cout << "Game is begin!" << endl;
	while (!psnake->SnakeGameOver)
	{
		pointer = &psnake->SnakeGameOver;
		GamePause(pointer);
		if (psnake->GameOver()) {
			cout << "Game is over" << endl;
			MessageBox(GetDesktopWindow(),"×²µ½ÉßÉíÁË", "Game Over!", MB_OK);
			psnake->SnakeGameOver = true;
			GameUnderway = false;
			break;
		}
		psnake->DramSnake();
		psnake->SnakeInput();
		psnake->MoveSnake();
		GameExit(psnake->SnakeGameOver);
		Sleep(100);
	}
	psnake->Music(2);
	delete psnake;
}

void GameSnakeModeBegin()
{
	GameUnderway = true;
	cout << "Welcome to my Game Box" << endl;
	cout << "plase input you select" << endl;
	SnakeMode();
}
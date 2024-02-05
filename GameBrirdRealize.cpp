#include"Brird.h"
extern int WallNum;
extern void GamePause(bool* GameOvertemp);
extern void GameExit(bool& xgameover);
extern bool GameUnderway;
void GameBrirdModeBegin()
{
	GameUnderway = true;
	Wall* pwall = new Wall;
	bool* brirdgamepointer;
	pwall->Music(1);
	pwall->brirdgame->Gameinit();
	std::cout << "Gameinit" << std::endl;
	std::cout << "SCREENX" << pwall->brirdgame->GetWidth() << std::endl;
	std::cout << ((pwall->brirdgame->GetWidth() - 2 * ICONSIZE) / ICONSIZE) - 5 << std::endl;
	std::cout << WallNum << std::endl;
	pwall->wallinit();
	brirdgamepointer = &pwall->BrirdGameOver;
	while (pwall->BrirdGameOver)
	{
		GamePause(brirdgamepointer);
		pwall->print();
		pwall->Jump();
		GameExit(pwall->BrirdGameOver);
		Sleep(50);
	}
	if (GameUnderway != false)
		GameUnderway = false;
	pwall->Music(2);
	delete pwall;
}
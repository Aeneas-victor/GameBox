#include"common.h"
#include<iostream>
#include<vector>
#include<Windows.h>
bool gamepause = false;
extern bool GameUnderway;
using namespace std;
////BOOL CALLBACK��ʾһ���ص������ķ���ֵΪ����ֵ
////LPARAM  //windows�е�һ����ʾ�����͵Ĳ���
//BOOL CALLBACK EnumerationWindowProc(HWND hwnd, LPARAM parametric)
//{
//	std::vector<HWND>* WindowsDesktopHandle = (std::vector<HWND>*)parametric;
//	//����һ��vector������������ΪWorkerW�ľ��
//	char ClassName[256];
//	GetClassName(hwnd, ClassName, sizeof(ClassName));
//	//GetClassName������Ҫ֪��ClassName�������Ĵ�С����ȷ��������д�볬���������߽�����ݡ�
//	//����ʹ��sizeof��̬��ȡClassName�Ĵ�С
//	if (strcmp(ClassName, "WorkerW") == 0 || strcmp(ClassName, "Progman") == 0)
//	{
//		// �ҵ�����Ϊ"WorkerW"�Ĵ��ڣ���¼����
//		//��Ϊ���ڶ����������������Ϊ��WorkerW"�����
//		WindowsDesktopHandle->push_back(hwnd);
//	}
//	return TRUE;
//}
//std::vector<HWND> EnumerationWindowHandle()
//{
//	std::vector<HWND>WorkerWHandle;
//	// ö�����ж�������
//	EnumWindows(EnumerationWindowProc, (LPARAM)&WorkerWHandle);
//	return WorkerWHandle;
//}
void GamePause(bool* GameOvertemp)
{
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) // ���ո������
    {
        if (gamepause)
        {
            // ���¿ո�����л�Ϊ������Ϸ
            gamepause = false;
        }
        else
        {
            // ���¿ո�����л�Ϊ��ͣ��Ϸ
            gamepause = true;
            int result = MessageBox(GetDesktopWindow(), "�Ƿ������Ϸ?", "��ͣ", MB_YESNO);
            if (result == IDYES)
            {
                gamepause = false; // �û�ѡ�������Ϸ
            }
            if (result == IDNO)
            {
                *GameOvertemp = !*GameOvertemp;
                GameUnderway = false;
            }
        }
    }
}
void GameExit(bool& XGameOver)
{
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        XGameOver = !XGameOver;
        MessageBox(GetDesktopWindow(),"�ѽ�����Ϸ","��ʾ",MB_OK);
        GameUnderway = false;
    }
}

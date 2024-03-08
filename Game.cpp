#include"Game.h"
std::map<std::string, std::string>_FilePath;//firstΪ�ļ�����//secondΪ·��
Game::Game()
{
    desktop = GetDesktopHandle();
    cout << "Game::Game()->win" << endl;
    cout << "HWND:" << desktop << endl;
}
Game::~Game()
{
    for (auto b : _FilePath)
    {
        LPCSTR c(b.second.c_str());
        if (DeleteFile(c))//ɾ�����ڴ������ļ�
        {
            cout << "File delete successfully!" << endl;
        }
        else
        {
            cout << "Failed to delete file!" << endl;
        }
    }
}
//HWND Game::GetDesktopHandle()//��Ҫ��ȡ������;����ֻ��ȡһ�Σ�ʣ����һ�������Getdesktop������ȡ
//{//////����������ʹ��function.cpp�еĻص�����
//	std::vector<HWND>WorkerWHandle = EnumerationWindowHandle();
//	if (!WorkerWHandle.empty()) {
//		//for (std::vector<HWND>::iterator it = WorkerWHandle.begin(); it != WorkerWHandle.end(); it++){
//		for (HWND hwnd : WorkerWHandle) {
//			//��������vector�����������Ӵ���
//			HWND SHELLDLLDefView = FindWindowExA(hwnd, NULL, "SHELLDLL_DefView", NULL);
//			if (SHELLDLLDefView == NULL) {
//				continue;
//			}
//			else {
//				HWND HwndSysListView32 = FindWindowExA(SHELLDLLDefView, NULL, "SysListView32", NULL);
//				if (HwndSysListView32 == NULL) {
//					continue;
//				}
//				else {
//					cout << "GetdesktopMain->win" << endl;
//					return HwndSysListView32;
//				}
//			}
//		}
//	}
//	else
//	{
//		cout << "GetdesktopMain->fail" << endl;
//		return NULL;
//	}
//}
HWND Game::GetDesktopHandle()//��Ҫ��ȡ������;����ֻ��ȡһ�Σ�ʣ����һ�������Getdesktop������ȡ
{//////////����һ
   return GetIconHandle();
   /* HWND DesktopHandle = GetDesktopWindow();
    HWND WorkerWHandle = NULL;
    HWND SHELLDLLDefViewHandle = NULL;
    HWND SysListView32Handle = NULL;
    HWND ProgmanHandle = NULL;
    ProgmanHandle = FindWindowExA(DesktopHandle, NULL, "Progman", NULL);
    SHELLDLLDefViewHandle = FindWindowExA(ProgmanHandle, NULL, "SHELLDLL_DefView", NULL);
    if (SHELLDLLDefViewHandle == NULL) {
        WorkerWHandle = FindWindowExA(DesktopHandle, WorkerWHandle, "WorkerW", NULL);
        SHELLDLLDefViewHandle = FindWindowExA(WorkerWHandle, NULL, "SHELLDLL_DefView", NULL);
        while (SHELLDLLDefViewHandle == NULL && WorkerWHandle != NULL) {
            WorkerWHandle = FindWindowExA(DesktopHandle, WorkerWHandle, "WorkerW", NULL);
            SHELLDLLDefViewHandle = FindWindowExA(WorkerWHandle, NULL, "SHELLDLL_DefView", NULL);
        }
    }
    SysListView32Handle = FindWindowExA(SHELLDLLDefViewHandle, NULL, "SysListView32", NULL);
    return SysListView32Handle;*/
}
void Game::Gameinit()//��Ϸ��ʼ��������ͼ�꣬
{
    //��������ʽȡ��/////////////////////////////////////////////////////////////////
    Negation(desktop);
   /* DWORD style = ListView_GetExtendedListViewStyle(desktop, GWL_EXSTYLE);
    if (style & LVS_EX_SNAPTOGRID)
    {
        ListView_SetExtendedListViewStyle(desktop, style & ~LVS_EX_SNAPTOGRID);
    }*/
    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////��ȡ�ؼ�����

    iconCount = SendMessage(desktop, LVM_GETITEMCOUNT, 0, 0);
    TCHAR path[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path);
    cout << path << endl;
    string slash = "\\";
    while (iconCount < 90)//ͼ��С��90��-�������洴��ini�ļ�
    {
        string name = to_string(iconCount++) + ".ini";//�������Ϊ�ڼ���ͼ�����ini��׺
        string tempPath(path); // ��TCHAR·��ת��Ϊstd::string
        tempPath += slash + name; // ƴ��·�����ļ���
        LPCSTR Path = tempPath.c_str(); // ��ȡC����ַ���
        _FilePath.insert(make_pair(name, Path));//��������
        //////////////�����ļ�/////
        HANDLE hFile = CreateFile(Path,//·��
                                  GENERIC_WRITE,//������ļ����豸�ķ���Ȩ��
                                  0,            //������ļ����豸�Ĺ���ģʽ
                                  NULL,//�ļ����豸���Ժͱ�־ FILE_ATTRIBUTE_NORMAL ���ļ������Ĭ��ֵ��
                                  CREATE_ALWAYS,//
                                  FILE_ATTRIBUTE_NORMAL,//���ļ�δ�����������ԡ� �����Խ��ڵ���ʹ��ʱ��Ч��
                                  NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            std::cout << "File created successfully!" << std::endl;
            CloseHandle(hFile); // �ر��ļ����
        }
        else {
            std::cout << "Failed to create file!" << std::endl;
        }
    }
    //Get  Systemϵͳ
    //   Metrics ������ָ��
    //   SM_CXSCREEN
    // //GetSystemMetrics
    //����ָ����ϵͳָ���ϵͳ�������á�
   // ��ע�⣬ GetSystemMetrics ����������ά�ȶ�������Ϊ��λ��
    Width = GetSystemMetrics(SM_CXSCREEN) * 1.5; //��ȡ��Ļ�ķֱ���(��)
    Height = GetSystemMetrics(SM_CYSCREEN) * 1.5;//���豸���õ�DPI���ţ�ʹ��Ϊ150%;���Ի�ȡʹ�������1.5
    //����λ��Ϊ  x=30   y=1380  ���½�λ��,
//������Ļ�߽�Ϊ
    int screenx = 30;
    int screeny = Height - BORDER;
    RECT rect;
    POINT iconposition;

    //��������ͼ��
    for (int i = 0; i < iconCount; i++)
    {
        ListView_SetItemPosition(desktop, i, screenx, screeny);
        //////////�ƶ�λ�ú���
        /*SendMessageA(desktop, LVM_SETITEMPOSITION, i, (screeny << 16) + screenx);*/
    }////////////����λ�ú���
    cout << "Width:" << Width << "   " << "Height" << Height << endl;
}
int Game::GetWidth()//��Ļ��
{

    return Width;
}

int Game::GetHeight()//��Ļ��
{
    return Height;
}

int Game::GetIconCount()
{
    return iconCount;
}


HWND Game::Getdesktop()//��ȡ�ѻ�õ�desktop�ľ��
{
    return desktop;
}


#include"Game.h"
std::map<std::string, std::string>_FilePath;//first为文件名，//second为路径
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
        if (DeleteFile(c))//删除多于创建的文件
        {
            cout << "File delete successfully!" << endl;
        }
        else
        {
            cout << "Failed to delete file!" << endl;
        }
    }
}
//HWND Game::GetDesktopHandle()//主要获取桌面句柄途径，只获取一次，剩下由一储存过的Getdesktop（）获取
//{//////方法二，需使用function.cpp中的回调函数
//	std::vector<HWND>WorkerWHandle = EnumerationWindowHandle();
//	if (!WorkerWHandle.empty()) {
//		//for (std::vector<HWND>::iterator it = WorkerWHandle.begin(); it != WorkerWHandle.end(); it++){
//		for (HWND hwnd : WorkerWHandle) {
//			//遍历整个vector容器查找其子窗口
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
HWND Game::GetDesktopHandle()//主要获取桌面句柄途径，只获取一次，剩下由一储存过的Getdesktop（）获取
{//////////方法一
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
void Game::Gameinit()//游戏初始化，隐藏图标，
{
    //将桌面样式取反/////////////////////////////////////////////////////////////////
    Negation(desktop);
   /* DWORD style = ListView_GetExtendedListViewStyle(desktop, GWL_EXSTYLE);
    if (style & LVS_EX_SNAPTOGRID)
    {
        ListView_SetExtendedListViewStyle(desktop, style & ~LVS_EX_SNAPTOGRID);
    }*/
    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////获取控件个数

    iconCount = SendMessage(desktop, LVM_GETITEMCOUNT, 0, 0);
    TCHAR path[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path);
    cout << path << endl;
    string slash = "\\";
    while (iconCount < 90)//图标小于90个-》在桌面创建ini文件
    {
        string name = to_string(iconCount++) + ".ini";//名字组成为第几号图标加上ini后缀
        string tempPath(path); // 将TCHAR路径转换为std::string
        tempPath += slash + name; // 拼接路径和文件名
        LPCSTR Path = tempPath.c_str(); // 获取C风格字符串
        _FilePath.insert(make_pair(name, Path));//创建对组
        //////////////创建文件/////
        HANDLE hFile = CreateFile(Path,//路径
                                  GENERIC_WRITE,//请求对文件或设备的访问权限
                                  0,            //请求的文件或设备的共享模式
                                  NULL,//文件或设备属性和标志 FILE_ATTRIBUTE_NORMAL 是文件最常见的默认值。
                                  CREATE_ALWAYS,//
                                  FILE_ATTRIBUTE_NORMAL,//该文件未设置其他属性。 此属性仅在单独使用时有效。
                                  NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            std::cout << "File created successfully!" << std::endl;
            CloseHandle(hFile); // 关闭文件句柄
        }
        else {
            std::cout << "Failed to create file!" << std::endl;
        }
    }
    //Get  System系统
    //   Metrics 度量，指标
    //   SM_CXSCREEN
    // //GetSystemMetrics
    //检索指定的系统指标或系统配置设置。
   // 请注意， GetSystemMetrics 检索的所有维度都以像素为单位。
    Width = GetSystemMetrics(SM_CXSCREEN) * 1.5; //获取屏幕的分辨率(宽)
    Height = GetSystemMetrics(SM_CYSCREEN) * 1.5;//本设备启用的DPI缩放，使其为150%;所以获取使按其乘以1.5
    //隐藏位置为  x=30   y=1380  左下角位置,
//电脑屏幕边界为
    int screenx = 30;
    int screeny = Height - BORDER;
    RECT rect;
    POINT iconposition;

    //隐藏桌面图标
    for (int i = 0; i < iconCount; i++)
    {
        ListView_SetItemPosition(desktop, i, screenx, screeny);
        //////////移动位置函数
        /*SendMessageA(desktop, LVM_SETITEMPOSITION, i, (screeny << 16) + screenx);*/
    }////////////设置位置函数
    cout << "Width:" << Width << "   " << "Height" << Height << endl;
}
int Game::GetWidth()//屏幕宽
{

    return Width;
}

int Game::GetHeight()//屏幕高
{
    return Height;
}

int Game::GetIconCount()
{
    return iconCount;
}


HWND Game::Getdesktop()//获取已获得的desktop的句柄
{
    return desktop;
}


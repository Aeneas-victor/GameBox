#include"Game.h"
static HWND desktop;
extern bool GameUnderway;
int d0[5][3] = { {1,1,1},
                 {1,0,1},
                 {1,0,1},
                 {1,0,1},
                 {1,1,1} };
int d1[5][3] = { {0,0,1},
                 {0,0,1},
                 {0,0,1},
                 {0,0,1},
                 {0,0,1} };
int d2[5][3] = { {1,1,1},
                 {0,0,1},
                 {1,1,1},
                 {1,0,0},
                 {1,1,1} };
int d3[5][3] = { {1,1,1},
                 {0,0,1},
                 {1,1,1},
                 {0,0,1},
                 {1,1,1} };
int d4[5][3] = { {1,0,1},
                 {1,0,1},
                 {1,1,1},
                 {0,0,1},
                 {0,0,1} };
int d5[5][3] = { {1,1,1},
                 {1,0,0},
                 {1,1,1},
                 {0,0,1},
                 {1,1,1} };
int d6[5][3] = { {1,1,1},
                 {1,0,0},
                 {1,1,1},
                 {1,0,1},
                 {1,1,1} };
int d7[5][3] = { {1,1,1},
                 {0,0,1},
                 {0,0,1},
                 {0,0,1},
                 {0,0,1} };
int d8[5][3] = { {1,1,1},
                 {1,0,1},
                 {1,1,1},
                 {1,0,1},
                 {1,1,1} };
int d9[5][3] = { {1,1,1},
                 {1,0,1},
                 {1,1,1},
                 {0,0,1},
                 {1,1,1} };

int(*arrayx[10])[5][3] = { &d0, &d1, &d2, &d3, &d4, &d5, &d6, &d7, &d8, &d9 };
POINT Second = { 1000,700 };
POINT Second0 = { 1320,700 };
POINT Minute{ 1600,220 };
POINT Minute0{ 1920,220 };
POINT Hour{ 420,220 };
POINT Hour0 = { 740,220 };
POINT(arrPOINT[6]) = { Second0 ,Second ,Minute0 ,Minute ,Hour0,Hour };
int Secondarr[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,78,79,90 };
int Secondarr0[16] = { 13,14,15,16,17,18,19,20,21,22,23,24,25,80,81 ,91 };
int Minutearr[16] = { 26,27,28,29,30,31,32,33,34,35,36,37,38,82,83 ,92 };
int Minutearr0[16] = { 39,40,41,42,43,44,45,46,47,48,49,50,51 ,84,85,93 };
int Hourarr[16] = { 52,53,54,55,56,57,58,59,60,61,62,63,64, 86,87,94 };
int Hourarr0[16] = { 65,66,67,68,69,70,71,72,73,74,75,76,77,88,89 ,95 };
int* arrayarrs[16] = { Secondarr0, Secondarr, Minutearr0,Minutearr, Hourarr0, Hourarr };
void SetPosition(int numberposition, int number)//a为哪个位置的数字0为秒的个位，以此类推
{
    std::mutex mtx;
    int h = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mtx.lock();
            if ((*arrayx[number])[i][j] == 1)
            {
                ListView_SetItemPosition(desktop, arrayarrs[numberposition][h++],
                    arrPOINT[numberposition].x + j * ICON_SIZE, arrPOINT[numberposition].y + i * ICON_SIZE);
            }
            else {
                ListView_SetItemPosition(desktop, arrayarrs[numberposition][h++], 30, 1380);
            }
            mtx.unlock();
        }
    }
}
void Timeinit(short& _sec0, short& _sec1, short& _min0, short& _min1, short& _hour0, short& _hour1)
{
    int a = 0;
    time_t nowtime;
    time(&nowtime);
    tm ptime;
    localtime_s(&ptime, &nowtime);
    _sec0 = ptime.tm_sec % 10; _sec1 = ptime.tm_sec / 10;
    _min0 = ptime.tm_min % 10; _min1 = ptime.tm_min / 10;
    _hour0 = ptime.tm_hour % 10; _hour1 = ptime.tm_hour / 10;
    thread sec0(SetPosition, 0, _sec0); sec0.detach();
    thread sec1(SetPosition, 1, _sec1); sec1.detach();
    thread min0(SetPosition, 2, _min0); min0.detach();
    thread min1(SetPosition, 3, _min1); min1.detach();
    thread hour0(SetPosition, 4, _hour0); hour0.detach();
    thread hour1(SetPosition, 5, _hour1); hour1.detach();
}
void ClockMode()
{
    GameUnderway = true;
    Game* GameClock=new Game;
    desktop = GameClock->Getdesktop();
    GameClock->Gameinit();//初始化位置
    short sec0, sec1, min0, min1, hour0, hour1;
    clock_t start_t, end_t;
    Timeinit(sec0, sec1, min0, min1, hour0, hour1);
    while (true)
    {
        start_t = clock(); sec0++;
        if (sec0 <= 9)
        {
            SetPosition(0, sec0);
        }
        else if (sec0 == 10) {
            sec0 = 0; sec1++;
            if (sec1 == 6)goto sec1_6;
            SetPosition(0, sec0);
            SetPosition(1, sec1);
        }
    sec1_6:
        if (sec1 == 6) {
            sec1 = 0; min0++;
            if (min0 == 10)goto min0_10;
            SetPosition(1, sec1);
            SetPosition(2, min0);
        }
    min0_10:
        if (min0 == 10) {
            min0 = 0; min1++;
            if (min1 == 6)goto min1_6;
            SetPosition(2, min0);
            SetPosition(3, min1);
        }
    min1_6:
        if (min1 == 6) {
            min1 = 0; hour0++;
            if (hour0 == 10)goto hour0_10;
            SetPosition(3, min1);
            SetPosition(4, hour0);
        }
    hour0_10:
        if (hour0 == 10) {
            hour0 = 0; hour1++;
            if (hour1 == 6)break;
            SetPosition(4, hour0);
            SetPosition(5, hour1);
        } if (hour1 == 2 && hour0 == 4) {
            hour0 = 0; hour1 = 0;
            min0 = 0; min1 = 0;
            sec0 = 0; sec1 = 0;
            thread h0(SetPosition, 4, hour0); h0.detach();
            thread h1(SetPosition, 5, hour1); h1.detach();
            thread m0(SetPosition, 2, min0); m0.detach();
            thread m1(SetPosition, 3, min1); m1.detach();
            thread s0(SetPosition, 0, sec0); s0.detach();
            thread s1(SetPosition, 1, sec1); s1.detach();
        }
        end_t = clock();
        std::cout << "程序运行时间：" << end_t - start_t << endl;
        Sleep(1000 - (double)(end_t - start_t));
    }
    delete GameClock;
    if (GameUnderway != false)
        GameUnderway = false;
}
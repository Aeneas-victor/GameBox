#ifndef STATICLIBDESKTOP_H
#define STATICLIBDESKTOP_H

#ifndef WINDOWS_H
#include<Windows.h>
#endif

#ifndef COMMCTRL_H
#include<CommCtrl.h>
#endif

#ifndef WINDEF_H
#include<windef.h>
#endif

HWND GetIconHandle();
void Negation(HWND desktop);
#endif

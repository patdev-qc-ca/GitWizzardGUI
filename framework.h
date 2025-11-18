#pragma once
#define LookTiner 0x01000 //timer horlogerie
#define KEY_DOWN(key) (GetAsyncKeyState(key) &0x8000)
#define LOWORD(l)           ((WORD)(l))
#include "targetver.h"
#define branche 'origin\\'
#define racine 'Main'
#define ko 0x400
#define Mo 0x100000
#define ERR_CLECHEMIN	1
#define ERR_NOM			2
#define ERR_FERMER		3
#define ERR_ECRIRE		4
#define ERR_CREERCLE	5
#define ERR_SUPRCLE		6
#define ERR_SUPRVAL		7
#define IDEFINE_GUID(n,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) const IGUID n = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
#define WIN32_LEAN_AND_MEAN     

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <WinSvc.h>
#include <Winreg.h>
#include <Shlwapi.h>
#include <commctrl.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include "ddraw.h"
#include <tlhelp32.h>
#include <lzexpand.h>
#include "resource.h"

#pragma comment (lib,"comctl32")
#pragma comment (lib,"Shlwapi")
#pragma comment (lib,"Advapi32")
#pragma comment (lib,"ddraw")
#pragma comment (lib,"dxguid")
#pragma comment(lib,"User32")
#pragma comment(lib,"Lz32")
#pragma comment(lib,"shlwapi")
#pragma comment(lib,"wininet")

#pragma warning(disable:28251)
#pragma warning(disable:26495)
#pragma warning(disable:6125)
#pragma warning(disable:6001)
#pragma warning(disable:28159)
#pragma warning(disable:6031)
#pragma warning(disable:4996)
#pragma warning(disable:4700)
#pragma warning(disable:4715)
#pragma warning(disable:4091)
typedef int(__cdecl* MYPROC)(LPWSTR);
// GitWizzardGUI.cpp : Définit le point d'entrée de l'application.
//

#include "pch.h"
#include "framework.h"
#include "GitWizzardGUI.h"

extern "C" BOOL SetLayeredWindowAttributesA(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
#define SetLayeredWindowAttributesA SetLayeredWindowAttributes

#define MAX_LOADSTRING 100
#pragma warning(disable:4996)

// Variables globales :
CHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
CHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale
CHAR tempon[MAX_PATH];
HINSTANCE hInst;
HICON hIcon;
COLORREF Avant = RGB(0, 128, 255),Arriere=RGB(84,84,84);
HWND hMain;
HMENU hmenu;
INITCOMMONCONTROLSEX iccex;
WNDCLASSEX wcex;
POINT pt;
LPDIRECTDRAW7			g_pDirectDraw;
LPDIRECTDRAWSURFACE7	g_pPrimarySurface,g_pSecondarySurface,g_pOffsreenSurface,g_pOffsreenSurface2;
DDSURFACEDESC2			g_ddsd;
DDSCAPS2				g_ddscaps;
HKEY hTempCle = 0,tBase = 0;
RGBA rgba;
REGS32 rg;
BOOL GestionErreur;
DOUBLE dwKeyEn = sizeof(LONG);
DWORD dwAttrs = 0x00,size=0x00;
LSTATUS returnValue = 0x00;
ULONG hResType = 0,dwLen = 0;
INT numpx=0;
PTCHAR data2 = NULL;

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine,_In_ INT       nCmdShow){
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	hInst = hInstance;
    LoadString(hInstance, 104, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_GITWIZZARDGUI, szWindowClass, MAX_LOADSTRING);
    ClasseFenetrePrincipale(hInstance);
    if (!InitialisationProgammePrincipal (hInstance, nCmdShow)) {   return FALSE;    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GITWIZZARDGUI));
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
   Fermeture();
   return (INT) msg.wParam;
}

ATOM ClasseFenetrePrincipale(HINSTANCE hInstance)
{
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = ProceduresProgammePrincipal;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
	hIcon = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_GITWIZZARDGUI);
    wcex.hIcon          = hIcon;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(Arriere);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_GITWIZZARDGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm = hIcon;
    return RegisterClassEx(&wcex);
}
BOOL InitialisationProgammePrincipal(HINSTANCE hInstance, INT nCmdShow)
{
	hInst = hInstance; 
	RECT rc;
	iccex.dwICC = ICC_LISTVIEW_CLASSES|ICC_TREEVIEW_CLASSES|ICC_BAR_CLASSES|ICC_TAB_CLASSES|ICC_UPDOWN_CLASS|ICC_PROGRESS_CLASS|ICC_HOTKEY_CLASS 
	|ICC_ANIMATE_CLASS|ICC_WIN95_CLASSES|ICC_DATE_CLASSES|ICC_COOL_CLASSES|ICC_INTERNET_CLASSES
	|ICC_PAGESCROLLER_CLASS|ICC_NATIVEFNTCTL_CLASS|ICC_STANDARD_CLASSES|ICC_LINK_CLASS;
	iccex.dwSize = sizeof(iccex);
	InitCommonControlsEx(&iccex);
	pt.x = 0x400;
	pt.y = 0x300;
	GetClientRect(GetDesktopWindow(), &rc);
	hMain = CreateWindowEx(WS_EX_CLIENTEDGE|WS_EX_CONTEXTHELP|WS_EX_DLGMODALFRAME,szWindowClass, szTitle, WS_OVERLAPPED |WS_CAPTION |WS_SYSMENU, 0, 0, pt.x,pt.y, nullptr, nullptr, hInstance, nullptr);
	if (!hMain){return FALSE;  }
	Initialize(hMain);
	ShowWindow(hMain, nCmdShow);
	AddShappe(hMain);
	return UpdateWindow(hMain);
}
LRESULT CALLBACK ProceduresProgammePrincipal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message){
    case WM_COMMAND:{
            INT wmId = LOWORD(wParam);
            // Analyse les sélections de menu :
            switch (wmId)
            {
            case IDM_ABOUT: DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, ProceduresProgammeAPropos);break;
            case IDM_EXIT:  DestroyWindow(hWnd);break;
			case ID_PRINCIPALESCOMMANDESGIT_CONFIG: GetID(32785);break;
			case ID_PRINCIPALESCOMMANDESGIT_INIT32786: GetID(32786);break;
			case ID_PRINCIPALESCOMMANDESGIT_ADD : GetID(32787);break;
			case ID_PRINCIPALESCOMMANDESGIT_CLONE: GetID(32788);break;
			case ID_PRINCIPALESCOMMANDESGIT_COMMIT: GetID(32789);break;
			case ID_PRINCIPALESCOMMANDESGIT_STATUS: GetID(32790);break;
			case ID_PRINCIPALESCOMMANDESGIT_PUSH: GetID(32791);break;
			case ID_PRINCIPALESCOMMANDESGIT_CHECKOUT: GetID(32792);break;
			case ID_PRINCIPALESCOMMANDESGIT_CHECKOUT32793: GetID(32793);break;
			case ID_PRINCIPALESCOMMANDESGIT_REMOTE: GetID(32794);break;
			case ID_PRINCIPALESCOMMANDESGIT_REMOTEADDORIGIN: GetID(32795);break;
			case ID_PRINCIPALESCOMMANDESGIT_BRANCH: GetID(32796);break;
			case ID_PRINCIPALESCOMMANDESGIT_PULL: GetID(32797);break;
			case ID_PRINCIPALESCOMMANDESGIT_MERGE: GetID(32798);break;
			case ID_PRINCIPALESCOMMANDESGIT_DIFF: GetID(32799);break;
			case ID_PRINCIPALESCOMMANDESGIT_TAG : GetID(32800);break;
			case ID_PRINCIPALESCOMMANDESGIT_LOG : GetID(32801);break;
			case ID_PRINCIPALESCOMMANDESGIT_RESET: GetID(32802);break;
			case ID_PRINCIPALESCOMMANDESGIT_RM  : GetID(32803);break;
			case ID_PRINCIPALESCOMMANDESGIT_STASH: GetID(32804);break;
			case ID_PRINCIPALESCOMMANDESGIT_SHOW: GetID(32805);break;
			case ID_PRINCIPALESCOMMANDESGIT_FETCH: GetID(32806);break;
			case ID_PRINCIPALESCOMMANDESGIT_LS  : GetID(32807);break;
			case ID_PRINCIPALESCOMMANDESGIT_GREP: GetID(32808);break;
			case ID_PRINCIPALESCOMMANDESGIT_GC  : GetID(32809);break;
			case ID_PRINCIPALESCOMMANDESGIT_ARCHIVE: GetID(32810);break;
			case ID_PRINCIPALESCOMMANDESGIT_PRUNE: GetID(32811);break;
			case ID_PRINCIPALESCOMMANDESGIT_FSCK: GetID(32812);break;
			case ID_PRINCIPALESCOMMANDESGIT_REBASE: GetID(32813);break;
			case ID_OPTIONS_CON: {ConfigurerOptionsPersonellesGiT();}break;           
			default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Ajoutez ici le code de dessin qui utilise hdc...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK ConfigGitUser(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG: {
		CreateStatusWindow(WS_CHILD | WS_VISIBLE, "TGîT créée par Patrice Waechter-Ebling 2022", hDlg, 6000);
	}return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam)) {
			case IDOK: {
				char tmp[256];
				GetDlgItemText(hDlg, IDC_GIT_USERNAME, tmp, 0x60);
				SetGitUserName(tmp);
				GetDlgItemText(hDlg, IDC_GIT_MAIL, tmp, 0x60);
				SetGitUserMail(tmp);
				GetDlgItemText(hDlg, IDC_GIT_MAIL, tmp, 0x60);
				SetGitUserName(tmp);
			//	IDC_SAFE_FOLDER
				
			}break;
			case IDCANCEL: {
			}return	EndDialog(hDlg, LOWORD(wParam));
		}
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK ProceduresProgammeAPropos(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
VOID CreerUneBranche(char* Branche)
{
	// TODO: Ajoutez ici votre code d'implémentation..
}
VOID SupprimerBranche(char* Branche)
{
	// TODO: Ajoutez ici votre code d'implémentation..
}
VOID ConfigurerOptionsPersonellesGiT(){	DialogBox(hInst, MAKEINTRESOURCE(131), hMain,ConfigGitUser );}
VOID GetServiceInfo(LPSTR subkey) {
	DWORD dwType = REG_SZ;
	HKEY hKey = 0;
	CHAR value[1024]={0x00};
	DWORD value_length = 1024;
	RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
	RegQueryValueEx(hKey, "ObjectName", NULL, &dwType, (LPBYTE)&rg.ObjectName, &value_length);
	RegQueryValueEx(hKey, "Description", NULL, &dwType, (LPBYTE)&rg.Description, &value_length);
	RegQueryValueEx(hKey, "ImagePath", NULL, &dwType, (LPBYTE)&rg.ImagePath, &value_length);
	RegQueryValueEx(hKey, "RequiredPrivileges", NULL, &dwType, (LPBYTE)&rg.RequiredPrivileges, &value_length);
	strcpy(rg.FilePath, rg.ImagePath);
	PathRemoveFileSpec(rg.FilePath);
}
REGS32 ExtractServiceInfo(LPSTR Service) {
	CHAR regKey[256];
	wsprintf(regKey,"SYSTEM\\CurrentControlSet\\Services\\%s",Service);
	GetServiceInfo(regKey);
	return rg;
}
VOID InscrireRegistre(){
	CHAR buffer[260];
	HKEY hClef=0;
	GetCurrentDirectory(256, buffer);
/*	CreerCle("HKEY_CLASSES_ROOT", "Software\\SOSPC", &hClef);
	CreerCle("HKEY_CLASSES_ROOT", "Software\\SOSPC\\Real Games", &hClef);
	CreerCle("HKEY_CLASSES_ROOT", "Software\\SOSPC\\Real Games\\ProxyGames", &hClef);
	CreerCle("HKEY_CLASSES_ROOT", "Software\\SOSPC\\Real Games\\ProxyGames\\RealArcadeGames4", &hClef);
	OuvrirCle("HKEY_CLASSES_ROOT", "Software\\SOSPC\\Real Games\\ProxyGames\\RealArcadeGames4", &hClef);
	EcrireValeur(hClef, "Path", (LPSTR)buffer, "REG_SZ");
	EcrireValeur(hClef, "Commande", (LPSTR)__argv[0], "REG_SZ");
	EcrireValeur(hClef, "Version", "2.23.47.0", "REG_SZ");
	CreerCle("HKEY_CLASSES_ROOT", "Software\\SOSPC\\Real Games\\ProxyGames\\RealArcadeGames4\\Config", &hClef);
	OuvrirCle("HKEY_CLASSES_ROOT", "Software\\SOSPC\\Real Games\\ProxyGames\\RealArcadeGames4\\Config", &hClef);
	EcrireValeur(hClef, "Nom", (LPSTR)buffer, "REG_SZ");
	EcrireValeur(hClef, "Société", (LPSTR)__argv[0], "REG_SZ");
	EcrireValeur(hClef, "Plateforme", "RealArcadeGames4", "REG_SZ");
	EcrireValeur(hClef, "Version", "RealArcadeGames4", "REG_SZ");
	EcrireValeur(hClef, "Clef", "wzjridsd4e4ex7d55dcvh2gf288ghb28b8f8rd4e455ww", "REG_SZ");
*/
}
LPSTR Phraser(CHAR* valeur) {
	CHAR* tmp = valeur;	tmp[0] = valeur[1] - 0x22;	tmp[1] = 0xEE;	tmp[2] = valeur[2] - 0x20;	strcat(tmp, ".");	return tmp;
}
VOID GetID(INT valeur) 
{	CHAR tmp[1024];	
	if (valeur >= ID_PRINCIPALESCOMMANDESGIT_CONFIG) {	LoadString(hInst, valeur-0x7F48, tmp, sizeof(tmp));		MessageBox(hMain, Phraser(tmp), "Informations rapides",MB_ICONINFORMATION | MB_OK);	}
	else {	MessageBeep(valeur);}
}
HKEY  ChoisirBase(LPSTR base){
	if (strcmp(base, "HKEY_CURRENT_USER") == 0)				tBase = HKEY_CURRENT_USER;
	else if (strcmp(base, "HKEY_USERS") == 0)				tBase = HKEY_USERS;
	else if (strcmp(base, "HKEY_LOCAL_MACHINE") == 0)		tBase = HKEY_LOCAL_MACHINE;
	else if (strcmp(base, "HKEY_CURRENT_CONFIG") == 0)		tBase = HKEY_CURRENT_CONFIG;
	else if (strcmp(base, "HKEY_CLASSES_ROOT") == 0)		tBase = HKEY_CLASSES_ROOT;
	return tBase;
}
ULONG ChoisirType(LPSTR type){
	if (strcmp(type, "REG_NONE") == 0)						hResType = REG_NONE;
	else if (strcmp(type, "REG_SZ") == 0)					hResType = REG_SZ;
	else if (strcmp(type, "REG_BINARY") == 0)				hResType = REG_BINARY;
	else if (strcmp(type, "REG_DWORD") == 0)				hResType = REG_DWORD;
	else if (strcmp(type, "REG_DWORD_BIG_ENDIAN") == 0)		hResType = REG_DWORD_BIG_ENDIAN;
	else if (strcmp(type, "REG_LINK") == 0)					hResType = REG_LINK;
	else if (strcmp(type, "REG_MULTI_SZ") == 0)				hResType = REG_MULTI_SZ;
	return hResType;
}

BOOL OuvrirCle(LPSTR base, LPSTR chemin, HKEY* hCle)
{
	returnValue = RegOpenKey(ChoisirBase(base), chemin, &hTempCle);
	if (returnValue != ERROR_SUCCESS) {if (GestionErreur)OnRegError(ERR_CLECHEMIN);return false;}
	*hCle = hTempCle;
	return 	true;
}

LPSTR LireValeur(HKEY hCle, LPSTR nom, BOOL* OpRes){
	returnValue = RegQueryValueEx(hCle, nom, NULL, NULL, NULL, &dwLen);
	returnValue = RegQueryValueEx(hCle, nom, NULL, NULL, (LPBYTE)&dwKeyEn, &dwLen);
	if (returnValue != ERROR_SUCCESS) { *OpRes = false; if (GestionErreur)OnRegError(ERR_NOM);return (LPSTR)"Erreur!";	}
	*OpRes = true;
	return (LPSTR)&dwKeyEn;
}
BOOL EcrireValeur(HKEY hCle, LPSTR nom, LPSTR valeur, LPSTR type){
	returnValue = RegSetValueEx(hCle, nom, NULL, ChoisirType(type), (PBYTE)valeur, strlen(valeur));
	if (returnValue != ERROR_SUCCESS) {if (GestionErreur)OnRegError(ERR_ECRIRE);return false;}
	return true;
}
BOOL  CreerCle(LPSTR base, LPSTR chemin, HKEY* hCle){
	HKEY hTempCle = 0;
	LONG returnValue = RegCreateKey(ChoisirBase(base), chemin, &hTempCle);
	if (returnValue != ERROR_SUCCESS) {if (GestionErreur)OnRegError(ERR_CREERCLE);return false;	}
	*hCle = hTempCle;
	return true;
}
BOOL  SupprimerCle(LPSTR base, LPSTR chemin){
	returnValue = RegDeleteKey(ChoisirBase(base), chemin);
	if (returnValue != ERROR_SUCCESS) {if (GestionErreur)OnRegError(ERR_SUPRCLE);return false;}
	return true;
}
BOOL  SupprimerValeur(LPSTR base, LPSTR chemin, LPSTR nom){
	if (!OuvrirCle(base, chemin, &hTempCle))return false;
	returnValue = RegDeleteValue(hTempCle, nom);
	if (returnValue != ERROR_SUCCESS) {	if (GestionErreur)OnRegError(ERR_SUPRVAL);	return false;}
	return true;
}
BOOL  FermerCle(HKEY hCle){
	returnValue = RegCloseKey(hCle);
	if (returnValue != ERROR_SUCCESS) {	if (GestionErreur)	OnRegError(ERR_FERMER);	return false;	}
	return true;
}
VOID  OnRegError(INT nError){
	Erreur err;
	err.style = MB_ICONSTOP;
	err.numero = nError;
	switch (nError) {
	case ERR_CLECHEMIN:	err.description = "La base et le chemin indiqués n'existe pas ou sont inaccessible!";	break;
	case ERR_NOM:		err.description = "Le nom indiqué n'existe pas ou est inaccessible!";	break;
	case ERR_FERMER:	err.description = "La clé n'a pas pu être fermée!";		break;
	case ERR_ECRIRE:	err.description = "La nouvelle valeur n'a pas pu être écrite!";	break;
	case ERR_CREERCLE:	err.description = "Une erreur s'est produite! La clé n'a pas pu être créé!";break;
	case ERR_SUPRCLE:	err.description = "La clé n'a pas pu être supprimé! Veuillez verifier la base et le chemin indiqué!";		break;
	case ERR_SUPRVAL:	err.description = "La valeur n'a pa pu être supprimé!\nLe nom de la clé indiqué n'existe pas! Veuillez verifier le nom!"; break;
	}
	MessageBox(hMain, err.description, "Registre", err.style);
}
VOID AddShappe(HWND hwnd) {
	HRGN hrgn = CreateRoundRectRgn(0, 0,GetSystemMetrics(SM_CXFULLSCREEN)-16, 0x41, 50, 60);
	FillRgn(GetDC(hwnd), hrgn, CreateSolidBrush(RGB(0,64,0)));
	RECT rc = { 35,3,305,44 };
	LoadString(wcex.hInstance, IDS_APP_TITLE, tempon, MAX_LOADSTRING);
	hrgn = CreateRoundRectRgn(rc.left-3,rc.top,rc.right+3, rc.bottom+3, 50, 60);
	FillRgn(GetDC(hwnd), hrgn, CreateSolidBrush(RGB(0,255,128)));
	DrawText(GetDC(hwnd), tempon, MAX_LOADSTRING, &rc, DT_SINGLELINE| DT_MODIFYSTRING| DT_VCENTER);
}
INT AddBackScreeenPict(HWND hwnd) {
	RECT rc, rc1;
	GetClientRect(GetDesktopWindow(), &rc);
	GetClientRect(hwnd, &rc1);
	return StretchBlt(GetDC(hwnd), rc1.top, rc1.left, rc1.right, rc1.bottom, GetDC(GetDesktopWindow()), rc.top, rc.left, rc.right, rc.bottom, SRCPAINT);
}
INT Initialize(HWND hwnd) {
	LPDIRECTDRAW7			g_pDirectDraw;
/*
	* Profondeur de la couleur 
	*	ne pas depasser 
	*	pour Windows 95, 98,Me <= 0x10 
	*		pt.x<= 0x320
	*		pt.y<= 0x258
	* 	pour Windows NT3.5.x ,NT4, 2000 <=0x18 possible bug avec le bios CirrusLogic sur les Cartes de type S3 (VLB 32bits)
	*   pour Windows XP, Vista (oui je sais Ouach Vista) 
	*		si chipset Cirus Logic S3 <=0x10
	*		<=0x18
	*	pour Windows7,8,10 <=0x20
	*/	//	ShowCursor(FALSE);
	if (FAILED(DirectDrawCreateEx(NULL, (VOID**)&g_pDirectDraw, IID_IDirectDraw7, NULL))) { return 1; }
	if (FAILED(g_pDirectDraw->SetCooperativeLevel(hwnd, DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE))) { return 2; }
	if (FAILED(g_pDirectDraw->SetDisplayMode(pt.x,pt.y,0x10, 0, 0))) { return 3; } //valeurs admissibles 0x08, 0x10, 0x18, 0x20 
	g_ddsd.dwSize = sizeof(DDSURFACEDESC2);
	g_ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	g_ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	g_ddsd.dwBackBufferCount = 1;
	if (g_pDirectDraw->CreateSurface(&g_ddsd, &g_pPrimarySurface, NULL) != DD_OK) { return 4; }
	g_ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	if (g_pPrimarySurface->GetAttachedSurface(&g_ddscaps, &g_pSecondarySurface) != DD_OK) { return 5; }
	DDCOLORKEY colkey;
	colkey.dwColorSpaceHighValue = 0;
	colkey.dwColorSpaceLowValue = 0;
	if (FAILED(g_pSecondarySurface->SetColorKey(DDCKEY_SRCBLT, &colkey) != DD_OK)) { return 6; }
	DDPIXELFORMAT pxFmt;
	g_pPrimarySurface->GetPixelFormat(&pxFmt);
	getRGB16(pxFmt.dwRBitMask, pxFmt.dwGBitMask, pxFmt.dwBBitMask);
}
INT Fermeture() {
	if (g_pPrimarySurface) {if (FAILED(g_pPrimarySurface->Release())) { return 1; }	}
	if (g_pDirectDraw) {if (FAILED(g_pDirectDraw->Release())) { return 2; }	}
	return 0;
}
INT getRGB16(DWORD r, DWORD g, DWORD b) {
	while (r > 0) {		numpx++;		r = (div(r, 2).quot);	}	rgba.rouge = numpx - 5;
	numpx = 0;	while (g > 0) {		numpx++;		g = (div(g, 2).quot);	}	rgba.bleu = numpx - 5;
	numpx = 0;	while (b > 0) {		numpx++;		b = (div(b, 2).quot);	}	rgba.vert = numpx - 5;
	numpx = 0;
	return 0;
}
INT getRGB32(DWORD r, DWORD g, DWORD b,FLOAT a) {
	rgba.alpha = a;
	while (r > 0) {		numpx++;		r = (div(r, 2).quot);	}	rgba.vert = numpx - 5;
	numpx = 0;	while (g > 0) {		numpx++;		g = (div(g, 2).quot);	}	rgba.bleu = numpx - 5;
	numpx = 0;	while (b > 0) {		numpx++;		b = (div(b, 2).quot);	}	rgba.vert = numpx - 5;
	numpx = 0;
	return 0;
}
LPSTR __stdcall encrypt(LPSTR data, INT decalage) {
	UINT i, cnt;
	PTCHAR data2=NULL;
	strcpy(data2, data);
	cnt = 0;
	while (data[cnt] != '\0')	cnt++;
	for (i = 0; i < cnt; i++)	data2[i] = data[i] + decalage;
	return data2;
}
LPSTR __stdcall decrypt(LPSTR data, INT decalage) {
	UINT i, cnt;
	strcpy(data2, data);
	cnt = 0;
	while (data[cnt] != '\0')	cnt++;
	for (i = 0; i < cnt; i++)	data2[i] = data[i] - decalage;
	return data2;
}
INT KillProcess(LPSTR argv)
{
	CHAR szName[100];
	strcpy(szName, argv);
	INT iRes;
	iRes = KILL_PROC_BY_NAME(szName);
	return iRes;
}
// merci Sardine pour tes modifs concernant le kernell Windows9x
INT KILL_PROC_BY_NAME(const LPSTR szToTerminate)
{
	BOOL bResult, bResultm;
	DWORD aiPID[1000], iCb = 1000, iNumProc, iV2000 = 0x00;
	DWORD iCbneeded, i, iFound = 0x00;
	CHAR szName[MAX_PATH], szToTermUpper[MAX_PATH];
	HANDLE hProc, hSnapShot, hSnapShotm;
	OSVERSIONINFO osvi;
	HINSTANCE hInstLib=NULL;
	INT iLen, iLenP, indx;
	HMODULE hMod;
	PROCESSENTRY32 procentry;
	MODULEENTRY32 modentry;
	iLenP =(INT) strlen(szToTerminate);
	if (iLenP<1 || iLenP>MAX_PATH) return 0x278;
	for (indx = 0x00; indx < iLenP; indx++)	szToTermUpper[indx] = toupper(szToTerminate[indx]);
	szToTermUpper[iLenP] = 0x00;
	BOOL(WINAPI * lpfEnumProcesses)(DWORD*, DWORD cb, DWORD*);
	BOOL(WINAPI * lpfEnumProcessModules)(HANDLE, HMODULE*, DWORD, LPDWORD);
	DWORD(WINAPI * lpfGetModuleBaseName)(HANDLE, HMODULE, LPTSTR, DWORD);
	HANDLE(WINAPI * lpfCreateToolhelp32Snapshot)(DWORD, DWORD);
	BOOL(WINAPI * lpfProcess32First)(HANDLE, LPPROCESSENTRY32);
	BOOL(WINAPI * lpfProcess32Next)(HANDLE, LPPROCESSENTRY32);
	BOOL(WINAPI * lpfModule32First)(HANDLE, LPMODULEENTRY32);
	BOOL(WINAPI * lpfModule32Next)(HANDLE, LPMODULEENTRY32);
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	bResult = GetVersionEx(&osvi);
	if (!bResult) return 0x25E;
	if ((osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) && (osvi.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS))return 0x25F;
	if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)	{
		hInstLib = LoadLibraryA("PSAPI.DLL");
		if (hInstLib == NULL)  return 0x25D;
		lpfEnumProcesses = (BOOL(WINAPI*)(DWORD*, DWORD, DWORD*))GetProcAddress(hInstLib, "EnumProcesses");
		lpfEnumProcessModules = (BOOL(WINAPI*)(HANDLE, HMODULE*, DWORD, LPDWORD)) GetProcAddress(hInstLib, "EnumProcessModules");
		lpfGetModuleBaseName = (DWORD(WINAPI*)(HANDLE, HMODULE, LPTSTR, DWORD)) GetProcAddress(hInstLib, "GetModuleBaseNameA");
		if (lpfEnumProcesses == NULL || lpfEnumProcessModules == NULL || lpfGetModuleBaseName == NULL){FreeLibrary(hInstLib);return 0x2BC;}
		bResult = lpfEnumProcesses(aiPID, iCb, &iCbneeded);
		if (!bResult){FreeLibrary(hInstLib);return 0x2BD;}
		iNumProc = iCbneeded / sizeof(DWORD);
		for (i = 0x00; i < iNumProc; i++){
			strcpy(szName, "Unknown");
			hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aiPID[i]);
			if (hProc){	if (lpfEnumProcessModules(hProc, &hMod, sizeof(hMod), &iCbneeded)){iLen = lpfGetModuleBaseName(hProc, hMod, szName, MAX_PATH);}	}
			if (hProc==0x00) { return 0x20A; }
			CloseHandle(hProc);
			if (strcmp(_strupr(szName), szToTermUpper) == 0x00){
				iFound = 1;
				hProc = OpenProcess(PROCESS_TERMINATE, FALSE, aiPID[i]);
				if (hProc){
					if (TerminateProcess(hProc, 0x00)){CloseHandle(hProc);FreeLibrary(hInstLib);return 0x00;}
					else{CloseHandle(hProc);FreeLibrary(hInstLib);return 0x25A;}
				}else{FreeLibrary(hInstLib);return 0x25C;
				}
			}
		}
	}
	//changement de localisation des fonctions sous Windows 9x ne marche pas aves Win32s
	if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS){
		hInstLib = LoadLibraryA("Kernel32.DLL");
		if (hInstLib == NULL)return 0x2BE;
		lpfCreateToolhelp32Snapshot =(HANDLE(WINAPI*)(DWORD, DWORD))	GetProcAddress(hInstLib, "CreateToolhelp32Snapshot");
		lpfProcess32First = (BOOL(WINAPI*)(HANDLE, LPPROCESSENTRY32))	GetProcAddress(hInstLib, "Process32First");
		lpfProcess32Next = (BOOL(WINAPI*)(HANDLE, LPPROCESSENTRY32))	GetProcAddress(hInstLib, "Process32Next");
		lpfModule32First = (BOOL(WINAPI*)(HANDLE, LPMODULEENTRY32))		GetProcAddress(hInstLib, "Module32First");
		lpfModule32Next = (BOOL(WINAPI*)(HANDLE, LPMODULEENTRY32))		GetProcAddress(hInstLib, "Module32Next");
		if (lpfProcess32Next == NULL || lpfProcess32First == NULL || lpfModule32Next == NULL || lpfModule32First == NULL || lpfCreateToolhelp32Snapshot == NULL){FreeLibrary(hInstLib);	return 0x2BF;}
		hSnapShot = lpfCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0x00);
		if (hSnapShot == INVALID_HANDLE_VALUE)	{FreeLibrary(hInstLib);	return 0x2C0;}
		procentry.dwSize = sizeof(PROCESSENTRY32);
		bResult = lpfProcess32First(hSnapShot, &procentry);
		while (bResult){
			hSnapShotm = lpfCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procentry.th32ProcessID);
			if (hSnapShotm == INVALID_HANDLE_VALUE){CloseHandle(hSnapShot);FreeLibrary(hInstLib);return 0x2C0;}
			modentry.dwSize = sizeof(MODULEENTRY32);
			bResultm = lpfModule32First(hSnapShotm, &modentry);
			while (bResultm){
				if (strcmp(modentry.szModule, szToTermUpper) == 0x00){
					iFound = 1;
					hProc = OpenProcess(PROCESS_TERMINATE, FALSE, procentry.th32ProcessID);
					if (hProc){
						if (TerminateProcess(hProc, 0x00)){CloseHandle(hSnapShotm);CloseHandle(hSnapShot);CloseHandle(hProc);FreeLibrary(hInstLib);return 0x00;}
						else{CloseHandle(hSnapShotm);CloseHandle(hSnapShot);CloseHandle(hProc);FreeLibrary(hInstLib);return 0x25A;}
					}else{CloseHandle(hSnapShotm);CloseHandle(hSnapShot);FreeLibrary(hInstLib);return 0x25C;}
				}else{modentry.dwSize = sizeof(MODULEENTRY32); bResultm = lpfModule32Next(hSnapShotm, &modentry);}
			}
			CloseHandle(hSnapShotm);
			procentry.dwSize = sizeof(PROCESSENTRY32);
			bResult = lpfProcess32Next(hSnapShot, &procentry);
		}
		CloseHandle(hSnapShot);
	}
	if (iFound == 0x00){FreeLibrary(hInstLib);return 0x25B;}
	FreeLibrary(hInstLib);
	return 0x00;
}
BOOL VerifWinXPMinimum() {
	OSVERSIONINFO osvi;
	INFOVERSION info;
	osvi.dwPlatformId = osvi.dwMajorVersion = 0;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	info.ID = osvi.dwPlatformId;
	info.Majeur = osvi.dwMajorVersion;
	info.Edition = osvi.dwBuildNumber;
	info.Mineure = osvi.dwMinorVersion;
	info.Taille = osvi.dwOSVersionInfoSize;
	if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) return false;
	if((osvi.dwMajorVersion >= 5) && (osvi.dwMinorVersion >= 5))
	return (osvi.dwMajorVersion >= 5);
}
VOID Tocken(){ //attention on s'attribue des privileges tres particuliers
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS_P, (VOID**)&hToken);
	LookupPrivilegeValue(NULL, SE_SYSTEM_ENVIRONMENT_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)TOKEN_MANDATORY_POLICY_OFF, 0);
}
VOID OnRedmarragedeWindows(){Tocken(); ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0); }
VOID OnFermeturedeWindows(){ Tocken(); ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0); }
VOID SurveillanceRepertoire(LPSTR lpDir){
	DWORD dwWaitStatus;
	HANDLE dwChangeHandles[2];
	CHAR lpDrive[4];
	CHAR lpFile[_MAX_FNAME];
	CHAR lpExt[_MAX_EXT];
	_tsplitpath(lpDir, lpDrive, NULL, lpFile, lpExt);
	lpDrive[2] = (CHAR)'\\';
	lpDrive[3] = (CHAR)'\0';
	dwChangeHandles[0] = FindFirstChangeNotification(lpDir, FALSE, FILE_NOTIFY_CHANGE_FILE_NAME);
	if (dwChangeHandles[0] == INVALID_HANDLE_VALUE) ExitProcess(GetLastError());
	dwChangeHandles[1] = FindFirstChangeNotification(lpDrive, TRUE, FILE_NOTIFY_CHANGE_DIR_NAME);
	if (dwChangeHandles[1] == INVALID_HANDLE_VALUE)  ExitProcess(GetLastError());
	while (TRUE) {
		dwWaitStatus = WaitForMultipleObjects(2, dwChangeHandles, FALSE, INFINITE);
		switch (dwWaitStatus) {
		case WAIT_OBJECT_0:
			if (FindNextChangeNotification(dwChangeHandles[0]) == FALSE) ExitProcess(GetLastError());
			break;
		case WAIT_OBJECT_0 + 1:
			if (FindNextChangeNotification(dwChangeHandles[1]) == FALSE)   ExitProcess(GetLastError());
			break;
		default: ExitProcess(GetLastError());
		}
	}
}
LPSTR NomFormat8_3(LPSTR fichier){GetShortPathName(fichier, tempon, 256);return strupr(tempon);}
LPSTR LZGetExpandedName(LPSTR Source){GetExpandedName(Source, tempon);	return tempon;}
DWORD LZGetCompressedFileSize(LPSTR Source){	 size;	GetCompressedFileSize(Source, &size);	return HIWORD(size);}
VOID Afficher(LPSTR fichier){ dwAttrs = GetFileAttributes(fichier);if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {SetFileAttributes(fichier, dwAttrs | ~FILE_ATTRIBUTE_HIDDEN);}}
VOID Cacher(LPSTR fichier){dwAttrs = GetFileAttributes(fichier);	if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {SetFileAttributes(fichier, dwAttrs | FILE_ATTRIBUTE_HIDDEN);	}}
LONG Attribuer(LPSTR fichier, DWORD attribut){dwAttrs = GetFileAttributes(fichier);	if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {SetFileAttributes(fichier, dwAttrs | FILE_ATTRIBUTE_READONLY);	}return dwAttrs;}
INT DeAttribuer(LPSTR fichier, DWORD attribut){return SetFileAttributes(fichier, ~attribut);}
VOID ProtegerEcriture(LPSTR fichier){dwAttrs = GetFileAttributes(fichier);if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {SetFileAttributes(fichier, dwAttrs | FILE_ATTRIBUTE_READONLY);}}
VOID DeProtegerEcriture(LPSTR fichier){dwAttrs = GetFileAttributes(fichier);if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {SetFileAttributes(fichier, dwAttrs | ~FILE_ATTRIBUTE_READONLY);	}}
// ne pas retirer les attributs systeme sur le bootsect.dat
VOID ProtegerSysteme(LPSTR fichier){DWORD dwAttrs = GetFileAttributes(fichier);if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {SetFileAttributes(fichier, dwAttrs | FILE_ATTRIBUTE_SYSTEM);}}
VOID DeProtegerSysteme(LPSTR fichier){dwAttrs = GetFileAttributes(fichier);if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) {SetFileAttributes(fichier, dwAttrs | ~FILE_ATTRIBUTE_SYSTEM);}}
VOID OnTransparence(INT Valeur) {	SetWindowLong(hMain, GWL_EXSTYLE, WS_EX_LAYERED);		SetLayeredWindowAttributes(hMain,GetSysColor(COLOR_BACKGROUND),Valeur,LWA_ALPHA | LWA_COLORKEY);	}
VOID Transparence10() { OnTransparence(25); }
VOID Transparence20() { OnTransparence(51); }
VOID Transparence30() { OnTransparence(76); }
VOID Transparence40() { OnTransparence(102); }
VOID Transparence50() { OnTransparence(128); }
VOID Transparence60() { OnTransparence(153); }
VOID Transparence70() { OnTransparence(178); }
VOID Transparence80() { OnTransparence(204); }
VOID Transparence90() { OnTransparence(229); }
VOID Transparence100() { OnTransparence(5); }
LPSTR GetNom_Projet() { return git.nom_Projet; }
INT GetlongeurNomProjet() { return git.longeurNomProjet; }
LPSTR GetNomBranche() { return git.nomBranche; }
LPSTR GetURL() { return git.url; }
LPSTR GetCheminGit() { return git.cheminGit; }
LPSTR GetGitUserName() { return git.UserName; }
LPSTR GetGitUserMail() { return git.UserMail; }
VOID SetNom_Projet(LPSTR value) { strncpy(git.nom_Projet, value,140); }
VOID SetNomBranche(LPSTR value) { strncpy(git.nomBranche, value,36); }
VOID SetURL(LPSTR value){ strncpy(git.url, value, 255); }
VOID SetCheminGit(LPSTR value){ strncpy(git.url, value, 255); }
VOID SetGitUserName(LPSTR value){ strncpy(git.url, value, 255); }
VOID SetGitUserMail(LPSTR value){ strncpy(git.url, value, 255); }

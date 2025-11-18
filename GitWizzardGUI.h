#pragma once

#include "resource.h"
typedef struct _IGUID
{
	ULONG Data1;
	USHORT Data2;
	USHORT Data3;
	UCHAR Data4[8];
}	IGUID;
typedef struct _INFOVERSION {
	DWORD Taille;
	DWORD Majeur;
	DWORD Mineure;
	DWORD Edition;
	DWORD ID;
	CHAR  szCSDVersion[0x7F]; 
	CHAR  Titre[0x100];
} INFOVERSION, * PINFOVERSION, * LPINFOVERSION;

struct REGS32 {
	CHAR  Description[ko];
	CHAR  DisplayName[ko];
	CHAR  ImagePath[ko];
	CHAR  ObjectName[ko];
	CHAR  RequiredPrivileges[ko];
	CHAR FilePath[ko];
};
struct Erreur{
	INT numero;
	INT style;
	CONST CHAR* description;
};
typedef struct _RGBA
{
	BYTE bleu;
	BYTE vert;
	BYTE rouge;
	FLOAT alpha;
} RGBA;
struct _GiT
{
	CHAR nom_Projet[0x8C];
	INT longeurNomProjet = 0x01;
	CHAR nomBranche[0x24];
	CHAR url[0xFF];
	CHAR cheminGit[0x104];
	CHAR UserName[0x60];
	CHAR UserMail[0x40];
}GIT, * PGIT, * LPGIT, git;

// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                ClasseFenetrePrincipale(HINSTANCE hInstance);
BOOL                InitialisationProgammePrincipal(HINSTANCE, INT);
LRESULT CALLBACK    ProceduresProgammePrincipal(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ProceduresProgammeAPropos(HWND, UINT, WPARAM, LPARAM);
/* Section GIT */
LPSTR GetNom_Projet();
INT GetlongeurNomProjet();
LPSTR GetNomBranche();
LPSTR GetURL();
LPSTR GetCheminGit();
LPSTR GetGitUserName();
LPSTR GetGitUserMail();
VOID SetNom_Projet(LPSTR value);
VOID SetNomBranche(LPSTR value);
VOID SetURL(LPSTR value);
VOID SetCheminGit(LPSTR value);
VOID SetGitUserName(LPSTR value);
VOID SetGitUserMail(LPSTR value);
VOID CreerUneBranche(LPSTR Branche);
VOID SupprimerBranche(LPSTR Branche);
VOID ConfigurerOptionsPersonellesGiT();
INT_PTR CALLBACK ConfigGitUser(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
/*Section Registre*/
VOID GetServiceInfo(LPSTR subkey);
REGS32 ExtractServiceInfo(LPSTR Service);
VOID InscrireRegistre();
HKEY ChoisirBase(LPSTR base);
ULONG ChoisirType(LPSTR type);
BOOL OuvrirCle(LPSTR base, LPSTR chemin, HKEY* hCle);
LPSTR LireValeur(HKEY hCle, LPSTR nom, BOOL* OpRes);
BOOL EcrireValeur(HKEY hCle, LPSTR nom, LPSTR valeur, LPSTR type);
BOOL CreerCle(LPSTR base, LPSTR chemin, HKEY* hCle);
BOOL SupprimerCle(LPSTR base, LPSTR chemin);
BOOL SupprimerValeur(LPSTR base, LPSTR chemin, LPSTR nom);
BOOL FermerCle(HKEY hCle);
VOID OnRegError(INT nError);
/*Section AffichageDirectX*/
INT Initialize(HWND hwnd);
INT Fermeture();
INT getRGB16(DWORD r, DWORD g, DWORD b);
INT getRGB32(DWORD r, DWORD g, DWORD b,FLOAT a);
VOID AddShappe(HWND hwnd);
INT AddBackScreeenPict(HWND hwnd);
/*Section Codage*/
LPSTR __stdcall encrypt(LPSTR data, INT decalage);
LPSTR __stdcall decrypt(LPSTR data, INT decalage);
/*Section Systeme*/
VOID Transparence10();
VOID Transparence20();
VOID Transparence30();
VOID Transparence40();
VOID Transparence50();
VOID Transparence60();
VOID Transparence70();
VOID Transparence80();
VOID Transparence90();
VOID Transparence100();
VOID OnTransparence(INT Valeur);
LPSTR Phraser(CHAR* valeur);
VOID GetID(INT valeur);
INT KillProcess(LPSTR argv);
INT KILL_PROC_BY_NAME(const LPSTR szToTerminate);// merci Sardine pour tes modifs concernant le kernell Windows9x
BOOL VerifWinXPMinimum();
VOID Tocken();
VOID OnRedmarragedeWindows();
VOID OnFermeturedeWindows();
VOID SurveillanceRepertoire(LPSTR lpDir);
LPSTR NomFormat8_3(LPSTR fichier);
LPSTR LZGetExpandedName(LPSTR Source);
DWORD LZGetCompressedFileSize(LPSTR Source);
VOID Afficher(LPSTR fichier);
LONG Attribuer(LPSTR fichier, DWORD attribut);
VOID Cacher(LPSTR fichier);
INT DeAttribuer(LPSTR fichier, DWORD attribut);
VOID DeProtegerEcriture(LPSTR fichier);
VOID DeProtegerSysteme(LPSTR fichier);
VOID ProtegerEcriture(LPSTR fichier);
VOID ProtegerSysteme(LPSTR fichier);

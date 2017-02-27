#include <windows.h>
#include <stdio.h>


BOOL EnablePriv(LPCSTR lpszPRiv);
BOOL ProtectProcess();


typedef VOID ( _stdcall *RtlSetProcessIsCritical ) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue, // (optional)
	IN BOOLEAN     IsWinlogon );

BOOL EnablePriv(LPCSTR lpszPriv) // by Napalm
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if(!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if(!LookupPrivilegeValue(NULL, lpszPriv, &luid)){
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}

BOOL ProtectProcess() // by _FIL73R_
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA("ntdll.dll");
	if ( hDLL != NULL )
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical) GetProcAddress( (HINSTANCE)hDLL, "RtlSetProcessIsCritical" );
		if(!fSetCritical) return 0;
		fSetCritical(1,0,0);
		return 1;
	} else
		return 0;
}

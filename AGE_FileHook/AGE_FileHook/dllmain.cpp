#include <Windows.h>
#include <string>

#include "Rxx/include/Hook.h"
#include "Rxx/include/Console.h"
#include "Rxx/include/Hook_API_DEF.h"

static DWORD g_dwExeBase = (DWORD)GetModuleHandleW(NULL);
static pCreateFileA sg_fnCreateFileA = CreateFileA;
static pLoadLibraryA sg_fnLoadLibraryA = LoadLibraryA;
static const char* sg_cpFolder = "AGE_CN_FileHook\\";

HANDLE WINAPI CreateFileA_NEW(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	static char path[512] = { 0 };
	strcpy_s(path, 512, sg_cpFolder);
	strcat_s(path, 512, lpFileName);
	if (GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES) { lpFileName = path; }
	return sg_fnCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HMODULE WINAPI LoadLibraryA_NEW(LPCSTR lpLibFileName)
{
	if (!strcmp(lpLibFileName, "AGERC.DLL")) { lpLibFileName = "AGERC_CN.DLL"; }
	return sg_fnLoadLibraryA(lpLibFileName);
}

VOID StartHook()
{
	Rut::HookX::HookTitleExA("杺摫岻妅 乣埮偺寧彈恄偼摫崙偱塺偆乣", "魔导巧壳 汉化版 V3 程序修正");
	Rut::HookX::DetourAttachFunc(&sg_fnCreateFileA, CreateFileA_NEW);
	Rut::HookX::DetourAttachFunc(&sg_fnLoadLibraryA, LoadLibraryA_NEW);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		StartHook();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) void Dir_A() {}
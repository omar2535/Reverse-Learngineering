// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "AssaultCubeDLLNew.h"

DWORD __stdcall Thread(void* pParam) {

	processMain();
	return S_OK;
}

BOOL __stdcall DllMain(HINSTANCE hDll, DWORD dwReason, void* pReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, Thread, nullptr, 0, nullptr);
	}
	return TRUE;
}


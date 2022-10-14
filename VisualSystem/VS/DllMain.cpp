#include <Windows.h>
#include "Params.hpp"
#include "ProgramData.hpp"

DWORD Stdcall __START( void )
{
	Program->SetupGameSettings();
	Program->SetupLuaSettings();
	Program->SetupConsoleCommands();
	Program->ConsoleListen();

	ExitThread( 0x0 );
}



BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	static HANDLE H_START_THREAD = NULL;

	switch( dwReason )
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hModule);
			H_START_THREAD = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)__START, 0, 0, 0 );
		break;
		case DLL_PROCESS_DETACH:
			delete Program;
			TerminateThread( H_START_THREAD, 0x0 );
			CloseHandle( H_START_THREAD );
	}
	return TRUE;
}

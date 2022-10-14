#include <Windows.h>
#include <TlHelp32.h>
#include "ProcessManager.hpp"

typedef Win32Utils::Win32Process Process;

bool __stdcall Process::GetProcessId( 
	const char* ProcessName,
	unsigned int* TargetProcessId
) {
		bool RetCode = false;
		PROCESSENTRY32 ProcEntry = { 0 };
		ProcEntry.dwSize = sizeof(PROCESSENTRY32);
		HANDLE Snap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
		if( Snap != INVALID_HANDLE_VALUE )
		{
			Process32First( Snap, &ProcEntry );
			do
			{
				if( !strcmp(ProcessName, ProcEntry.szExeFile) ) {
					*TargetProcessId = ProcEntry.th32ProcessID;
					RetCode = true;
					break;
				}
			} while (Process32Next(Snap, &ProcEntry));
			CloseHandle(Snap);
		}
		
		return RetCode;
}

bool __stdcall Process::GetModuleInformation(
	const int ProcessId,
	const char* ModuleName,
	const Win32Utils::PWin32ModuleInformation ModuleInfo
	) {
		bool RetCode = false;
		MODULEENTRY32 ModEntry = { 0 };
		ModEntry.dwSize = sizeof(MODULEENTRY32);
		HANDLE Snap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, ProcessId );
		if( Snap != INVALID_HANDLE_VALUE ) {
			Module32First(Snap, &ModEntry);
			do
			{
				if( !strcmp( ModuleName, ModEntry.szModule ) ) {
					RetCode = true;
					ModuleInfo->Address = (PVOID)ModEntry.modBaseAddr;
					ModuleInfo->Size	= ModEntry.modBaseSize;
					break;
				}
			}while( Module32Next( Snap, &ModEntry) );
			CloseHandle( Snap );
		}
		return RetCode;
}

bool __stdcall Process::GetProcessGeneralThread(
	const int ProcessId,
	unsigned int* TargetThreadId
)
{
	bool RetCode = false;
	THREADENTRY32 ThreadEntry = { 0 };
	ThreadEntry.dwSize = sizeof(THREADENTRY32);
	HANDLE Snap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, ProcessId );
	if( Snap != INVALID_HANDLE_VALUE ) {
		Thread32First( Snap, &ThreadEntry );
		do
		{
			if( ThreadEntry.th32OwnerProcessID == ProcessId )
			{
				*TargetThreadId = ThreadEntry.th32ThreadID;
				RetCode = true;
				break;
			}

		} while( Thread32Next( Snap, &ThreadEntry ) );
		CloseHandle( Snap );
	}
	return RetCode;
}
#include <Windows.h>
#include "ThreadManager.hpp"

typedef Win32Utils::Win32Thread Thread;
#pragma warning( disable : 4800 ) // int to bool convert warning

bool __stdcall Thread::SuspendThread(
	const unsigned int ThreadId
	) {
		HANDLE hThread = OpenThread( THREAD_SUSPEND_RESUME, FALSE, ThreadId );
		DWORD Result = ::SuspendThread( hThread );
		CloseHandle( hThread );
		return Result != ((DWORD)-1) ? true : false;
}

bool __stdcall Thread::ResumeThread(
	const unsigned int ThreadId
	){
		HANDLE hThread = OpenThread( THREAD_SUSPEND_RESUME, FALSE, ThreadId );
		DWORD Result = ::ResumeThread( hThread );
		CloseHandle( hThread );
		return Result != ((DWORD)-1) ? true : false;
}
	
bool __stdcall Thread::TerminateThread(
	const unsigned int ThreadId
	) {
		HANDLE hThread = OpenThread( THREAD_TERMINATE, FALSE, ThreadId );
		BOOL Result = ::TerminateThread( hThread, 0x0 );
		CloseHandle( hThread );
		return (bool)Result;		
}
#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "LogManager.hpp"
#include "../Utils/FileManager.hpp"

#pragma warning( disable : 4996 ) // printf_s warning
#pragma warning( disable : 4800 ) // int to bool convert warning


#define TIME_SIGNATURE "%02d.%02d.%d  %02d:%02d "

ILogManager::~ILogManager( void ) { /* pure */ }

CLogManager::CLogManager( const char* LogPath )
{
	this->LogPath = LogPath;
	this->ConsoleActive = false;
}

CLogManager::~CLogManager( void ) {
	if( this->ConsoleActive )
		this->CloseConsole();
}

bool Thiscall CLogManager::Clear( void ) {
	return Win32Utils::Win32File::Create( this->LogPath );
}

#define LOG_BUFFER_SIZE (unsigned int)256
void __cdecl CLogManager::LogMsgV( const char* Msg, ... ) {
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);

	Win32Utils::Win32File::Write( this->LogPath, "a", TIME_SIGNATURE, SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute );
	
	CHAR Buffer_[LOG_BUFFER_SIZE] = { 0 };

	if( this->ConsoleActive ) {
		ConsolePrintVS( TIME_SIGNATURE, SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute )
		CONST HANDLE Descriptor_ = GetStdHandle( STD_OUTPUT_HANDLE );
		if( Descriptor_ ) {
			va_list ArgPointer;
			va_start(ArgPointer, Msg);
			vsnprintf( Buffer_, sizeof(Buffer_), Msg, ArgPointer);
			va_end(ArgPointer);

			WriteConsoleA( Descriptor_ , Buffer_, strlen( Buffer_ ), NULL, NULL );
		}
	}

	FILE* hStream = fopen( this->LogPath, "a");
	if(!hStream ) // Поток не открыт
		return ;

	va_list ArgPointer;
	va_start( ArgPointer, Msg );
	vsnprintf( Buffer_, sizeof(Buffer_), Msg, ArgPointer );
	va_end( ArgPointer );

	fputs( Buffer_, hStream );
	fclose( hStream );
}

void Thiscall CLogManager::LogMsg( const char* Msg ) {
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);

	Win32Utils::Win32File::Write( this->LogPath, "a", TIME_SIGNATURE, SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute );
	
	if( this->ConsoleActive ) {
		ConsolePrintVS( TIME_SIGNATURE, SysTime.wDay, SysTime.wMonth, SysTime.wYear, SysTime.wHour, SysTime.wMinute )
		CONST HANDLE Descriptor_ = GetStdHandle( STD_OUTPUT_HANDLE );
			if( Descriptor_ )
				WriteConsoleA( Descriptor_ , Msg, strlen( Msg ), NULL, NULL );
	}	
	
	FILE* hStream = fopen( this->LogPath, "a");
	if(!hStream ) // Поток не открыт
		return ;
	
	fputs( Msg, hStream );
	fclose( hStream );
}

void Thiscall CLogManager::EnableConsole ( const char* ConTitle ) {
	this->ConsoleActive = true;
	ConsoleCreateVS( ConTitle )
}

void Thiscall CLogManager::CloseConsole( void ) {
	this->ConsoleActive = false;
	ConsoleCloseVS()
}

bool Thiscall CLogManager::ConsoleIsActive( void ) {
	return this->ConsoleActive;
}
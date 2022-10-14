#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "FileManager.hpp"

#pragma warning( disable : 4996 )

typedef Win32Utils::Win32File File;


#define FILEWRITE_BUFFER_SIZE (unsigned int)256
bool __cdecl File::Write(
				const char* FilePath,
				const char* Flag, // open flag ( w, r, a ... )
				const char* Fmt,
				...
				) {
	int Result = 0;
	CHAR Message[ FILEWRITE_BUFFER_SIZE ] = { 0 };
	FILE* hStream = fopen(FilePath, Flag);
	if(!hStream ) // Поток не открыт
		return false;

	va_list ArgPointer;
	va_start( ArgPointer, Fmt );
	vsnprintf( Message, sizeof(Message), Fmt, ArgPointer );
	va_end( ArgPointer );

	Result = fputs( Message, hStream );
	fclose( hStream );

    return Result < 0 ? false : true;
}

bool __stdcall File::Create( const char* FilePath ) {
	FILE* hStream = fopen(FilePath, "w" );
	if(!hStream ) // Поток не открыт
		return FALSE;

	fclose( hStream );
	return true;
}
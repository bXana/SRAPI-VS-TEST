#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "ConsoleManager.hpp"

#pragma warning( disable : 4996 ) // printf_s warning
#pragma warning( disable : 4800 ) // int to bool convert warning

typedef Win32Utils::Win32Console Console;

bool __stdcall Console::Create( 
				const char* ConTitle // Console title
				) {
	if( AllocConsole() ) {
		SetConsoleTitle( ConTitle );
		return true;
	}

	return false;
}

bool __stdcall Console::Close( void ) { 
	return FreeConsole();
}

#define CONSOLE_BUFFER_SIZE (unsigned int)256

bool __cdecl Console::Write(
				const char* Fmt,
				...
				) {
	CHAR Buffer_[CONSOLE_BUFFER_SIZE] = { 0 };
	CONST HANDLE Descriptor_ = GetStdHandle( STD_OUTPUT_HANDLE );
	if( Descriptor_ ) {
		va_list ArgPointer;
		va_start(ArgPointer, Fmt);
		vsnprintf( Buffer_, sizeof(Buffer_), Fmt, ArgPointer);
		va_end(ArgPointer);

		return WriteConsoleA( Descriptor_ , Buffer_, strlen( Buffer_ ), NULL, NULL );
	}

	return false;	
}

 bool __stdcall Console::Clear( void ) {
	CONST HANDLE Descriptor_ = GetStdHandle( STD_OUTPUT_HANDLE );
	if( Descriptor_ ) {
	 COORD coordScreen = { 0, 0 }; // исходная позиция для курсора
	   DWORD cCharsWritten;
	   CONSOLE_SCREEN_BUFFER_INFO csbi;
	   DWORD dwConSize;
	// Получим число символьных ячеек в текущем буфере.

	   if( !GetConsoleScreenBufferInfo( Descriptor_, &csbi ))
		  return false;
	   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// Заполним полностью экран пробелами.

	   if( !FillConsoleOutputCharacter( Descriptor_, (TCHAR) ' ',
		  dwConSize, coordScreen, &cCharsWritten ))
		  return false;

	   // Получим текущие атрибуты текста.

	   if( !GetConsoleScreenBufferInfo( Descriptor_, &csbi ))
		  return false;

	   // Установим соответствующие атрибуты буфера.

	   if( !FillConsoleOutputAttribute( Descriptor_, csbi.wAttributes,
		  dwConSize, coordScreen, &cCharsWritten ))
		  return false;

		// Поместим курсор в его изначальные координаты
	   SetConsoleCursorPosition( Descriptor_, coordScreen );
	   return true;
	}

	return false;
 }

bool __stdcall Console::SetColor(
				const unsigned int Attributes // FOREGROUND_GREEN | FOREGROUND_INTENSITY
				) {
	CONST HANDLE Descriptor_ = GetStdHandle( STD_OUTPUT_HANDLE ); 
    if( !Descriptor_ )
        return false;

    return SetConsoleTextAttribute( Descriptor_, Attributes );

}
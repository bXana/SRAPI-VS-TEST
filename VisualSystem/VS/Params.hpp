#ifndef _PARAMS_HPP_
#define _PARAMS_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include <Windows.h>
#include "../Utils/ConsoleManager.hpp"

typedef int			  Int;
typedef unsigned int  UInt;
typedef unsigned char Byte;
typedef Byte*		  PByte;
typedef void*		  PVoid;
typedef float		  Float;
typedef bool		  Bool;
typedef Bool*		  PBool;
typedef wchar_t		  Unicode;
typedef long long	  Qword;
typedef double		  Double;

#define Stdcall   __stdcall
#define Thiscall __thiscall
#define This (*this)


typedef Win32Utils::Win32Console Console;

#define WIN32_LEAN_AND_MEAN

#define ConsoleCreateVS( ConTitle ) Console::Create( ConTitle ); \
		Console::SetColor( FOREGROUND_GREEN | FOREGROUND_INTENSITY );			
#define ConsolePrintVS( ... ) Console::Write( __VA_ARGS__ );
#define ConsoleReadVS( BufferSize , ... ) Console::Read<BufferSize>( __VA_ARGS__ );
#define ConsoleCloseVS( ) Console::Close();
#define ConsoleClearVS( ) Console::Clear();


#endif
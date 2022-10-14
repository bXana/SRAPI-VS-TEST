#include "ExceptionManager.hpp"
#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>

#pragma warning( disable : 4996 )

CExceptionManager::CExceptionManager( 		
		const char* Fmt,
		... ) {
		va_list ArgPointer;
		va_start(ArgPointer, Fmt);
		vsnprintf( this->ErrMsg_, sizeof(this->ErrMsg_), Fmt, ArgPointer);
		va_end(ArgPointer);
}
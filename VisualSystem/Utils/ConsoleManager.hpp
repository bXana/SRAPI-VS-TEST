#ifndef _CONSOLEMANAGER_HPP_
#define _CONSOLEMANAGER_HPP_

#include <stdio.h>
#pragma warning( disable : 4996 )

namespace Win32Utils {

	/* Win32 Console class */
	typedef class {
		public:
			static bool __stdcall Create( 
				const char* ConTitle // Console title
				);
			static bool __stdcall Close( void );
			static bool __cdecl	  Write(
				const char* Fmt,
				...
				);
			static bool __stdcall Clear( void );

			static bool __stdcall SetColor(
				const unsigned int Attributes // FOREGROUND_GREEN | FOREGROUND_INTENSITY
				);

			template< unsigned int UBufferSize >
			static unsigned int __stdcall Read(
							const unsigned int ArgsCount,
							const char* Fmt,
							...
						) {
				PDWORD ArgPointer = (PDWORD)&Fmt;
				for( unsigned int i = 0; i < ArgsCount; i++ )
					++ArgPointer;

				unsigned int RetCode = 0;
				CHAR Buffer_[UBufferSize] = { 0 };
				DWORD BytesRead = 0;
				CONST HANDLE Descriptor_ = GetStdHandle( STD_INPUT_HANDLE );
				if( Descriptor_ ) {
					if( !ReadConsoleA( Descriptor_, Buffer_, sizeof(Buffer_), &BytesRead, NULL ) )
						return RetCode;
					
					__asm
					{
						mov eax, ArgsCount
						mov ecx, [ArgPointer]
						back_:
						cmp eax, 0
						jz exit_;
						push [ecx]
						dec eax
						sub ecx, 0x4
						jmp back_
						exit_:
					}
					RetCode = sscanf( Buffer_, Fmt );
					BytesRead = 0x4 * ArgsCount;
					__asm add esp, BytesRead
				}

				return RetCode;	
			}

	} Win32Console;

}

#endif 
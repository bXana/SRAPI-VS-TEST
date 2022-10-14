

#ifndef _FILEMANAGER_HPP_
#define _FILEMANAGER_HPP_

namespace Win32Utils {
	typedef class {
		public:
			static bool __stdcall Create( const char* FilePath );

			static bool __cdecl Write(
				const char* FilePath,
				const char* Flag, // open flag ( w, r, a ... )
				const char* Fmt,
				...
				);
	} Win32File;
}


#endif
#include "Lua_Program.hpp"
#include "../../../Utils/FileManager.hpp"
#include "../../ProgramData.hpp"
#include <time.h>

namespace VS_LUA_GAMEMETHODS
{

	namespace LUA_PROGRAM
	{
		int Stdcall IsPlaying( lua_State* LuaHandle ) {
			lua_pushboolean( LuaHandle, Program->SRAPI()->IsPlaying() );
			return 1;
		}

		int Stdcall Print( lua_State* LuaHandle ) {
			const char* Msg = luaL_checkstring( LuaHandle, 2 );
			if( Program->Logger()->ConsoleIsActive() )
				ConsolePrintVS( Msg )

			return 0;
		}

		int Stdcall FPrint( lua_State* LuaHandle ) {
			const char* FPath = luaL_checkstring( LuaHandle, 2 );
			const char* Flag  = luaL_checkstring( LuaHandle, 3 );
			const char* Msg   = luaL_checkstring( LuaHandle, 4 );
			Win32Utils::Win32File::Write( FPath, Flag, Msg );

			return 0;
		}

		int Stdcall Log( lua_State* LuaHandle ) {
			const char* Msg = luaL_checkstring( LuaHandle, 2 );
			Program->Logger()->LogMsg( Msg );

			return 0;
		}

		int Stdcall Random( lua_State* LuaHandle )
		{
			srand( (unsigned int)time( NULL ) );

			Int Min = (UInt)luaL_checkinteger( LuaHandle, 2 );
			Int Max = (UInt)luaL_checkinteger( LuaHandle, 3 );
			luaL_argcheck( LuaHandle, Min <= Max, 3, "Invalid interval" );

			Int RandN = rand() % ( Max - Min + 1 );

			if( Max >= 0 )
				RandN += Min;
			else
				RandN = Max -RandN;

			lua_pushinteger( LuaHandle, RandN );

			return 1;
		}
	}
}
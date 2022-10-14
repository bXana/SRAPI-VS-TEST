///////////////////////////////////////
//		Lua GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Program Lua API 
///////////////////////////////////////
#ifndef _PROGRAM_LUA_HPP_
#define _PROGRAM_LUA_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif


#include "../../Params.hpp"
#include "../../../LuaAPI/LuaInclude.hpp"

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_PROGRAM
	{
		int Stdcall IsPlaying( lua_State* LuaHandle );
		int Stdcall Print( lua_State* LuaHandle );
		int Stdcall FPrint( lua_State* LuaHandle );
		int Stdcall Log( lua_State* LuaHandle );
		int Stdcall Random( lua_State* LuaHandle );

	}
}



#define SR_LUA_PROGRAM_MT_NAME  "VS.Program"
#define SR_LUA_PROGRAM_OBJ_NAME "Program"

#endif
///////////////////////////////////////
//		Lua GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Sector Lua API 
///////////////////////////////////////
#ifndef _SECTOR_LUA_HPP_
#define _SECTOR_LUA_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "../../Params.hpp"
#include "../../../LuaAPI/LuaInclude.hpp"

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_SECTOR
	{
		int Stdcall Stars( lua_State* LuaHandle );

		int Stdcall IsEqual( lua_State* LuaHandle );

		// Возвращает количество систем в секторе
		int Stdcall StarsCount( lua_State* LuaHandle );

		// Возвращает объект системы
		int Stdcall Star( lua_State* LuaHandle );

		// Виден ли сектор
		int Stdcall IsVisible( lua_State* LuaHandle );
		int Stdcall SetVisible( lua_State* LuaHandle );
	}
}

#define SR_LUA_SECTOR_METATABLE_NAME "VS.Sector"

#endif
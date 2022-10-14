///////////////////////////////////////
//		Lua GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Galaxy Lua API 
///////////////////////////////////////
#ifndef _GALAXY_LUA_HPP_
#define _GALAXY_LUA_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "../../Params.hpp"
#include "../../../LuaAPI/LuaInclude.hpp"

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_GALAXY
	{
		// Возвращает/устанавливает настройки галактики
		int Stdcall Settings( lua_State* LuaHandle );
		int Stdcall SetSettings( lua_State* LuaHandle );

		// Работа с тонкой настройкой
		int Stdcall AdjustmentSettings( lua_State* LuaHandle );
		int Stdcall SetAdjustmentSettings( lua_State* LuaHandle );

		// table pairs
		int Stdcall Stars( lua_State* LuaHandle );
		int Stdcall Sectors( lua_State* LuaHandle );

		// Передаёт объект корабля
		int Stdcall Player( lua_State* LuaHandle );

		// Возвращает роджерию
		int Stdcall Rojeria( lua_State* LuaHandle );

		int Stdcall Blazer( lua_State* LuaHandle );

		int Stdcall Keller( lua_State* LuaHandle );

		int Stdcall Terron( lua_State* LuaHandle );

		// Количество секторов в галактике
		int Stdcall SectorsCount( lua_State* LuaHandle );
		int Stdcall Sector( lua_State* LuaHandle );

		// Количество систем в галактике
		int Stdcall StarsCount( lua_State* LuaHandle );
		int Stdcall Star( lua_State* LuaHandle );
	}
}

#define SR_LUA_GALAXY_METATABLE_NAME "VS.Galaxy"
#define SR_LUA_GALAXY_OBJECT_NAME "Galaxy"


#endif
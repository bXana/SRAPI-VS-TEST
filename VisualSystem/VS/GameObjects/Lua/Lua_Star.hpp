///////////////////////////////////////
//		Lua GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Star Lua API 
///////////////////////////////////////
#ifndef _STAR_LUA_HPP_
#define _STAR_LUA_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "../../Params.hpp"
#include "../../../LuaAPI/LuaInclude.hpp"

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_STAR
	{	
		int Stdcall Ships( lua_State* LuaHandle );
		int Stdcall Planets( lua_State* LuaHandle );

		// meta method equal
		int Stdcall IsEqual( lua_State* LuaHandle );

		// Возвращает/устанавливает фракцию, владеющую системой
		int Stdcall Fraction( lua_State* LuaHandle );
		int Stdcall SetFraction( lua_State* LuaHandle );

		// Возвращает/устанавливает серию доминаторов, владеющую системой (или владевшую ей ранее)
		int Stdcall DomSeries( lua_State* LuaHandle );
		int Stdcall SetDomSeries( lua_State* LuaHandle );

		// Возвращает количество кораблей в системе
		int Stdcall	ShipsCount( lua_State* LuaHandle );
		int Stdcall	Ship( lua_State* LuaHandle );

		// Создаёт базу
		int Stdcall CreateBase( lua_State* LuaHandle );
		
		// Ведется ли сражение в системе
		int Stdcall IsBattle( lua_State* LuaHandle );

		// Возвращает количество планет в системе
		int Stdcall PlanetsCount( lua_State* LuaHandle );

		// Возвращает объект планеты
		int Stdcall Planet( lua_State* LuaHandle );

		// Возвращает/устанавливает номер фона системы
		int Stdcall FonImage( lua_State* LuaHandle );
		int Stdcall SetFonImage( lua_State* LuaHandle );

		// Возвращает сектор системы
		int Stdcall Sector( lua_State* LuaHandle );

		// Возвращает/устанавливает флаги системы
		int Stdcall Flags( lua_State* LuaHandle );
		int Stdcall SetFlags( lua_State* LuaHandle );

		// Возвращает/устанавливает модель корабля
		int Stdcall VisualModel( lua_State* LuaHandle );
		int Stdcall SetVisualModel( lua_State* LuaHandle );
	}
}

#define SR_LUA_STAR_METATABLE_NAME "VS.Star"


#endif
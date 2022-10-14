///////////////////////////////////////
//		Lua GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Planet Lua API 
///////////////////////////////////////
#ifndef _PLANET_LUA_HPP_
#define _PLANET_LUA_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "../../Params.hpp"
#include "../../../LuaAPI/LuaInclude.hpp"

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_PLANET
	{
		int Stdcall Warriors( lua_State* LuaHandle );

		int Stdcall IsEqual( lua_State* LuaHandle );

		// ¬озвращает/устанавливает текущего обладател€ планеты
		int Stdcall Fraction( lua_State* LuaHandle );
		int Stdcall SetFraction( lua_State* LuaHandle );

		// ¬озвращает/устанавливает родную расу на планете
		int Stdcall Species( lua_State* LuaHandle );
		int Stdcall SetSpecies( lua_State* LuaHandle );

		// ¬озвращает/устанавливает форму правлени€ на планете
		int Stdcall Government( lua_State* LuaHandle );
		int Stdcall SetGovernment( lua_State* LuaHandle );

		// ¬озвращает/устанавливает тип экономики на планете
		int Stdcall Economy( lua_State* LuaHandle );
		int Stdcall SetEconomy( lua_State* LuaHandle );

		// ¬озвращает/устанавливает исследуемые территории на планете( незаселЄнной )
		int Stdcall Terrain( lua_State* LuaHandle );
		int Stdcall SetTerrain( lua_State* LuaHandle ); 

		// ¬озвращает/устанавливает исследованные территории на планете( незаселЄнной )
		int Stdcall TerrainExplored( lua_State* LuaHandle );
		int Stdcall SetTerrainExplored( lua_State* LuaHandle );

		// ¬озвращает/устанавливает радиус планеты
		int Stdcall Radius( lua_State* LuaHandle );
		int Stdcall SetRadius( lua_State* LuaHandle );

		// ¬озвращает/устанавливает тангенциальную скорость планеты
		int Stdcall OrbitalVelocity( lua_State* LuaHandle );
		int Stdcall SetOrbitalVelocity( lua_State* LuaHandle );

		// ¬озвращает/устанавливает размер планеты
		//UInt SR_API Size( void );
		//void SR_API SetSize( const UInt uSize );

		// ¬озвращает/устанавливает попул€цию планеты
		int Stdcall Population( lua_State* LuaHandle );
		int Stdcall SetPopulation( lua_State* LuaHandle );

		//¬озвращает количество военных кораблей, приписанных планете
		int Stdcall WarriorsCount( lua_State* LuaHandle );
		int Stdcall Warrior( lua_State* LuaHandle );

		// ¬озвращает/устанавливает флаг работы планеты
		int Stdcall Flags( lua_State* LuaHandle );
		int Stdcall SetFlags( lua_State* LuaHandle );

		// ¬озвращает/устанавливает текущий проект планеты
		int Stdcall Invention( lua_State* LuaHandle );
		int Stdcall SetInvention( lua_State* LuaHandle );

		// ¬озвращает/устанавливает уровень исследовани€ проекта планеты. ¬ отрезке [ 0; 100 ]
		// ¬ единственном экземпл€ре: не прив€зан к какому-либо проекту.
		int Stdcall InventionPoints( lua_State* LuaHandle );
		int Stdcall SetInventionPoints( lua_State* LuaHandle );

		// ¬озвращает/устанавливает технический уровень проекта планеты
		int Stdcall InventionLvl( lua_State* LuaHandle );
		int Stdcall SetInventionLvl( lua_State* LuaHandle ); 

		// возвращает систему планеты
		int Stdcall Star( lua_State* LuaHandle );

		// ¬озвращает/устанавливает модель планеты
		int Stdcall VisualModel( lua_State* LuaHandle );
		int Stdcall SetVisualModel( lua_State* LuaHandle );

		//int Stdcall Name( lua_State* LuaHandle );
	}
}

#define SR_LUA_PLANET_METATABLE_NAME "VS.Planet"

#endif
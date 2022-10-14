#include "Lua_Planet.hpp"
#include "Lua_Ship.hpp"
#include "Lua_Star.hpp"

#include "../Planet.hpp"

#pragma warning( disable : 4800 )

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_PLANET
	{
		int Stdcall Warriors( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			UInt* ObjAddress = NULL;
			lua_newtable( LuaHandle );
			for( UInt I = 0; I < Planet->WarriorsCount(); I++ )
			{
				lua_pushinteger( LuaHandle, I + 1 );
				ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SHIP*) );
				*ObjAddress = (UInt)Planet->Warrior(I);
				luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
				lua_settable( LuaHandle, -3 );
			}
			return 1;
		}

		int Stdcall IsEqual( lua_State* LuaHandle )
		{
			PVoid ObjA = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			PVoid ObjB = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 2, SR_LUA_PLANET_METATABLE_NAME );
			
			lua_pushboolean( LuaHandle, ObjA == ObjB );
			return 1;
		}

		// ¬озвращает/устанавливает текущего обладател€ планеты
		int Stdcall Fraction( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushinteger(LuaHandle, Planet->Fraction() );
			return 1;
		}

		int Stdcall SetFraction( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			E_FRACTION_OWNER NewFraction = (E_FRACTION_OWNER)luaL_checkinteger( LuaHandle, 2 );
			Planet->SetFraction( NewFraction );
			return 0;
		}

		// ¬озвращает/устанавливает родную расу на планете
		int Stdcall Species( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Planet->Species() );
			return 1;
		}

		int Stdcall SetSpecies( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			E_SPECIES_OWNER NewSpecies = (E_SPECIES_OWNER)luaL_checkinteger(LuaHandle, 2);
			Planet->SetSpecies( NewSpecies );
			return 0;
		}

		// ¬озвращает/устанавливает форму правлени€ на планете
		int Stdcall Government( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Planet->Government() );
			return 1;
		}

		int Stdcall SetGovernment( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			E_GOVERNMENT_FORM NewGovernment = (E_GOVERNMENT_FORM)luaL_checkinteger( LuaHandle, 2 );
			Planet->SetGovernment( NewGovernment );
			return 0;
		}

		// ¬озвращает/устанавливает тип экономики на планете
		int Stdcall Economy( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Planet->Economy() );
			return 1;
		}

		int Stdcall SetEconomy( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			E_ECONOMY NewEco = (E_ECONOMY)luaL_checkinteger( LuaHandle, 2 );
			Planet->SetEconomy( NewEco );
			return 0;
		}

		// ¬озвращает/устанавливает исследуемые территории на планете( незаселЄнной )
		int Stdcall Terrain( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			S_PLANET_TERRAIN PlanetTerrain;
			Planet->Terrain( PlanetTerrain );

			lua_newtable( LuaHandle );
			lua_pushstring(LuaHandle, "Hill" );
			lua_pushinteger( LuaHandle, PlanetTerrain.Hill );
			lua_settable( LuaHandle, -3 );

			lua_pushstring( LuaHandle, "Land" );
			lua_pushinteger( LuaHandle, PlanetTerrain.Land );
			lua_settable( LuaHandle, -3 );

			lua_pushstring( LuaHandle, "Water" );
			lua_pushinteger( LuaHandle, PlanetTerrain.Water );
			lua_settable( LuaHandle, -3 );

			return 1;
		}
		int Stdcall SetTerrain( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TTABLE );
			S_PLANET_TERRAIN PlanetTerrain;
			Planet->Terrain( PlanetTerrain );

			lua_pushstring( LuaHandle, "Hill" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				if( lua_isinteger( LuaHandle, -1 ) )
					PlanetTerrain.Hill = (UInt)lua_tointeger( LuaHandle, -1 );
			lua_pushstring( LuaHandle, "Land" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				if( lua_isinteger( LuaHandle, -1 ) )
					PlanetTerrain.Land = (UInt)lua_tointeger( LuaHandle, -1 );
			lua_pushstring( LuaHandle, "Water" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				if( lua_isinteger( LuaHandle, -1 ) )
					PlanetTerrain.Water = (UInt)lua_tointeger( LuaHandle, -1 );
		//	lua_pop( LuaHandle, 3 );

			Planet->SetTerrain( PlanetTerrain );

			return 0;
		}

		// ¬озвращает/устанавливает исследованные территории на планете( незаселЄнной )
		int Stdcall TerrainExplored( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			S_PLANET_TERRAIN PlanetTerrain;
			Planet->TerrainExplored( PlanetTerrain );

			lua_newtable( LuaHandle );
			lua_pushstring(LuaHandle, "Hill" );
			lua_pushinteger( LuaHandle, PlanetTerrain.Hill );
			lua_settable( LuaHandle, -3 );

			lua_pushstring( LuaHandle, "Land" );
			lua_pushinteger( LuaHandle, PlanetTerrain.Land );
			lua_settable( LuaHandle, -3 );

			lua_pushstring( LuaHandle, "Water" );
			lua_pushinteger( LuaHandle, PlanetTerrain.Water );
			lua_settable( LuaHandle, -3 );

			return 1;
		}

		int Stdcall SetTerrainExplored( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TTABLE );
			S_PLANET_TERRAIN PlanetTerrain;
			Planet->TerrainExplored( PlanetTerrain );

			lua_pushstring( LuaHandle, "Hill" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				if( lua_isinteger( LuaHandle, -1 ) )
					PlanetTerrain.Hill = (UInt)lua_tointeger( LuaHandle, -1 );
			lua_pushstring( LuaHandle, "Land" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				if( lua_isinteger( LuaHandle, -1 ) )
					PlanetTerrain.Land = (UInt)lua_tointeger( LuaHandle, -1 );
			lua_pushstring( LuaHandle, "Water" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				if( lua_isinteger( LuaHandle, -1 ) )
					PlanetTerrain.Water = (UInt)lua_tointeger( LuaHandle, -1 );
		//	lua_pop( LuaHandle, 3 );

			Planet->SetTerrainExplored( PlanetTerrain );

			return 0;
		}

		// ¬озвращает/устанавливает радиус планеты
		int Stdcall Radius( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushnumber( LuaHandle, Planet->Radius() );
			return 1;
		}

		int Stdcall SetRadius( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			Double NewRadius = (Double)luaL_checknumber( LuaHandle, 2 );
			Planet->SetRadius( NewRadius );
			return 0;
		}

		// ¬озвращает/устанавливает тангенциальную скорость планеты
		int Stdcall OrbitalVelocity( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushnumber( LuaHandle, Planet->OrbitalVelocity() );
			return 1;
		}

		int Stdcall SetOrbitalVelocity( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			Double NewOrbitalVelocity = (Double)luaL_checknumber( LuaHandle, 2 );
			Planet->SetOrbitalVelocity( NewOrbitalVelocity );
			return 0;
		}

		// ¬озвращает/устанавливает попул€цию планеты
		int Stdcall Population( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Planet->Population() );
			return 1;
		}

		int Stdcall SetPopulation( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			UInt NewPopulation = (UInt)luaL_checkinteger( LuaHandle, 2 );
			Planet->SetPopulation( NewPopulation );
			return 0;
		}

		//¬озвращает количество военных кораблей, приписанных планете
		int Stdcall WarriorsCount( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Planet->WarriorsCount() );
			return 1;
		}

		int Stdcall Warrior( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			UInt i_warrior = (UInt)luaL_checkinteger( LuaHandle, 2 ) -1;

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_SHIP* ) );
			*ObjAddress = (UInt)Planet->Warrior(i_warrior);
			luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			return 1;
		}

		// ¬озвращает/устанавливает флаг работы планеты
		int Stdcall Flags( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			S_PLANET_FLAGS PlanetFlags;
			Planet->Flags( PlanetFlags );

			lua_newtable( LuaHandle );
			lua_pushstring(LuaHandle, "NoBuyShips" );
			lua_pushboolean( LuaHandle, PlanetFlags.NoBuyShips );
			lua_settable( LuaHandle, -3 );

			lua_pushstring(LuaHandle, "NoRandomEvents" );
			lua_pushboolean( LuaHandle, PlanetFlags.NoRandomEvents );
			lua_settable( LuaHandle, -3 );

			return 1;
		}

		int Stdcall SetFlags( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TTABLE );
			S_PLANET_FLAGS PlanetFlags;
			Planet->Flags( PlanetFlags );

			lua_pushstring( LuaHandle, "NoBuyShips" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TBOOLEAN )
				PlanetFlags.NoBuyShips = (Bool)lua_toboolean( LuaHandle, -1 );
			lua_pushstring( LuaHandle, "NoRandomEvents" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TBOOLEAN )
				PlanetFlags.NoRandomEvents = (Bool)lua_toboolean( LuaHandle, -1 );
		//	lua_pop( LuaHandle, 2 );

			Planet->SetFlags( PlanetFlags );

			return 0;
		}

		// ¬озвращает/устанавливает текущий проект планеты
		int Stdcall Invention( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Planet->Invention() );
			return 1;
		}

		int Stdcall SetInvention( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			E_INVENTION NewInvention = (E_INVENTION)luaL_checkinteger( LuaHandle, 2 );
			Planet->SetInvention( NewInvention );
			return 0;
		}

		// ¬озвращает/устанавливает уровень исследовани€ проекта планеты. ¬ отрезке [ 0; 100 ]
		// ¬ единственном экземпл€ре: не прив€зан к какому-либо проекту.
		int Stdcall InventionPoints( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			lua_pushnumber( LuaHandle, Planet->InventionPoints() );
			return 1;
		}

		int Stdcall SetInventionPoints( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			Float NewInventionPoints = (Float)luaL_checknumber( LuaHandle, 2 );

			Planet->SetInventionPoints( NewInventionPoints );
			return 0;
		}

		// ¬озвращает/устанавливает технический уровень проекта планеты
		int Stdcall InventionLvl( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			E_INVENTION InventionType = (E_INVENTION)luaL_checkinteger( LuaHandle, 2 );
			lua_pushinteger( LuaHandle, Planet->InventionLvl( InventionType ) );
			return 1;
		}

		int Stdcall SetInventionLvl( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			E_INVENTION InventionType = (E_INVENTION)luaL_checkinteger( LuaHandle, 2 );
			UInt NewInvLvl = (UInt)luaL_checkinteger(LuaHandle, 3 );
			Planet->SetInventionLvl( InventionType, NewInvLvl );
			return 0;
		}

		// возвращает систему планеты
		int Stdcall Star( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata(LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_STAR*) );
			*ObjAddress = (UInt)Planet->Star();
			luaL_setmetatable( LuaHandle, SR_LUA_STAR_METATABLE_NAME );
			return 1;
		}

		int Stdcall VisualModel( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			const Unicode* WVisModel = Planet->VisualModel();
			const UInt StringLen = wcslen( WVisModel );
			char* MVisModel = new char[ StringLen + 1 ]; 
			WideCharToMultiByte( CP_UTF8, NULL, WVisModel, -1, MVisModel, StringLen + 1, NULL, NULL );
			lua_pushstring( LuaHandle, MVisModel );
			delete[] MVisModel;
			return 1;
		}

		int Stdcall SetVisualModel( lua_State* LuaHandle )
		{
			C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
			const char* MVisModel = luaL_checkstring( LuaHandle, 2 );
			const UInt StringLen = strlen( MVisModel );
			Unicode* WVisModel = new Unicode[ StringLen + 1 ];
			MultiByteToWideChar( CP_UTF8, NULL, MVisModel, -1, WVisModel, StringLen + 1 );
			Planet->SetVisualModel( WVisModel );
			delete[] WVisModel;
			return 0;
		}

		//int Stdcall Name( lua_State* LuaHandle )
		//{
		//	C_PLANET* Planet = (C_PLANET*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_PLANET_METATABLE_NAME );
		//	const Unicode* WVisModel = Planet->Name();
		//	const UInt StringLen = wcslen( WVisModel );
		//	char* MVisModel = new char[ StringLen + 1 ]; 
		//	WideCharToMultiByte( CP_UTF8, NULL, WVisModel, -1, MVisModel, StringLen + 1, NULL, NULL );
		//	lua_pushstring( LuaHandle, MVisModel );
		//	delete[] MVisModel;
		//	return 1;
		//}

	}
}
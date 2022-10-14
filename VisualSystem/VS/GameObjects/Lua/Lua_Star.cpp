#include "Lua_Star.hpp"
#include "Lua_Ship.hpp"
#include "Lua_Planet.hpp"
#include "Lua_Sector.hpp"

#include "../Star.hpp"

#pragma warning( disable : 4800 )

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_STAR
	{
		int Stdcall Planets( lua_State* LuaHandle )
		{
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			UInt* ObjAddress = NULL;
			lua_newtable( LuaHandle );
			for( UInt I = 0; I < Star->PlanetsCount(); I++ )
			{
				lua_pushinteger( LuaHandle, I + 1 );
				ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_PLANET*) );
				*ObjAddress = (UInt)Star->Planet(I);
				luaL_setmetatable( LuaHandle, SR_LUA_PLANET_METATABLE_NAME );
				lua_settable( LuaHandle, -3 );
			}
			return 1;
		}

		int Stdcall Ships( lua_State* LuaHandle )
		{
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			UInt* ObjAddress = NULL;
			lua_newtable( LuaHandle );
			for( UInt I = 0; I < Star->ShipsCount(); I++ )
			{
				lua_pushinteger( LuaHandle, I + 1 );
				ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SHIP*) );
				*ObjAddress = (UInt)Star->Ship(I);
				luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
				lua_settable( LuaHandle, -3 );
			}
			return 1;
		}

		int Stdcall IsEqual( lua_State* LuaHandle )
		{
			PVoid ObjA = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			PVoid ObjB = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 2, SR_LUA_STAR_METATABLE_NAME );
			
			lua_pushboolean( LuaHandle, ObjA == ObjB );
			return 1;
		}

		// Возвращает/устанавливает фракцию, владеющую системой
		int Stdcall Fraction( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Star->Fraction() );
			return 1;
		}

		int Stdcall SetFraction( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			E_FRACTION Fraction = (E_FRACTION)luaL_checkinteger( LuaHandle, 2 );
			Star->SetFraction( Fraction );
			return 0;
		}

		// Возвращает/устанавливает серию доминаторов, владеющую системой (или владевшую ей ранее)
		int Stdcall DomSeries( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Star->DomSeries() );
			return 1;
		}
		int Stdcall SetDomSeries( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			E_DOMSERIES DomSeries = (E_DOMSERIES)luaL_checkinteger( LuaHandle, 2 );
			Star->SetDomSeries( DomSeries );
			return 0;
		}

		// Возвращает количество кораблей в системе
		int Stdcall	ShipsCount( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Star->ShipsCount() );
			return 1;
		}

		int Stdcall	Ship( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			UInt i_ship = (UInt)luaL_checkinteger( LuaHandle, 2 ) -1;

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SHIP*) );
			*ObjAddress = (UInt)Star->Ship(i_ship);
			luaL_setmetatable(LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			return 1;
		}

		// Создаёт базу
		int Stdcall CreateBase( lua_State* LuaHandle ) {
			static C_SHIP NewShip;
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			E_BASE_TYPE BaseType = (E_BASE_TYPE)luaL_checkinteger( LuaHandle, 2 );
			Star->CreateBase( BaseType, &NewShip );

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_SHIP* ) );
			*ObjAddress = (UInt)&NewShip;
			luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			return 1;
		}
		
		// Ведется ли сражение в системе
		int Stdcall IsBattle( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			lua_pushboolean( LuaHandle, Star->IsBattle() );
			return 1;
		}

		// Возвращает количество планет в системе
		int Stdcall  PlanetsCount( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Star->PlanetsCount() );
			return 1;
		}

		// Возвращает объект планеты
		int Stdcall Planet( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			UInt i_planet = (UInt)luaL_checkinteger( LuaHandle, 2 ) -1;

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_PLANET*) );
			*ObjAddress = (UInt)Star->Planet(i_planet);
			luaL_setmetatable( LuaHandle, SR_LUA_PLANET_METATABLE_NAME );
			return 1;
		}

		// Возвращает/устанавливает номер фона системы
		int Stdcall FonImage( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Star->FonImage() );
			return 1;
		}
		int Stdcall SetFonImage( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			UInt FonImage = (UInt)luaL_checkinteger( LuaHandle, 2 );
			Star->SetFonImage( FonImage );
			return 0;
		}

		// Возвращает сектор системы
		int Stdcall Sector( lua_State* LuaHandle ) {
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SECTOR*) );
			*ObjAddress = (UInt)Star->Sector();
			luaL_setmetatable( LuaHandle, SR_LUA_SECTOR_METATABLE_NAME );
			return 1;
		}

		int Stdcall Flags( lua_State* LuaHandle )
		{
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			S_STAR_FLAGS Flags;
			Star->Flags( Flags );

			lua_newtable( LuaHandle );

			lua_pushstring( LuaHandle, "NoComeKling" );
			lua_pushboolean( LuaHandle, Flags.NoComeKling );
			lua_settable( LuaHandle, -3 );

			return 1;
		}

		int Stdcall SetFlags( lua_State* LuaHandle )
		{
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TTABLE );

			S_STAR_FLAGS Flags;
			Star->Flags( Flags );

			lua_pushstring( LuaHandle, "NoComeKling" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TBOOLEAN )
				Flags.NoComeKling = (Bool)lua_toboolean( LuaHandle, -1 );

			Star->SetFlags( Flags );

			return 0;
		}

		int Stdcall VisualModel( lua_State* LuaHandle )
		{
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			const Unicode* WVisModel = Star->VisualModel();
			const UInt StringLen = wcslen( WVisModel );
			char* MVisModel = new char[ StringLen + 1 ]; 
			WideCharToMultiByte( CP_UTF8, NULL, WVisModel, -1, MVisModel, StringLen + 1, NULL, NULL );
			lua_pushstring( LuaHandle, MVisModel );
			delete[] MVisModel;
			return 1;
		}

		int Stdcall SetVisualModel( lua_State* LuaHandle )
		{
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_STAR_METATABLE_NAME );
			const char* MVisModel = luaL_checkstring( LuaHandle, 2 );
			const UInt StringLen = strlen( MVisModel );
			Unicode* WVisModel = new Unicode[ StringLen + 1 ];
			MultiByteToWideChar( CP_UTF8, NULL, MVisModel, -1, WVisModel, StringLen + 1 );
			Star->SetVisualModel( WVisModel );
			delete[] WVisModel;
			return 0;
		}
	}
}
#include "Lua_Sector.hpp"
#include "Lua_Star.hpp"

#include "../Sector.hpp"

#pragma warning( disable : 4800 )

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_SECTOR
	{
		int Stdcall Stars( lua_State* LuaHandle )
		{
			C_SECTOR* Sector = (C_SECTOR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SECTOR_METATABLE_NAME );
			UInt* ObjAddress = NULL;
			lua_newtable( LuaHandle );
			for( UInt I = 0; I < Sector->StarsCount(); I++ )
			{
				lua_pushinteger( LuaHandle, I + 1 );
				ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_STAR*) );
				*ObjAddress = (UInt)Sector->Star(I);
				luaL_setmetatable( LuaHandle, SR_LUA_STAR_METATABLE_NAME );
				lua_settable( LuaHandle, -3 );
			}
			return 1;
		}

		int Stdcall IsEqual( lua_State* LuaHandle )
		{
			PVoid ObjA = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 1, SR_LUA_SECTOR_METATABLE_NAME );
			PVoid ObjB = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 2, SR_LUA_SECTOR_METATABLE_NAME );
			
			lua_pushboolean( LuaHandle, ObjA == ObjB );
			return 1;
		}

		// Возвращает количество систем в секторе
		int Stdcall StarsCount( lua_State* LuaHandle )
		{
			C_SECTOR* Sector = (C_SECTOR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SECTOR_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Sector->StarsCount() );
			return 1;
		}

		// Возвращает объект системы
		int Stdcall Star( lua_State* LuaHandle )
		{
			C_SECTOR* Sector = (C_SECTOR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SECTOR_METATABLE_NAME );
			UInt i_star = (UInt)luaL_checkinteger( LuaHandle, 2 ) -1;

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_STAR*) );
			*ObjAddress = (UInt)Sector->Star(i_star);
			luaL_setmetatable(LuaHandle, SR_LUA_STAR_METATABLE_NAME );
			return 1;
		}

		// Виден ли сектор
		int Stdcall IsVisible( lua_State* LuaHandle )
		{
			C_SECTOR* Sector = (C_SECTOR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SECTOR_METATABLE_NAME );
			lua_pushboolean( LuaHandle, Sector->IsVisible() );
			return 1;
		}

		int Stdcall SetVisible( lua_State* LuaHandle )
		{
			C_SECTOR* Sector = (C_SECTOR*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SECTOR_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TBOOLEAN );
			bool VisibleFlag = (bool)lua_toboolean( LuaHandle, 2 );
			Sector->SetVisible( VisibleFlag );
			return 0;
		}
	}
}
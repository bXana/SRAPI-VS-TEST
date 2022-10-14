#include "Lua_Ship.hpp"
#include "Lua_Planet.hpp"
#include "Lua_Star.hpp"

#include "../Ship.hpp"

#pragma warning( disable : 4800 )

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_SHIP
	{
		int Stdcall IsEqual( lua_State* LuaHandle )
		{
			PVoid ObjA = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			PVoid ObjB = (PVoid)**(UInt**)luaL_checkudata( LuaHandle, 2, SR_LUA_SHIP_METATABLE_NAME );
			
			lua_pushboolean( LuaHandle, ObjA == ObjB );
			return 1;
		}

		// Возвращает модель корабля
		int Stdcall VisualModel( lua_State* LuaHandle ) 
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			const Unicode* WVisModel = Ship->VisualModel();
			const UInt StringLen = wcslen( WVisModel );
			char* MVisModel = new char[ StringLen + 1 ]; 
			WideCharToMultiByte( CP_UTF8, NULL, WVisModel, -1, MVisModel, StringLen + 1, NULL, NULL );
			lua_pushstring( LuaHandle, MVisModel );
			delete[] MVisModel;
			return 1;
		}
		// Устанавливает постоянную модель корабля
		int Stdcall SetVisualModel ( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			luaL_checktype( LuaHandle, 3, LUA_TBOOLEAN );
			bool IsPermanentFlag = (bool)lua_toboolean( LuaHandle, 3 ); 
			const char* MVisModel = luaL_checkstring( LuaHandle, 2 );
			const UInt StringLen = strlen( MVisModel );
			Unicode* WVisModel = new Unicode[ StringLen + 1 ];
			MultiByteToWideChar( CP_UTF8, NULL, MVisModel, -1, WVisModel, StringLen + 1 );
			Ship->SetVisualModel( WVisModel, IsPermanentFlag );
			delete[] WVisModel;
			return 0;
		}

		// Возвращает родную планету корабля
		int Stdcall Home( lua_State* LuaHandle ) 
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			
			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_PLANET*) );
			*ObjAddress = (UInt)Ship->Home();
			luaL_setmetatable( LuaHandle, SR_LUA_PLANET_METATABLE_NAME );
			return 1;
		}

		// Возвращает/Изменяет тип корабля
		int Stdcall Type( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Ship->Type() );
			return 1;
		}

		// Для станций устанавливать исключительно Типы базы
		int Stdcall SetType( lua_State* LuaHandle ) {
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_SHIP_TYPE NewType = (E_SHIP_TYPE)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetType( NewType );
			return 0;
		}

		int Stdcall SubType( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_SHIP_SUBTYPE SubType = Ship->SubType();
			lua_pushinteger( LuaHandle, SubType );
			return 1;
		}

		int Stdcall SetSubType( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_SHIP_SUBTYPE eNewShipSubType = (E_SHIP_SUBTYPE)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetSubType( eNewShipSubType );
			return 0;
		}

		// Возвращает систему, в которой находится корабль
		int Stdcall Star( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_STAR*) );
			*ObjAddress = (UInt)Ship->Star();
			luaL_setmetatable( LuaHandle, SR_LUA_STAR_METATABLE_NAME );
			return 1;
		}

		// Возвращает/устанавливает серию доминатора
		// Использовать только на доминаторах
		int Stdcall DomSeries( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Ship->DomSeries() );
			return 1;
		}
		int Stdcall	SetDomSeries( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_DOMSERIES eNewSeries = (E_DOMSERIES)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetDomSeries( eNewSeries );
			return 0;
		}

		// Возвращает/устанавливает фракцию корабля( Фракцию, а не расу управляющего кораблём )
		int Stdcall Fraction( lua_State* LuaHandle ) 
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Ship->Fraction() );
			return 1;
		}
		// Для обычных кораблей фракции доминаторов и неизвестных кораблей вылетают
		int Stdcall SetFraction( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_FRACTION_OWNER NewFraction = (E_FRACTION_OWNER)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetFraction( NewFraction );
			return 0;
		}

		// Возвращает/устанавливает расу пилота
		int Stdcall Species( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Ship->Species() );
			return 1;
		}

		int Stdcall SetSpecies( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_SPECIES_OWNER NewSpecies = (E_SPECIES_OWNER)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetSpecies( NewSpecies );
			return 0;
		}

		// Возвращает/изменяет статус корабля на принадлежность определенному типу
		int Stdcall StatusType( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Ship->StatusType() );
			return 1;
		}
		// Вне зависимости от вмешательства пользователя, Изменяет статус на стандартный
		int Stdcall SetStatusType( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_SHIP_STATUS NewStatus = (E_SHIP_STATUS)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetStatusType( NewStatus );
			return 0;
		}

		int Stdcall Destroy( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			Ship->Destroy();
			return 0;
		}

		// Возвращает/устанавливает текущую цель
		int Stdcall Target( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SHIP*) );
			*ObjAddress = (UInt)Ship->Target();
			luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			return 1;
		}

		int Stdcall SetTarget( lua_State* LuaHandle )
		{
			C_SHIP* Ship	  = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			C_SHIP* NewTarget = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 2, SR_LUA_SHIP_METATABLE_NAME );
			Ship->SetTarget( *NewTarget );
			return 0;
		}

		// В гипер-пространстве ли корабль?
		int Stdcall InHyper( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushboolean( LuaHandle, Ship->InHyper() );
			return 1;
		}

		// На планете ли корабль?
		int Stdcall OnPlanet( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			C_PLANET* Planet = Ship->OnPlanet();

			if( *(UInt*)Planet )
			{
				UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_PLANET* ) );
				*ObjAddress = (UInt)Planet;
				luaL_setmetatable( LuaHandle, SR_LUA_PLANET_METATABLE_NAME );
			}
			else
				lua_pushnil( LuaHandle );

			return 1;
		}

		// На базе ли корабль?
		int Stdcall OnBase( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			C_SHIP* Base = Ship->OnBase();

			if( *(UInt*)Base )
			{
				UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_SHIP* ) );
				*ObjAddress = (UInt)Base;
				luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			}
			else
				lua_pushnil( LuaHandle );

			return 1;
		}

		int Stdcall Teleport( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 2, SR_LUA_STAR_METATABLE_NAME );
			luaL_checktype( LuaHandle, 3, LUA_TTABLE );
			SVec2Position<Float> Position;

			lua_pushstring( LuaHandle, "X" );
			if( lua_rawget( LuaHandle, 3 ) == LUA_TNUMBER )
				Position.X = (Float)lua_tonumber( LuaHandle, -1 );
			lua_pushstring( LuaHandle, "Y" );
			if( lua_rawget( LuaHandle, 3 ) == LUA_TNUMBER )
				Position.Y = (Float)lua_tonumber( LuaHandle, -1 );

			const UInt JmpDuration = (UInt)luaL_checkinteger( LuaHandle, 4 );

			Ship->Teleport( Star, Position, JmpDuration );
			return 0;
		}

		int Stdcall Land( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			luaL_checktype( LuaHandle, 3, LUA_TBOOLEAN );
			C_OBJECT* TargetObject = NULL;

			if( !luaL_testudata( LuaHandle, 2, SR_LUA_PLANET_METATABLE_NAME ) )
			{
				if( !luaL_testudata( LuaHandle, 2, SR_LUA_SHIP_METATABLE_NAME ) )
					luaL_argexpected( LuaHandle, false, 2, "Station or Planet" );

				TargetObject = (C_OBJECT*)*(UInt*)luaL_testudata( LuaHandle, 2, SR_LUA_SHIP_METATABLE_NAME );
				Ship->Land( TargetObject, lua_toboolean( LuaHandle, 3 ) );
			}
			else
			{
				TargetObject = (C_OBJECT*)*(UInt*)luaL_testudata( LuaHandle, 2, SR_LUA_PLANET_METATABLE_NAME );
				Ship->Land( TargetObject, lua_toboolean( LuaHandle, 3 ) );
			}

			return 0;
		}

		// Взлететь со станции/планеты
		int Stdcall TakeOff( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			Ship->TakeOff();
			return 0;
		}

		// Направляет корабль на позицию
		int Stdcall Move( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TTABLE );
			luaL_checktype( LuaHandle, 3, LUA_TBOOLEAN );
			SVec2Position<Float> Position;

			lua_pushstring( LuaHandle, "X" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				Position.X = (Float)lua_tonumber( LuaHandle, -1 );
			lua_pushstring( LuaHandle, "Y" );
			if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER )
				Position.Y = (Float)lua_tonumber( LuaHandle, -1 );

			Ship->Move( Position, lua_toboolean( LuaHandle, 3 ) );

			return 0;
		}

		// Направляет корабль за кораблём
		int Stdcall Fallow( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			C_SHIP* TargetShip = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 2, SR_LUA_SHIP_METATABLE_NAME );
			E_FALLOW_TYPE FallowType = (E_FALLOW_TYPE)luaL_checkinteger( LuaHandle, 3 );
			luaL_checktype( LuaHandle, 4, LUA_TBOOLEAN );
			
			Ship->Fallow( TargetShip, FallowType, lua_toboolean( LuaHandle, 4 ) );

			return 0;
		}

		// Совершить прыжок в другую систему
		int Stdcall Jump( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			C_STAR* Star = (C_STAR*)*(UInt*)luaL_checkudata( LuaHandle, 2, SR_LUA_STAR_METATABLE_NAME );
			luaL_checktype( LuaHandle, 3, LUA_TBOOLEAN );

			Ship->Jump( Star, lua_toboolean( LuaHandle, 3 ) );
			
			return 0;
		}

		// Отменяет текущие команды
		int Stdcall CancelTask( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			Ship->CancelTask();
			return 0;
		}

		// Возвращает/устанавливает ранг у коалиции
		int Stdcall CRank( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Ship->CRank() );
			return 1;
		}

		int Stdcall SetCRank( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_SHIP_RANK_COALITION NewRank = (E_SHIP_RANK_COALITION)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetCRank( NewRank );
			return 0;
		}

		// Возвращает/устанавливает ранг у пиратов
		int Stdcall PRank( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Ship->PRank() );
			return 1;
		}
		int Stdcall SetPRank( lua_State* LuaHandle )
		{
			C_SHIP* Ship = (C_SHIP*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_SHIP_METATABLE_NAME );
			E_SHIP_RANK_PIRATE NewRank = (E_SHIP_RANK_PIRATE)luaL_checkinteger( LuaHandle, 2 );
			Ship->SetPRank( NewRank );
			return 0;
		}
	}
}

///////////////////////////////////////
//		Lua GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Ship Lua API 
///////////////////////////////////////
#ifndef _SHIP_LUA_HPP_
#define _SHIP_LUA_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "../../Params.hpp"
#include "../../../LuaAPI/LuaInclude.hpp"

namespace VS_LUA_GAMEMETHODS
{
	namespace LUA_SHIP
	{
		int Stdcall IsEqual( lua_State* LuaHandle );

		// Возвращает модель корабля
		int Stdcall VisualModel( lua_State* LuaHandle );
		// Устанавливает постоянную модель корабля
		int Stdcall SetVisualModel ( lua_State* LuaHandle );

		// Возвращает родную планету корабля
		int Stdcall Home( lua_State* LuaHandle );

		// Возвращает/Изменяет тип корабля
		int Stdcall Type( lua_State* LuaHandle );
		// Для станций устанавливать исключительно Типы базы
		int Stdcall SetType( lua_State* LuaHandle );

		// Возвращает/устанавливает подтип корабля
		int Stdcall SubType( lua_State* LuaHandle );
		int Stdcall SetSubType( lua_State* LuaHandle );

		// Возвращает систему, в которой находится корабль
		int Stdcall Star( lua_State* LuaHandle );

		// Возвращает/устанавливает серию доминатора
		// Использовать только на доминаторах
		int Stdcall DomSeries( lua_State* LuaHandle );
		int Stdcall	SetDomSeries( lua_State* LuaHandle );

		// Возвращает/устанавливает фракцию корабля( Фракцию, а не расу управляющего кораблём )
		int Stdcall Fraction( lua_State* LuaHandle );
		// Для обычных кораблей фракции доминаторов и неизвестных кораблей вылетают
		int Stdcall SetFraction( lua_State* LuaHandle );

		// Возвращает/устанавливает расу пилота
		int Stdcall Species( lua_State* LuaHandle );
		int Stdcall SetSpecies( lua_State* LuaHandle );

		// Возвращает/изменяет статус корабля на принадлежность определенному типу
		int Stdcall StatusType( lua_State* LuaHandle );
		// Вне зависимости от вмешательства пользователя, Изменяет статус на стандартный
		int Stdcall SetStatusType( lua_State* LuaHandle );

		// Уничтожить корабль
		int Stdcall Destroy( lua_State* LuaHandle );

		// Возвращает/устанавливает текущую цель
		int Stdcall Target( lua_State* LuaHandle );
		int Stdcall SetTarget( lua_State* LuaHandle );

		// В гипер-пространстве ли корабль?
		int Stdcall InHyper( lua_State* LuaHandle );

		// На планете ли корабль?
		int Stdcall OnPlanet( lua_State* LuaHandle );

		// На базе ли корабль?
		int Stdcall OnBase( lua_State* LuaHandle );

		// Телепортироваться в указанную систему( Работает только для доминиона и военной базы )
		int Stdcall Teleport( lua_State* LuaHandle );

		// Совершить посадку на планету/станцию
		int Stdcall Land( lua_State* LuaHandle );

		// Взлететь со станции/планеты
		int Stdcall TakeOff( lua_State* LuaHandle );

		// Направляет корабль на позицию
		int Stdcall Move( lua_State* LuaHandle );

		// Направляет корабль за кораблём
		int Stdcall Fallow( lua_State* LuaHandle );

		// Совершить прыжок в другую систему
		int Stdcall Jump( lua_State* LuaHandle );

		// Отменяет текущие команды
		int Stdcall CancelTask( lua_State* LuaHandle );

		// Возвращает/устанавливает ранг у коалиции
		int Stdcall CRank( lua_State* LuaHandle );
		int Stdcall SetCRank( lua_State* LuaHandle );

		// Возвращает/устанавливает ранг у пиратов
		int Stdcall PRank( lua_State* LuaHandle );
		int Stdcall SetPRank( lua_State* LuaHandle );
	}
}

#define SR_LUA_SHIP_METATABLE_NAME "VS.Ship"

#endif
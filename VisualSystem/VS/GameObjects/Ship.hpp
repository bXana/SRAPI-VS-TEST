///////////////////////////////////////
//		GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Ship API
///////////////////////////////////////

#ifndef _SHIP_HPP_
#define _SHIP_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "GameObject.hpp"
#include "Planet.hpp"
#include "Item.hpp"

#include "../Math.hpp"

enum E_SHIP_TYPE
{
	// Корабли
	SHIP_KLING				 = 0,
	SHIP_RANGER				 = 1,
	SHIP_TRANSPORT			 = 2,
	SHIP_PIRATE				 = 3,
	SHIP_WARRIOR			 = 4,
	SHIP_TRANCLUTATOR		 = 5,
	// Базы
	SHIP_RANGER_CENTER_BASE	 = 6,
	SHIP_PIRATE_BASE		 = 7,
	SHIP_MILITARY_BASE		 = 8,
	SHIP_SCIENCE_BASE		 = 9,
	SHIP_BUSINES_CENTER_BASE = 10,
	SHIP_MEDICAL_CENTER_BASE = 11,
	SHIP_DOMINION_BASE		 = 12,
	SHIP_UNKNOWN_BASE		 = 13
};

enum E_SHIP_SUBTYPE
{
	E_SHIP_SUBTYPE_RANGER_TRAIDER = 0,
	E_SHIP_SUBTYPE_RANGER_PIRATE  = 1,
	E_SHIP_SUBTYPE_RANGER_WARRIOR = 2,

	E_SHIP_SUBTYPE_DOMINATOR_BOSS	  = 0,
	E_SHIP_SUBTYPE_DOMINATOR_EKVENTOR = 1,
	E_SHIP_SUBTYPE_DOMINATOR_URGANT	  = 2,
	E_SHIP_SUBTYPE_DOMINATOR_SMERSH	  = 3,
	E_SHIP_SUBTYPE_DOMINATOR_MENOK	  = 4,
	E_SHIP_SUBTYPE_DOMINATOR_SHTIP	  = 5,
	E_SHIP_SUBTYPE_DOMINATOR_BERTOR	  = 6,
	E_SHIP_SUBTYPE_DOMINATOR_KLIG	  = 7,

	E_SHIP_SUBTYPE_CIVILIAN_TRANSPORT = 0,
	E_SHIP_SUBTYPE_CIVILIAN_LINER	  = 1,
	E_SHIP_SUBTYPE_CIVILIAN_DIPLOMAT  = 2,

	E_SHIP_SUBTYPE_WARRIOR_STANDART	= 0,
	E_SHIP_SUBTYPE_WARRIOR_FLAGMAN	= 1,

	E_SHIP_SUBTYPE_PIRATE_FREE	= 0,
	E_SHIP_SUBTYPE_PIRATE_TANK = 1,
	E_SHIP_SUBTYPE_PIRATE_SNIPER = 2,
	E_SHIP_SUBTYPE_PIRATE_FASTER = 3
};

enum E_SHIP_STATUS
{
	E_SHIP_STATUS_KLING		= 0,
	E_SHIP_STATUS_NONE		= 1,
	E_SHIP_STATUS_CWARRIOR  = 2,
	E_SHIP_STATUS_CACTIVE	= 3,
	E_SHIP_STATUS_CPASSIVE	= 4,
	E_SHIP_STATUS_NEUTRAL	= 5,
	E_SHIP_STATUS_PPASSIVE	= 6,
	E_SHIP_STATUS_PACTIVE	= 7,
	E_SHIP_STATUS_PWARRIOR	= 8,
	E_SHIP_STATUS_CUSTOM	= 9
};

enum E_SHIP_RANK_COALITION
{
	E_SHIP_RANK_COALITION_NEWBIE	 = 0,
	E_SHIP_RANK_COALITION_CADET		 = 1,
	E_SHIP_RANK_COALITION_PILOT		 = 2,
	E_SHIP_RANK_COALITION_CAPTIAN	 = 3,
	E_SHIP_RANK_COALITION_FIGHTER	 = 4,
	E_SHIP_RANK_COALITION_AS		 = 5,
	E_SHIP_RANK_COALITION_COMMANDER  = 6,
	E_SHIP_RANK_COALITION_ADMIRAL	 = 7
};

enum E_SHIP_RANK_PIRATE
{
	E_SHIP_RANK_PIRATE_ROOKIE		 = 0,
	E_SHIP_RANK_PIRATE_BOY			 = 1,
	E_SHIP_RANK_PIRATE_RAIDER		 = 2,
	E_SHIP_RANK_PIRATE_SKIPPER		 = 3,
	E_SHIP_RANK_PIRATE_THUG			 = 4,
	E_SHIP_RANK_PIRATE_ATAMAN		 = 5,
	E_SHIP_RANK_PIRATE_KHAN			 = 6,
	E_SHIP_RANK_PIRATE_BARON		 = 7
};

enum E_FALLOW_TYPE
{
	E_FALLOW_TYPE_FALLOWING		  = 0,
	E_FALLOW_TYPE_DIST_SHOOT	  = 1,
	E_FALLOW_TYPE_LONG_DIST_SHOOT = 2
};

class C_STAR;
class C_PLANET;
class C_ITEM;

class C_SHIP: public C_OBJECT
{	
	friend class CSpaceRangersAPI;
	friend class C_STAR;
	friend class C_PLANET;
	friend class C_GALAXY;
		C_SHIP& operator = ( const void* Object );

		// visual model changer
		static void *DetachFromSE_, *RuinsChangeVisualConst_, *RuinsChangeVisualF_, 
					*LinkToSE_, *SetGraphName_, *SetAngle_,
					*CalcParam_, *CalcParamGraphSize_;

		static void* OrderTakeOff_, *OrderFallowShip_, *OrderJump_, *OrderNone_;

	public:
		// Возвращает модель корабля
		const Unicode* SR_API VisualModel( void );
		// Устанавливает постоянную модель корабля
		void  SR_API SetVisualModel ( const Unicode* NewVisualId, const bool IsPermanent );

		// Возвращает родную планету корабля
		C_PLANET* SR_API Home( void );

		// Возвращает/Изменяет тип корабля
		E_SHIP_TYPE SR_API Type( void );
		// Для станций устанавливать исключительно Типы базы
		void SR_API SetType( const E_SHIP_TYPE NewType );

		// Возвращает/устанавливает подтип корабля
		E_SHIP_SUBTYPE SR_API SubType( void );
		void SR_API SetSubType( const E_SHIP_SUBTYPE eNewSubType );

		// Возвращает систему, в которой находится корабль
		C_STAR* SR_API Star( void );

		// Возвращает/устанавливает серию доминатора
		// Использовать только на доминаторах
		E_DOMSERIES SR_API DomSeries( void );
		void SR_API	SetDomSeries( const E_DOMSERIES eNewDomSeries );

		// Возвращает/устанавливает фракцию корабля( Фракцию, а не расу управляющего кораблём )
		E_FRACTION_OWNER SR_API Fraction( void );
		// Для обычных кораблей фракции доминаторов и неизвестных кораблей вылетают
		void SR_API SetFraction( const E_FRACTION_OWNER eNewFraction );

		// Возвращает/устанавливает расу пилота
		E_SPECIES_OWNER SR_API Species( void );
		void SR_API SetSpecies( const E_SPECIES_OWNER eNewSpecies );

		// Возвращает/изменяет статус корабля на принадлежность определенному типу
		E_SHIP_STATUS SR_API StatusType( void );
		// Вне зависимости от вмешательства пользователя, Изменяет статус на стандартный
		void SR_API SetStatusType( const E_SHIP_STATUS eNewStatus );

		// Уничтожить корабль
		void SR_API Destroy( void );

		// Возвращает/устанавливает текущую цель
		C_SHIP* SR_API Target( void );
		void SR_API SetTarget( const C_SHIP& CNewTarget );

		// В гипер-пространстве ли корабль?
		Bool SR_API InHyper( void );

		// На планете ли корабль?
		C_PLANET* SR_API OnPlanet( void );

		// На базе ли корабль?
		C_SHIP* SR_API OnBase( void );

		// Телепортироваться в указанную систему( Работает только для доминиона и военной базы )
		void SR_API Teleport( const C_STAR* TargetSystem, const SVec2Position< float >& Position, const UInt JmpDuration );

		// Совершить посадку на планету/станцию
		void SR_API Land( const C_OBJECT* Object, const Bool Priority );

		// Взлететь со станции/планеты
		// Не использовать на игроке
		void __thiscall TakeOff( void );

		// Направляет корабль на позицию
		void SR_API Move( const SVec2Position< float >& Position, const Bool Priority );

		// Направляет корабль за кораблём
		void SR_API Fallow( const C_SHIP* TargetShip, const E_FALLOW_TYPE FallowType, const Bool Priority );

		// Совершить прыжок в другую систему
		void SR_API Jump( const C_STAR* TargetStar, const Bool Priority );

		// Отменяет текущие команды
		void SR_API CancelTask( void );

		// Возвращает/устанавливает ранг у коалиции
		E_SHIP_RANK_COALITION SR_API CRank( void );
		void SR_API SetCRank( const E_SHIP_RANK_COALITION eNewRank );

		// Возвращает/устанавливает ранг у пиратов
		E_SHIP_RANK_PIRATE SR_API PRank( void );
		void SR_API SetPRank( const E_SHIP_RANK_PIRATE eNewRank );

		/* Ignored */

		// Количество вещей в трюме
		UInt SR_API ItemsCount( void );
		C_ITEM* SR_API Item( const UInt ItemN );

		// Возвращает Скорость корабля
		UInt SR_API Speed( void );

		// Возвращает броню корабля
		UInt SR_API Armor( void );

};


#endif
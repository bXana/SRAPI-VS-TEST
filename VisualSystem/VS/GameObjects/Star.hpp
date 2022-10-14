///////////////////////////////////////
//		GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Star API
///////////////////////////////////////
#ifndef _STAR_HPP_
#define _STAR_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "Ship.hpp"
#include "Planet.hpp"
#include "GameObject.hpp"

class C_OBJECT;
class C_GALAXY;
class C_SHIP;
class C_PLANET;
class C_SECTOR;

#pragma warning( disable : 4482 )

struct S_STAR_FLAGS
{
	Bool NoComeKling;
};

enum E_FRACTION
{
	FRACTION_COALITION = 0,
	FRACTION_DOMINATOR = 1,
	FRACTION_PIRATE	  = 2
};

enum E_BASE_TYPE
{
	BASE_RANGER_CENTER		= 6,
	BASE_PIRATE				= 7,
	BASE_MILITARY			= 8,
	BASE_SCIENCE			= 9,
	BASE_BUSINES_CENTER		= 10,
	BASE_MEDICAL_CENTER		= 11,
	BASE_DOMINION			= 12
};

class C_STAR : public C_OBJECT
{
	// pObj = FactObjAddress;
	friend class CSpaceRangersAPI;
	friend class C_GALAXY;

	static void *RuinsObject, *RuinsCreate, *RuinsInit;
		bool __thiscall operator == ( const C_STAR* Object );

		static void* StarChangeVisualF_, *StarChangeVisualConst_,
			*SetGraphNameConst_;
	public:

		// Возвращает/устанавливает фракцию, владеющую системой
		E_FRACTION SR_API Fraction( void );
		void	   SR_API SetFraction( const E_FRACTION eNewFraction );

		// Возвращает/устанавливает серию доминаторов, владеющую системой (или владевшую ей ранее)
		E_DOMSERIES SR_API DomSeries( void );
		void		SR_API SetDomSeries( const E_DOMSERIES eNewDomSeries );

		// Возвращает количество кораблей в системе
		UInt    SR_API	ShipsCount( void );
		C_SHIP* SR_API	Ship( const UInt ShipN );

		// Создаёт базу
		void SR_API  CreateBase( const E_BASE_TYPE eBaseType, C_SHIP* NewShip);
		
		// Ведется ли сражение в системе
		Bool	SR_API  IsBattle( void );

		// Возвращает количество планет в системе
		UInt	SR_API  PlanetsCount( void );

		// Возвращает объект планеты
		C_PLANET* SR_API Planet( const UInt PlanetN );

		// Возвращает/устанавливает номер фона системы
		UInt	  SR_API FonImage( void );
		void	  SR_API SetFonImage( const UInt NewFonImage );

		// Возвращает сектор системы
		C_SECTOR* SR_API Sector( void );

		// Возвращает/устанавливает флаги системы
		void SR_API Flags( S_STAR_FLAGS& Flags );
		void SR_API SetFlags( S_STAR_FLAGS& Flags );

		// Возвращает/устанавливает модель корабля
		const Unicode* SR_API VisualModel( void );
		void  SR_API SetVisualModel( const Unicode* NewVisualId );

};



#endif
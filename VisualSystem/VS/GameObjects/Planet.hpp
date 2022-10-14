///////////////////////////////////////
//		GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Planet API
///////////////////////////////////////
#ifndef _PLANET_HPP_
#define _PLANET_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "GameObject.hpp"

class C_SHIP;
class C_STAR;
enum E_SHIP_SUBTYPE;

enum E_FRACTION_OWNER
{
	E_FRACTION_OWNER_MALOC		= 0,
	E_FRACTION_OWNER_PELENG	    = 1,
	E_FRACTION_OWNER_PEOPLE		= 2,
	E_FRACTION_OWNER_FEI		= 3,
	E_FRACTION_OWNER_GAAL		= 4,
	E_FRACTION_OWNER_KLING		= 5, // dominator
	E_FRACTION_OWNER_NONE		= 6,
	E_FRACTION_OWNER_PIRATECLAN	= 7
};

enum E_SPECIES_OWNER
{
	E_SPECIES_OWNER_MALOC		= 0,
	E_SPECIES_OWNER_PELENG	    = 1,
	E_SPECIES_OWNER_PEOPLE		= 2,
	E_SPECIES_OWNER_FEI			= 3,
	E_SPECIES_OWNER_GAAL		= 4
};

enum E_GOVERNMENT_FORM
{
	E_GOVERNMENT_ANARCHY   = 0,
	E_GOVERNMENT_DICTATOR  = 1,
	E_GOVERNMENT_MONARCHY  = 2,
	E_GOVERNMENT_REPUBLIC  = 3,
	E_GOVERNMENT_DEMOCRACY = 4
};

enum E_ECONOMY
{
	E_ECONOMY_AGRAR		 = 0,
	E_ECONOMY_MIXED		 = 1,
	E_ECONOMY_INDUSTRIAL = 2
};

enum E_INVENTION
{
	E_INVENTION_HULL			  = 0,
	E_INVENTION_FTANK			  = 1, // fuel tanks
	E_INVENTION_ENGINE			  = 2,
	E_INVENTION_RADAR			  = 3,
	E_INVENTION_SCANNER			  = 4,
	E_INVENTION_RDROID			  = 5, // repair droid
	E_INVENTION_CHOOK			  = 6, // cargo hook
	E_INVENTION_TECHLVL			  = 7, // general tech lvl on planet
	E_INVENTION_WPN_ILASER		  = 8, // industrial laser
	E_INVENTION_WPN_FWEAPON		  = 9, // Fragmentation weapon
	E_INVENTION_WPN_LEZKA		  = 10, // Lezka
	E_INVENTION_WPN_RLAUNCHER	  = 11, // Rocket Launcher
	E_INVENTION_WPN_THRETON		  = 12, // 
	E_INVENTION_WPN_WAVEPHASER	  = 13, // wave phaser
	E_INVENTION_WPN_SBLASTER	  = 14, // Streaming blaster
	E_INVENTION_WPN_ECUTTER		  = 15, // electronic cutter
	E_INVENTION_WPN_MRESONATOR	  = 16, // multiresonator
	E_INVENTION_WPN_ATOMVISION	  = 17, // atomic vision
	E_INVENTION_WPN_DISINTEGRATOR = 18, // desintigrator
	E_INVENTION_WPN_TURBOGRAVIR	  = 19  // turbogravir
};

struct S_PLANET_TERRAIN
{
	UInt Water;
	UInt Land;
	UInt Hill;
};

struct S_PLANET_FLAGS
{
	Bool NoBuyShips;
	Bool NoRandomEvents;
};

class C_PLANET: public C_OBJECT
{
	friend class CSpaceRangersAPI;
	static void* PlanetChangeVisualConst_, *PlanetChangeVisualF_;
	static void* CalcSpeedRotate_, *CalcPosAndRadius_;
	public:
		// ¬озвращает/устанавливает текущего обладател€ планеты
		E_FRACTION_OWNER SR_API Fraction( void );
		void SR_API SetFraction( const E_FRACTION_OWNER eNewFraction );

		// ¬озвращает/устанавливает родную расу на планете
		E_SPECIES_OWNER SR_API Species( void );
		void SR_API SetSpecies( const E_SPECIES_OWNER eNewSpecies );

		// ¬озвращает/устанавливает форму правлени€ на планете
		E_GOVERNMENT_FORM SR_API Government( void );
		void SR_API SetGovernment( const E_GOVERNMENT_FORM eNewGovForm );

		// ¬озвращает/устанавливает тип экономики на планете
		E_ECONOMY __thiscall Economy( void );
		void SR_API SetEconomy( const E_ECONOMY eNewEconomy );

		// ¬озвращает/устанавливает исследуемые территории на планете( незаселЄнной )
		void SR_API Terrain( S_PLANET_TERRAIN& STerrainData );
		void SR_API SetTerrain( S_PLANET_TERRAIN& STerrainData ); 

		// ¬озвращает/устанавливает исследованные территории на планете( незаселЄнной )
		void SR_API TerrainExplored( S_PLANET_TERRAIN& STerrainData );
		void SR_API SetTerrainExplored( S_PLANET_TERRAIN& STerrainData );

		// ¬озвращает/устанавливает радиус планеты
		Double SR_API Radius( void );
		void  SR_API SetRadius( const Double fNewRadius );

		// ¬озвращает/устанавливает тангенциальную скорость планеты
		Double SR_API OrbitalVelocity( void );
		void   SR_API SetOrbitalVelocity( const Double dVelocity );

		// ¬озвращает/устанавливает размер планеты
		//UInt SR_API Size( void );
		//void SR_API SetSize( const UInt uSize );

		// ¬озвращает/устанавливает попул€цию планеты
		UInt   SR_API Population( void );
		void   SR_API SetPopulation( const UInt uNewPopulation );

		//¬озвращает количество военных кораблей, приписанных планете
		UInt  SR_API WarriorsCount( void );
		C_SHIP* SR_API Warrior( const UInt uWarriorN );

		// ¬озвращает/устанавливает флаг работы планеты
		void  SR_API Flags( S_PLANET_FLAGS& Flags );
		void  SR_API SetFlags( S_PLANET_FLAGS& Flags );

		// ¬озвращает/устанавливает текущий проект планеты
		E_INVENTION  SR_API Invention( void );
		void		 SR_API SetInvention( const E_INVENTION NewCurInvention );

		// ¬озвращает/устанавливает уровень исследовани€ проекта планеты. ¬ отрезке [ 0; 100 ]
		// ¬ единственном экземпл€ре: не прив€зан к какому-либо проекту.
		Float SR_API InventionPoints( void );
		void  SR_API SetInventionPoints( const Float NewPoints );

		// ¬озвращает/устанавливает технический уровень проекта планеты
		Byte  SR_API InventionLvl( const E_INVENTION Invention );
		void  SR_API SetInventionLvl( const E_INVENTION Invention, const Byte NewLvl ); 

		// возвращает систему планеты
		C_STAR* SR_API Star( void );

		// ¬озвращает/устанавливает модель планеты
		const Unicode* SR_API VisualModel( void );
		void SR_API SetVisualModel( const Unicode* NewVisualId );
};

class C_HIDDEN_PLANET : public C_PLANET
{
	friend class CSpaceRangersAPI;
	friend class C_GALAXY;
	
	static PVoid RestoreHiddenForm_;
	public:
		// ќткрывает границы скрытого сектора
		void SR_API UnlockHiddenSector( void );
};


#endif
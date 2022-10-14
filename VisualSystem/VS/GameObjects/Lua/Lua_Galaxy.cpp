#include "Lua_Galaxy.hpp"
#include "Lua_Ship.hpp"
#include "Lua_Star.hpp"
#include "Lua_Sector.hpp"
#include "Lua_Planet.hpp"

#include "../../ProgramData.hpp"
#include "../Galaxy.hpp"

#pragma warning( disable: 4800 )

#define VS_RegisterSettingBool( OptionName ) \
	lua_pushstring( LuaHandle, #OptionName ); \
	lua_pushboolean( LuaHandle, Settings.##OptionName ); \
	lua_settable( LuaHandle, -3 );

#define VS_RegisterSettingInt( OptionName ) \
	lua_pushstring( LuaHandle, #OptionName ); \
	lua_pushinteger( LuaHandle, Settings.##OptionName ); \
	lua_settable( LuaHandle, -3 );

#define VS_SetSettingBool( OptionName ) \
	lua_pushstring( LuaHandle, #OptionName ); \
	if( lua_rawget( LuaHandle, 2 ) == LUA_TBOOLEAN ) \
			Settings.##OptionName = (Bool)lua_toboolean( LuaHandle, -1); \
		lua_pop( LuaHandle, 1 ); 

#define VS_SetSettingInt( OptionName ) \
	lua_pushstring( LuaHandle, #OptionName ); \
	if( lua_rawget( LuaHandle, 2 ) == LUA_TNUMBER ) \
		if( lua_isinteger( LuaHandle, -1 ) ) \
			Settings.##OptionName = (Byte)lua_tointeger( LuaHandle, -1 ); \
		lua_pop( LuaHandle, 1 ); 

namespace VS_LUA_GAMEMETHODS 
{
	namespace LUA_GALAXY
	{
		// Возвращает/устанавливает настройки галактики
		int Stdcall Settings( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			SGalaxySettings Settings;
			Galaxy->Settings( &Settings );

			lua_newtable( LuaHandle );

			VS_RegisterSettingInt( Pirates )
			VS_RegisterSettingInt( Values )
			VS_RegisterSettingInt( Science )
			VS_RegisterSettingInt( Breakdowns )
			VS_RegisterSettingInt( Equipment )
			VS_RegisterSettingInt( Tasks )
			VS_RegisterSettingInt( BlackHoles )
			VS_RegisterSettingInt( Luck )

			return 1;
		}

		int Stdcall SetSettings( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TTABLE );
			SGalaxySettings Settings;
			Galaxy->Settings( &Settings );

			VS_SetSettingInt( Pirates )
			VS_SetSettingInt( Values )
			VS_SetSettingInt( Science )
			VS_SetSettingInt( Breakdowns )
			VS_SetSettingInt( Equipment )
			VS_SetSettingInt( Tasks )
			VS_SetSettingInt( BlackHoles )
			VS_SetSettingInt( Luck )

			Galaxy->SetSettings( &Settings );

			return 0;
		}

		int Stdcall AdjustmentSettings( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			SAdjustmentSettings Settings;
			Galaxy->AdjustmentSettings( &Settings );

			lua_newtable( LuaHandle );

			VS_RegisterSettingBool( IronWill )
			VS_RegisterSettingBool( AdvancedSettings )
			VS_RegisterSettingInt( DominatorEquipmentRatio )
			VS_RegisterSettingInt( DominatorAggressiveRatio )
			VS_RegisterSettingInt( DominatorRespawnRateRatio )
			VS_RegisterSettingInt( PirateClanAggressiveRatio )
			VS_RegisterSettingInt( CoalitionAggressiveRatio )
			VS_RegisterSettingInt( AsteroidsRatio )
			VS_RegisterSettingInt( StarDamageRatio )
			VS_RegisterSettingInt( TechLvlBonus )
			VS_RegisterSettingInt( ShopAkrinCount )
			VS_RegisterSettingInt( DominatorNodeDropRatio )
			VS_RegisterSettingInt( EquipmentValueInHyperRatio )
			VS_RegisterSettingInt( EquipmentValueInSpaceRatio )
			VS_RegisterSettingInt( GalaxyAgrarPlanetsCount )
			VS_RegisterSettingInt( GalaxyMixedPlanetsCount )
			VS_RegisterSettingInt( GalaxyIndustrialPlanetsCount )
			VS_RegisterSettingInt( AdditionalRangersCount )
			VS_RegisterSettingInt( ShipHPInHyperRatio )
			VS_RegisterSettingInt( ShipDamageInHyperRatio )
			VS_RegisterSettingInt( StarItemsLimit )
			VS_RegisterSettingBool( UseRandom )
			VS_RegisterSettingBool( InteractWithAllItems )
			VS_RegisterSettingBool( BuildStationsInCenter )
			VS_RegisterSettingBool( StationsFight )
			VS_RegisterSettingBool( UseOldShips )
			VS_RegisterSettingBool( SpawnWithoutExperience )
			VS_RegisterSettingBool( BotsAttackAllInHyper )
			VS_RegisterSettingBool( DominatorsUseOwnWeapons )
			VS_RegisterSettingBool( HomeSystemInCenter )
			VS_RegisterSettingBool( BotsUseRocketsOnMaxDistance )
			VS_RegisterSettingBool( FlyInHyper )
			VS_RegisterSettingBool( BuyNodesOnPirateBase )
			VS_RegisterSettingBool( BotsBuyEquipment )
			VS_RegisterSettingBool( StationsBuyEquipment )
			VS_RegisterSettingBool( UseSameArtefacts )
			VS_RegisterSettingInt(  ShipSizeFlag )
			VS_RegisterSettingBool( ChangeEquipmentInHyper )
			VS_RegisterSettingBool( UseOldSpeedCalculation )
			VS_RegisterSettingBool( UseRocketAkrinFlag )

			return 1;
		}
		int Stdcall SetAdjustmentSettings( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			luaL_checktype( LuaHandle, 2, LUA_TTABLE );
			SAdjustmentSettings Settings;
			Galaxy->AdjustmentSettings( &Settings );

			VS_SetSettingBool( IronWill )
			VS_SetSettingBool( AdvancedSettings )
			VS_SetSettingInt( DominatorEquipmentRatio )
			VS_SetSettingInt( DominatorAggressiveRatio )
			VS_SetSettingInt( DominatorRespawnRateRatio )
			VS_SetSettingInt( PirateClanAggressiveRatio )
			VS_SetSettingInt( CoalitionAggressiveRatio )
			VS_SetSettingInt( AsteroidsRatio )
			VS_SetSettingInt( StarDamageRatio )
			VS_SetSettingInt( TechLvlBonus )
			VS_SetSettingInt( ShopAkrinCount )
			VS_SetSettingInt( DominatorNodeDropRatio )
			VS_SetSettingInt( EquipmentValueInHyperRatio )
			VS_SetSettingInt( EquipmentValueInSpaceRatio )
			VS_SetSettingInt( GalaxyAgrarPlanetsCount )
			VS_SetSettingInt( GalaxyMixedPlanetsCount )
			VS_SetSettingInt( GalaxyIndustrialPlanetsCount )
			VS_SetSettingInt( AdditionalRangersCount )
			VS_SetSettingInt( ShipHPInHyperRatio )
			VS_SetSettingInt( ShipDamageInHyperRatio )
			VS_SetSettingInt( StarItemsLimit )
			VS_SetSettingBool( UseRandom )
			VS_SetSettingBool( InteractWithAllItems )
			VS_SetSettingBool( BuildStationsInCenter )
			VS_SetSettingBool( StationsFight )
			VS_SetSettingBool( UseOldShips )
			VS_SetSettingBool( SpawnWithoutExperience )
			VS_SetSettingBool( BotsAttackAllInHyper )
			VS_SetSettingBool( DominatorsUseOwnWeapons )
			VS_SetSettingBool( HomeSystemInCenter )
			VS_SetSettingBool( BotsUseRocketsOnMaxDistance )
			VS_SetSettingBool( FlyInHyper )
			VS_SetSettingBool( BuyNodesOnPirateBase )
			VS_SetSettingBool( BotsBuyEquipment )
			VS_SetSettingBool( StationsBuyEquipment )
			VS_SetSettingBool( UseSameArtefacts )
			VS_SetSettingInt( ShipSizeFlag )
			VS_SetSettingBool( ChangeEquipmentInHyper )
			VS_SetSettingBool( UseOldSpeedCalculation )
			VS_SetSettingBool( UseRocketAkrinFlag )

			Galaxy->SetAdjustmentSettings( &Settings );
			return 0;
		}

		int Stdcall Stars( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			UInt* ObjAddress = NULL;
			lua_newtable( LuaHandle );
			for( UInt I = 0; I < Galaxy->StarsCount(); I++ )
			{
				lua_pushinteger( LuaHandle, I + 1 );
				ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_STAR*) );
				*ObjAddress = (UInt)Galaxy->Star(I);
				luaL_setmetatable( LuaHandle, SR_LUA_STAR_METATABLE_NAME );
				lua_settable( LuaHandle, -3 );
			}

			return 1;
		}

		int Stdcall Sectors( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			UInt* ObjAddress = NULL;
			lua_newtable( LuaHandle );
			for( UInt I = 0; I < Galaxy->SectorsCount(); I++ )
			{
				lua_pushinteger( LuaHandle, I + 1 );
				ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SECTOR*) );
				*ObjAddress = (UInt)Galaxy->Sector(I);
				luaL_setmetatable( LuaHandle, SR_LUA_SECTOR_METATABLE_NAME );
				lua_settable( LuaHandle, -3 );
			}
			return 1;
		}

		// Асинхронный вызов запрещён
		int Stdcall Player( lua_State* LuaHandle ) {
			static C_SHIP PlayerShip;
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			Galaxy->Player( &PlayerShip );

			UInt* ObjAddr = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SHIP*)  );
			*ObjAddr = (UInt)&PlayerShip;
			luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			return 1;
		}

		int Stdcall Rojeria( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );

			UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_PLANET* ) );
			*ObjAddress = (UInt)Program->SRAPI()->Rojeria();
			luaL_setmetatable( LuaHandle, SR_LUA_PLANET_METATABLE_NAME );
			return 1;
		}

		int Stdcall Blazer( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			C_SHIP* Blazer_ = Program->SRAPI()->Blazer();
			if( *(UInt*)Blazer_ )
			{
				UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_SHIP* ) );
				*ObjAddress = (UInt)Blazer_;
				luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			}
			else
				lua_pushnil( LuaHandle );

			return 1;
		}

		int Stdcall Keller( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			C_SHIP* Keller_ = Program->SRAPI()->Keller();
			if( *(UInt*)Keller_ )
			{
				UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_SHIP* ) );
				*ObjAddress = (UInt)Keller_;
				luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			}
			else
				lua_pushnil( LuaHandle );

			return 1;
		}

		int Stdcall Terron( lua_State* LuaHandle )
		{
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			C_SHIP* Terron_ = Program->SRAPI()->Terron();
			if( *(UInt*)Terron_ )
			{
				UInt* ObjAddress = (UInt*)lua_newuserdata( LuaHandle, sizeof( C_SHIP* ) );
				*ObjAddress = (UInt)Terron_;
				luaL_setmetatable( LuaHandle, SR_LUA_SHIP_METATABLE_NAME );
			}
			else
				lua_pushnil( LuaHandle );

			return 1;
		}

		// Количество секторов в галактике
		int Stdcall SectorsCount( lua_State* LuaHandle ) {
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Galaxy->SectorsCount() );
			return 1;
		}

		int Stdcall Sector( lua_State* LuaHandle ) {
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			UInt i_sector = (UInt)luaL_checkinteger( LuaHandle, 2 ) -1;

			UInt* ObjAddr = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_SECTOR*)  );
			*ObjAddr = (UInt)Galaxy->Sector( i_sector );
			luaL_setmetatable( LuaHandle, SR_LUA_SECTOR_METATABLE_NAME );
			return 1;
		}

		// Количество систем в галактике
		int Stdcall StarsCount( lua_State* LuaHandle ) {
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			lua_pushinteger( LuaHandle, Galaxy->StarsCount() );
			return 1;
		}

		int Stdcall Star( lua_State* LuaHandle ) {
			C_GALAXY* Galaxy = (C_GALAXY*)*(UInt*)luaL_checkudata( LuaHandle, 1, SR_LUA_GALAXY_METATABLE_NAME );
			UInt i_star = (UInt)luaL_checkinteger( LuaHandle, 2 ) -1;

			UInt* ObjAddr = (UInt*)lua_newuserdata( LuaHandle, sizeof(C_STAR*)  );
			*ObjAddr = (UInt)Galaxy->Star( i_star );
			luaL_setmetatable( LuaHandle, SR_LUA_STAR_METATABLE_NAME );
			return 1;
		}
	}
}
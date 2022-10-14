#include "Galaxy.hpp"

void* C_GALAXY::GetLocalPlayer_ = NULL;

// Корабль игрока
void SR_API C_GALAXY::Player( C_SHIP* pShip ) {
	void* Object = NULL;
	__asm {
		call [GetLocalPlayer_]
		mov [Object], eax
	}
	*pShip = Object;
}

UInt SR_API C_GALAXY::SectorsCount( void ) {
	return *(UInt*)(*(UInt*)((UInt)this->pObject + 0x164) + 8);
}

C_SECTOR* SR_API C_GALAXY::Sector( const UInt SectorNumber ) {
	return (C_SECTOR*)(*(UInt*)( *(UInt*)((UInt)this->pObject + 0x164) + 4) + 4 * SectorNumber);
}

//UInt SR_API C_GALAXY::DeltaWin( const E_FRACTION eFraction ) {
//	return *(UInt*)( *(UInt*)this->pObject + 4 * eFraction + 0xF4);
//}
//
//void  SR_API C_GALAXY::SetDeltaWin( const E_FRACTION eFraction, const UInt NewDelta ) {
//	*(UInt*)( *(UInt*)this->pObject + 4 * eFraction + 0xF4 ) = NewDelta;
//}

UInt SR_API C_GALAXY::StarsCount( void )
{
	return *(UInt*)(*(UInt*)((UInt)this->pObject + 44) + 8);
}

C_STAR* SR_API C_GALAXY::Star( const UInt StarNumber )
{
	return (C_STAR*)(*(UInt*)(*(UInt *)( (UInt)this->pObject + 44 ) + 4) + 4 * StarNumber );
}

UInt SR_API C_GALAXY::CurrentDay( void )
{
	return *(UInt*)( (UInt)this->pObject + 0x4C );
}

// Возвращает информацию тонкой настройки
void SR_API C_GALAXY::AdjustmentSettings( SAdjustmentSettings* Settings )
{
	Settings->IronWill						=		*( (PBool)this->pObject + 0x17C ); // -1
	Settings->AdvancedSettings				=		*( (PBool)this->pObject + 0x188 ); // 0
	Settings->DominatorEquipmentRatio		=		*( (PByte)this->pObject + 0x189 ); // 1
	Settings->DominatorAggressiveRatio		=		*( (PByte)this->pObject + 0x18A ); // 2
	Settings->DominatorRespawnRateRatio		=		*( (PByte)this->pObject + 0x18B ); // 3
	Settings->PirateClanAggressiveRatio		=		*( (PByte)this->pObject + 0x18C ); // 4
	Settings->CoalitionAggressiveRatio		=		*( (PByte)this->pObject + 0x18D ); // 5
	Settings->AsteroidsRatio				=		*( (PByte)this->pObject + 0x18E ); // 6
	Settings->StarDamageRatio				=		*( (PByte)this->pObject + 0x18F ); // 7
	Settings->TechLvlBonus					=		*( (PByte)this->pObject + 0x190 ); // 8
	Settings->ShopAkrinCount				=		*( (PByte)this->pObject + 0x191 ); // 9
	Settings->DominatorNodeDropRatio		=		*( (PByte)this->pObject + 0x192 ); // 10
	Settings->EquipmentValueInHyperRatio	=		*( (PByte)this->pObject + 0x193 ); // 11
	Settings->EquipmentValueInSpaceRatio	=		*( (PByte)this->pObject + 0x194 ); // 12
	Settings->GalaxyAgrarPlanetsCount		=		*( (PByte)this->pObject + 0x195 ); // 13
	Settings->GalaxyMixedPlanetsCount		=		*( (PByte)this->pObject + 0x196 ); // 14
	Settings->GalaxyIndustrialPlanetsCount	=		*( (PByte)this->pObject + 0x197 ); // 15
	Settings->AdditionalRangersCount		=		*( (PByte)this->pObject + 0x198 ); // 16
	Settings->ShipHPInHyperRatio			=		*( (PByte)this->pObject + 0x199 ); // 17
	Settings->ShipDamageInHyperRatio		=		*( (PByte)this->pObject + 0x19A ); // 18
	Settings->StarItemsLimit				=		*( (PByte)this->pObject + 0x19B ); // 19
	Settings->UseRandom						=		*( (PBool)this->pObject + 0x19C ); // 20
	Settings->InteractWithAllItems			=		*( (PBool)this->pObject + 0x19D ); // 21
	Settings->BuildStationsInCenter			=		*( (PBool)this->pObject + 0x19E ); // 22
	Settings->StationsFight					=		*( (PBool)this->pObject + 0x19F ); // 23
	Settings->UseOldShips					=		*( (PBool)this->pObject + 0x1A0 ); // 24
	Settings->SpawnWithoutExperience		=		*( (PBool)this->pObject + 0x1A1 ); // 25
	Settings->BotsAttackAllInHyper			=		*( (PBool)this->pObject + 0x1A2 ); // 26
	Settings->DominatorsUseOwnWeapons		=		*( (PBool)this->pObject + 0x1A3 ); // 27
	Settings->HomeSystemInCenter			=		*( (PBool)this->pObject + 0x1A4 ); // 28
	Settings->BotsUseRocketsOnMaxDistance   =		*( (PBool)this->pObject + 0x1A5 ); // 29
	Settings->FlyInHyper					=		*( (PBool)this->pObject + 0x1A6 ); // 30
	Settings->BuyNodesOnPirateBase			=		*( (PBool)this->pObject + 0x1A7 ); // 31
	Settings->BotsBuyEquipment				=		*( (PBool)this->pObject + 0x1A8 ); // 32
	Settings->StationsBuyEquipment			=		*( (PBool)this->pObject + 0x1A9 ); // 33
	Settings->UseSameArtefacts				=		*( (PBool)this->pObject + 0x1AA ); // 34
	Settings->ShipSizeFlag					=		*( (PByte)this->pObject + 0x1AB ); // 35
	Settings->ChangeEquipmentInHyper		=		*( (PBool)this->pObject + 0x1AC ); // 36
	Settings->UseOldSpeedCalculation		=		*( (PBool)this->pObject + 0x1AD ); // 37
	Settings->UseRocketAkrinFlag			=		*( (PBool)this->pObject + 0x1AE ); // 38
}

void SR_API C_GALAXY::SetAdjustmentSettings( const SAdjustmentSettings* Settings )
{
	*( (PBool)this->pObject + 0x17C ) = Settings->IronWill;						// -1
	*( (PBool)this->pObject + 0x188 ) = Settings->AdvancedSettings;				// 0
	*( (PByte)this->pObject + 0x189 ) = Settings->DominatorEquipmentRatio;		// 1
	*( (PByte)this->pObject + 0x18A ) = Settings->DominatorAggressiveRatio;		// 2
	*( (PByte)this->pObject + 0x18B ) = Settings->DominatorRespawnRateRatio;	// 3
	*( (PByte)this->pObject + 0x18C ) = Settings->PirateClanAggressiveRatio;	// 4
	*( (PByte)this->pObject + 0x18D ) = Settings->CoalitionAggressiveRatio;		// 5
	*( (PByte)this->pObject + 0x18E ) = Settings->AsteroidsRatio;				// 6
	*( (PByte)this->pObject + 0x18F ) = Settings->StarDamageRatio;				// 7
	*( (PByte)this->pObject + 0x190 ) = Settings->TechLvlBonus;					// 8
	*( (PByte)this->pObject + 0x191 ) = Settings->ShopAkrinCount;				// 9
	*( (PByte)this->pObject + 0x192 ) = Settings->DominatorNodeDropRatio;		// 10
	*( (PByte)this->pObject + 0x193 ) = Settings->EquipmentValueInHyperRatio;	// 11
	*( (PByte)this->pObject + 0x194 ) = Settings->EquipmentValueInSpaceRatio;	// 12
	*( (PByte)this->pObject + 0x195 ) = Settings->GalaxyAgrarPlanetsCount;		// 13
	*( (PByte)this->pObject + 0x196 ) = Settings->GalaxyMixedPlanetsCount;		// 14
	*( (PByte)this->pObject + 0x197 ) = Settings->GalaxyIndustrialPlanetsCount;	// 15
	*( (PByte)this->pObject + 0x198 ) = Settings->AdditionalRangersCount;		// 16
	*( (PByte)this->pObject + 0x199 ) = Settings->ShipHPInHyperRatio;			// 17
	*( (PByte)this->pObject + 0x19A ) = Settings->ShipDamageInHyperRatio;		// 18
	*( (PByte)this->pObject + 0x19B ) = Settings->StarItemsLimit;				// 19
	*( (PBool)this->pObject + 0x19C ) = Settings->UseRandom;					// 20
	*( (PBool)this->pObject + 0x19D ) = Settings->InteractWithAllItems;			// 21
	*( (PBool)this->pObject + 0x19E ) = Settings->BuildStationsInCenter;		// 22
	*( (PBool)this->pObject + 0x19F ) = Settings->StationsFight;				// 23
	*( (PBool)this->pObject + 0x1A0 ) = Settings->UseOldShips;					// 24
	*( (PBool)this->pObject + 0x1A1 ) = Settings->SpawnWithoutExperience;		// 25
	*( (PBool)this->pObject + 0x1A2 ) = Settings->BotsAttackAllInHyper;			// 26
	*( (PBool)this->pObject + 0x1A3 ) = Settings->DominatorsUseOwnWeapons;		// 27
	*( (PBool)this->pObject + 0x1A4 ) = Settings->HomeSystemInCenter;			// 28
	*( (PBool)this->pObject + 0x1A5 ) = Settings->BotsUseRocketsOnMaxDistance;  // 29
	*( (PBool)this->pObject + 0x1A6 ) = Settings->FlyInHyper;					// 30
	*( (PBool)this->pObject + 0x1A7 ) = Settings->BuyNodesOnPirateBase;			// 31
	*( (PBool)this->pObject + 0x1A8 ) = Settings->BotsBuyEquipment;				// 32
	*( (PBool)this->pObject + 0x1A9 ) = Settings->StationsBuyEquipment;			// 33
	*( (PBool)this->pObject + 0x1AA ) = Settings->UseSameArtefacts;				// 34
	*( (PByte)this->pObject + 0x1AB ) = Settings->ShipSizeFlag;					// 35
	*( (PBool)this->pObject + 0x1AC ) = Settings->ChangeEquipmentInHyper;		// 36
	*( (PBool)this->pObject + 0x1AD ) = Settings->UseOldSpeedCalculation;		// 37
	*( (PBool)this->pObject + 0x1AE ) = Settings->UseRocketAkrinFlag;			// 38
}

// Формула ( Byte + 1 ) * 50 = ProcentDiff
// При сумме всех сложностей, берётся Sum*0.125

// Возвращает/устанавливает настройки галактики
void SR_API C_GALAXY::Settings( SGalaxySettings* Settings_ )
{
	Settings_->Pirates	  =  *( (PByte)this->pObject + 0x50 + 0 );
	Settings_->Values	  =  *( (PByte)this->pObject + 0x50 + 1 );
	Settings_->Science	  =  *( (PByte)this->pObject + 0x50 + 2 );
	Settings_->Breakdowns =  *( (PByte)this->pObject + 0x50 + 3 );
	Settings_->Equipment  =  *( (PByte)this->pObject + 0x50 + 4 );
	Settings_->Tasks	  =  *( (PByte)this->pObject + 0x50 + 5 );
	Settings_->BlackHoles =  *( (PByte)this->pObject + 0x50 + 6 );
	Settings_->Luck		  =  *( (PByte)this->pObject + 0x50 + 7 );
}

void SR_API C_GALAXY::SetSettings( SGalaxySettings* Settings_ )
{
	*( (PByte)this->pObject + 0x50 + 0 ) = Settings_->Pirates;
	*( (PByte)this->pObject + 0x50 + 1 ) = Settings_->Values;
	*( (PByte)this->pObject + 0x50 + 2 ) = Settings_->Science;
	*( (PByte)this->pObject + 0x50 + 3 ) = Settings_->Breakdowns;
	*( (PByte)this->pObject + 0x50 + 4 ) = Settings_->Equipment;
	*( (PByte)this->pObject + 0x50 + 5 ) = Settings_->Tasks;
	*( (PByte)this->pObject + 0x50 + 6 ) = Settings_->BlackHoles;
	*( (PByte)this->pObject + 0x50 + 7 ) = Settings_->Luck;
}
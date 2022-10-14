#include "Planet.hpp"
#include "../ProgramData.hpp"

#pragma warning( disable : 4482 )

PVoid C_HIDDEN_PLANET::RestoreHiddenForm_ = NULL;
void* C_PLANET::PlanetChangeVisualConst_ = NULL, 
	* C_PLANET::PlanetChangeVisualF_;

void* C_PLANET::CalcSpeedRotate_  = NULL,
	* C_PLANET::CalcPosAndRadius_ = NULL;

E_FRACTION_OWNER SR_API C_PLANET::Fraction( void ) {
	return (E_FRACTION_OWNER)*( (Byte*)this->pObject + 0x74 );
}

void SR_API C_PLANET::SetFraction( const E_FRACTION_OWNER eNewFraction ) {
	*( (Byte*)this->pObject + 0x74 ) = (Byte)eNewFraction;
}

E_SPECIES_OWNER SR_API C_PLANET::Species( void ) {
	return (E_SPECIES_OWNER)*( (PByte)this->pObject + 0x76 );
}
void SR_API C_PLANET::SetSpecies( const E_SPECIES_OWNER eNewSpecies ) {
	*( (PByte)this->pObject + 0x76 ) = (Byte)eNewSpecies;
}

E_GOVERNMENT_FORM SR_API C_PLANET::Government( void ) {
	return (E_GOVERNMENT_FORM)*( (PByte)this->pObject + 0x77 );
}

void SR_API C_PLANET::SetGovernment( const E_GOVERNMENT_FORM eNewGovForm ) {
	*( (PByte)this->pObject + 0x77 ) = (Byte)eNewGovForm;
}

E_ECONOMY __thiscall C_PLANET::Economy( void ) {
	return (E_ECONOMY)*( (PByte)this->pObject + 0x6C );
}

void SR_API C_PLANET::SetEconomy( const E_ECONOMY eNewEconomy ) {
	*( (PByte)this->pObject + 0x6C ) = (Byte)eNewEconomy;
}

void SR_API C_PLANET::Terrain( S_PLANET_TERRAIN& STerrainData ) {
	STerrainData.Water = *(UInt*)( (UInt)this->pObject + 0x120 );
	STerrainData.Land  = *(UInt*)( (UInt)this->pObject + 0x128 );
	STerrainData.Hill  = *(UInt*)( (UInt)this->pObject + 0x130 );
}

void SR_API C_PLANET::SetTerrain( S_PLANET_TERRAIN& STerrainData ) {
	 *(UInt*)( (UInt)this->pObject + 0x120 ) = STerrainData.Water;
	 *(UInt*)( (UInt)this->pObject + 0x128 ) = STerrainData.Land;
	 *(UInt*)( (UInt)this->pObject + 0x130 ) = STerrainData.Hill;
}

void SR_API C_PLANET::TerrainExplored( S_PLANET_TERRAIN& STerrainData ) {
	STerrainData.Water = *(UInt*)( (UInt)this->pObject + 0x124 );
	STerrainData.Land  = *(UInt*)( (UInt)this->pObject + 0x12C );
	STerrainData.Hill  = *(UInt*)( (UInt)this->pObject + 0x134 );
}

void SR_API C_PLANET::SetTerrainExplored( S_PLANET_TERRAIN& STerrainData ) {
	 *(UInt*)( (UInt)this->pObject + 0x124 ) = STerrainData.Water;
	 *(UInt*)( (UInt)this->pObject + 0x12C ) = STerrainData.Land;
	 *(UInt*)( (UInt)this->pObject + 0x134 ) = STerrainData.Hill;
}

Double SR_API C_PLANET::Radius( void ) {
	return *(Double*)( (UInt)this->pObject + 0x28 );
}

void  SR_API C_PLANET::SetRadius( const Double fNewRadius ) {
	*(Double*)( (UInt)this->pObject + 0x28 ) = fNewRadius;
}

Double SR_API C_PLANET::OrbitalVelocity( void ) {
	return *(Double*)( (UInt)this->pObject + 0x40 );
}

void SR_API C_PLANET::SetOrbitalVelocity( const Double dVelocity ) {
	*(Double*)( (UInt)this->pObject + 0x40 ) = dVelocity;
}

//UInt SR_API C_PLANET::Size( void ) {
//	return *(UInt*)( (UInt)this->pObject + 0x38 );
//}
//
//void SR_API C_PLANET::SetSize( const UInt uSize ) {
//	*(UInt*)( (UInt)this->pObject + 0x38 ) = uSize;
//}

UInt SR_API C_PLANET::Population( void ) {
	return *(UInt*)( (UInt)this->pObject + 0x68 );
}

void SR_API C_PLANET::SetPopulation( const UInt uNewPopulation ) {
	*(UInt*)( (UInt)this->pObject + 0x68 ) = uNewPopulation;
}

UInt SR_API C_PLANET::WarriorsCount( void ) {
	return *(UInt*)(*(UInt*)((UInt)this->pObject + 0x114) + 8);
}

C_SHIP* SR_API C_PLANET::Warrior( const UInt uWarriorN ) {
	return (C_SHIP*)(*(UInt*)(*(UInt*)((UInt)this->pObject + 0x114) + 4) + 4 * uWarriorN);
}

void SR_API C_PLANET::Flags( S_PLANET_FLAGS& Flags ) {
	Flags.NoBuyShips	 =  *(PBool)( (UInt)this->pObject + 0x15E );
	Flags.NoRandomEvents =  *(PBool)( (UInt)this->pObject + 0x15F );
}

void  SR_API C_PLANET::SetFlags( S_PLANET_FLAGS& Flags ) {
	*(PBool)( (UInt)this->pObject + 0x15E ) = Flags.NoBuyShips;
	*(PBool)( (UInt)this->pObject + 0x15F ) = Flags.NoRandomEvents;
}

C_STAR* SR_API C_PLANET::Star( void ) {
	return (C_STAR*)( (UInt)this->pObject + 0x18);
}

E_INVENTION SR_API C_PLANET::Invention( void ) {
	return (E_INVENTION)*( (PByte)this->pObject + 0x5C );
}

void SR_API C_PLANET::SetInvention( const E_INVENTION NewCurInvention ) {
	*( (PByte)this->pObject + 0x5C ) = (Byte)NewCurInvention;
}

Float SR_API C_PLANET::InventionPoints( void ) {
	return *(Float*)( (UInt)this->pObject + 0x60 );
}

void SR_API C_PLANET::SetInventionPoints( const Float NewPoints ) {
	*(Float*)( (UInt)this->pObject + 0x60 ) = NewPoints;
}

Byte SR_API C_PLANET::InventionLvl( const E_INVENTION Invention ) {
	return *( (PByte)this->pObject + Invention + 0x48 );
}

void  SR_API C_PLANET::SetInventionLvl( const E_INVENTION Invention, const Byte NewLvl ) {
	*( (PByte)this->pObject + Invention + 0x48 ) = NewLvl;
}

void SR_API C_HIDDEN_PLANET::UnlockHiddenSector( void ) {
	PVoid Obj = NULL;
	PVoid Galaxy_ = Program->SRAPI()->Galaxy()->pObject;
	UInt Lim = *(UInt*)( *(UInt*)( (UInt)Galaxy_ + 0x164 ) + 8);
	for( UInt I = 0;
		 I < Lim;
		 I++ ) {
		Obj = (PVoid)*(UInt*)(*(UInt*)(*(UInt*)((UInt)Galaxy_ + 0x164) + 4) + 4 * I);
		__asm
		{
			mov eax, [Obj]
			call [RestoreHiddenForm_]
		}
	}
}

// ¬озвращает/устанавливает модель планеты
const Unicode* SR_API C_PLANET::VisualModel( void )
{
	return (const Unicode*)*(UInt*)( (UInt)this->pObject + 0x148 );
}

void SR_API C_PLANET::SetVisualModel( const Unicode* NewVisualId )
{
	PVoid Planet = this->pObject;
	long long int VArg = 0; // 8 bytes
	
	UInt StrSize = wcslen( NewVisualId );
	Unicode* NewStr = (Unicode*)new Byte[ 4 + StrSize * sizeof(Unicode) + sizeof(Unicode) ];
	*(UInt*)NewStr = StrSize * 2;
	NewStr += 2;
	memcpy( NewStr, NewVisualId, StrSize * sizeof(Unicode) + sizeof(Unicode) );

	WORD DefaultRotation = NULL;

	PVoid SetGraphName = C_SHIP::SetGraphName_;
	PVoid DetachFromSE = C_SHIP::DetachFromSE_;
	PVoid LinkToSE	   = C_SHIP::LinkToSE_;
	__asm
	{
		mov edx, [NewStr]
		mov eax, [Planet]
		add eax, 0x148
		call [SetGraphName]

		mov eax, [Planet]
		mov eax, [eax + 0x144]
		mov ax, [eax + 0x60 ]
		mov DefaultRotation, ax

		mov eax, [Planet]
		add eax, 0x144
		call [DetachFromSE]

		lea eax, VArg
		push eax
		mov  ecx, [ NewStr ]
		mov edx, 1
		mov eax, [PlanetChangeVisualConst_]
		call [PlanetChangeVisualF_]

		mov edx, eax
		mov eax, [Planet]
		add eax, 0x144
		call [LinkToSE]

		movzx edx, DefaultRotation
		mov eax, [Planet]
		mov eax, [ eax + 0x144 ]
		call [CalcSpeedRotate_]

		lea edx, VArg
		mov eax, [Planet]
		add eax, 0x20
		call [CalcPosAndRadius_]

		lea edx, VArg
		mov eax, [Planet]
		mov eax, [eax + 0x144]
		mov ecx, [eax]
		call [ecx + 0xC]
		
		//mov eax, [Planet]
		//mov eax, [eax + 0x144]
		//mov eax, [eax + 0x80]
		//mov edx, [Planet]
		//mov [edx + 0x140], eax
	}

	NewStr -= 2;
	delete [] NewStr;
}

//const Unicode* SR_API C_PLANET::Name( void )
//{
//	return (const Unicode*)*(UInt*)( (UInt)this->pObject + 0x14 );
//}
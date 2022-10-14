#include "Star.hpp"

// CreateBase() components
void* C_STAR::RuinsObject = NULL; 
void* C_STAR::RuinsCreate = NULL;
void* C_STAR::RuinsInit	  = NULL;

// Change VisualModel
void * C_STAR::StarChangeVisualF_	  = NULL,
	 * C_STAR::StarChangeVisualConst_ = NULL,
	 * C_STAR::SetGraphNameConst_	  = NULL;

#pragma warning( disable: 4482 )

bool __thiscall C_STAR::operator == ( const C_STAR* Object ) {
	if( this->pObject == Object->pObject )
		return true;
	else
		return false;
}


E_FRACTION SR_API C_STAR::Fraction( void )
{
	return (E_FRACTION)( *(PByte)( (UInt)this->pObject + 0x42 ) );
}

void SR_API C_STAR::SetFraction( const E_FRACTION eNewFraction ) {
	*(PByte)( (UInt)this->pObject + 0x42 ) = (Byte)eNewFraction;
}

UInt SR_API	C_STAR::ShipsCount( void ) {
	return *(UInt*)( *((UInt*)this->pObject + 11 ) + 8 );
}

C_SHIP* SR_API C_STAR::Ship( const UInt ShipN ) {
	return (C_SHIP*)(*(UInt*)( *((UInt*)this->pObject + 11 ) + 4) + 4 * ShipN );
}

Bool SR_API C_STAR::IsBattle( void ) {
	return *(Bool*)( (UInt)this->pObject + 0x48 );
}

E_DOMSERIES SR_API C_STAR::DomSeries( void ) {
	return  (E_DOMSERIES)( *( (Byte*)this->pObject + 0x49 ) );
}

void SR_API C_STAR::SetDomSeries( const E_DOMSERIES eNewDomSeries ) {
	*((Byte*)this->pObject + 0x49 ) = (Byte)eNewDomSeries;
}

void SR_API  C_STAR::CreateBase( const E_BASE_TYPE eBaseType, C_SHIP* NewShip ) {
	void* System = this->pObject;
	void* NewBase = NULL;
	__asm
	{
		mov dl, 1
		mov eax, [RuinsObject]
		call [RuinsCreate]
		mov [NewBase], eax
		push 0
		mov edx, [eBaseType]
		mov ecx, [System]
		call [RuinsInit]
	}
	*NewShip = NewBase;

	return;
}

UInt SR_API C_STAR::PlanetsCount( void ) {
	return *(UInt*)( *((UInt*)this->pObject + 9) + 8 );
}

C_PLANET* SR_API C_STAR::Planet( const UInt PlanetN ) {
	return (C_PLANET*)(*(UInt*)( *((UInt*)this->pObject + 9 ) + 4) + 4 * PlanetN );
}

UInt SR_API C_STAR::FonImage( void )
{
	return *(UInt*)( (UInt)this->pObject + 0x7C );
}

void SR_API C_STAR::SetFonImage( const UInt NewFonImage ) {
	*(UInt*)( (UInt)this->pObject + 0x7C ) = NewFonImage;
}

C_SECTOR* SR_API C_STAR::Sector( void ) {
	return (C_SECTOR*)( (UInt)this->pObject + 0xD0 );
}

// Возвращает/устанавливает флаги системы
void SR_API C_STAR::Flags( S_STAR_FLAGS& Flags )
{
	Flags.NoComeKling = *( (PBool)this->pObject + 0xD8 );
}

void SR_API C_STAR::SetFlags( S_STAR_FLAGS& Flags )
{
	*( (PBool)this->pObject + 0xD8 ) = Flags.NoComeKling;
}

const Unicode* SR_API C_STAR::VisualModel( void )
{
	return (const Unicode*)*(UInt*)( *(UInt*)( (UInt)this->pObject + 0x6C ) + 0x18 );
}

void SR_API C_STAR::SetVisualModel( const Unicode* NewVisualId )
{
	PVoid Star = this->pObject;
	long long int VArg = 0; // 8 bytes

	UInt StrSize = wcslen( NewVisualId );
	Unicode* NewStr = (Unicode*)new Byte[ 4 + StrSize * sizeof(Unicode) + sizeof(Unicode) ];
	*(UInt*)NewStr = StrSize * 2;
	NewStr += 2;
	memcpy( NewStr, NewVisualId, StrSize * sizeof(Unicode) + sizeof(Unicode) );
	
	void* DetachFromSE = C_SHIP::DetachFromSE_;
	void* LinkToSE = C_SHIP::LinkToSE_;
	void* SetGraphName = C_SHIP::SetGraphName_;
	__asm
	{
		mov eax, [Star]
		add eax, 0x6C
		call [DetachFromSE]

		lea eax, VArg
		push eax
		mov  ecx, [ NewStr ]
		mov edx, 1
		mov eax, [StarChangeVisualConst_]
		call [StarChangeVisualF_]

		mov edx, eax
		mov eax, [Star]
		add eax, 0x6C
		call [LinkToSE]

		mov eax, [Star]
		add eax, 0x3C
		mov edx, [SetGraphNameConst_]
		call [SetGraphName]
	}
		VArg = 0;
	__asm
	{
		mov eax, [Star]
		mov eax, [eax + 0x6C]
		mov ecx, [eax]
		call [ecx +0xC]
	}

	NewStr -= 2;
	delete [] NewStr;
}
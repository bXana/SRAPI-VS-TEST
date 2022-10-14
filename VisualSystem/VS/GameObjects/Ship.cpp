#include "Ship.hpp"

// VisualModel changer 
void * C_SHIP::DetachFromSE_			= NULL,
	 * C_SHIP::RuinsChangeVisualConst_  = NULL,
	 * C_SHIP::RuinsChangeVisualF_		= NULL, 
	 * C_SHIP::LinkToSE_			    = NULL,
	 * C_SHIP::SetGraphName_			= NULL,
	 * C_SHIP::SetAngle_				= NULL,
	 * C_SHIP::CalcParam_				= NULL,
	 * C_SHIP::CalcParamGraphSize_		= NULL;
/*---------------------------------*/
// Order TakeOff
void* C_SHIP::OrderTakeOff_		= NULL,
	* C_SHIP::OrderFallowShip_  = NULL,
	* C_SHIP::OrderJump_		= NULL,
	* C_SHIP::OrderNone_		= NULL;

#pragma warning( disable : 4482 )


C_SHIP& C_SHIP::operator = ( const void* Object ) {
	this->pObject = (PVoid)Object;
	return *this;
}

const Unicode* SR_API C_SHIP::VisualModel( void ) {
	return (const Unicode*)*(UInt*)( *(UInt*)( (UInt)this->pObject + 0x450 ) + 0x18 );
}

void SR_API C_SHIP::SetVisualModel ( const Unicode* NewVisualId, const bool IsPermanent ) {
	PVoid Ship = this->pObject;
	long long int VArg = 0; // 8 bytes
	
	UInt StrSize = wcslen( NewVisualId );
	Unicode* NewStr = (Unicode*)new Byte[ 4 + StrSize * sizeof(Unicode) + sizeof(Unicode) ];
	*(UInt*)NewStr = StrSize * 2;
	NewStr += 2;
	memcpy( NewStr, NewVisualId, StrSize * sizeof(Unicode) + sizeof(Unicode) );

	__asm
	{
		mov eax, [Ship]
		add eax, 0x450
		call [DetachFromSE_]

		lea eax, VArg
		push eax
		mov  ecx, [ NewStr ]
		mov edx, 1
		mov eax, [RuinsChangeVisualConst_]
		call [RuinsChangeVisualF_]

		mov edx, eax
		mov eax, [Ship]
		add eax, 0x450
		call [LinkToSE_]

		mov eax, [Ship]
		add eax, 0x454
		mov edx, [Ship]
		mov edx, [edx + 0x450]
		mov edx, [edx + 0x18]
		call [SetGraphName_]

		mov eax, [Ship]
		lea edx, [eax + 0x14]
		mov eax, [Ship]
		mov eax, [eax + 0x450]
		mov ecx, [eax]
		call [ecx + 0xC ]

		mov eax, [Ship]
		push [ eax + 0x424 ]
		push [ eax + 0x420 ]
		call [SetAngle_]

		mov edx, eax
		mov eax, [Ship]
		mov eax, [eax + 0x450]
		mov ecx, [eax]
		call [ ecx + 0x2C ]

		xor edx, edx
		mov eax, [Ship]
		mov eax, [eax + 0x450]
		mov ecx, [eax]
		call [ ecx + 0x24 ]

		xor edx, edx
		mov dl,  IsPermanent

		mov eax, [Ship]
		mov [eax + 0x49C ], edx
		mov eax, [Ship]
		mov [ eax + 0x461 ], 0
		mov dl, 1
		mov eax, [Ship]
		call [CalcParam_]
		mov eax, [Ship]
		call [CalcParamGraphSize_]
	}

	NewStr -= 2;
	delete [] NewStr;
}

C_PLANET* SR_API C_SHIP::Home( void ) {
	return (C_PLANET*)( (UInt)this->pObject + 0x2C );
}

E_SHIP_TYPE SR_API C_SHIP::Type( void ) {
	return (E_SHIP_TYPE)*( (PByte)this->pObject + 0x10 );
}

void SR_API C_SHIP::SetType( const E_SHIP_TYPE NewType ) {
	*( (PByte)this->pObject + 0x10 ) = (Byte)NewType;
}

E_SHIP_SUBTYPE SR_API C_SHIP::SubType( void )
{
	switch( this->Type() )
	{
		case E_SHIP_TYPE::SHIP_KLING:
			return (E_SHIP_SUBTYPE)*(UInt*)( (UInt)this->pObject + 0x4D0 ); 
		case E_SHIP_TYPE::SHIP_TRANSPORT:
			return (E_SHIP_SUBTYPE)*(UInt*)( (UInt)this->pObject + 0x510 ); 
		case E_SHIP_TYPE::SHIP_WARRIOR:
			return (E_SHIP_SUBTYPE)*(UInt*)( (UInt)this->pObject + 0x510 ); 
		case E_SHIP_TYPE::SHIP_PIRATE:
			return (E_SHIP_SUBTYPE)*(UInt*)( (UInt)this->pObject + 0x514 ); 
		case E_SHIP_TYPE::SHIP_RANGER:
			return (E_SHIP_SUBTYPE)*(UInt*)( (UInt)this->pObject + 0x51C ); 
		default:
			return (E_SHIP_SUBTYPE)0;
	}
}

void SR_API C_SHIP::SetSubType( const E_SHIP_SUBTYPE eNewSubType )
{
	switch( this->Type() )
	{
		case E_SHIP_TYPE::SHIP_KLING:
			*(UInt*)( (UInt)this->pObject + 0x4D0 ) = eNewSubType;
		case E_SHIP_TYPE::SHIP_TRANSPORT:
			*(UInt*)( (UInt)this->pObject + 0x510 ) = eNewSubType;
		case E_SHIP_TYPE::SHIP_WARRIOR:
			*(UInt*)( (UInt)this->pObject + 0x510 ) = eNewSubType;
		case E_SHIP_TYPE::SHIP_PIRATE:
			*(UInt*)( (UInt)this->pObject + 0x514 ) = eNewSubType;
		case E_SHIP_TYPE::SHIP_RANGER:
			*(UInt*)( (UInt)this->pObject + 0x51C ) = eNewSubType;
	}
}

C_STAR* SR_API C_SHIP::Star( void ) {
	return (C_STAR*)( (UInt)this->pObject + 0x24 );
}

// Возвращает/устанавливает серию доминатора, если это доминатор
E_DOMSERIES SR_API C_SHIP::DomSeries( void )
{
	return (E_DOMSERIES)*( (PByte)this->pObject + 0x4D1 );
}
void SR_API	C_SHIP::SetDomSeries( const E_DOMSERIES eNewDomSeries )
{
	*( (PByte)this->pObject + 0x4D1 ) = (Byte)eNewDomSeries;
}

E_FRACTION_OWNER SR_API C_SHIP::Fraction( void ) {
	return (E_FRACTION_OWNER)*( (PByte)this->pObject + 0x11);
}

void SR_API C_SHIP::SetFraction( const E_FRACTION_OWNER eNewFraction ) {
	*( (PByte)this->pObject + 0x11) = (Byte)eNewFraction;
}

E_SHIP_STATUS SR_API C_SHIP::StatusType( void ) {
	return (E_SHIP_STATUS)*( (PByte)this->pObject + 0x4B0 );
}

void SR_API C_SHIP::SetStatusType( const E_SHIP_STATUS eNewStatus ) {
	*( (PByte)this->pObject + 0x4B0 ) = (Byte)eNewStatus;
}

E_SPECIES_OWNER SR_API C_SHIP::Species( void ) {
	return (E_SPECIES_OWNER)*( (PByte)this->pObject + 0x408 );
}

void SR_API C_SHIP::SetSpecies( const E_SPECIES_OWNER eNewSpecies ) {
	*( (PByte)this->pObject + 0x408 ) = (Byte)eNewSpecies;
}

void SR_API C_SHIP::Destroy( void )
{
	*( (PByte)this->pObject + 0x460 ) = true;
}

C_SHIP* SR_API C_SHIP::Target( void )
{
	return (C_SHIP*)( (UInt)this->pObject + 0x3F4 );
}

void SR_API C_SHIP::SetTarget( const C_SHIP& CNewTarget )
{
	*(UInt*)( (UInt)this->pObject + 0x3F4 ) = (UInt)CNewTarget.pObject;
}

Bool SR_API C_SHIP::InHyper( void )
{
	return *( (PBool)this->pObject + 0x459 );
}

C_PLANET* SR_API C_SHIP::OnPlanet( void )
{
	return (C_PLANET*)( (UInt)this->pObject + 0x1C );
}

C_SHIP* SR_API C_SHIP::OnBase( void )
{
	return (C_SHIP*)( (UInt)this->pObject + 0x20 );
}

// Телепортироваться в указанную систему
void SR_API C_SHIP::Teleport( const C_STAR* TargetSystem, const SVec2Position< float >& Position, const UInt JmpDuration  )
{
	*( (PByte)this->pObject + 0x428 ) = 7;
	*(UInt*)( (UInt)this->pObject + 0x430 )  = *(UInt*)TargetSystem;
	*(UInt*)( (UInt)this->pObject + 0x43C )  = 1;
	*(Float*)( (UInt)this->pObject + 0x434 ) = Position.X;
	*(Float*)( (UInt)this->pObject + 0x438 ) = Position.Y;
	*(UInt*)( (UInt)this->pObject + 0x42C )  = JmpDuration;

	return;
}

void SR_API C_SHIP::Land( const C_OBJECT* Object, const Bool Priority )
{
	if( *(UInt*)( (UInt)this->pObject + 0xC4 ) > 0 )
	{
		*( (PByte)this->pObject + 0x428 ) = 2;
		*(UInt*)( (UInt)this->pObject + 0x430 ) = *(UInt*)Object;
		*(UInt*)( (UInt)this->pObject + 0x434 ) = 0;
		*(UInt*)( (UInt)this->pObject + 0x438 ) = 0;
		// priority flag
		*(UInt*)( (UInt)this->pObject + 0x43C ) = (UInt)Priority;
	}
}

void __thiscall C_SHIP::TakeOff( void )
{
	void* Ship = (void*)this->pObject;
	Byte ScriptOrder = *( (PByte)this->pObject + 0x44C );
	*( (PByte)this->pObject + 0x44C ) = 0;

	__asm
	{
		mov eax, [Ship]
		call [OrderTakeOff_]
	}

	*( (PByte)this->pObject + 0x44C ) = ScriptOrder;
}

void SR_API C_SHIP::Move( const SVec2Position< float >& Position, const Bool Priority )
{
	if( *(UInt*)( (UInt)this->pObject + 0xC4 ) > 0 )
	{
		*( (PByte)this->pObject + 0x428 ) = 1;
		*(Float*)( (UInt)this->pObject + 0x434 ) = Position.X;
		*(Float*)( (UInt)this->pObject + 0x438 ) = Position.Y;
		// priority flag
		*(UInt*)( (UInt)this->pObject + 0x43C ) = (UInt)Priority;
		*(UInt*)( (UInt)this->pObject + 0x430 ) = 0;
	}
}

// Направляет корабль за кораблём
void SR_API C_SHIP::Fallow( const C_SHIP* TargetShip, const E_FALLOW_TYPE FallowType, const Bool Priority )
{
	void* Ship = this->pObject;
	Byte ScriptOrder = *( (PByte)this->pObject + 0x44C );
	*( (PByte)this->pObject + 0x44C ) = 0;
	UInt Priority_  = (UInt)Priority;
	UInt TargetShip_ = *(UInt*)TargetShip;
	__asm
	{
		push Priority_
		mov edx, TargetShip_
		mov ecx, FallowType
		mov eax, [Ship]
		call [OrderFallowShip_]
	}
	*( (PByte)this->pObject + 0x44C ) = ScriptOrder;
}

// Совершить прыжок в другую систему
void SR_API C_SHIP::Jump( const C_STAR* TargetStar, const Bool Priority )
{
	void* Ship = this->pObject;
	Byte ScriptOrder = *( (PByte)this->pObject + 0x44C );
	*( (PByte)this->pObject + 0x44C ) = 0;
	UInt Priority_  = (UInt)Priority;
	UInt TargetStar_ = *(UInt*)TargetStar;
	__asm
	{
		mov edx, TargetStar_
		mov ecx, Priority_
		mov eax, [Ship]
		call [OrderJump_]
	}
	*( (PByte)this->pObject + 0x44C ) = ScriptOrder;
}

// Отменяет текущие команды
void SR_API C_SHIP::CancelTask( void )
{
	void* Ship = this->pObject;
	Byte ScriptOrder = *( (PByte)this->pObject + 0x44C );
	*( (PByte)this->pObject + 0x44C ) = 0;
	__asm
	{
		xor edx, edx
		mov eax, [Ship]
		call [OrderNone_]
	}
	*( (PByte)this->pObject + 0x44C ) = ScriptOrder;
}

E_SHIP_RANK_COALITION SR_API C_SHIP::CRank( void )
{
	return (E_SHIP_RANK_COALITION)*(UInt*)( (UInt)this->pObject + 0x500 );
}

void SR_API C_SHIP::SetCRank( const E_SHIP_RANK_COALITION eNewRank )
{
	*(UInt*)( (UInt)this->pObject + 0x500 ) = (UInt)eNewRank;
}

E_SHIP_RANK_PIRATE SR_API C_SHIP::PRank( void )
{
	return (E_SHIP_RANK_PIRATE)*(UInt*)( (UInt)this->pObject + 0x508 );
}

void SR_API C_SHIP::SetPRank( const E_SHIP_RANK_PIRATE eNewRank )
{
	*(UInt*)( (UInt)this->pObject + 0x508 ) = (UInt)eNewRank;
}

UInt SR_API C_SHIP::ItemsCount( void )
{
	return *(UInt*)( *(UInt*)( (UInt)this->pObject + 0x3B8 ) + 8 );
}

C_ITEM* SR_API C_SHIP::Item( const UInt ItemN )
{
	return (C_ITEM*)(*(UInt*)( *(UInt*)( (UInt)this->pObject + 0x3B8 ) + 4) + 4 * ItemN );
}

// Скорость корабля
UInt SR_API C_SHIP::Speed( void )
{
	return *(UInt*)( (UInt)this->pObject + 0xC4 );
}

UInt SR_API C_SHIP::Armor( void )
{
	return 0;
}
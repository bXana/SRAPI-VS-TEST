#include "Item.hpp"

E_EQUIPMENT_TYPE SR_API C_ITEM::Type( void )
{
	return (E_EQUIPMENT_TYPE)*(UInt*)( (UInt)this->pObject + 0xC );
}

void SR_API C_ITEM::SetType( const E_EQUIPMENT_TYPE eNewType )
{
	*(UInt*)( (UInt)this->pObject + 0xC ) = (UInt)eNewType;
}

UInt SR_API C_ITEM::Size( void )
{
	return *(UInt*)( (UInt)this->pObject + 0x18 );
}

void SR_API C_ITEM::SetSize( const UInt NewSize )
{
	*(UInt*)( (UInt)this->pObject + 0x18 ) = NewSize;
}

E_FRACTION_OWNER SR_API C_ITEM::Fraction( void )
{
	return (E_FRACTION_OWNER)*(UInt*)( (UInt)this->pObject + 0x1C );
}

void SR_API C_ITEM::SetFraction( const E_FRACTION_OWNER eNewFraction )
{
	*(UInt*)( (UInt)this->pObject + 0x1C ) = eNewFraction;
}

E_DOMSERIES SR_API C_ITEM::DomSeries( void )
{
	return (E_DOMSERIES)*(UInt*)( (UInt)this->pObject + 0x5C );
}

void SR_API C_ITEM::SetDomSeries( const E_DOMSERIES eNewDomSeries )
{
	*(UInt*)( (UInt)this->pObject + 0x5C ) = (UInt)eNewDomSeries;
}

UInt SR_API C_ITEM::Cost( void )
{
	return *(UInt*)( (UInt)this->pObject + 0x20 );
}

void SR_API C_ITEM::SetCost( const UInt NewCost )
{
	*(UInt*)( (UInt)this->pObject + 0x20 ) = NewCost;
}
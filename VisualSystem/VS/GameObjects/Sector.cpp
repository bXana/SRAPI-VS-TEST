#include "Sector.hpp"

UInt SR_API C_SECTOR::StarsCount( void ) {
	return  *(UInt*)( *(UInt*)( (UInt)this->pObject + 0x18 ) + 8 );
}

C_STAR* SR_API C_SECTOR::Star( const UInt StarNumber ) {
	return (C_STAR*)(*(UInt*)( *(UInt*)( (UInt)this->pObject + 0x18 ) + 4) + 4 * StarNumber );
}

Bool SR_API C_SECTOR::IsVisible( void ) {
	return *(Bool*)( (UInt)this->pObject + 9 );
}

void SR_API C_SECTOR::SetVisible( const Bool VisibleFlag ) {
	*(Bool*)( (UInt)this->pObject + 9 ) = VisibleFlag;
}
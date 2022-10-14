///////////////////////////////////////
//		GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Sector API
///////////////////////////////////////

#ifndef _SECTOR_HPP_
#define _SECTOR_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "GameObject.hpp"
#include "Star.hpp"

class C_SECTOR : public C_OBJECT
{
	public:
		// Возвращает количество систем в секторе
		UInt SR_API StarsCount( void );

		// Возвращает объект системы
		C_STAR* SR_API Star( const UInt StarNumber );

		// Виден ли сектор
		Bool	SR_API IsVisible( void );
		void	SR_API SetVisible( const Bool VisibleFlag );
};


#endif
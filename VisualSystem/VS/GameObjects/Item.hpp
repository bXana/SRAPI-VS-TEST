///////////////////////////////////////
//		GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
// 		Item API
///////////////////////////////////////
#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "GameObject.hpp"
#include "Ship.hpp"

class C_OBJECT;

enum E_EQUIPMENT_TYPE
{

};


class C_ITEM: public C_OBJECT
{
	public:
		// Возвращает/устанавливает тип объекта
		E_EQUIPMENT_TYPE SR_API Type( void );
		void SR_API SetType( const E_EQUIPMENT_TYPE eNewType );
		// Возвращает/устанавливает размер предмета
		UInt SR_API Size( void );
		void SR_API SetSize( const UInt NewSize );

		// Возвращает/устанавливает фракцию-изготовителя предмета
		E_FRACTION_OWNER SR_API Fraction( void );
		void SR_API SetFraction( const E_FRACTION_OWNER eNewFraction );

		// Возвращает/устанавливает подтип доминатора-изготовителя
		E_DOMSERIES SR_API DomSeries( void );
		void SR_API SetDomSeries( const E_DOMSERIES eNewDomSeries );

		// Возвращает/устанавливает Стоимость предмета
		UInt SR_API Cost( void );
		void SR_API SetCost( const UInt NewCost );
};

#endif

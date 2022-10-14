///////////////////////////////////////
//		GameAPI ver.1.0.
//		Author: bAnXZ
//		Description:
//		Space Rangers HD a war apart
//		Allow to interact with game objects( ships, planets, and etc.. )
///////////////////////////////////////
#ifndef _SRAPI_HPP_
#define _SRAPI_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "Params.hpp"
#include "GameObjects/Galaxy.hpp"
#include "GameObjects/Ship.hpp"
#include "GameObjects/Planet.hpp"

class ISpaceRangersAPI 
{
	public:
		virtual ~ISpaceRangersAPI( void ) = 0;

		virtual C_GALAXY* SR_API Galaxy( void ) = 0;
		virtual C_HIDDEN_PLANET* SR_API Rojeria( void ) = 0;
		virtual C_SHIP* SR_API Blazer( void ) = 0;
		virtual C_SHIP* SR_API Keller( void ) = 0;
		virtual C_SHIP* SR_API Terron( void ) = 0;
		virtual Bool SR_API IsPlaying( void ) = 0;
};

class CSpaceRangersAPI: public ISpaceRangersAPI
{
	private:
		// galaxy addr pointer
		C_GALAXY*  CGalaxy;
		C_HIDDEN_PLANET* CRojeria;
		C_SHIP* CKeller, *CTerron, *CBlazer;
	public:
		CSpaceRangersAPI( const char* ProcessName );
		virtual ~CSpaceRangersAPI( void );
		virtual C_GALAXY* SR_API Galaxy( void );
		virtual C_HIDDEN_PLANET* SR_API Rojeria( void );
		virtual C_SHIP* SR_API Blazer( void );
		virtual C_SHIP* SR_API Keller( void );
		virtual C_SHIP* SR_API Terron( void );
		virtual Bool SR_API IsPlaying( void );
};

#endif
///////////////////////////////////////
//		ScriptManager ver.1.0.
//		Author: bAnXZ
//		Description:
//		RequiredScript class
///////////////////////////////////////

#ifndef _SCRIPTMANAGER_HPP_
#define _SCRIPTMANAGER_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "Params.hpp"

class CScriptManager
{
	UInt Frequency_; // in days
	char* ScriptPath_;
	
	public:
		CScriptManager( char* ScriptPath, const UInt Frequency );
		CScriptManager( void );
		void Thiscall InitParams( char* ScriptPath, const UInt Frequency );
	   ~CScriptManager( void );

	   inline UInt Frequency( void ) { return this->Frequency_; }
	   inline const char* Path( void ) { return this->ScriptPath_; }
};


#endif
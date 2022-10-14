#ifndef _EXCEPTIONMANAGER_HPP_
#define _EXCEPTIONMANAGER_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

class CExceptionManager {
	char ErrMsg_[256];
	
	public:
		CExceptionManager( 		
		const char* Fmt,
		... );
	
		inline const char* __thiscall ErrMsg( void ) { return this->ErrMsg_; }
};

#endif
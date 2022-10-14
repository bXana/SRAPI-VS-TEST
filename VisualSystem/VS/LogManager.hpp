#ifndef _LOGMANAGER_HPP_
#define _LOGMANAGER_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "Params.hpp"

class ILogManager
{
		
	public:
		virtual ~ILogManager( void ) = 0;
		virtual bool Thiscall Clear( void ) = 0;
		virtual void __cdecl  LogMsgV( const char* Msg, ... ) = 0;
		virtual void Thiscall LogMsg( const char* Msg ) = 0;
		virtual void Thiscall EnableConsole ( const char* ConTitle ) = 0;
		virtual void Thiscall CloseConsole( void ) = 0;
		virtual bool Thiscall ConsoleIsActive( void ) = 0;
};

class CLogManager: public ILogManager
{
	private:
		const char* LogPath;
		bool ConsoleActive;
	public:
		CLogManager( const char* LogPath );
		virtual ~CLogManager( void );
		virtual bool Thiscall Clear( void );
		virtual void __cdecl  LogMsgV( const char* Msg, ... );
		virtual void Thiscall LogMsg( const char* Msg );
		virtual void Thiscall EnableConsole ( const char* ConTitle );
		virtual void Thiscall CloseConsole( void );
		virtual bool Thiscall ConsoleIsActive( void );

};

#endif
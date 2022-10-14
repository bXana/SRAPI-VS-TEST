///////////////////////////////////////
//		ConVar API ver.1.0.
//		Author: bAnXZ
//		Description:
// 		Console Variable interface
///////////////////////////////////////

#ifndef _CONVAR_HPP_
#define _CONVAR_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "Params.hpp"

class IConVar;
class CConVar;

template< typename VType, UInt VarLim >
class TConVarArray
{
	VType* Vars[VarLim];
	UInt VarCount;
	public:
		TConVarArray( void ) { this->VarCount = 0; }

		bool Thiscall RegisterVar( VType* Var ) {
			if( VarCount >= VarLim )
				return false;

			this->Vars[VarCount] = Var;
			++VarCount;
			return true;
		}

		// ArgsCount - количество аргументов команды
		void* __cdecl SetVar( const UInt ArgsCount, const char* VarName, ... ) {
			for( UInt I = 0; I < VarCount; I++ ) {
				if( !strcmp( Vars[I]->VarName(), VarName ) ) {
					if( ArgsCount < Vars[I]->ArgsCount() )
						throw CExceptionManager( Vars[I]->Description() );
					
					return Vars[I]->Execute( &VarName );
				}
			}
			throw CExceptionManager( "Unknown command\n" );
		}
};

class IConVar
{
	public:
		virtual const char* Thiscall VarName( void ) = 0;
		virtual const UInt  Thiscall ArgsCount( void ) = 0;
		virtual const char* Thiscall Description( void ) = 0;
		// возвращает значение callback функции в приведении указателя
		virtual void* Thiscall Execute( const void* VPointer ) = 0;		
};

class CConVar: public IConVar
{
	const char* VarName_;
	const char* VarDescription_;
	UInt ArgsCount_;
	void* CallbackFunction_;
	public:
		CConVar( const char* VarName, void* CallbackFunction, const UInt ArgsCount, const char* Description );
		virtual const char* Thiscall VarName( void );
		virtual void* Thiscall Execute( const void* VPointer );
		virtual const UInt  Thiscall ArgsCount( void );
		virtual const char* Thiscall Description( void );
};

#endif
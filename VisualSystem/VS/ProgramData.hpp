///////////////////////////////////////
//		ProgramData ver.1.0.
//		Author: bAnXZ
//		Description:
// 		Program modules 
///////////////////////////////////////
#ifndef _PROGRAMDATA_HPP_
#define _PROGRAMDATA_HPP_

#include "Params.hpp"
#include "SRAPI.hpp"
#include "LogManager.hpp"
#include "ConVar.hpp"
#include "../LuaAPI/LuaManager.hpp"
#include "ScriptManager.hpp"
#include "../Utils/MemoryManager.hpp"

#include <vector>

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

class IProgramData
{
	public:
		virtual ~IProgramData( void ) = 0;

		virtual void Thiscall SetupGameSettings( void ) = 0;
		virtual void Thiscall SetupConsoleCommands( void ) = 0;
		virtual void Thiscall SetupLuaSettings( void ) = 0;
		virtual void Thiscall RestartLuaSettings( void ) = 0;
		virtual void Thiscall ConsoleListen( void ) = 0;
		virtual ISpaceRangersAPI* Thiscall SRAPI( void ) = 0;
		virtual LuaAPI::ILuaManager* Thiscall Lua( void ) = 0;
		virtual ILogManager* Thiscall Logger( void ) = 0;
		virtual CRITICAL_SECTION* Thiscall HCritical( void ) = 0;
		virtual std::vector< CScriptManager >* Thiscall GetRequiredScripts( void ) = 0;
		virtual void Thiscall InitJumpPoints( void ) = 0;
		virtual void Thiscall ResetJumpPoints( void ) = 0;

		virtual void Thiscall TestScripts( void ) = 0;
};

struct __ConsoleArgs;
class CProgramData: public IProgramData
{
	friend class CSpaceRangersAPI;
	friend DWORD WINAPI __ConsoleListen( const __ConsoleArgs* Arguments );

	static PVoid GameMoveFunction_;
	static UInt GameThreadId_;
	static PVoid GetLocalPlayerF_;
	private:
		ILogManager* Log;
		LuaAPI::ILuaManager* LuaMachine;
		ISpaceRangersAPI* SRApi;
		TConVarArray< IConVar, 4 > AConsoleVars;

		std::vector< CScriptManager > RequiredScripts;
		CRITICAL_SECTION hLuaResourceController;
		Win32Utils::RedirectionManager JGameMove;
	public:
		CProgramData( void );
		virtual ~CProgramData( void );
		virtual void Thiscall SetupGameSettings( void );
		virtual void Thiscall SetupLuaSettings( void );
		virtual void Thiscall RestartLuaSettings( void );
		virtual void Thiscall SetupConsoleCommands( void );
		virtual void Thiscall ConsoleListen( void );
		virtual ISpaceRangersAPI* Thiscall SRAPI( void );
		virtual LuaAPI::ILuaManager* Thiscall Lua( void );
		virtual ILogManager* Thiscall Logger( void );
		virtual CRITICAL_SECTION* Thiscall HCritical( void );
		virtual std::vector< CScriptManager >* Thiscall GetRequiredScripts( void );
		virtual void Thiscall InitJumpPoints( void );
		virtual void Thiscall ResetJumpPoints( void );

		virtual void Thiscall TestScripts( void );

		static UInt Stdcall CProgramData::GameMoveListener( void );
};

// global program interface
extern IProgramData* Program;

#endif

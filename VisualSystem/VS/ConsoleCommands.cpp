#include "ConsoleCommands.hpp"
#include "../LuaAPI/LuaStackException.hpp"
#include "../LuaAPI/LuaManager.hpp"
#include "../Utils/ProcessManager.hpp"
#include "../Utils/ThreadManager.hpp"
#include "../Utils/ConsoleManager.hpp"
#include "Params.hpp"
#include "ProgramData.hpp"

static BOOL Stdcall TerminateProgram( void ) {
	return TerminateProcess( GetCurrentProcess(), 0x0 );
}

static void Stdcall RestartLua( void )
{
	EnterCriticalSection( Program->HCritical() );
		Program->RestartLuaSettings();
	LeaveCriticalSection( Program->HCritical() );
}

static void Stdcall ExecuteScript( const char* ScriptPath )
{
	EnterCriticalSection( Program->HCritical() );
		LuaAPI::ILuaManager* LuaMachine = Program->Lua();
		//LuaAPI::CLuaStackNormaliser StackCheck( LuaMachine->GetHandle() );
		LuaStackException( StackCheck, LuaMachine->GetHandle() );
		 try {
			LuaMachine->ExecuteScripts( 1, ScriptPath );
		 } catch( LuaAPI::CLuaException& Error ) {
			 ConsolePrintVS( "%s\n",Error.ErrMsg() );
		 }
	LeaveCriticalSection( Program->HCritical() );
}

CConVar ConClear("Clear", &Console::Clear, 0, "" );
CConVar ConExit("Exit", &TerminateProgram, 0, "" );
CConVar ConExecuteScript("ExecuteScript", &ExecuteScript, 1, "Warning: Need write Path to the script file\n" );
CConVar ConRestartLua("RestartLuaSettings", &RestartLua, 0, "" );
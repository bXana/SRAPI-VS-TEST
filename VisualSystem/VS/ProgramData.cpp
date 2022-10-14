#include <Windows.h>
#include "ProgramData.hpp"
#include "ExceptionManager.hpp"
#include "ConsoleCommands.hpp"
#include "../LuaAPI/LuaStackException.hpp"
#include "../Utils/ThreadManager.hpp"

#define SR_PROGRAM_LOG (const char*)"Log.log"
#define SR_GDATA_PATH "VSScripts/userdata/VSConfig.lua"
// Lua Variables 
#define SR_GDATA_TABLE "GameInformation"
#define SR_PROCNAME_F  "ProcessName"
#define SR_CONSOLE_ENABLE_B "ConsoleEnable"
#define SR_REQUIRED_SCRIPTS_FIELD "RequiredScripts"
#define SR_REQUIRED_SCRIPT_EXECUTE_F "RequiredScriptsExecute"

#pragma warning( disable : 4800 )

IProgramData* Program = new CProgramData;	

PVoid CProgramData::GameMoveFunction_ = NULL;
UInt  CProgramData::GameThreadId_ = 0;
PVoid CProgramData::GetLocalPlayerF_ = NULL;

UInt Stdcall CProgramData::GameMoveListener( void )
{
	EnterCriticalSection( Program->HCritical() );

	std::vector< CScriptManager >& RequiredScripts = *Program->GetRequiredScripts();

	UInt DayData = Program->SRAPI()->Galaxy()->CurrentDay();
	LuaAPI::ILuaManager* LuaMachine = Program->Lua();
	for( UInt I = 0; I < RequiredScripts.size(); I++ )
		if(  !( DayData % RequiredScripts[I].Frequency() ) )
		{
			 try {
				LuaMachine->ExecuteScripts( 1, RequiredScripts[I].Path() );
			 }
			 catch( LuaAPI::CLuaException& Error )
			 {
			 	 Program->Logger()->LogMsgV( "%s\n", Error.ErrMsg() );
			 }
		}

	LeaveCriticalSection( Program->HCritical() );

	void* X = CProgramData::GetLocalPlayerF_;
	__asm
	{
		call [X]
		mov [X], eax
	}
	return (UInt)X;
}

IProgramData::~IProgramData( ) { /* pure */ }

CProgramData::CProgramData( void ) 
{
	this->SRApi = NULL;
	this->LuaMachine = NULL;
	this->Log = NULL;

	InitializeCriticalSection( &this->hLuaResourceController );
}

void Thiscall CProgramData::InitJumpPoints( void )
{
	Win32Utils::Win32Thread::SuspendThread( this->GameThreadId_ );
		this->JGameMove.CreateJump( this->GameMoveFunction_, CProgramData::GameMoveListener, Win32Utils::E_REDIRECTION_COMMAND_TYPE::REDIRECTION_CALL );
	Win32Utils::Win32Thread::ResumeThread( this->GameThreadId_ );
}

void Thiscall CProgramData::ResetJumpPoints( void )
{
	Win32Utils::Win32Thread::SuspendThread( this->GameThreadId_ );
		this->JGameMove.CloseJump();
	Win32Utils::Win32Thread::ResumeThread( this->GameThreadId_ );
}

CRITICAL_SECTION* Thiscall CProgramData::HCritical( void )
{
	return &this->hLuaResourceController;
}

std::vector< CScriptManager >* Thiscall CProgramData::GetRequiredScripts( void )
{
	return &this->RequiredScripts;
}

CProgramData::~CProgramData( void ) {
	if( this->SRApi )
		delete this->SRApi;

	if( this->LuaMachine )
		delete this->LuaMachine;

	if( this->Log )
		delete this->Log;

	this->JGameMove.CloseJump();

	DeleteCriticalSection( &this->hLuaResourceController );
}

void Thiscall CProgramData::SetupGameSettings( void ) {
	this->Log = new CLogManager( SR_PROGRAM_LOG );
	Log->Clear();
	LuaAPI::CLuaManager* LuaMachine_ = NULL;
	try
	{
		LuaMachine_ = new LuaAPI::CLuaManager;
	}
	catch( LuaAPI::CLuaException& Error )
	{
		Log->LogMsgV( "%s\n", Error.ErrMsg() );
		ExitThread( 0x0 );
	}
	lua_State* LuaHandle = LuaMachine_->GetHandle();
	try {
		/* Procedures */
		LuaMachine_->ExecuteScripts(1, SR_GDATA_PATH );

		if( lua_getglobal( LuaHandle, SR_GDATA_TABLE ) != LUA_TTABLE ) {
			lua_pop( LuaHandle, 1 );
			throw CExceptionManager( "Error: cannot find \'%s\' table\n", SR_GDATA_TABLE );
		}
		/*--------------------------------------------*/
		if( lua_getfield( LuaHandle, -1, SR_PROCNAME_F ) != LUA_TSTRING ) {
			lua_pop( LuaHandle, 2 );
			throw CExceptionManager( "Error: invalid value \'%s\'\n", SR_PROCNAME_F );
		}
		this->SRApi	= new CSpaceRangersAPI( lua_tostring( LuaHandle, -1 ) );
		lua_pop( LuaHandle, 1 );
		/*--------------------------------------------*/
		if( lua_getfield( LuaHandle, -1, SR_CONSOLE_ENABLE_B ) == LUA_TBOOLEAN ) {
			if( (bool)lua_toboolean( LuaHandle, -1 ) )
				this->Log->EnableConsole( "" );
		}
		lua_pop( LuaHandle, 1 );
		/*--------------------------------------------*/
		lua_pop( LuaHandle, 1 );
	} 
	catch ( CExceptionManager& Error ) {
		Log->LogMsg( Error.ErrMsg() );
		delete LuaMachine_;
		ExitThread( 0x0 );
	}
	catch( LuaAPI::CLuaException& Error ) {
		Log->LogMsgV( "%s\n", Error.ErrMsg() );
		delete LuaMachine_;
		ExitThread( 0x0 );
	}

	delete LuaMachine_;
}

// Всё работает, но нужен другой вариант
//void Thiscall CProgramData::ConsoleListen( void ) {
//	char VarName[ 100 ] = "";
//	char VarArg[ 100 ]  = "";
//	UInt ArgsCount = 0;
//	while ( Log->ConsoleIsActive() ) {
//		ArgsCount = ConsoleReadVS( sizeof(VarName), 2, "%s%s", VarName, VarArg )
//		try {
//			this->AConsoleVars.SetVar( ArgsCount - 1, VarName, VarArg );
//		} catch( CExceptionManager& Error ) {
//			ConsolePrintVS( Error.ErrMsg() )
//		}
//		ZeroMemory( VarName, sizeof(VarName) );
//		ZeroMemory( VarArg, sizeof(VarArg) );
//	};
//		
//	return;
//}

struct __ConsoleArgs
{
	char VarName[ 100 ];
	char VarArg[ 100 ];
	UInt ArgsCount;
	CProgramData* ProgData;
};

DWORD WINAPI __ConsoleListen( const __ConsoleArgs* Arguments )
{
	try {
			Arguments->ProgData->AConsoleVars.SetVar( 
			Arguments->ArgsCount - 1, 
			Arguments->VarName, Arguments->VarArg 
			);
	} catch( CExceptionManager& Error ) {
		ConsolePrintVS( Error.ErrMsg() )
	}

	delete Arguments;
	ExitThread( 0x0 );
}

void Thiscall CProgramData::ConsoleListen( void ) {
	__ConsoleArgs* Args = NULL;
	HANDLE ThreadHandle = NULL;
	while ( Log->ConsoleIsActive() ) {
		Args = new __ConsoleArgs;
		Args->ProgData = this;
		Args->ArgsCount = ConsoleReadVS( sizeof(Args->VarName), 2, "%s%s", Args->VarName, Args->VarArg )
		ThreadHandle = CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)__ConsoleListen, Args, 0, NULL );
		CloseHandle( ThreadHandle );
	};
	return;
}

ISpaceRangersAPI* Thiscall CProgramData::SRAPI( void ) {
	return this->SRApi;
}

void Thiscall CProgramData::SetupConsoleCommands( void ) {
	this->AConsoleVars.RegisterVar( &ConClear );
	this->AConsoleVars.RegisterVar( &ConExit );
	this->AConsoleVars.RegisterVar( &ConExecuteScript );
	this->AConsoleVars.RegisterVar( &ConRestartLua );
}

#include "GameObjects/Lua/Lua_Program.hpp"
#include "GameObjects/Lua/Lua_Galaxy.hpp"
#include "GameObjects/Lua/Lua_Sector.hpp"
#include "GameObjects/Lua/Lua_Star.hpp"
#include "GameObjects/Lua/Lua_Planet.hpp"
#include "GameObjects/Lua/Lua_Ship.hpp"

void Thiscall CProgramData::SetupLuaSettings( void ) { 
	try
	{
		this->LuaMachine = new LuaAPI::CLuaManager;
	} catch( LuaAPI::CLuaException& Error ) {
		Log->LogMsgV( "%s\n", Error.ErrMsg() );
		ExitThread( 0x0 );
	}

	lua_State* LuaHandle = this->LuaMachine->GetHandle();
	LuaStackException( StackCheck, LuaHandle );
	UInt* LuaObject = NULL;

	luaL_Reg ProgramMethods[] =
	{
		{ "IsPlaying", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PROGRAM::IsPlaying },
		{ "Print", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PROGRAM::Print },
		{ "FPrint", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PROGRAM::FPrint },
		{ "Log", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PROGRAM::Log },
	//	{ "Random", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PROGRAM::Random },

		{ NULL, NULL }
	};

	luaL_Reg GalaxyMethods[ ] = 
	{
		{ "Settings", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Settings },
		{ "SetSettings", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::SetSettings },
		{ "AdjustmentSettings", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::AdjustmentSettings },
		{ "SetAdjustmentSettings", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::SetAdjustmentSettings },

		{ "Stars", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Stars },
		{ "Sectors", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Sectors },

		{ "Player", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Player },
		{ "Rojeria", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Rojeria },
		{ "Blazer", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Blazer },
		{ "Keller", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Keller },
		{ "Terron", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Terron },
		{ "SectorsCount", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::SectorsCount },
		{ "Sector", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Sector },
		{ "StarsCount", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::StarsCount },
		{ "Star", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_GALAXY::Star },

		{ NULL, NULL }
	};

	luaL_Reg SectorMethods[] =
	{
		{ "Stars", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SECTOR::Stars },

		{"StarsCount", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SECTOR::StarsCount },
		{"Star", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SECTOR::Star },
		{"IsVisible", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SECTOR::IsVisible },
		{"SetVisible", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SECTOR::SetVisible },

		{ NULL, NULL }
	};

	luaL_Reg StarMethods[] =
	{
		{ "Ships", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::Ships },
		{ "Planets", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::Planets },

		{ "Fraction", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::Fraction },
		{ "SetFraction", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::SetFraction },
		{ "DomSeries", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::DomSeries },
		{ "SetDomSeries", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::SetDomSeries },
		{ "ShipsCount", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::ShipsCount },
		{ "Ship", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::Ship },
		{ "CreateBase", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::CreateBase },
		{ "IsBattle", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::IsBattle },
		{ "PlanetsCount", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::PlanetsCount },
		{ "Planet", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::Planet },
		{ "FonImage", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::FonImage },
		{ "SetFonImage", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::SetFonImage },
		{ "Sector", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::Sector },
		{ "Flags", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::Flags },
		{ "SetFlags", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::SetFlags },
		{ "VisualModel", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::VisualModel },
		{ "SetVisualModel", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::SetVisualModel },

		{ NULL, NULL }
	};

	luaL_Reg PlanetMethods[] =
	{
		{ "Warriors", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Warriors },

		{ "Fraction", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Fraction },
		{ "SetFraction", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetFraction },
		{ "Species", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Species },
		{ "SetSpecies", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetSpecies },
		{ "Government", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Government },
		{ "SetGovernment", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetGovernment },
		{ "Economy", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Economy },
		{ "SetEconomy", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetEconomy },
	//	{ "Terrain", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Terrain },
	//	{ "SetTerrain", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetTerrain },
	//	{ "TerrainExplored", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::TerrainExplored },
	//	{ "SetTerrainExplored", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetTerrainExplored },
		{ "Radius", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Radius },
		{ "SetRadius", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetRadius },
		{ "OrbitalVelocity", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::OrbitalVelocity },
		{ "SetOrbitalVelocity", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetOrbitalVelocity },
		{ "Population", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Population },
		{ "SetPopulation", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetPopulation },
		{ "WarriorsCount", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::WarriorsCount },
		{ "Warrior", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Warrior },
		{ "Flags", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Flags },
		{ "SetFlags", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetFlags },
		{ "Invention", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Invention },
		{ "SetInvention", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetInvention },
		{ "InventionPoints", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::InventionPoints },
		{ "SetInventionPoints", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetInventionPoints },
		{ "InventionLvl", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::InventionLvl },
		{ "SetInventionLvl", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetInventionLvl },
		{ "Star", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Star },
		{ "VisualModel", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::VisualModel },
		{ "SetVisualModel", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::SetVisualModel },
		//{ "Name", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::Name },

		{ NULL, NULL }
	};

	luaL_Reg ShipMethods[] =
	{
		{"VisualModel", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::VisualModel },
		{"SetVisualModel", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetVisualModel },
		{"Home", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Home },
		{"Type", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Type },
		{"SetType", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetType },
		{"SubType", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SubType },
		{"SetSubType", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetSubType },
		{"Star", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Star },
		{"DomSeries", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::DomSeries },
		{"SetDomSeries", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetDomSeries },
		{"Fraction", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Fraction },
		{"SetFraction", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetFraction },
		{"Species", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Species },
		{"SetSpecies", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetSpecies },
		{"StatusType", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::StatusType },
		{"SetStatusType", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetStatusType },
		{"Destroy", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Destroy },
		{"Target", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Target },
		{"SetTarget", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetTarget },
		{"InHyper", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::InHyper },
		{"OnPlanet", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::OnPlanet },
		{"OnBase", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::OnBase },
		{"Teleport", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Teleport },
		{"Land", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Land },
		{"TakeOff", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::TakeOff },
		{"Move", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Move },
		{"Fallow", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Fallow },
		{"Jump", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::Jump },
		{"CancelTask", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::CancelTask },
		{"CRank", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::CRank },
		{"SetCRank", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetCRank },
		{"PRank", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::PRank },
		{"SetPRank", (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::SetPRank },

		{ NULL, NULL }
	};



		// Program
		this->LuaMachine->CreateObject(
			SR_LUA_PROGRAM_OBJ_NAME,
			sizeof(int),
			ProgramMethods,
			SR_LUA_PROGRAM_MT_NAME
			);

		// Galaxy
	LuaObject = (UInt*)this->LuaMachine->CreateObject( 
			SR_LUA_GALAXY_OBJECT_NAME,
			sizeof(C_GALAXY*),
			GalaxyMethods, 
			SR_LUA_GALAXY_METATABLE_NAME );
		*LuaObject = (UInt)this->SRApi->Galaxy();


	struct _REGLUA
	{
		luaL_Reg* Methods;
		const char* ObjectName;
		lua_CFunction EqFunction;
	};


	_REGLUA LuaObjects[4] =
	{
		{ SectorMethods, SR_LUA_SECTOR_METATABLE_NAME, (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SECTOR::IsEqual },
		{ StarMethods, SR_LUA_STAR_METATABLE_NAME, (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_STAR::IsEqual },
		{ PlanetMethods, SR_LUA_PLANET_METATABLE_NAME, (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_PLANET::IsEqual },
		{ ShipMethods, SR_LUA_SHIP_METATABLE_NAME, (lua_CFunction)VS_LUA_GAMEMETHODS::LUA_SHIP::IsEqual }
	};
		
	for( UInt I = 0; I < 4 ; I++ )
	{
		this->LuaMachine->CreateMetaTableObject( LuaObjects[I].Methods, LuaObjects[I].ObjectName );
		
		// Добавление возможности сравнения объектов
		luaL_getmetatable( LuaHandle, LuaObjects[I].ObjectName );
		lua_pushcfunction( LuaHandle, LuaObjects[I].EqFunction );
		lua_setfield( LuaHandle, -2, "__eq" );
	}
	lua_pop( LuaHandle, 4 );

	// VSConfig.lua
	this->LuaMachine->ExecuteScripts(1, SR_GDATA_PATH );

	// Read Required Scripts
	if( lua_getglobal( LuaHandle, SR_REQUIRED_SCRIPTS_FIELD ) == LUA_TTABLE )
	{
		UInt TableLen = 0;
		lua_len( LuaHandle, -1 );
		TableLen = (UInt)lua_tointeger( LuaHandle, -1 );
		lua_pop( LuaHandle, 1 );

		CScriptManager Script;

		for( UInt I = 0; I < TableLen; I++ )
		{
			lua_pushinteger( LuaHandle, I + 1 );
			if( lua_gettable( LuaHandle, -2 ) == LUA_TTABLE )
			{
				lua_pushinteger( LuaHandle, 1 );
				if( lua_gettable( LuaHandle, -2 ) == LUA_TSTRING )
				{
					lua_pushinteger( LuaHandle, 2 );
					if( lua_gettable( LuaHandle, -3 ) == LUA_TNUMBER )
					{
						UInt ScriptFrequency = (UInt)lua_tointeger( LuaHandle, -1 );
						char* ScriptPath = (char*)lua_tostring( LuaHandle, -2 );

						if( ScriptFrequency >= 1 )
						{
							Script.InitParams( ScriptPath, ScriptFrequency );
							this->RequiredScripts.push_back( Script );
						}
					}
					lua_pop( LuaHandle, 1 );
				}
				lua_pop( LuaHandle, 1 );
			}
			lua_pop( LuaHandle, 1 );
		}
	}
	lua_pop( LuaHandle, 1 );

	// Check ExecuteRequiredScriptsFlag
	if( lua_getglobal( LuaHandle, SR_GDATA_TABLE ) == LUA_TTABLE )
	{
		if( lua_getfield( LuaHandle, -1, SR_REQUIRED_SCRIPT_EXECUTE_F ) == LUA_TBOOLEAN ) {
			if( (bool)lua_toboolean( LuaHandle, -1 ) )
				this->InitJumpPoints();
		}
		lua_pop( LuaHandle, 1 );
	}
	lua_pop( LuaHandle, 1 );

	// Базовые библиотеки
	luaL_openlibs( LuaHandle );
}

 LuaAPI::ILuaManager* Thiscall CProgramData::Lua( void ) {
	 return this->LuaMachine;
 }

 ILogManager* Thiscall CProgramData::Logger( void ) {
	 return this->Log;
 }

 void Thiscall CProgramData::RestartLuaSettings( void )
 {
	 this->ResetJumpPoints();

	 delete this->LuaMachine;
	 this->LuaMachine = NULL;
	 this->RequiredScripts.clear();
	 this->SetupLuaSettings();
 }

 void Thiscall CProgramData::TestScripts( void ) {

 }


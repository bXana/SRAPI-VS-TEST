#include <Windows.h>
#include "SRAPI.hpp"
#include "../Utils/MemoryManager.hpp"
#include "../Utils/ProcessManager.hpp"
#include "ExceptionManager.hpp"
#include "ProgramData.hpp"

#pragma warning( disable : 4800 )

typedef Win32Utils::Win32Memory			Memory;
typedef Win32Utils::Win32Process		Process;
typedef Win32Utils::CPattern			Signature;
typedef Win32Utils::RedirectionManager  JmpManager;

static Signature GalaxyObject( "8B 00 8B 40 2C 8B 50 08 8B 45 FC 8B 00" );
static Signature CreateBase( "89 45 F0 6A 00 8A 55 EC 8B 4D F4 8B 45 F0" );
static Signature GetLocalPlayer( "89 4D F4 89 55 F8 89 45 FC E8 ? ? ? ? 8B D0 8B 45 FC 8B 00" );
static Signature GetPirateClanBase( "A1 ? ? ? ? 8B 00 8B 80 0C 01 00 00 B9 14 00 00 00 8B 55 F0" );
static Signature RestoreHiddenForm( "8B 00 8B 80 64 01 00 00 8B 55 F0" );
static Signature ChangeVisualId( "8D 45 E0 50 8D 45 DC 50 8D 55 D8 8B 45 FC 8B 40 08" );
static Signature ChangeStarVisualId( "8D 55 E8 8B 45 F4 8B 40 6C 8B 08 FF 51 0C 33 C0" );
static Signature ChangePlanetVisualId("8B 45 F4 8B 80 44 01 00 00 66 8B 40 60 66 89 45" );
static Signature OrderTakeOff("8B 45 FC 8B 50 1C 8B 45 FC E8 ? ? ? ? 8B 45 FC 83 B8 DC 00 00 00 00");
static Signature OrderFallowShip("74 ? 6A 00 33 C9 8B 45 FC 8B 90 D8 04 00 00 8B 45 FC E8" );
static Signature OrderJump("8B 45 EC 8B 55 F4 89 42 24 8B 45 F4 8A 80 4C 04 00 00 88 45 E3 8B 45 F4 C6 80 4C");
static Signature BossPointers("8B 45 F8 89 45 FC 8B 45 FC 8B 80 B8 03 00 00 8B 40 08 48 83 F8 00 7C");

/* GameMove */
static Signature GameMove( "64 FF 30 64 89 20 8B 45 FC 80 B8 59 04 00 00 00");


static PByte __stdcall FIND_SIGNATURE( 
	Signature& Pattern,
	Win32Utils::Win32ModuleInformation& ModInfo,
	const char* ObjName 
	)
{
		UInt* Candidates[2] = { NULL, NULL };
		UInt  CandidatesCount = 0;

		CandidatesCount = Memory::FindSignature( 
		ModInfo.Address, 
		ModInfo.Size,	
		&Pattern,		
		Candidates,		
		2				
	);					
							
	if( CandidatesCount != 1 )	
		throw CExceptionManager( "Error: cannot find game object \'%s\'\n", ObjName );

	return (PByte)Candidates[0];
}


ISpaceRangersAPI::~ISpaceRangersAPI( void ) { /* pure */ }

CSpaceRangersAPI::~CSpaceRangersAPI( void ) { 

}

CSpaceRangersAPI::CSpaceRangersAPI( const char* ProcessName )
{
	Win32Utils::Win32ModuleInformation ModInfo;

	DWORD ProcId = 0;
	if( !Process::GetProcessId( ProcessName, (unsigned int*)&ProcId ) )
		throw CExceptionManager( "Error: cannot find \'%s\' process\n", ProcessName );

	if( !Process::GetModuleInformation( ProcId, ProcessName, &ModInfo ) )
		throw CExceptionManager( "Error: cannot read data from \'%s\' module\n", ProcessName );

	if( !Process::GetProcessGeneralThread( ProcId, &CProgramData::GameThreadId_ ) )
		throw CExceptionManager( "Error: cannot find \'%s\' thread\n", ProcessName );

	// Init objects

	/* GameMove */
	Byte* ObjData = FIND_SIGNATURE( GameMove , ModInfo, "DayMove" );
	CProgramData::GameMoveFunction_ = (PVoid)( (UInt)ObjData + 0x4C );

	/* Galaxy object */
	ObjData = FIND_SIGNATURE( GalaxyObject, ModInfo, "Galaxy" );
	this->CGalaxy = (C_GALAXY*)( **(UInt**)( ObjData - 4 ) );
	/*-------------------------------------------------------------------*/

	/* GetLocalPlayer */
	ObjData = FIND_SIGNATURE( GetLocalPlayer, ModInfo, "Player" );
	ObjData = (Byte*)JmpManager::GetEndJmpAddress( ObjData + 9 );
	C_GALAXY::GetLocalPlayer_ = ObjData;
	CProgramData::GetLocalPlayerF_ = ObjData;
	/*-------------------------------------------------------------------*/

	/* GetPirateClanBase */
	ObjData = FIND_SIGNATURE( GetPirateClanBase, ModInfo, "Rojeria" );
	this->CRojeria = (C_HIDDEN_PLANET*)( **(UInt**)( ObjData + 1 ) );
	/* OpenSector function */
	ObjData = FIND_SIGNATURE( RestoreHiddenForm, ModInfo, "OpenSector" );
	C_HIDDEN_PLANET::RestoreHiddenForm_ = JmpManager::GetEndJmpAddress( ObjData + 0x10 );
	/*-------------------------------------------------------------------*/

	/* CreateBase modules */
	ObjData = FIND_SIGNATURE( CreateBase, ModInfo, "CreateBase" );
	C_STAR::RuinsObject =  (void*)(**(UInt**)( (PByte)( ObjData - 9 ) ) );
	C_STAR::RuinsCreate = JmpManager::GetEndJmpAddress( ObjData - 5 );
	C_STAR::RuinsInit   = JmpManager::GetEndJmpAddress( ObjData + 0xE );
	/*-------------------------------------------------------------------*/

	/* ChangeVisualId modules */
	ObjData = FIND_SIGNATURE( ChangeVisualId, ModInfo, "VisualModelChanger" );
	C_SHIP::DetachFromSE_			= JmpManager::GetEndJmpAddress( ObjData - 0x11 );
	C_SHIP::RuinsChangeVisualConst_ = (PVoid)**(UInt**)( (UInt)JmpManager::GetEndJmpAddress( ObjData + 0x3C ) + 0x12A );
	C_SHIP::RuinsChangeVisualF_		= JmpManager::GetEndJmpAddress( (const void*)((UInt)JmpManager::GetEndJmpAddress( ObjData + 0x3C ) + 0x12E) );
	C_SHIP::LinkToSE_				= JmpManager::GetEndJmpAddress( ObjData + 0x4B );
	C_SHIP::SetGraphName_			= JmpManager::GetEndJmpAddress( ObjData + 0x64 );
	C_SHIP::SetAngle_				= JmpManager::GetEndJmpAddress( ObjData + 0x8C );
	C_SHIP::CalcParam_				= JmpManager::GetEndJmpAddress( ObjData + 0xCA );
	C_SHIP::CalcParamGraphSize_		= JmpManager::GetEndJmpAddress( ObjData + 0xD2 );

	// Planet VisualId objects //
	C_PLANET::PlanetChangeVisualConst_ =  (PVoid)**(UInt**)( (UInt)JmpManager::GetEndJmpAddress( ObjData + 0x3C ) + 0x82 );
	C_PLANET::PlanetChangeVisualF_	   =  JmpManager::GetEndJmpAddress( (const void*)((UInt)JmpManager::GetEndJmpAddress( ObjData + 0x3C ) + 0x86) );

	/* Star VisualId changer */
	C_STAR::StarChangeVisualConst_ = (PVoid)**(UInt**)( (UInt)JmpManager::GetEndJmpAddress( ObjData + 0x3C ) + 0x2E );
	C_STAR::StarChangeVisualF_	   = JmpManager::GetEndJmpAddress( (const void*)((UInt)JmpManager::GetEndJmpAddress( ObjData + 0x3C ) + 0x32) );
	ObjData = FIND_SIGNATURE( ChangeStarVisualId, ModInfo, "StarVisualModelChanger" );
	C_STAR::SetGraphNameConst_ = (PVoid)*(UInt*)( ObjData - 0x15 );

	/* PlanetVisualId changer */
	ObjData = FIND_SIGNATURE( ChangePlanetVisualId, ModInfo, "PlanetVisualModelChanger" );
	C_PLANET::CalcSpeedRotate_  = JmpManager::GetEndJmpAddress( ObjData + 0x5C );
	C_PLANET::CalcPosAndRadius_ = JmpManager::GetEndJmpAddress( ObjData + 0xDF );

	/* Order take off */
	ObjData = FIND_SIGNATURE( OrderTakeOff, ModInfo, "TakeOffCommand" );
	C_SHIP::OrderTakeOff_ = JmpManager::GetEndJmpAddress( ObjData + 0x1D );

	/* Order FallowShip */
	ObjData = FIND_SIGNATURE( OrderFallowShip, ModInfo, "FallowShipCommand" );
	C_SHIP::OrderFallowShip_ = JmpManager::GetEndJmpAddress( ObjData + 0x12 );

	/* Order Jump */
	ObjData = FIND_SIGNATURE( OrderJump, ModInfo, "JumpCommand" );
	C_SHIP::OrderJump_ = JmpManager::GetEndJmpAddress( ObjData + 0x27 );
	C_SHIP::OrderNone_ = JmpManager::GetEndJmpAddress( (PByte)C_SHIP::OrderJump_ + 0x3B ); 

	/* BossPointers */
	ObjData = FIND_SIGNATURE( BossPointers, ModInfo, "BossPointers" );
	this->CBlazer = (C_SHIP*)**(UInt**)( (UInt)ObjData - 0x7D );
	this->CKeller = (C_SHIP*)**(UInt**)( (UInt)ObjData - 0x71 );
	this->CTerron = (C_SHIP*)**(UInt**)( (UInt)ObjData - 0x65 );

	/*------------------------------------------------------------------------------*/
}

C_GALAXY* SR_API CSpaceRangersAPI::Galaxy( void ) {
	return this->CGalaxy;
}

 C_HIDDEN_PLANET* SR_API CSpaceRangersAPI::Rojeria( void ) {
	 return this->CRojeria;
 }

 Bool SR_API CSpaceRangersAPI::IsPlaying( void ) {
	 return (Bool)this->CGalaxy->pObject;
 }

C_SHIP* SR_API CSpaceRangersAPI::Blazer( void )
{
	return this->CBlazer;
}

C_SHIP* SR_API CSpaceRangersAPI::Keller( void )
{
	return this->CKeller;
}

C_SHIP* SR_API CSpaceRangersAPI::Terron( void )
{
	return this->CTerron;
}
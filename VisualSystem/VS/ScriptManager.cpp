#include "ScriptManager.hpp"

CScriptManager::CScriptManager( char* ScriptPath, const UInt Frequency )
{
	this->ScriptPath_ = ScriptPath;
	this->Frequency_  = Frequency;
}

void Thiscall CScriptManager::InitParams( char* ScriptPath, const UInt Frequency )
{
	this->ScriptPath_ = ScriptPath;
	this->Frequency_  = Frequency;
}

CScriptManager::CScriptManager( void )
{

}

CScriptManager::~CScriptManager( void ) {  }


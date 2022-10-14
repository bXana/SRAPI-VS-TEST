#include "LuaManager.hpp"
#include "LuaStackException.hpp"

using namespace LuaAPI;

#pragma warning( disable : 4800 ) // bool warn
#pragma warning( disable : 4146 ) // 

#define LUA_INIT_ERROR (const char*)"Error: cannot init Lua module"

ILuaManager::~ILuaManager( void ) { /* pure */ }

CLuaManager::CLuaManager( void ) {
	this->hLuaHandle_ = luaL_newstate();
	if( !this->hLuaHandle_ )
		throw LuaAPI::CLuaException( LUA_INIT_ERROR );
}

CLuaManager::~CLuaManager( void )
{
	lua_close( this->hLuaHandle_ );
}

const char* __thiscall CLuaManager::GetVersion( void ) {
	return LUA_RELEASE;
}

void __cdecl CLuaManager::ExecuteScripts( const unsigned int ScriptsCount, ... ) {
	const char* ErrMsg = NULL;
	const char** Args = (const char**)&ScriptsCount;
	++Args;
	for( unsigned int I = 0; I < ScriptsCount; I++ )
		if( luaL_dofile( this->hLuaHandle_, Args[I] ) )
		{
			ErrMsg = lua_tostring( this->hLuaHandle_, -1 );
			lua_pop(this->hLuaHandle_, 1 );
			throw LuaAPI::CLuaException( ErrMsg );
		}	
}

lua_State* __thiscall CLuaManager::GetHandle( void ) {
	return this->hLuaHandle_;
}

void* __thiscall CLuaManager::CreateObject( 
	const char* ObjectName, 
	const unsigned int ObjectSize, 
	luaL_Reg* Methods, 
	const char* MetatableName 
	) {
	void* NewUserDataObject = NULL;
	if( !luaL_newmetatable( this->hLuaHandle_ , MetatableName ) )
		return NewUserDataObject;

	lua_pushvalue( this->hLuaHandle_ , -1 );
	lua_setfield( this->hLuaHandle_ , -2, "__index" );
	luaL_setfuncs( this->hLuaHandle_ , Methods, 0 );
	lua_pop( this->hLuaHandle_ , 1 );

	NewUserDataObject = lua_newuserdata( this->hLuaHandle_, ObjectSize  );
	luaL_setmetatable( this->hLuaHandle_ , MetatableName );
	lua_setglobal( this->hLuaHandle_, ObjectName );

	return NewUserDataObject;
}

bool __thiscall CLuaManager::CreateMetaTableObject( luaL_Reg* Methods, const char* MetatableName ) {

	if( !luaL_newmetatable( this->hLuaHandle_ , MetatableName ) )
		return false;

	lua_pushvalue( this->hLuaHandle_ , -1 );
	lua_setfield( this->hLuaHandle_ , -2, "__index" );
	luaL_setfuncs( this->hLuaHandle_ , Methods, 0 );
	lua_pop( this->hLuaHandle_ , 1 );

	return true;
}
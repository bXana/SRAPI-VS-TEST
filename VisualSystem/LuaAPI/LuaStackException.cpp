#include "LuaStackException.hpp"
using namespace LuaAPI;

#pragma warning( disable : 4996 )

#define LUA_STACK_CORRUPTER_ERROR (const char*)"Error: Stack is corrupted\n"
#define LUA_STACK_LIMIT_ERROR (const char*)"Error: Exceeded the number of arguments to the stack"

CLuaStackException::CLuaStackException( lua_State* LuaHandle, const unsigned int ArgsCount ) {
	if( ArgsCount > LUA_MINSTACK )
		throw LUA_STACK_LIMIT_ERROR;

	this->hLuaHandle_ = LuaHandle;
	this->StackSize_  = lua_gettop( LuaHandle );
}

CLuaStackException::CLuaStackException( lua_State* LuaHandle ) {
	this->hLuaHandle_ = LuaHandle;
	this->StackSize_  = lua_gettop( LuaHandle );
}

CLuaStackException::~CLuaStackException( void )
{
	if( StackSize_ != lua_gettop( this->hLuaHandle_ ) )
		throw LUA_STACK_CORRUPTER_ERROR;
}


CLuaStackNormaliser::CLuaStackNormaliser( lua_State* LuaHandle ) {
	this->hLuaHandle_ = LuaHandle;
	this->StackSize_  = lua_gettop( LuaHandle );
}

CLuaStackNormaliser::~CLuaStackNormaliser( void ) {
	lua_settop( this->hLuaHandle_, this->StackSize_ );
}

CLuaException::CLuaException( 		
	const char* Fmt,
	... ) {
	va_list ArgPointer;
	va_start(ArgPointer, Fmt);
	vsnprintf( this->ErrMsg_, sizeof(this->ErrMsg_), Fmt, ArgPointer);
	va_end(ArgPointer);
}
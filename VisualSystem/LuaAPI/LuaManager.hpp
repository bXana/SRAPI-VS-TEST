///////////////////////////////////////
//		Lua Manager ver.2.0.
//		Author: bAnXZ
//		Description:
// 		Lua Interact Interface 
///////////////////////////////////////
#ifndef _LUAMANAGER_HPP_
#define _LUAMANAGER_HPP_

#include "LuaInclude.hpp"

namespace LuaAPI
{
	class ILuaManager
	{
		public:
			virtual ~ILuaManager( void ) = 0;

			virtual void __cdecl ExecuteScripts( const unsigned int ScriptsCount, ... ) = 0;
			virtual void* __thiscall CreateObject( const char* ObjectName, const unsigned int ObjectSize, luaL_Reg* Methods, const char* MetatableName ) = 0;
			virtual bool __thiscall CreateMetaTableObject( luaL_Reg* Methods, const char* MetatableName ) = 0;  
			virtual const char* __thiscall GetVersion( void ) = 0;
			virtual lua_State*  __thiscall GetHandle( void ) = 0;
	};
	
	class CLuaManager : public ILuaManager
	{
		lua_State* hLuaHandle_;

		public:
					 CLuaManager( void );
			virtual ~CLuaManager( void );

			virtual void __cdecl ExecuteScripts( const unsigned int ScriptsCount, ... );
			virtual void* __thiscall CreateObject( const char* ObjectName, const unsigned int ObjectSize, luaL_Reg* Methods, const char* MetatableName );
			virtual bool __thiscall CreateMetaTableObject( luaL_Reg* Methods, const char* MetatableName );
			virtual const char* __thiscall GetVersion( void );
			virtual lua_State*  __thiscall GetHandle( void );
	};
}

#endif

///////////////////////////////////////
//		Lua Stack Exception ver.1.0.
//		Author: bAnXZ
//		Rus Description:
// 		Генерирует исключение, если целостность стека нарушена в пределах функции
///////////////////////////////////////
#ifndef _LUASTACKEXCEPTION_HPP_
#define _LUASTACKEXCEPTION_HPP_

#include "LuaInclude.hpp"

namespace LuaAPI
{
	class CLuaStackException
	{
		private:
			int StackSize_;
			lua_State* hLuaHandle_;
		public:
			CLuaStackException( lua_State* LuaHandle, const unsigned int ArgsCount );
			CLuaStackException( lua_State* LuaHandle );
		   ~CLuaStackException( void );

	};

	class CLuaStackNormaliser
	{
		private:
			int StackSize_;
			lua_State* hLuaHandle_;
		public:
			CLuaStackNormaliser( lua_State* LuaHandle );
		   ~CLuaStackNormaliser( void );

	};

	class CLuaException {
		char ErrMsg_[256];
	
		public:
			CLuaException( 		
			const char* Fmt,
			... );
	
			inline const char* __thiscall ErrMsg( void ) { return this->ErrMsg_; }
	};
}

//#define VS_LUASTACKEXCEPTION_CHECK

#ifdef VS_LUASTACKEXCEPTION_CHECK
	#define LuaStackExceptionV( VarName, ArgsCount, LHandle ) LuaAPI::CLuaStackException VarName( LHandle, ArgsCount );
	#define LuaStackException( VarName, LHandle ) LuaAPI::CLuaStackException VarName( LHandle );
#else
	#define LuaStackExceptionV( VarName, ArgsCount, LHandle )
	#define LuaStackException( VarName, LHandle )
#endif

#endif
#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include "../Params.hpp"
#define SR_API __thiscall

enum E_DOMSERIES
{
	TBLAZER = 0,
	TKELLER = 1,
	TTERRON = 2
};

class C_OBJECT  {
	protected:
		PVoid pObject;
};


#endif


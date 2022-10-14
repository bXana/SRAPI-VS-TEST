#include "ConVar.hpp"
#include "ExceptionManager.hpp"

CConVar::CConVar( const char* VarName, void* CallbackFunction, const UInt ArgsCount, const char* Description ) {
	this->CallbackFunction_ = CallbackFunction;
	this->VarName_	= VarName;
	this->ArgsCount_ = ArgsCount;
	this->VarDescription_ = Description;
}

const char* Thiscall CConVar::VarName( void ) {
	return this->VarName_;
}


void* Thiscall CConVar::Execute( const void* VPointer  ) {
	UInt* ArgPointer = (UInt*)VPointer;
	ArgPointer	    += this->ArgsCount_;
	UInt UArgsCount  = this->ArgsCount_;

	void* Function = this->CallbackFunction_;
		__asm
		{
			mov eax, UArgsCount
			mov edx, [ArgPointer]
			back_:
			cmp eax, 0
			jz exit_;
			mov ebx, [edx]
			push ebx
			dec eax
			sub edx, 0x4
			jmp back_
			exit_:
			call [Function] // must be Stdcall

			mov UArgsCount, eax
		}

		return (void*)UArgsCount;
}

const UInt  Thiscall CConVar::ArgsCount( void ) {
	return this->ArgsCount_;
}

const char* Thiscall CConVar::Description( void ) {
	return this->VarDescription_;
}
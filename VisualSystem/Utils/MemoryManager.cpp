#include <Windows.h>
#include "MemoryManager.hpp"

using namespace Win32Utils;

#pragma warning( disable : 4482 )

#define SIGN_MIN (unsigned char)'0'
#define SIGN_MAX (unsigned char)'F'
#define SIGN_ERROR (const char*)"Error: bad signature"

CPattern::CPattern( const char* Bytes ) {
	unsigned int SignSize = 0;
	unsigned char* Signature = new unsigned char[ strlen( (const char*)Bytes ) + 1 ];
	unsigned char* Mask		 = new unsigned char[ strlen( (const char*)Bytes ) + 1 ];
	for( const unsigned char* Byte = (const unsigned char*)Bytes; 
		 Byte[0] != '\0' && Byte[1] != '\0'
		 ; Byte++ )
	{
		if( *Byte == 0x20 ) // space
			continue;
		else if( *Byte == '\?' )
		{
			Mask[SignSize] = '\?';
			Signature[SignSize] = (unsigned char)0x0;
			++SignSize;
			continue;
		}
		else if ( *Byte   > SIGN_MAX ||
				  Byte[1] > SIGN_MAX ||
				  *Byte	  < SIGN_MIN ||
				  Byte[1] < SIGN_MIN )
				{
					delete[ ] Signature;
					delete[ ] Mask;
					throw SIGN_ERROR;
				}

		Mask[SignSize] = 'x';
		Signature[SignSize] = (unsigned char)strtoul( (const char*)Byte, NULL, 16 );
		++SignSize;
		++Byte;
	}
	this->Signature_ = new unsigned char[ SignSize ];
	this->Mask_		 = new unsigned char[ SignSize ];
	this->SignatureSize_ = SignSize;

	memcpy( Signature_, Signature, SignSize );
	memcpy( Mask_, Mask, SignSize );

	delete[] Signature;
	delete[] Mask;
}

CPattern::~CPattern( void ) {
	if( this->Mask_ )
		delete[ ] Mask_;

	if( this->Signature_ )
		delete [ ] Signature_;
}


inline unsigned int __stdcall CheckSignature(
	 const unsigned char* Address,
	 const unsigned char* Signature,
	 const unsigned char* Mask,
	 const unsigned int MaskSize
	 ) {
		 unsigned int BytesRead = 0;
		 for( 
			 unsigned int I = 0;
			 I < MaskSize;
			 I++, BytesRead++
			) {
				if( Mask[I] == '\?' ||
					Address[I] == Signature[I]
				  )
					continue;
				else
					return BytesRead;
			 }
	return BytesRead;
}


unsigned int __stdcall Win32Memory::FindSignature(
				const void* StartAddress,
				const unsigned int PageSize,
				const unsigned char* Signature,
				const unsigned char* Mask,
				const unsigned int SignSize,
				const void* AddrBuffer, // Finded signatures address
				const unsigned int AddrBufferLim //  Addr. download Limit
				) {
	CONST DWORD MaskSize = SignSize;
	PDWORD FindedSignatureAddress = (PDWORD)AddrBuffer;
	DWORD FindedSignaturesCount = 0;
	DWORD BytesRead = 0;
	for( 
		PBYTE StartAddress_ = (PBYTE)StartAddress;
		(DWORD)StartAddress_ <= (DWORD)StartAddress + (DWORD)PageSize - MaskSize;
	   ) {
		   BytesRead = CheckSignature( StartAddress_, Signature, Mask, MaskSize );
		   if( BytesRead == MaskSize )
		   {
			   FindedSignatureAddress[ FindedSignaturesCount ] = (DWORD)StartAddress_;
			   FindedSignaturesCount++;
			   if( FindedSignaturesCount >= AddrBufferLim )
				   break;
		   }

		   StartAddress_ += ( BytesRead + 1 );
	   }

	return FindedSignaturesCount;
}

unsigned int __stdcall Win32Memory::FindSignature(
				const void* StartAddress,
				const unsigned int PageSize,
				CPattern* Pattern,
				const void* AddrBuffer, // Finded signatures address
				const unsigned int AddrBufferLim //  Addr. download Limit
				) {
					return Win32Memory::FindSignature( 
						StartAddress, 
						PageSize, 
						Pattern->Signature(), 
						Pattern->Mask(),
						Pattern->Size(),
						AddrBuffer,
						AddrBufferLim
						);
}

RedirectionManager::RedirectionManager( void )
{
	this->JumpAddress_ = 0;
	this->RedirectionStatus_ = REDIRECTION_INACTIVE;
}
RedirectionManager::~RedirectionManager( void )
{
	this->CloseJump( );
}

void __thiscall RedirectionManager::CreateJump( 
	const void* JumpAddress,
	const void* EndAddress,
	const E_REDIRECTION_COMMAND_TYPE eCommandType
	)
{
	if( this->RedirectionStatus_ == REDIRECTION_ACTIVE )
		return;

	BYTE Command;
	switch( eCommandType )
	{
		case E_REDIRECTION_COMMAND_TYPE::REDIRECTION_JMP:
			Command = 0xE9;
			break;
		case E_REDIRECTION_COMMAND_TYPE::REDIRECTION_CALL:
			Command = 0xE8;
			break;
		default:
			return;
	}
	this->JumpAddress_ = (unsigned int)JumpAddress;
	memcpy( this->OriginalBytes, JumpAddress, sizeof(OriginalBytes) );
	DWORD OldProtect = 0;
	DWORD EndAddress_ = (DWORD)EndAddress;
	DWORD JumpBytes    = EndAddress_ + ( (-1)*( (DWORD)JumpAddress + (DWORD)5 ) );
	VirtualProtectEx( GetCurrentProcess(), (LPVOID)JumpAddress, sizeof(OriginalBytes), 
		PAGE_EXECUTE_READWRITE, &OldProtect 
		);
	__asm
	{
		mov eax, [JumpAddress]
		mov ebx, [JumpBytes]
		mov cl, [Command]
		mov [eax + 0x0], cl
		mov [eax + 0x1], ebx
	}
	VirtualProtectEx( GetCurrentProcess(), (LPVOID)JumpAddress, sizeof(OriginalBytes), 
		OldProtect, &EndAddress_ 
		);
	this->RedirectionStatus_ = REDIRECTION_ACTIVE;
}

void __thiscall RedirectionManager::CloseJump( void )
{
	if( this->RedirectionStatus_ == REDIRECTION_ACTIVE )
	{
		DWORD OldProtect = 0, OldProtect2 = 0;

		VirtualProtectEx( 
			GetCurrentProcess(), (LPVOID)JumpAddress_, sizeof(OriginalBytes), 
			PAGE_EXECUTE_READWRITE, &OldProtect2 
			);
		memcpy( (void*)JumpAddress_, OriginalBytes, sizeof(OriginalBytes) );

		VirtualProtectEx( 
			GetCurrentProcess(), (LPVOID)JumpAddress_, sizeof(OriginalBytes), 
			OldProtect,&OldProtect2 
			);
		this->RedirectionStatus_ = REDIRECTION_INACTIVE;
	}
}

void* __stdcall RedirectionManager::GetEndJmpAddress( const void* CommandAddress ) {
	PBYTE EncodedBytes = (PBYTE)CommandAddress;
	++EncodedBytes;
	return (PVOID)( *(unsigned int*)EncodedBytes + (unsigned int)CommandAddress + (unsigned int)5 );
}
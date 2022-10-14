

#ifndef _MEMORYMANAGER_HPP_
#define _MEMORYMANAGER_HPP_

namespace Win32Utils {
	class CPattern
	{
		private:
			unsigned int   SignatureSize_;
			unsigned char* Signature_;
			unsigned char* Mask_;
		public:
		CPattern( const char* Bytes );
		 ~CPattern( void );
		inline unsigned char*   __thiscall Mask( void ) { return this->Mask_; }
		inline unsigned char*   __thiscall Signature( void ) { return this->Signature_; }
		inline unsigned int		__thiscall Size( void ) { return this->SignatureSize_; }
	};

	typedef class {
		public:
			
			static unsigned int __stdcall FindSignature(
				const void* StartAddress,
				const unsigned int PageSize,
				const unsigned char* Signature,
				const unsigned char* Mask,
				const unsigned int SignSize,
				const void* AddrBuffer, // Finded signatures address
				const unsigned int AddrBufferLim //  Addr. download Limit
				);

			static unsigned int __stdcall FindSignature(
				const void* StartAddress,
				const unsigned int PageSize,
				CPattern* Pattern,
				const void* AddrBuffer, // Finded signatures address
				const unsigned int AddrBufferLim //  Addr. download Limit
				);

	} Win32Memory ;

	enum E_REDIRECTION_COMMAND_TYPE
	{
		REDIRECTION_JMP	 = 0,
		REDIRECTION_CALL = 1
	};

	class RedirectionManager
	{
		private:
			enum
			{
				REDIRECTION_INACTIVE = 0,
				REDIRECTION_ACTIVE	 = 1
			} RedirectionStatus_;
			unsigned char OriginalBytes[5];
			unsigned int  JumpAddress_;
		public:
			RedirectionManager( void );
			~RedirectionManager( void );

			void __thiscall CreateJump( 
				const void* JumpAddress,
				const void* EndAddress,
				const E_REDIRECTION_COMMAND_TYPE eCommandType
				);

			void __thiscall CloseJump( void );


			static void* __stdcall GetEndJmpAddress( const void* CommandAddress );  

	public:

	};
}

#endif
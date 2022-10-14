

#ifndef _PROCESSMANAGER_HPP_
#define _PROCESSMANAGER_HPP_

/*
#define DECLARE_CLASS_( VType ,Var )  \
	private:						    \
		VType Var;						\
	public:								\
	VType Get##Var( void ) {					\
		return Var;						\
	}									\
										\
	void Set##Var( VType Arg ) {			\
		Var = Arg;						\
	}									
*/

namespace Win32Utils {
	typedef struct
	{
		void* Address;
		unsigned int Size;

		/*
		DECLARE_CLASS_( void* , Address_ );
		DECLARE_CLASS_( unsigned int, Size_ );

		Win32ModuleInformation& operator =( const Win32ModuleInformation& Module );
		*/
	} Win32ModuleInformation, *PWin32ModuleInformation;



	typedef class
	{
		public:
		static bool __stdcall GetProcessId( 
			const char* ProcessName,
			unsigned int* TargetProcessId
		);

		static bool __stdcall GetModuleInformation(
			const int ProcessId,
			const char* ModuleName,
			const PWin32ModuleInformation ModuleInfo // ModuleInfo buffer
		);

		// Получение основного потока
		static bool __stdcall GetProcessGeneralThread(
			const int ProcessId,
			unsigned int* TargetThreadId
		);			
			
	} Win32Process;
}


#endif
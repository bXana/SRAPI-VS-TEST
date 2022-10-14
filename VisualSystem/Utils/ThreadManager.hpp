#ifndef _THREADMANAGER_HPP_
#define _THREADMANAGER_HPP_

namespace Win32Utils {

	typedef class
	{
		public:
			static bool __stdcall SuspendThread(
				const unsigned int ThreadId
			);
			
			static bool __stdcall ResumeThread(
				const unsigned int ThreadId
			);
				
			static bool __stdcall TerminateThread(
				const unsigned int ThreadId
			);
			
	} Win32Thread;
	
}

#endif
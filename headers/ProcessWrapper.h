#ifndef PROCESS_WRAPPER
#define PROCESS_WRAPPER
#include <windows.h>
#include <string>

namespace QTools{
	namespace ProcessWrapper{
		/**
		 * Return an HWND of a given process. May not give correct window if multiple instances of a process are open.
		 * @param  p_name name of process
		 * @return        handle to a window of that process
		 */
		HWND retrieveHWND(std::string p_name);

		/**
		 * Retrieve a handle to a process
		 * @param  std::string name of process
		 * @return             handle
		 */
		HANDLE retrieveHandle(std::string);
	}
}

#endif
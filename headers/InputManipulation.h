#ifndef INPUT_MANIP
#define INPUT_MANIP

#include "windows.h"
#include <string>

namespace QTools {
	namespace InputManipulation {
		/**
		 * Performs a click at the given coordinates. First the mouse is moved to given coordinate then
		 * a click is performed
		 * @param  x       x coordinate
		 * @param  y       y coordinate
		 * @param  process handle to a window of a process
		 * @return         whether or not click was perfomed. Will return false if handle is 0x0 
		 */
		bool ClickHere(int x, int y, HWND process);

		/**
		 * Sends event message while enumin through windows. Not currently functional
		 * @param x       [description]
		 * @param y       [description]
		 * @param process [description]
		 */
		void ExhaustiveClick(int x, int y, HWND process);

		/**
		 * Moves the mouse cursor to the given coordinates
		 * @param  x       
		 * @param  y       
		 * @param  process handle to window of a process
		 * @return         0 if process is not 0x0 otherwise -1
		 */
		int MoveHere(int x, int y, HWND process);
	}
}

#endif
#ifndef SCREEN_CAP
#define SCREEN_CAP

#include <string>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
namespace QTools{
	namespace ScreenCap{
		// default codec for saving bitmaps
		const CLSID codec = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };

		/**
		 * Takes a snapshot of a the window that correpsonds to the given window handle
		 * @param  m           pointer to bitmap pointer. Necessary to make modifications in other files and prevent memory leaks
		 * @param  main_window handle to window
		 * @return             0 if successful, else failed
		 */
		int takeSnapshot(Gdiplus::Bitmap** m, HWND main_window);
	}
}

#endif
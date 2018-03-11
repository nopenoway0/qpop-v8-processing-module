#include "ScreenCap.h"
#include <tchar.h>
#include <psapi.h>

//#include <img_processing.h>

namespace QTools{
	namespace ScreenCap{

		/**
		 * Saves HBITMAP to a file
		 * @param  hbmp      HBITMAP to save
		 * @param  file_name name of saved file
		 * @return           0 on complete 1 if error occurs
		 */
		inline int saveHBITMAP(HBITMAP hbmp, std::string file_name){
		   	const CLSID codec = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };
			Gdiplus::Bitmap img(hbmp, NULL); 
			int size = file_name.length();
			wchar_t* name = new wchar_t[size + 1];
			swprintf(name, size + 1, L"%s", file_name.c_str());
			int status = img.Save(name, &codec, NULL);
			if(status){
				return 1;
			}
			return 0;
		}

		int takeSnapshot(Gdiplus::Bitmap** m, HWND main_window){
			if(main_window == 0)
				return -1;
			RECT dimensions;
			delete *m; // clear old image

			if (GetWindowRect(main_window, &dimensions) == 0)
				return -2;

			//***********************************************************************************************************************
			//http://stackoverflow.com/questions/7292757/how-to-get-screenshot-of-a-window-as-bitmap-object-in-c : Davide Piras******
			//***********************************************************************************************************************
		    HDC hdcScreen = GetDC(NULL);
			if (hdcScreen == NULL)
				return -3;
		    //Sets image size
		    HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, dimensions.right - dimensions.left, dimensions.bottom - dimensions.top);
			if (hbmp == NULL)
				return -4;
		   	HDC pic = CreateCompatibleDC(hdcScreen);
			if (pic == NULL)
				return -5;
			if (SelectObject(pic, hbmp) == NULL)
				return -6;
			if(!PrintWindow(main_window, pic, PW_CLIENTONLY)){
				delete *m;
				*m = nullptr;
				//main_window = 0; //if this fails, the process must be closed
				DeleteDC(pic);
				DeleteDC(hdcScreen);
				DeleteObject(hbmp);
				CloseHandle(main_window);
				return -7;
			}
			//***********************************************************************************************************************
			//http://stackoverflow.com/questions/7292757/how-to-get-screenshot-of-a-window-as-bitmap-object-in-c : Davide Piras******
			//***********************************************************************************************************************
		    *m = Gdiplus::Bitmap::FromHBITMAP(hbmp, NULL);
		    DeleteDC(pic);
		    DeleteDC(hdcScreen);
		    DeleteObject(hbmp);
			return 0;
		}
	}
}

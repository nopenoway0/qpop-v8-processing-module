#include "InputManipulation.h"

namespace QTools {
	namespace InputManipulation {
		typedef struct coordinates {
			int x;
			int y;
		} coordinates;

		int MoveHere(int x, int y, HWND process) {
			if (process != 0)
			{
				WINDOWINFO info = { sizeof(WINDOWINFO) };
				POINT currentPos;
				GetCursorPos(&currentPos);
				GetWindowInfo(process, &info);
				SetCursorPos(info.rcWindow.left + x, info.rcWindow.top + y);
				return 0;
			}
			return -1;
		}

		bool ClickHere(int x, int y, HWND process) {
			if (process != 0) {
				MoveHere(x, y, process);
				LPINPUT inputs = new INPUT[2];
				inputs[0] = { INPUT_MOUSE, {0, 0, 0, MOUSEEVENTF_LEFTDOWN, 0} };
				inputs[1] = { INPUT_MOUSE,{ 0, 0, 0, MOUSEEVENTF_LEFTUP, 0 } };
				SendInput(2, inputs, sizeof(INPUT));
				return true;
			}
			return false;
		}

		BOOL CALLBACK ClickChildProc(HWND hwnd, LPARAM lparam) {
			coordinates* input = (struct coordinates*) lparam;
			WINDOWINFO pwi;
			pwi.cbSize = sizeof(WINDOWINFO);
			int result = GetWindowInfo(hwnd, &pwi);
			if (result == 0) 
				return false;
			else
				ClickHere(input->x, input->y, hwnd);
			return true;
		}

		void ExhaustiveClick(int x, int y, HWND process) {
			coordinates input;
			input.x = x;
			input.y = y;
			if (process != 0) EnumChildWindows(process, &ClickChildProc, (LPARAM)&input);
		}


	}
}
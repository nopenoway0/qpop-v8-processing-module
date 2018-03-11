#include "ProcessWrapper.h"
#include <tchar.h>
#include <psapi.h>

namespace QTools{
	namespace ProcessWrapper{

		typedef struct handle_data{
			HWND window;
			DWORD pid;
		}handle_data;

		BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam){
			DWORD pid = 0;
			GetWindowThreadProcessId(hwnd, &pid);
			handle_data* data = (handle_data*) lParam;
			if(data->pid == pid){
				data->window = hwnd;
				//********************************************************
				//Make sure window is bigger than minimized version
				RECT dimensions;
				GetWindowRect(hwnd, &dimensions);
				/*if(dimensions.right - dimensions.left > 400 && dimensions.bottom - dimensions.top > 400){
					return FALSE;
				}*/
				//return TRUE;
				return FALSE;
				//********************************************************
				
			}
			return TRUE;
		}

		HWND retrieveHWND(std::string p_name){
			//***********************************Seperate into utility funciton************************************
			//*************************************Find PID with process name**************************************
			DWORD* list_processes = (DWORD*) malloc(sizeof(DWORD) * 4096);
			DWORD bytes_returned;
			if(!EnumProcesses(list_processes, sizeof(DWORD) * 4096, &bytes_returned)){
				return 0;
			}
			//Print all processes
			HANDLE process;
			HMODULE* modules = (HMODULE*) calloc(bytes_returned, sizeof(HMODULE));
			//DWORD bytes_required;
			DWORD pid = -1;
			char* name = (char*) calloc(40, sizeof(char));

			for(int x = 0; x < (bytes_returned / sizeof(DWORD)); x++){
				process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, list_processes[x]);
				if( NULL == process){
				}
				if(!GetModuleBaseNameA(process, NULL, name, 20)){
				}
				if(!(p_name.compare(std::string(name)))){
					pid = list_processes[x];
					break;
				}
				CloseHandle(process);
			}

			free(name);
			free(modules);
			free(list_processes);
			//*************************************************************************************************************
			
			if(pid == (DWORD) -1){
				return 0;
			} 

			//add check for failure
			handle_data* data = (handle_data*) calloc(1, sizeof(handle_data));

			data->pid = pid;
			if(EnumWindows(WNDENUMPROC (*EnumWindowsProc), (LPARAM) data)){
				free(data);
				return 0;
			}
			HWND result = data->window;
			free(data);
			return result;
		}

		HANDLE retrieveHandle(std::string p_name){
			DWORD* list_processes = (DWORD*)malloc(sizeof(DWORD) * 4096);
			DWORD bytes_returned;
			if (!EnumProcesses(list_processes, sizeof(DWORD) * 4096, &bytes_returned)) {
				return 0;
			}
			//Print all processes
			HANDLE process;
			HMODULE* modules = (HMODULE*)calloc(bytes_returned, sizeof(HMODULE));
			//DWORD bytes_required;
			DWORD pid = -1;
			char* name = (char*)calloc(40, sizeof(char));
			bool found = false;
			for (int x = 0; x < (bytes_returned / sizeof(DWORD)); x++) {
				process = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, list_processes[x]);
				if (NULL == process) {
				}
				if (!GetModuleBaseNameA(process, NULL, name, 20)) {
				}
				if (!(p_name.compare(std::string(name)))) {
					pid = list_processes[x];
					found = true;
					break;
				}
				CloseHandle(process);
			}
			free(name);
			free(modules);
			free(list_processes);
			if (found)
				return process;
			CloseHandle(process);
			return nullptr;
		}
	}
}

#include "memory.h"

bool memory::setProcessHandle(const wchar_t* name) {
	pId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 pEntry = { 0 };
	pEntry.dwSize = sizeof(pEntry);
	if (Process32First(hSnap, &pEntry)) {
		for (; Process32Next(hSnap, &pEntry); ) {
			if (!wcscmp(pEntry.szExeFile, name)) {
				CloseHandle(hSnap);
				pId = pEntry.th32ProcessID;
				pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pId);
				return true;
			}
		}
	}
	return false;
}

bool memory::setModuleInfo(const wchar_t* name) {
	MODULEENTRY32 modEntry = { 0 };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pId);
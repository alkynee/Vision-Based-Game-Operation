#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include <unordered_map>

struct patternStruct {
	const char* pattern, * mask;
	const wchar_t* moduleName;
	bool relative;
	int extra;
	std::vector<int> offsets;
};

class memory {
private:
	bool setProcessHandle(const wchar_t* name);
	bool setModuleInfo(const wchar_t* name);
	unsigned long patternScan(const char* pattern, const char* mask, const unsigned long begin, const unsigned long size);
public:
	memory();
	~memory();

	std::unordered_map<const wchar_t*, std::pair<unsigned long, unsigned long>> modules;

	HANDLE pHandle;
	int pId;

	bool init(const wchar_t* pName, std::vector<const wchar_t*> moduleNames);
	unsigned long getOffset(const pa
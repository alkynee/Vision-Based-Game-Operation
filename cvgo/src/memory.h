#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include <unordered_map>

struct patternStruct {
	const char* pattern, * mask;
	const wchar
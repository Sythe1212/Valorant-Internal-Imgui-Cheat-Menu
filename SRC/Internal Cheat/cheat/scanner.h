#pragma once
#include "etc.h"

#define RVA(addr, size) ((PBYTE)(addr + *(DWORD*)(addr + ((size) - 4)) + size))

class Scanner {
public:
	PIMAGE_NT_HEADERS getHeader(HMODULE base);
	PBYTE FindPattern(HMODULE mxdule, LPCSTR pattern, LPCSTR mask);
	
	HMODULE moduleBase;
};

inline Scanner* g_Scanner = new Scanner;


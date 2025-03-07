#include "scanner.h"

PIMAGE_NT_HEADERS Scanner::getHeader(HMODULE mxdule) {
	return (PIMAGE_NT_HEADERS)((PBYTE)mxdule + PIMAGE_DOS_HEADER(mxdule)->e_lfanew);
}

PBYTE Scanner::FindPattern(HMODULE mxdule, LPCSTR pattern, LPCSTR mask) {

	size_t size = getHeader(mxdule)->OptionalHeader.SizeOfImage;

	auto checkMask = [](PBYTE buffer, LPCSTR pattern, LPCSTR mask) -> BOOL
	{
		for (auto x = buffer; *mask; pattern++, mask++, x++) {
			auto addr = *(BYTE*)(pattern);
			if (addr != *x && *mask != '?')
				return FALSE;
		}

		return TRUE;
	};

	for (auto x = 0; x < size - strlen(mask); x++) {

		auto addr = (PBYTE)mxdule + x;
		if (checkMask(addr, pattern, mask))
			return addr;
	}

	return NULL;
}

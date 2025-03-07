#pragma once

#include "etc.h"

class render {
public:
	void execute(HMODULE mxdule);
	short DiscordGetAsyncKeyState(const int vKey);
};

inline render* g_Render = new render;
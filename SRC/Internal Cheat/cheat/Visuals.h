#pragma once
#include "etc.h"
#include "exploits.h"
#include "aimbot.h"
#include "VisualsHelper.h"
#include "GameSDK.h"
#include <string>

class Visuals
{
public:

	void DrawMenu();
	void Entity();
	

};

inline Visuals* g_Visuals = new Visuals;
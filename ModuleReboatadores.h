#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL_rect.h"

class ModuleRebotadores : public Module
{
public:
	ModuleRebotadores(Application* app, bool start_enabled = true);
	virtual ~ModuleRebotadores();	

	void Rebote_1(PhysBody* bodyA, PhysBody* bodyB, int velocity);

};
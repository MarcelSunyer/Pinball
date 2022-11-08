#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "SDL/include/SDL_rect.h"

struct Bat
{
	PhysBody* Rect;
	PhysBody* Circle;
	bool rightSide;
};

struct Muelle
{
	PhysBody* pivot;
	PhysBody* mobile;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	p2List<Bat*> bats;
	SDL_Rect rectSect = { 48, 250, 64, 20 };
};
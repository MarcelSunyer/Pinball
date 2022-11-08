#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:

	// Constructors & Destructors
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	// Lists of physics objects
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> chain_carcasa;
	p2List<PhysBody*> mitg;



	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	PhysBody* prueva;
	bool sensed;

	// Textures
	
	SDL_Texture* t_carcasa;
	SDL_Texture* t_mitg;
	SDL_Texture* t_map;
	SDL_Texture* t_bola;
	

	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};

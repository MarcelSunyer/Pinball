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
	p2List<PhysBody*> collider_carcasa;
	p2List<PhysBody*> collider_mitg;
	p2List<PhysBody*> collider_palanca_d;
	p2List<PhysBody*> collider_palanca_e;
	p2List<PhysBody*> collider_dreta_s;
	p2List<PhysBody*> collider_dreta_i;
	p2List<PhysBody*> collider_esquerra_t;
	p2List<PhysBody*> collider_pivot_1;
	p2List<PhysBody*> collider_pivot_2;
	p2List<PhysBody*> collider_pivot_3;
	p2List<PhysBody*> collider_pivot_4;
	p2List<PhysBody*> collider_pivot_5;




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

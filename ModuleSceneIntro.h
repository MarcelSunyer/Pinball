#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModulePhysics.h"

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
	
	p2List<PhysBody*> collider_pivot_i;
	p2List<PhysBody*> collider_pivot_c;
	
	
	PhysBody* collider_flipper_i;
	PhysBody* ref_i;
	b2RevoluteJoint* collider_flipper_joint_i;

	PhysBody* collider_flipper_d;







	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	
	PhysBody* prueva;
	bool sensed;

	// Textures
	
	SDL_Texture* t_carcasa;
	SDL_Texture* t_mitg;
	SDL_Texture* t_map;
	SDL_Texture* t_bola;
	SDL_Texture* t_flipper_e;
	
	PhysBody* collider_rebotador_1;
	SDL_Texture* t_rebotador_1;
	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};

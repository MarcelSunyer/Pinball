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
	PhysBody* circles;
	PhysBody* boxes;
	PhysBody* collider_carcasa;
	PhysBody* collider_mitg;
	PhysBody* collider_palanca_d;
	PhysBody* collider_palanca_e;
	PhysBody* collider_dreta_s;
	PhysBody* collider_dreta_i;
	PhysBody* collider_esquerra_t;
	
	PhysBody* collider_pivot_i;
	PhysBody* collider_pivot_c;
	
	
	p2List <PhysBody*> collider_inici_1;
	p2List <PhysBody*> collider_inici_2;
	
	PhysBody* collider_detector_i;

	b2Vec2 resetPos;
	b2Vec2 initMPos;
	b2Vec2 initMaxPos;


	PhysBody* collider_flipper_i;
	PhysBody* ref_i;
	b2RevoluteJoint* collider_flipper_joint_i;
	
	PhysBody* collider_flipper_d;
	PhysBody* ref_d;
	b2RevoluteJoint* collider_flipper_joint_d;

	PhysBody* disparo;
	PhysBody* ref_dis;
	b2PrismaticJoint* disparo_p;

	PhysBody* alien;
	PhysBody* ref_alien;
	b2PrismaticJoint* rebote;


	PhysBody* dead;

	PhysBody* muelle;
	PhysBody* muelle_max;



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
	SDL_Texture* t_flipper_d;
	SDL_Texture* t_alien;
	SDL_Texture* t_meteorito;

	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;
};

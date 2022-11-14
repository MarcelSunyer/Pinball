#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	b2Vec2 a = { -0.44, 0 };
	b2Vec2 b = { 0, 0 };

	//Bats------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	Bat* f1 = new Bat;
	f1->Circle = App->physics->CreateCircle(173, 675, 4, b2_staticBody);
	f1->Rect = App->physics->CreateRectangle(163 + rectSect.w / 2, 665 + rectSect.h / 2, rectSect.w, rectSect.h - 10, b2_dynamicBody);
	f1->rightSide = false;
	App->physics->CreateRevoluteJoint(f1->Rect, a, f1->Circle, b, 35.0f);
	bats.add(f1);

	Bat* f = new Bat;
	f->Circle = App->physics->CreateCircle(55, 435, 4, b2_staticBody);
	f->Rect = App->physics->CreateRectangle(40 + rectSect.w / 2, 420 + rectSect.h / 2, rectSect.w, rectSect.h - 10, b2_dynamicBody);
	f->rightSide = false;
	App->physics->CreateRevoluteJoint(f->Rect, a, f->Circle, b, 35.0f);
	bats.add(f);

	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		p2List_item<Bat*>* f = bats.getFirst();
		while (f != NULL)
		{
			if (f->data->rightSide == false)
			{
				f->data->Rect->body->ApplyForce({ -3,0 }, { 0,0 }, true);
			}
			f = f->next;
		}
	}
	return UPDATE_CONTINUE;
}




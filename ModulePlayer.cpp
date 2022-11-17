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
	//Load Textures
	ballTexture = App->textures->Load("pinball/ball.png");

	//Bats------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	b2Vec2 a = { -0.44, 0 };
	b2Vec2 b = { 0, 0 };
	
	//Bate izquierda-abajo
	Bat* f1 = new Bat;
	f1->Circle = App->physics->CreateCircle(173, 675, 4, b2_staticBody);
	f1->Rect = App->physics->CreateRectangle(163 + rectSect.w / 2, 665 + rectSect.h / 2, rectSect.w, rectSect.h - 10, b2_dynamicBody);
	f1->rightSide = false;
	App->physics->CreateRevoluteJoint(f1->Rect, a, f1->Circle, b, 35.0f);
	bats.add(f1);

	//Bate izquierda-arriba
	Bat* f = new Bat;
	f->Circle = App->physics->CreateCircle(55, 435, 4, b2_staticBody);
	f->Rect = App->physics->CreateRectangle(40 + rectSect.w / 2, 420 + rectSect.h / 2, rectSect.w, rectSect.h - 10, b2_dynamicBody);
	f->rightSide = false;
	App->physics->CreateRevoluteJoint(f->Rect, a, f->Circle, b, 35.0f);
	bats.add(f);

	b2Vec2 aR = { 0.44, 0 };
	b2Vec2 bR = { 0, 0 };

	//Bate derecha
	Bat* f2 = new Bat;
	f2->Circle = App->physics->CreateCircle(300, 675, 4, b2_staticBody);
	f2->Rect = App->physics->CreateRectangle(290 - rectSect.w / 2, 665 + rectSect.h / 2, rectSect.w, rectSect.h - 10, b2_dynamicBody);
	f2->rightSide = true;
	App->physics->CreateRevoluteJoint(f2->Rect, aR, f2->Circle, bR, 35.0f);
	bats.add(f2);

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


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
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		p2List_item<Bat*>* f = bats.getFirst();
		while (f != NULL)
		{
			if (f->data->rightSide == true)
			{
				f->data->Rect->body->ApplyForce({ 3,0 }, { 0,0 }, true);
			}
			f = f->next;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		balls.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8, b2_dynamicBody));
		balls.getLast()->data->listener = this;
	}


	//BLITS
	p2List_item<PhysBody*>* c = balls.getFirst();
	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ballTexture, x-5, y-5, &circleSect, true, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	p2List_item<Bat*>* f = bats.getFirst();
	while (f != NULL)
	{
		int x, y;
		f->data->Rect->GetPosition(x, y);

		App->renderer->Blit(ballTexture, x, y - 5, &rectSect, f->data->rightSide, 1.0f, f->data->Rect->GetRotation());

		f = f->next;
	}

	return UPDATE_CONTINUE;
}




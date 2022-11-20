#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleReboatadores.h"

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
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && pelota == 0)
	{
		balls.add(App->physics->CreateCircle(455 , 640, 10, b2_dynamicBody));
		balls.getLast()->data->listener = this;
		pelota += 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	{
		balls.add(App->physics->CreateCircle(mouse.x, mouse.y, 10, b2_dynamicBody));
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

	

	return UPDATE_CONTINUE;
}




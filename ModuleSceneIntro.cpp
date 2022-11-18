#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	ray_on = false;
	sensed = false;
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	// You should do some memory cleaning here, if required
}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	t_map = App->textures->Load("pinball/map.png");
	t_flipper_e = App->textures->Load("pinball/Flipper_esquerre.png");

	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT+23, SCREEN_WIDTH, 50, b2_dynamicBody);
	
	
	// Add this module (ModuleSceneIntro) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleSceneIntro::OnCollision()
	lower_ground_sensor->listener = this;


	
	int collider_point_carcasa[114] = {
		28, 15,	481, 14, 481, 738, 300, 741, 299, 722, 426, 629, 431, 621, 433, 611,
		434, 444, 422, 432,	440, 421, 438, 679, 443, 685, 451, 689, 458, 690, 463, 685,
		467, 678, 466, 178, 465, 161, 461, 137, 452, 119, 444, 109, 457, 101, 469, 87,
		476, 71, 476, 51, 467, 33, 455, 25, 440, 19, 422, 18, 405, 25, 393, 35,	386, 52,
		383, 62, 338, 51, 291, 47, 258, 47, 224, 48, 175, 59, 125, 82, 91, 115, 72, 139,
		47, 191, 41, 221, 40, 441, 55, 455, 59, 461, 54, 467, 44, 476, 45, 611,	48, 621,
		51, 626, 60, 636, 180, 721, 178, 739, 29, 736, 28, 16 };
	
	int collider_point_mitg[30] = {
		261, 365, 266, 356,	244, 314,237, 310,230, 311,	211, 353,	211, 360,	
		217, 365,	223, 363,	230, 352,	238, 349,	247, 351,	254, 362,	
		255, 367,	260, 366 };

	int collider_palanca_dreta[34] = {
		399, 612, 316, 676,	307, 664, 313, 658, 330, 647, 386, 605, 388, 600,
		385, 531, 390, 523, 396, 518, 403, 518, 407, 522, 409, 531, 408, 544,
		406, 595, 404, 604, 401, 609 };

	int collider_palanca_esquerra[32] = {
		92, 531, 89, 600, 91, 605, 170, 660, 170, 667, 163, 672,  156, 670, 
		83, 619, 76, 609, 71, 597, 69, 567, 70, 525, 73, 518, 79, 517, 84, 521,
		88, 525	};

	int collider_dreta_superior[64] = {
		417, 378, 425, 381, 428, 386, 429, 393,  433, 395, 440, 390, 441, 218, 
		441, 157, 431, 132, 421, 116, 405, 102, 390, 92, 370, 83, 348, 78, 324, 75,
		304, 76, 297, 79, 308, 83, 318, 88,	335, 97, 356, 112, 374, 128, 394, 154,
		408, 179, 423, 223, 428, 254, 429, 286, 426, 313, 418, 345, 411, 365, 410, 372,
		415, 377 };

	int collider_dreta_inferior[88] = {
		341, 336, 342, 330, 346, 324, 353, 317, 364, 306, 371, 291, 379, 272, 383, 255,
		385, 234, 381, 212, 374, 191, 363, 173, 347, 155, 331, 142, 315, 133, 303, 127,
		293, 117, 292, 108, 292, 104, 299, 106, 310, 111, 319, 115, 331, 123, 340, 129,
		347, 136, 357, 145, 365, 155, 372, 164, 378, 172, 383, 181, 390, 197, 396, 211,
		398, 226, 400, 241, 399, 266, 394, 292, 385, 312, 376, 328, 369, 340, 362, 349,
		353, 351, 345, 348, 341, 341, 341, 337 };

	int collider_esquerra[116] = {
		183, 262, 187, 258, 188, 252, 184, 244, 180, 233, 177, 218, 176, 204, 178, 185,
		182, 171, 187, 160, 195, 151, 203, 145, 210, 142, 213, 138, 213, 130, 213, 98,
		210, 93, 204, 93, 198, 95, 186, 101, 175, 108, 164, 117, 152, 132, 139, 152,
		132, 168, 125, 190, 121, 206, 119, 239, 120, 255, 122, 272, 125, 280, 128, 278,
		125, 271, 123, 260, 122, 244, 123, 224, 126, 210, 129, 199, 134, 186, 142, 171,
		153, 157, 164, 145, 173, 139, 182, 139, 188, 143, 189, 150, 186, 155, 181, 161,
		177, 168, 173, 176, 167, 189, 163, 205, 163, 216, 164, 230, 166, 244, 170, 254,
		177, 261, 181, 262 };

	int collider_pivote_izquiera[14] = {
		61, 258, 66, 261, 72, 259, 72, 239, 67, 235, 61, 239, 61, 257 };

	int collider_pivote_centre[14] = {
	237, 113, 240, 109, 240, 94, 236, 90, 232, 93, 232, 109, 236, 113 };

	int collider_flipper_dreta[16] = {
		10, 22,
	59, 40,
	65, 35,
	65, 28,
	51, 21,
	18, 6,
	10, 9,
	7, 15 };

	collider_carcasa = App->physics->CreateChain(0, 0, collider_point_carcasa, 114, b2_staticBody);
	collider_mitg = App->physics->CreateChain(0, 0, collider_point_mitg, 30, b2_staticBody);

	collider_palanca_d = App->physics->CreateChain(0, 0, collider_palanca_dreta, 34, b2_staticBody);
	collider_palanca_e = App->physics->CreateChain(0, 0, collider_palanca_esquerra, 32, b2_staticBody);

	collider_dreta_s = App->physics->CreateChain(0, 0, collider_dreta_superior, 64, b2_staticBody);
	collider_dreta_i = App->physics->CreateChain(0, 0, collider_dreta_inferior, 88, b2_staticBody);
	collider_esquerra_t = App->physics->CreateChain(0, 0, collider_esquerra, 116, b2_staticBody);

	collider_pivot_i = App->physics->CreateChain(15, -1, collider_pivote_izquiera, 14, b2_staticBody);
	collider_pivot_i = App->physics->CreateChain(0, 0, collider_pivote_centre, 14, b2_staticBody);
	collider_pivot_i = App->physics->CreateChain(30, 0, collider_pivote_centre, 14, b2_staticBody);


	//Flipper esquerra
	ref_i = App->physics->CreateRectangle(180, 675, 10, 10, b2_staticBody);
	collider_flipper_i = App->physics->CreateRectangle(210, 660, 60, 15, b2_dynamicBody);
	collider_flipper_joint_i = App->physics->CreateRevoluteJoint(ref_i, b2Vec2(0,0), collider_flipper_i, b2Vec2(-0.4, 0), 0, false, false);
	
	collider_flipper_joint_i->EnableLimit(true);
	collider_flipper_joint_i->SetLimits(-0.5, 0.3);
	
	//Flipper dreta
	ref_d = App->physics->CreateRectangle(300, 680, 10, 10, b2_staticBody);
	collider_flipper_d = App->physics->CreateRectangle(230, 660, 60, 15, b2_dynamicBody);
	collider_flipper_joint_d = App->physics->CreateRevoluteJoint(ref_d, b2Vec2(0,0), collider_flipper_d, b2Vec2(0.4, 0.07), 0, false, false);

	collider_flipper_joint_d->EnableLimit(true);
	collider_flipper_joint_d->SetLimits(-0.5, 0.3);


	t_rebotador_1 = App->textures->Load("pinball/bola1.png");
	//Load Textures

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(t_map, 0, 0);
	App->renderer->Blit(t_rebotador_1, 261, 192);
	// The target point of the raycast is the mouse current position (will change over game time)
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	
	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		collider_flipper_i->body->ApplyTorque(-50, true);
	else
	{
		collider_flipper_i->body->ApplyTorque(20, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		collider_flipper_d->body->ApplyTorque(50, true);
	else
	{
		collider_flipper_d->body->ApplyTorque(-20, true);
	}

	App->renderer->Blit(t_flipper_e, 160, 663);
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	App->audio->PlayFx(bonus_fx);

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
	
}

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFirstScene.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInit.h"
#include "ModuleHelicopterScene.h"
#include "ModuleElements1.h"

ModuleInit::ModuleInit()
{}

ModuleInit::~ModuleInit()
{}

// Load assets
bool ModuleInit::Start()
{
	LOG("Loading space scene");
	background_texture = App->textures->Load("assets/First_Scene.png");


	background.PushBack({ 1, 1, 220, 256 });
	background.PushBack({ 222, 1, 220, 256 });
	background.speed = 0.03f;

	LOG("Loading audio scene");
	music = App->music->LoadChunk("assets/Commando_01_Credit.wav");

	App->elements1->num_score = 0;

	return true;
}

// UnLoad assets
bool ModuleInit::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background_texture);
	
	return true;
}

// Update: draw background
update_status ModuleInit::Update()
{
	// Move camera forward -----------------------------


	// Draw everything --------------------------------------

	//App->render->Blit(background_texture, 0, 0, NULL);

	App->render->Blit(background_texture, 0, 0, &(background.GetCurrentFrame()), 0.75f);

	if ((App->input->keyboard[SDL_SCANCODE_1] == 1 || SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_START) == 1) && fading == false)
	{
		Mix_PlayChannel(-1, music, 0);
		App->fade->FadeToBlack(this, App->heli_scene, 2.0f);
		fading = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_2] == 1 && fading == false)
	{
		Mix_PlayChannel(-1, music, 0);
		App->fade->FadeToBlack(this, App->first_scene, 2.0f);
		fading = true;
		player_2 = true;
	}

	return UPDATE_CONTINUE;
}
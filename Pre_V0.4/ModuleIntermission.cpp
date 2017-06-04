#include "Globals.h" 
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFirstScene.h"
#include "ModuleInit.h"
#include "ModuleEndScene.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"
#include "ModuleSecondScene.h"
#include "ModuleIntermission.h"
#include "ModuleFonts.h"
#include <time.h>
#include <stdlib.h> 

ModuleIntermission::ModuleIntermission()
{
}


ModuleIntermission::~ModuleIntermission()
{
}

bool ModuleIntermission::Start()
{
	LOG("Loading intermission scene");

	intermission_back = App->textures->Load("assets/Intermission.png");
	intermission_front = App->textures->Load("assets/Intermission_1.png");
	intermission_front2 = App->textures->Load("assets/Intermission_2.png");
	srand(time(NULL));
	music = App->music->Load("assets/Commando_05_Stage_clear_Demo.ogg");
	Mix_PlayMusic(music, 100);

	App->fonts->Enable();
	text = App->fonts->Load("fonts/num_1.png", "abcdefghij 0123456789=", 2);

	//Intermission 1
	intermission.PushBack({ 1,1,48,64 });
	intermission.PushBack({ 50,1,48,64 });
	intermission.PushBack({ 99,1,48,64 });
	intermission.PushBack({ 50,1,48,64 });
	intermission.loop = true;
	intermission.speed = 0.02f;

	//Intermission 2
	intermission2.PushBack({ 1,1,31,62 });
	intermission2.PushBack({ 33,1,34,62 });
	intermission2.PushBack({ 68,1,37,62 });
	intermission2.PushBack({ 33,1,34,62 });
	intermission2.loop = true;
	intermission2.speed = 0.02f;

	timer = 0;

	return true;
}

update_status ModuleIntermission::Update()
{
	//previsional solution for a problem that send the camera to y=-1500
	if (App->inter_scene->IsEnabled() == true)
	{
		App->render->camera.x = 0;
		App->render->camera.y = 0;
	}
	App->render->Blit(intermission_back, 0, 0, nullptr, 0.75f);

	if (App->first_scene->IsEnabled() == false)	
	{
		++timer;
		App->render->Blit(intermission_front, 90, 130, &intermission.GetCurrentFrame());
	}

	if (timer >= 400) {
		if (App->first_scene->IsEnabled() == false)
		{
			App->fade->FadeToBlack(this, App->scene_map2, 2.0f);
			fading = true;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == 1 )
	{
		if (App->first_scene->IsEnabled() == false)
	{
			App->fade->FadeToBlack(this, App->scene_map2, 2.0f);
			fading = true;
	}

	}
	fading = true;
	player_2 = true;

	return UPDATE_CONTINUE;
}

bool ModuleIntermission::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(intermission_back);
	App->textures->Unload(intermission_front);
	App->textures->Unload(intermission_front2);
	App->player->Disable();
	App->fonts->Disable();

	return true;
}
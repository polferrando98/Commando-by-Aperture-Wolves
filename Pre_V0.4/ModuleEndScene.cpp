#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFirstScene.h"
#include "ModuleInit.h"
#include "ModuleEndScene.h"
#include "ModuleSecondScene.h"
#include "ModuleAudio.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"
#include "ModuleIntermission.h"

#include <stdio.h>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleEndScene::ModuleEndScene()
{}

ModuleEndScene::~ModuleEndScene()
{}

// Load assets
bool ModuleEndScene::Start()
{
	LOG("Loading space scene");

	background = App->textures->Load("assets/Rankings_empty.png");
	music = App->music->Load("assets/Commando_08_Name_Entry.ogg");
	Mix_PlayMusic(music, -1);
	num_1 = App->fonts->Load("fonts/num_1.png", "abcdefghij 0123456789=", 2);
	App->elements1->num_lives_play_1 = 3;

	App->scene_start->player_2 = false;

	return true;
}

// UnLoad assets
bool ModuleEndScene::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleEndScene::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, NULL);

	for (int i = 0; i < 7; i++)
	{
		sprintf_s(score, 10, "%7d", App->elements1->high_scores[i]);
		App->fonts->BlitText(60,(i*16)+ 112,num_1,score);
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == 1 && fading == false)
	{
		App->fade->FadeToBlack(this, App->scene_start, 2.0f);
		fading = true;
	}

	return UPDATE_CONTINUE;
}





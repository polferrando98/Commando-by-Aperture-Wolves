#include "Globals.h"
#include <time.h>
#include <stdlib.h>  
#include "Application.h"
#include "ModuleHelicopterScene.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFirstScene.h"
#include "ModuleInit.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleElements1.h"


ModuleHelicopterScene::ModuleHelicopterScene(){}
ModuleHelicopterScene::~ModuleHelicopterScene(){}

bool ModuleHelicopterScene::Start() {

	LOG("Loading heli scene");

	background = App->textures->Load("assets/Area1.png");
	textures = App->textures->Load("assets/PlaceHolder_Sprites.png");
	music = App->music->LoadChunk("assets/commando_24_.wav");
	Mix_PlayChannel(-1, music, 0);
	Mix_ExpireChannel(-1, 7000);

	App->elements1->Enable();



	player1.PushBack({421,163,29, 26});
	player1.PushBack({ 421,163,29, 26 });
	player1.PushBack({ 421,163,29, 26 });
	player1.loop = false;
	player1.speed = 0.1;

	heliPos = 1853;
	timer = 0;
	endScene = false;

	return true;
}

bool ModuleHelicopterScene::CleanUp() {

	LOG("Unloading heli scene");
	App->textures->Unload(background);
	App->textures->Unload(textures);
	App->elements1->Disable();
	return true;
}

update_status ModuleHelicopterScene::Update() {

	App->render->Blit(background, -16, -1908 + SCREEN_HEIGHT, NULL);
	App->render->Blit(textures, 100, 1600, &heli.GetCurrentFrame(), NULL);
	App->render->Blit(textures, 100, 1600, &heliWings.GetCurrentFrame(), NULL);


	if (App->input->keyboard[SDL_SCANCODE_C] == 1)
	{
		App->fade->FadeToBlack(this, App->first_scene, 2.0f);
		fading = true;
	}


	if (endScene) {		
		App->fade->FadeToBlack(this, App->first_scene, 2.0f);
		fading = true;
	}



	return UPDATE_CONTINUE;

}
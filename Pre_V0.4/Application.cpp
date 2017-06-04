#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleFirstScene.h"
#include "ModuleSecondScene.h"
#include "ModuleIntermission.h"
#include "ModuleEndScene.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleInit.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"
#include "ModuleHelicopterScene.h"


Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = scene_start = new ModuleInit();
	modules[i++] = heli_scene = new ModuleHelicopterScene();
	modules[i++] = first_scene = new ModuleFirstScene(); // Charge all the scenes before Player!!! if we don't do that the player will be under the background
	modules[i++] = scene_map2 = new ModuleSecondScene();
	modules[i++] = end_scene = new ModuleEndScene();
	modules[i++] = player_2 = new ModulePlayer2();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = enemies= new ModuleEnemies();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = music = new ModuleAudio();
	modules[i++] = elements1 = new ModuleElements1();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = inter_scene = new ModuleIntermission();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable all stopped modules here
	player->Disable();
	player_2->Disable();
	first_scene->Disable();
	scene_map2->Disable();
	end_scene->Disable();
	//music->Disable();
	collision->Disable();
	enemies->Disable();
	elements1->Disable();
	heli_scene->Disable();
	inter_scene->Disable();
	// ---

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}
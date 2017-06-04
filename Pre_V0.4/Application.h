#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 19

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleHelicopterScene;
class ModuleFirstScene;
class ModuleSecondScene;
class ModuleIntermission;
class ModuleEndScene;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleInit;
class ModuleAudio;
class ModuleCollision;
class ModuleEnemies;
class ModuleElements1;
class ModuleFonts;
class Module;

// TODO 1: Create an intro scene with rtype/intro.png that then fades to ModuleSpaceScene

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleHelicopterScene* heli_scene;
	ModuleFirstScene* first_scene; //li he canviat el nom perque crec que aixi es reconeix millor -pol
	ModuleSecondScene* scene_map2;
	ModuleIntermission* inter_scene;
	ModuleEndScene* end_scene;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModulePlayer2* player_2;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleInit* scene_start;
	ModuleAudio* music;
	ModuleEnemies* enemies;
	ModuleElements1* elements1;
	ModuleFonts* fonts;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
#ifndef __MODULE_HELICPOTER_SCENE_H__
#define __MODULE_HELICPOTER_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
struct SDL_Texture;

class ModuleHelicopterScene : public Module
{
public:
	ModuleHelicopterScene();
	~ModuleHelicopterScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* background = nullptr;
	SDL_Texture* textures = nullptr;
	Animation palm_trees;
	Animation heli;
	Animation heliMedium;
	Animation heliSmall;
	Animation heliWings;
	Animation heliWingsMedium;
	Animation heliWingsSmall;
	Animation player1;

	Mix_Chunk *music = NULL;

	bool fading = false;
	int heliPos;
	int timer;
	bool endScene;

private:

	
};

#endif


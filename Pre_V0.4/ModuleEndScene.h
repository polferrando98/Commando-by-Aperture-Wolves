#ifndef __MODULEENDSCENE_H__
#define __MODULEENDSCENE_H__

#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class ModuleEndScene : public Module
{
public:
	ModuleEndScene();
	~ModuleEndScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	SDL_Texture* stars = nullptr;
	Mix_Music* music = NULL;
	bool fading = false;
	char score[30];
	int num_1 = -1;
};

#endif // __MODULEENDSCENE_H__


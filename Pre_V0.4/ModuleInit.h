#ifndef __MODULEINIT_H__
#define __MODULEINIT_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class ModuleInit : public Module
{
public:
	ModuleInit();
	~ModuleInit();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background_texture = nullptr;
	Animation background;
	SDL_Texture* stars = nullptr;
	Mix_Chunk* music = NULL;
	bool fading = false;
	bool player_2 = false;
};

#endif // __MODULESCENESPACE_H__
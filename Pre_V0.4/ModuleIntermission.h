#ifndef __MODULEINTERMISSION_H__
#define __MODULEINTERMISSION_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class ModuleIntermission: public Module
{
public:
	ModuleIntermission();
	~ModuleIntermission();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* intermission_back = nullptr;
	SDL_Texture* intermission_front = nullptr;
	SDL_Texture* intermission_front2 = nullptr;

	Animation intermission;
	Animation intermission2;

	//BELLOW: For the text
	int text = -1;
	const char* text_str = "BROKE THE 1ST AREA, NOW RUSH TO THE SECOND AREA";
	char* new_str = "";
	int timer;

	bool fading = false;	
	bool player_2 = false;
	Mix_Music* music = NULL;

};

#endif __MODULEINTERMISSION_H__
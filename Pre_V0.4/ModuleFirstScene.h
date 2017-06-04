#ifndef __MODULEFIRSTSCENE_H__
#define __MODULEFIRSTSCENE_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define FINAL_BOSS_ENEMIES_1 10

struct SDL_Texture;

class ModuleFirstScene : public Module
{
public:
	ModuleFirstScene();
	~ModuleFirstScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	int boss_max_spawn_time = 400;
	int current_boss_spawn_time = 0;
	int boss_enemies_current_spawned = 0;

public:
	SDL_Texture* background = nullptr;
	SDL_Texture* inter = nullptr;

	Animation intermission;

	Mix_Music* music = NULL;
	Collider* mur1=nullptr;
	Collider* box = nullptr;
	Collider* box1 = nullptr;
	Collider* box2 = nullptr;
	Collider* box3 = nullptr;
	bool enteredBossArea = false;
	bool finishedBossArea = false;
	bool music_boss = false;
	int final_boss_rand;

	bool fading = false;
};

#endif // __MODULEFIRSTSCENE_H__
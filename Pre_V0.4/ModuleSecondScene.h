#ifndef __MODULESECONDSCENE_H__
#define __MODULESECONDSCENE_H__

#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define FINAL_BOSS_ENEMIES_2 13

struct SDL_Texture;

class ModuleSecondScene : public Module
{
public:
	ModuleSecondScene();
	~ModuleSecondScene();

	bool Start();
	update_status Update();
	bool CleanUp();

	void addStaticEnemies();

	int boss_max_spawn_time = 400;
	int current_boss_spawn_time = 0;
	int boss_enemies_current_spawned = 0;

	int rand_spawn_gate = 0;

public:

	SDL_Texture* background = nullptr;
	SDL_Texture* inter = nullptr;
	SDL_Texture* stars = nullptr;
	SDL_Texture* textures = nullptr;
	SDL_Rect bridge;
	SDL_Texture* cave = nullptr;
	SDL_Rect caves;

	Animation intermission;
	Mix_Music* music = NULL;
	bool fading = false;
	bool enteredBossArea = false;
	bool finishedBossArea = false;
	bool music_boss = false;
	int final_boss_rand;
	bool finished = false;
};

#endif // __MODULESECONDSCENE_H__
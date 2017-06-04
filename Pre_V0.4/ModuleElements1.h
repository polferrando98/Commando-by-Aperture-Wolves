#ifndef __MODULEELEMENTS1_H__
#define __MODULEELEMENTS1_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class ModuleElements1 : public Module
{
public:
	ModuleElements1();
	~ModuleElements1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* textures = nullptr;
	SDL_Texture* cannon = nullptr;
	SDL_Texture* helicopter_texture = nullptr;
	SDL_Texture* heli_wings = nullptr;

	Mix_Music* music = NULL;
	Animation palm_trees;
	Animation boxes;
	Animation boxes1;
	Animation boxes2;
	Animation boxes3;
	Animation open_doors;
	Animation close_doors;
	SDL_Rect palmTree;
	SDL_Rect palmTree_2;
	SDL_Rect rock;
	SDL_Rect lifeLogo;
	SDL_Rect grenadeLogo;
	

	Animation heli;
	Animation heliWings;
	Animation heliMedium;
	Animation heliSmall;
	Animation heliWingsMedium;
	Animation heliWingsSmall;
	Animation superJoeJump;
	Animation superJoeBye;
	Animation idleUP;
	Animation smallDoor;

	Collider* mur1 = nullptr;
	bool fading = false;
	bool pickupBox = false;
	bool pickupBox1 = false;
	bool pickupBox2 = false;
	bool pickupBox3 = false;
	bool liveUp = false;
	int num_lives_play_1 = 3;
	int num_grenades = 6;
	int num_1 = -1;
	int num_2 = -1;
	int let_2 = -1;
	int num_score = 0;
	int high_scores[10];
	int heliPos;
	int timer;
	int superJoePosY;
	int superJoePosX;
	char high_score[10] = { 0,0,0,0,0,0,0,0,0,0 };
	char grenade_num[10];
	char score[10];
	int loaded = 0;
};

#endif // __MODULEFIRSTSCENE_H__
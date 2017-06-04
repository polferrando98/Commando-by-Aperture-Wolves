#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#define BULLET_SPEED 4
#define GRENADE_SPEED 1.3f
#define SHOTS_PER_BURST 2
#define SHOT_DELAY 5

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	float transitionToDirection(float current_direction, float final_direction);
	void shot();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* bridge = nullptr;
	Mix_Chunk* music = NULL;

	Animation* current_animation = nullptr;
	Animation idle;
	Animation idle2;
	Animation up;
	Animation down;
	Animation left;
	Animation right;
	Animation idleUP;
	Animation idleDown;
	Animation idleRight;
	Animation idleLeft;
	Animation idleRightUP;
	Animation idleRightDOWN;
	Animation idleLeftUP;
	Animation idleLeftDOWN;
	Animation rightUP;
	Animation leftUP;
	Animation rightDOWN;
	Animation leftDOWN;
	Animation die;
	Animation bullet_explosion;
	Animation waterDie;
	Animation grenadeThrow;
	Collider* playercoll;
	Collider* feetcoll;
	int font_score = -1;


	enum LastDirection { UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT };
	LastDirection player_last_direction;
	iPoint position;
	bool stop = false;
	bool alive = false;
	bool anim = false;
	bool water = false;
	bool grenade = false;
	bool distance = false;
	float direction = M_PI * 1.5; //direccio en radiants cap avall
	bool shooting = false;
	int shots_fired = 0;
	int shot_current_delay = 0;
	int score = 0;
	int counter = 0;
	bool god = false;
	bool only = true;
};

#endif
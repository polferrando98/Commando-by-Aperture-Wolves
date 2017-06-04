#pragma once
#include "Enemy.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.6

class Commander : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_x = 0;

	Animation* current_animation = nullptr;
	Animation flight;
	Animation death_animation;
	int max_time_on_screen = 200;

	Path path;
	Path path2;
	iPoint original_pos;

public:

	Commander(int x, int y);
	void Move();

};




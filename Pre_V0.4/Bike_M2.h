#ifndef _BIKE_M2_H_
#define _BIKE_M2_H_

#include "Enemy.h"
#include "Path.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.5

class Bike_M2 : public Enemy
{
private:
	Path path;
	Path path2;
	Animation moveLeft;
	iPoint original_pos;
	fPoint move = { 0.0f,0.0f };
	Animation death_animation;
	Collider* collider2;

public:
	int shot_current_delay = ENEMY_SHOT_DELAY - 1;
	Bike_M2(int x, int y);
	void Move();

};

#endif 
#ifndef _BIKEENEMY_H_
#define _BIKEENEMY_H_

#include "Enemy.h"
#include "Path.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.5

class BikeEnemy : public Enemy
{
private:
	Path path;
	Path path2;
	Animation moveLeft;
	Animation grenade;
	iPoint original_pos;
	fPoint move = { 0.0f,0.0f };
	bool only = true;

	void shoot();
	float aim_to_player();

public:
	int shot_current_delay = ENEMY_SHOT_DELAY - 1;


	BikeEnemy(int x, int y);
	void Move();

};

#endif // _BIKEENEMY_H_
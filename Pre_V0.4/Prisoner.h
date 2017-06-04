#ifndef _PRISONER_H_
#define _PRISONER_H_

#include "Enemy.h"
#include "Path.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.5

class Prisoner : public Enemy
{
private:
	Path path;
	Path path2;
	Path path3;
	Path path4;
	Animation moveUp;
	Animation death_animation;
	Animation hello;
	Animation disappear;
	iPoint original_pos;
	fPoint move = { 0.0f,0.0f };

public:
	int shot_current_delay = ENEMY_SHOT_DELAY - 1;


	Prisoner(int x, int y);
	void Move();

};

#endif // __ENEMY_1_H__

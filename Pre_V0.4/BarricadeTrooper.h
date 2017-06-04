#ifndef __BARRICADE_TROOPER_H__
#define __BARRICADE_TROOPER_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.6

class BarricadeTrooper : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_x = 0;

	Animation* current_animation = nullptr;
	Animation behindCover;
	Animation behindCoverRight;
	Animation behindCoverLeft;
	Animation usingTurret;  
	Animation usingTurretLeft;
	Animation usingTurretRight;
	Animation moveDown;
	Animation moveUp;
	Animation moveLeft;
	Animation moveRight;
	Animation moveUpRight;
	Animation moveUpLeft;
	Animation moveDownRight;
	Animation moveDownLeft;
	Animation death_animation;
	iPoint original_pos;
	int max_time_on_screen = 200;

public:
	int shot_current_delay = ENEMY_SHOT_DELAY - 1;

	int go_up_max_time = 100;
	int go_up_current_time = 0;
	BarricadeTrooper(int x, int y);
	void Move();

	//added
	float aim_to_player();
	void update_animation();
	void shoot();


};

#endif // __BARRICADE_TROOPER_H__
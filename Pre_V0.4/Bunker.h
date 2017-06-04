#pragma once
#ifndef __BUNKER_H__
#define __BUNKER_H__

#include "Enemy.h"
#include "ModuleEnemies.h"


class Bunker : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_x = 0;

	Animation* current_animation = nullptr;
	Animation aimStraightLEFT;
	Animation aimDownLEFT;
	Animation aimUpLEFT;
	Animation aimStraightRIGHT;
	Animation aimDownRIGHT;
	Animation aimUpRIGHT;
	

	iPoint original_pos;
	int max_time_on_screen = 1600;

public:
	int shot_current_delay = ENEMY_SHOT_DELAY - 1;

	Bunker(int x, int y);
	void Move();

	//added
	float aim_to_player();
	void update_animation();
	void shoot();


};

#endif // __BUNKER_H__
#ifndef __GRANADIER_H__
#define __GRANADIER_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.6

class Granadier : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_x = 0;

	Animation* current_animation = nullptr;
	Animation moveDown;
	Animation moveUp;
	Animation moveLeft;
	Animation moveRight;
	Animation moveUpRight;
	Animation moveUpLeft;
	Animation moveDownRight;
	Animation moveDownLeft;
	Animation granada;
	Animation death_animation;
	iPoint original_pos;

	void shoot();
	float aim_to_player();

	void update_animation();

public:
	int shot_current_delay = ENEMY_SHOT_DELAY - 1;


	Granadier(int x, int y);
	void Move();

	//added



};

#endif // __GRANADIER_H__
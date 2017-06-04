#ifndef __HOLE_TROOPER_H__
#define __HOLE_TROOPER_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class HoleTrooper : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_x = 0;

	Animation* current_animation = nullptr;
	Animation behindCover;
	Animation behindCoverRight;
	Animation behindCoverLeft;
	Animation transition_behindCover;
	Animation transition_behindCoverRight;
	Animation transition_behindCoverLeft;
	Animation hidden;	

	Animation waterTrans;
	Animation waterHidden;
	Animation waterStraight;
	Animation waterLeft;
	Animation waterRight;
	Animation waterDeath;

	Animation death_animation;
	iPoint original_pos;

public:
	int shot_current_delay = 0;

	int down_max_time = 130;
	int down_current_time = 0;
	int max_transition_time = 5;
	int current_transition_time = 0;
	HoleTrooper(int x, int y);
	void Move();

	//added
	float aim_to_player();
	void update_animation();
	void shoot();


};

#endif // __HOLE_TROOPER_H__
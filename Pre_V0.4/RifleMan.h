#ifndef __ENEMY_1_H__
#define __ENEMY_1_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.6

class RifleMan : public Enemy
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
	Animation death_animation;
	iPoint original_pos;
	int max_time_on_screen = 600;

public:
	int shot_current_delay = ENEMY_SHOT_DELAY-1;


	RifleMan(int x, int y);
	void Move();

	//added
	float aim_to_player();
	void update_animation();
	void shoot();


};

#endif // __ENEMY_1_H__

//Com fer randoms 

//rand()%10 => 0,1,2,3,4,5,6,7,8,9
//lib  <stdlib.h> and #include <time.h>
// srand (time(NULL)); random seed

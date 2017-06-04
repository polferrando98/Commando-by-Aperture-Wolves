#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;

public:
	fPoint position;
	fPoint speed;
	int score;
	float randx, randy;
	iPoint pos;

	// added
	float shoot_direction;
	float walk_direction = M_PI / 2;
	enum Behaviour { FOLLOW, STAY, WANDER, LEAVE, WALK_LEFT, WALK_RIGHT, DODGING_WALL, HOLD_POSITION, ENTER_DOOR, RUN_FROM_COVER, TURRET, WATER_UP,WATER_HIDDEN };
	Behaviour behaviour = STAY;
	Behaviour previous_behaviour;
	enum AnimDirection { UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT };
	AnimDirection anim_direction;
	bool alive = true;
	int dead_animation_life;
	int dead_animation_current_life = 0;
	Animation* death = nullptr; 
	int time_on_screen = 0;
	int time_of_collision;
	float angle_width = M_PI * 0.125;
	bool on_action = false;
	int type = 0;




public:
	Enemy(int x, int y);
	virtual ~Enemy();

	Collider* GetCollider()const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);

	//added



};

#endif // __ENEMY_H__
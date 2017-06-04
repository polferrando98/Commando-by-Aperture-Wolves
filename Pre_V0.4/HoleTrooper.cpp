#include <math.h>
#include "Application.h"
#include "HoleTrooper.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include <time.h>
#include <stdlib.h>  

  HoleTrooper::HoleTrooper(int x, int y) : Enemy(x, y)
{

	srand(time(NULL));

	current_animation = NULL;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 14, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY_BEHIND_COVER, (Module*)App->enemies);


	hidden.PushBack ({ 66,497,16,16 });
	hidden.loop = false;
	hidden.speed = 0.05f;
	
	//behind cover frontal
	behindCover.PushBack({ 100,497,16,16 });
	behindCover.loop = false;
	behindCover.speed = 0.1f;

	//behind cover looking right
	behindCoverRight.PushBack({ 134,497,16,16 });
	behindCoverRight.loop = false;
	behindCoverRight.speed = 0.1f;

	//behind cover looking left
	behindCoverLeft.PushBack({ 117,497,16,16 });
	behindCoverLeft.loop = false;
	behindCoverLeft.speed = 0.1f;

	//behind cover frontal
	transition_behindCover.PushBack({ 83,497,16,16 });
	transition_behindCover.loop = false;
	transition_behindCover.speed = 0.1f;

	//death (THESE ONLY DIE BY GRENADE)
	death_animation.PushBack({ 247, 221, 16,16 });
	death_animation.PushBack({ 151, 497, 16,16 });
	death_animation.PushBack({ 168, 497, 16,16 });
	death_animation.PushBack({ 185, 497, 16,16 });
	death_animation.loop = false;
	death_animation.speed = 1;

	death = &death_animation;

	current_animation = &behindCoverRight;
	animation = &hidden;
	score = 500;

	//WATER TROOPER
	waterHidden.PushBack({ 181, 55, 29, 26 });
	waterHidden.loop = false;
	waterHidden.speed = 0.05f;

	waterTrans.PushBack({ 211, 55, 29, 26 });
	waterTrans.loop = false;
	waterTrans.speed = 0.1f;


	waterStraight.PushBack({ 241, 55, 29, 26 });
	waterStraight.loop = false;
	waterStraight.speed = 0.1f;

	waterLeft.PushBack({ 241, 55, 29, 26 });
	waterLeft.PushBack({ 271, 55, 29, 26 });
	waterLeft.loop = false;
	waterLeft.speed = 0.1f;

	waterRight.PushBack({ 301, 55, 29, 26 });
	waterRight.loop = false;
	waterRight.speed = 0.1f;

	waterDeath.PushBack({247, 221, 29, 26});
	waterDeath.PushBack({ 301, 136, 29, 26 });
	waterDeath.PushBack({ 301, 163, 29, 26 });
	waterDeath.PushBack({ 301, 190, 29, 26 });
	waterDeath.loop = false;
	waterDeath.speed = 1;

	
	
} 

  void HoleTrooper::Move() {
	  switch (behaviour)
	  {
	  case Enemy::DODGING_WALL:
		  break;
	  case Enemy::HOLD_POSITION:
		  if (down_current_time < down_max_time) {
			  down_current_time ++;
		  }
		  else {
			  down_current_time = rand() % int((down_max_time*0.5));
			  behaviour = TURRET;
		  }
		  break;
	  case Enemy::TURRET:
		  if (down_current_time < down_max_time) {
			  down_current_time++;
		  }
		  else {
			  down_current_time = rand() % int((down_max_time*0.5));
			  behaviour = HOLD_POSITION;
		  }
		  break;
	  case Enemy::WATER_UP:
		  if (down_current_time < down_max_time) {
			  down_current_time++;
		  }
		  else {
			  down_current_time = 0;
			  behaviour = WATER_HIDDEN;
		  }
		  break;
	  case Enemy::WATER_HIDDEN:
		  if (down_current_time < down_max_time) {
			  down_current_time++;
		  }
		  else {
			  down_current_time = 0;
			  behaviour = WATER_UP;
		  }
		  break;

	  default:
		  break;
	  }
	  collider->SetPos(position.x, position.y);
	  update_animation();
	  time_on_screen++;
	  
  }
  float HoleTrooper::aim_to_player() {
	  float x_distance;
	  float y_distance;

	  float new_direction;

	  x_distance = App->player->position.x - position.x;
	  y_distance = App->player->position.y - position.y;

	  new_direction = atan(y_distance / x_distance);

	  if (App->player->position.x < position.x) {
		  new_direction += M_PI;
	  }

	  return new_direction;
  }
  void HoleTrooper::update_animation(){
	  switch (behaviour)
	  {
	  case Enemy::DODGING_WALL:
		  break;
	  case Enemy::HOLD_POSITION:
		  current_transition_time = 0;
		  shot_current_delay = 0;
		  animation = &hidden;
		  break;
	  case Enemy::TURRET:
		  if (current_transition_time < max_transition_time) {
			  current_transition_time++;
			  animation = &transition_behindCover;
		  }
		  else {
			  if (aim_to_player() > M_PI * 0.6) {
				  animation = &behindCoverLeft;
			  }
			  else if (aim_to_player() > M_PI * 0.4) {
				  animation = &behindCover;
			  }
			  else {
				  animation = &behindCoverRight;
			  }
		  }
		  
		  shoot();
		  break;
	  case Enemy::WATER_HIDDEN:
		  current_transition_time = 0;
		  shot_current_delay = 0;
		  animation = &waterHidden;
		  break;
	  case Enemy::WATER_UP:
		  if (current_transition_time < max_transition_time) {
			  current_transition_time++;
			  animation = &waterTrans;
		  }
		  else {
			  if (aim_to_player() > 1.8) {
				  animation = &waterLeft;
			  }
			  else if (aim_to_player() < 1.1) {
				  animation = &waterRight;
			  }
			  else {
				  animation = &waterStraight;
			  }
		  }
		  shoot();
		  break;
	  default:
		  break;
	  }
  }
  void HoleTrooper::shoot(){
	  shoot_direction = aim_to_player();


		  App->particles->enemy_bullet.speed.y = sin(shoot_direction) * ENEMY_BULLET_SPEED;
		  App->particles->enemy_bullet.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;

		  if (shot_current_delay < 100) {
			  shot_current_delay++;
		  }
		  else {
			  if (shoot_direction < 3 && shoot_direction > 0) {
				App->particles->AddParticle(App->particles->enemy_bullet, position.x + 3, position.y + 8, COLLIDER_BULLET_BEHIND_COVER);
				shot_current_delay = 0;
				}
			}

  }

#include <math.h>
#include "Application.h"
#include "FinalBossRifleMan.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include <time.h>
#include <stdlib.h>
FinalBossRifleMan::FinalBossRifleMan(int x, int y) : Enemy(x, y)
{
	srand(time(NULL));

	current_animation = NULL;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 14, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//move down


	moveDown.PushBack({ 1, 1, 29, 26 });
	moveDown.PushBack({ 31,1,29,26 });
	moveDown.PushBack({ 1, 1, 29, 26 });
	moveDown.PushBack({ 61,1,29,26 });
	moveDown.loop = true;
	moveDown.speed = 0.1f;
	animation = &moveDown;

	//moveup
	moveUp.PushBack({ 1, 28, 29, 26 });
	moveUp.PushBack({ 31, 28, 29, 26 });
	moveUp.PushBack({ 1,28, 29, 26 });
	moveUp.PushBack({ 61, 28, 29, 26 });
	moveUp.loop = true;
	moveUp.speed = 0.1f;

	//move right							

	moveRight.PushBack({ 1, 82, 29, 26 });
	moveRight.PushBack({ 31, 82, 29, 26 });
	moveRight.PushBack({ 1, 82, 29, 26 });
	moveRight.PushBack({ 61, 82, 29, 26 });
	moveRight.loop = true;
	moveRight.speed = 0.1f;

	//move left

	moveLeft.PushBack({ 1, 55, 29, 26 });
	moveLeft.PushBack({ 31, 55, 29, 26 });
	moveLeft.PushBack({ 1, 55, 29, 26 });
	moveLeft.PushBack({ 61, 55, 29, 26 });
	moveLeft.loop = true;
	moveLeft.speed = 0.1f;


	//move upright

	moveUpRight.PushBack({ 1, 190, 29, 26 });
	moveUpRight.PushBack({ 31, 190, 29, 26 });
	moveUpRight.PushBack({ 1, 190, 29, 26 });
	moveUpRight.PushBack({ 61, 190, 29, 26 });
	moveUpRight.loop = true;
	moveUpRight.speed = 0.2f;

	//move upleft

	moveUpLeft.PushBack({ 1, 163, 29, 26 });
	moveUpLeft.PushBack({ 31, 163, 29, 26 });
	moveUpLeft.PushBack({ 1, 163, 29, 26 });
	moveUpLeft.PushBack({ 61, 163,29, 26 });
	moveUpLeft.loop = true;
	moveUpLeft.speed = 0.2f;

	//move down right

	moveDownRight.PushBack({ 1, 109, 29, 26 });
	moveDownRight.PushBack({ 31, 109, 29, 26 });
	moveDownRight.PushBack({ 1, 109, 29, 26 });
	moveDownRight.PushBack({ 61, 109, 29, 26 });
	moveDownRight.loop = true;
	moveDownRight.speed = 0.2f;

	//move down left

	moveDownLeft.PushBack({ 1,136,29, 26 });
	moveDownLeft.PushBack({ 31,136,29, 26 });
	moveDownLeft.PushBack({ 1,136,29, 26 });
	moveDownLeft.PushBack({ 61,136,29, 26 });
	moveDownLeft.loop = true;
	moveDownLeft.speed = 0.2f;

	//death animation

	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 211, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 211, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 211, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 211, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.PushBack({ 241, 217, 29,26 });
	death_animation.PushBack({ 181, 217, 29,26 });
	death_animation.loop = false;
	death_animation.speed = 1.5;
	dead_animation_life = 20;

	death = &death_animation;

	score = 200;
}

void FinalBossRifleMan::Move()
{
	//position = original_pos + movement_down.GetCurrentPosition();

	collider->SetPos(position.x, position.y);

	position.x += speed.x;
	position.y += speed.y;

	switch (behaviour)
	{
	case Enemy::FOLLOW:
		walk_direction = aim_to_player();
		speed.y = sin(walk_direction) * BOSS_RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * BOSS_RIFLEMAN_WALKSPEED;
		shoot();
		break;
	case Enemy::STAY:
		speed.y = 0;
		speed.x = 0;
		break;
	case Enemy::WANDER:
		if (time_on_screen % 200 == 0) {
			walk_direction = aim_to_player();
		}
		if (time_on_screen > max_time_on_screen) //que s'en vagi al cap d'un rato
			behaviour = LEAVE;
		speed.y = sin(walk_direction) * (BOSS_RIFLEMAN_WALKSPEED +0.2) ;
		speed.x = cos(walk_direction) * (BOSS_RIFLEMAN_WALKSPEED + 0.2);
		shoot();
		break;
	case Enemy::LEAVE:  // ho volia fer millor pero de moment anira cap avall i a correr
		walk_direction = M_PI * 0.5;
		speed.y = sin(walk_direction) * BOSS_RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * BOSS_RIFLEMAN_WALKSPEED;
		break;

	case Enemy::DODGING_WALL:
		//if (time_of_collision == 0) {

		//}
		//else if (time_of_collision == 50) {
		//	behaviour = WANDER;
		//}
		//time_of_collision++;
		//speed.y = sin(walk_direction) * BOSS_RIFLEMAN_WALKSPEED;
		//speed.x = cos(walk_direction) * BOSS_RIFLEMAN_WALKSPEED;
		//shoot();
		break;
	case Enemy::ENTER_DOOR:
		if (time_on_screen > 30)
			behaviour = WANDER;
		walk_direction = M_PI * 0.5;
		speed.y = sin(walk_direction) * 2;
		speed.x = cos(walk_direction) * 2;
		time_on_screen++;
	default:
		break;
	}
	update_animation();
	shoot_direction = aim_to_player();
	time_on_screen++;
}

float FinalBossRifleMan::aim_to_player()
{
	float x_distance;
	float y_distance;

	float new_direction;

	x_distance = App->player->position.x - position.x;
	y_distance = App->player->position.y - position.y;

	new_direction = atan(y_distance / x_distance);

	if (App->player->position.x < position.x) {
		new_direction += M_PI;
	}

	new_direction -= M_PI*0.2;
	new_direction += (rand()) / (static_cast <float> (RAND_MAX / (M_PI*0.4))) ;

	return new_direction;
}

void FinalBossRifleMan::update_animation()
{

	if (walk_direction >(M_PI - angle_width) && walk_direction < (M_PI + angle_width)) { //LEFT
		animation = &moveLeft;
	}
	else if (walk_direction >(1.5 * M_PI - angle_width) && walk_direction < (1.5 * M_PI + angle_width)) { //UP
		animation = &moveUp;
	}
	else if (walk_direction >(M_PI / 2 - angle_width) && walk_direction < (M_PI / 2 + angle_width)) { //DOWN
		animation = &moveDown;
	}
	else if (walk_direction >(1.75 * M_PI - angle_width) && walk_direction < (1.75 * M_PI + angle_width)) { //DOWN
		animation = &moveUpRight;
	}
	else if (walk_direction >(1.25 * M_PI - angle_width) && walk_direction < (1.25 * M_PI + angle_width)) { //DOWN
		animation = &moveUpLeft;
	}
	else if (walk_direction >(0.75 * M_PI - angle_width) && walk_direction < (0.75 * M_PI + angle_width)) { //DOWN
		animation = &moveDownLeft;
	}
	else if (walk_direction >(0.25 * M_PI - angle_width) && walk_direction < (0.25 * M_PI + angle_width)) { //DOWN
		animation = &moveDownRight;
	}
	else {
		animation = &moveRight;
	}
}


void FinalBossRifleMan::shoot()
{
	App->particles->enemy_bullet.speed.y = sin(shoot_direction) * ENEMY_BULLET_SPEED;
	App->particles->enemy_bullet.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;

	//App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);

	if (shot_current_delay < ENEMY_SHOT_DELAY)
		shot_current_delay++;
	else {
		App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);
		shot_current_delay = 0;
	}

}

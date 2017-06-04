#include <math.h>
#include "Application.h"
#include "Granadier.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Granadier::Granadier(int x, int y) : Enemy(x, y)
{
	current_animation = NULL;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 14, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//granada
	granada.PushBack({ 181, 136, 29, 26 });
	granada.PushBack({ 211, 136, 29, 26 });
	granada.PushBack({ 241, 136,29, 26 });
	granada.loop = true;
	granada.speed = 0.2f;

	//move up
	moveUp.PushBack({ 91, 28, 29, 26 });
	moveUp.PushBack({ 121, 28,29, 26 });
	moveUp.PushBack({ 91, 28,29, 26 });
	moveUp.PushBack({ 151, 28,29, 26 });
	moveUp.loop = true;
	moveUp.speed = 0.2f;

	//move left

	moveLeft.PushBack({ 91, 55, 29, 26 });
	moveLeft.PushBack({ 121, 55, 29, 26 });
	moveLeft.PushBack({ 91, 55,29, 26 });
	moveLeft.PushBack({ 151, 55, 29, 26 });
	moveLeft.loop = true;
	moveLeft.speed = 0.2f;

	//move right

	moveRight.PushBack({ 91, 82, 29, 26 });
	moveRight.PushBack({ 121, 82, 29, 26 });
	moveRight.PushBack({ 91, 82, 29, 26 });
	moveRight.PushBack({ 151, 82, 29, 26 });
	moveRight.loop = true;
	moveRight.speed = 0.2f;

	//move down

	moveDown.PushBack({91, 1, 29, 26});
	moveDown.PushBack({ 121, 1, 29, 26 });
	moveDown.PushBack({ 91, 1, 29, 26 });
	moveDown.PushBack({ 151, 1, 29, 26 });
	moveDown.loop = true;
	moveDown.speed = 0.2f;

	//move up left
	 
	moveUpLeft.PushBack({ 91, 163, 29, 26 });
	moveUpLeft.PushBack({ 121, 163, 29, 26 });
	moveUpLeft.PushBack({ 91, 163, 29, 26 });
	moveUpLeft.PushBack({ 151, 163, 29, 26 });
	moveUpLeft.loop = true;
	moveUpLeft.speed = 0.2f;

	//move up right

	moveUpRight.PushBack({91, 190,29, 26 });
	moveUpRight.PushBack({ 121, 190, 29, 26 });
	moveUpRight.PushBack({ 91, 190, 29, 26 });
	moveUpRight.PushBack({ 151, 190, 29, 26 });
	moveUpRight.loop = true;
	moveUpRight.speed = 0.2f;
	animation = &moveUp;

	//move down right

	moveDownRight.PushBack({ 91, 109, 29, 26 });
	moveDownRight.PushBack({ 121, 109, 29, 26 });
	moveDownRight.PushBack({ 91, 109, 29, 26 });
	moveDownRight.PushBack({ 151, 109, 29, 26 });
	moveDownRight.loop = true;
	moveDownRight.speed = 0.2f;

	//move down left

	moveDownLeft.PushBack({91, 136, 29, 26 });
	moveDownLeft.PushBack({ 121, 136,29, 26 });
	moveDownLeft.PushBack({ 91, 136, 29, 26 });
	moveDownLeft.PushBack({ 151, 136, 29, 26 });
	moveDownLeft.loop = true;
	moveDownLeft.speed = 0.2f;



	//death animation

	//for (int i = 0; i < 6; i++)
//	{

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
//	}

	dead_animation_life = 20;

	death = &death_animation;
	score = 300;
}

void Granadier::Move()
{
	//position = original_pos + movement_down.GetCurrentPosition();

	collider->SetPos(position.x, position.y);

	position.x += speed.x;
	position.y += speed.y;

	switch (behaviour)
	{
	case Enemy::FOLLOW:
		walk_direction = aim_to_player();
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
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
		if (time_on_screen > 600) //que s'en vagi al cap d'un rato
			behaviour = LEAVE;
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		shoot();
		break;
	case Enemy::LEAVE:  // ho volia fer millor pero de moment anira cap avall i a correr
		walk_direction = M_PI * 0.5;
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		break;
	case Enemy::WALK_LEFT:
		if (time_on_screen % 200 == 0) {
			walk_direction = M_PI;
		}
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		shoot();
		break;
	case Enemy::WALK_RIGHT:
		if (time_on_screen % 200 == 0) {
			walk_direction = 2 * M_PI;
		}
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		shoot();
		break;
	case Enemy::DODGING_WALL:
		if (time_of_collision == 0) {

		}
		else if (time_of_collision == 50) {
			behaviour = WANDER;
		}
		time_of_collision++;
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		shoot();
		break;
	default:
		break;
	}
	update_animation();
	shoot_direction = aim_to_player();
	time_on_screen++;
}

float Granadier::aim_to_player()
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

	return new_direction;
}

void Granadier::update_animation()
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

void Granadier::shoot()
{
	App->particles->enemy_bullet.speed.y = sin(shoot_direction) * ENEMY_BULLET_SPEED;
	App->particles->enemy_bullet.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;

	//App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);

	if (shot_current_delay < ENEMY_GRENADE_DELAY)
		shot_current_delay++;
	else {
		//App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);
		App->particles->enemy_grenade.speed.y = sin(shoot_direction) * ENEMY_BULLET_SPEED;
		App->particles->enemy_grenade.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;
		App->particles->AddParticle(App->particles->enemy_grenade, position.x + 11, position.y + 3, COLLIDER_NONE);
		shot_current_delay = 0;
	}
}

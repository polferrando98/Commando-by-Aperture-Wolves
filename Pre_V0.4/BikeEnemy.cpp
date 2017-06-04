#include <math.h>
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "PrisonerEnemies.h"
#include "BikeEnemy.h"


void BikeEnemy::shoot()
{
	App->particles->enemy_bullet.speed.y = sin(shoot_direction) * ENEMY_BULLET_SPEED;
	App->particles->enemy_bullet.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;

	//App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);

	if (shot_current_delay < 70)
		shot_current_delay++;
	else {
		//App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);
		App->particles->enemy_grenade.speed.y = sin(shoot_direction) * ENEMY_BULLET_SPEED;
		App->particles->enemy_grenade.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;
		App->particles->AddParticle(App->particles->enemy_grenade, position.x + 11, position.y + 3, COLLIDER_NONE);
		shot_current_delay = 0;
	}
}

float BikeEnemy::aim_to_player()
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

BikeEnemy::BikeEnemy(int x, int y) : Enemy(x, y)
{
	moveLeft.PushBack({ 196,550,48,26 });
	moveLeft.PushBack({ 245, 550, 48, 26 });
	moveLeft.speed = 0.2f;

	grenade.PushBack({ 294,550,48,26 });
	grenade.PushBack({ 343, 550, 48,26 });
	grenade.PushBack({ 294,550,48,26 });
	grenade.PushBack({ 392, 550, 48,26 });
	grenade.speed = 0.05f;

	animation = &moveLeft;
	path.PushBack({ -0.35f, 0.0f }, 350, animation);
	animation = &grenade;
	path.PushBack({ 0.0f,0.0f }, 5000, animation);
	animation = &moveLeft;
	path2.PushBack({ -0.35f, 0.0f }, 2000, animation);


	collider = App->collision->AddCollider({ 0, 0, 16, 22 }, COLLIDER_TYPE::COLLIDER_NONE, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void BikeEnemy::Move()
{
	if (App->player->position.y <= -600 && App->player->position.y>=-800 && App->player->only ==true) { //entrada parada
		position.x = original_pos.x + (float)path.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path.GetCurrentPosition(&animation).y;
		if (position.x < 85 && position.x > 70) {
			shoot_direction = aim_to_player();
			time_on_screen++;
			shoot();
		}
	}
	if(App->player->position.y <= -800 || App->player->only ==false) 
	{
		App->player->only = false;
		position.x = 85 + (float)path2.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path2.GetCurrentPosition(&animation).y; 
	}
 	if (App->player->position.y == 0) //me piro vampiro
	{
		path.Reset();
		path2.Reset();
		position.x = 200;
		path.accumulated_speed.x = 0;
		path2.accumulated_speed.x = 0;
	}

}
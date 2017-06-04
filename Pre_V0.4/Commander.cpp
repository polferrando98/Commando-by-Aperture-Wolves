#include "Commander.h"
#include <math.h>
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include <time.h>
#include <stdlib.h>

Commander::Commander(int x, int y) : Enemy(x, y)
{
	current_animation = NULL;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 14, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	//flight
	flight.PushBack({ 91, 271, 29, 26 });
	flight.PushBack({ 121, 271, 29, 26 });
	flight.PushBack({ 91, 271, 29, 26 });
	flight.PushBack({ 151, 271, 29, 26 });
	flight.loop = true;
	flight.speed = 0.2f;
	animation = &flight;

	death_animation.PushBack({301, 217, 29, 26});
	death_animation.loop = false;
	dead_animation_life = 40;
	death = &death_animation;

	score = 2000;
	srand(time(NULL));
}

void Commander::Move()
{
	//position = original_pos + movement_down.GetCurrentPosition();

	collider->SetPos(position.x, position.y);

	position.x += speed.x;
	position.y += speed.y;

	switch (behaviour)
	{
	case Enemy::WANDER:

		walk_direction = 1.75 * M_PI + M_PI * 0.65;

		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		break;
	case Enemy::LEAVE:  // ho volia fer millor pero de moment anira cap avall i a correr
		walk_direction = M_PI;
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		break;
	case Enemy::DODGING_WALL:
		walk_direction = M_PI;
 		time_of_collision++;
		speed.y = sin(walk_direction) * RIFLEMAN_WALKSPEED;
		speed.x = cos(walk_direction) * RIFLEMAN_WALKSPEED;
		break;
	default:
		break;
	}
	//	update_animation();                                               --Em falten els sprites  -p
	time_on_screen++;
}




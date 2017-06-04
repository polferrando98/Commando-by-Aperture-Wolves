#include "Bike_M2.h"
#include <math.h>
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "PrisonerEnemies.h"


Bike_M2::Bike_M2(int x, int y) : Enemy(x, y)
{
	moveLeft.PushBack({ 256, 577, 59, 27 });
	moveLeft.speed = 0.2f;
	animation = &moveLeft;
	
	path.PushBack({ 0.0f,0.0f }, 1, animation);
	path2.PushBack({ -2.0f, 0.0f }, 1, animation);

	collider = App->collision->AddCollider({ 0, 0, 59, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Bike_M2::Move()
{
	if (App->player->position.y <=0 ){
		position.x = original_pos.x + (float)path2.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path2.GetCurrentPosition(&animation).y;
	}
	else
	{
		position.x = original_pos.x + (float)path.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path.GetCurrentPosition(&animation).y;
	}

}



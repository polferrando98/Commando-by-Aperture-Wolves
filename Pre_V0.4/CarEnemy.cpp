#include "CarEnemy.h"
#include <math.h>
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "PrisonerEnemies.h"


CarEnemy::CarEnemy(int x, int y) : Enemy(x, y)
{
	moveUp.PushBack({ 316,577,59,27 });	
	moveUp.speed = 0.2f;
	animation = &moveUp;

	path.PushBack({ 0.0f, 0.0f }, 1, animation);
	path2.PushBack({ 0.0f,-1.5f }, 1, animation);

	collider = App->collision->AddCollider({ 0, 0, 18, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

}

void CarEnemy::Move()
{
	if (App->player->position.y >=0) {
		position.x = original_pos.x + (float)path.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path.GetCurrentPosition(&animation).y;
	}
	else
	{
		position.x = original_pos.x + (float)path2.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path2.GetCurrentPosition(&animation).y;
	}

}



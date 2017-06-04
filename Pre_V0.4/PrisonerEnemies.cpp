#include <math.h>
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleInit.h"
#include "ModuleEnemies.h"
#include "PrisonerEnemies.h"


PrisonerEnemies::PrisonerEnemies(int x, int y) : Enemy(x, y)
{
	moveUp.PushBack({ 181,82,29,26 });
	moveUp.PushBack({ 211, 82, 29, 26 });
	moveUp.PushBack({ 181,82,29,26 });
	moveUp.PushBack({ 241, 82, 29, 26 });
	moveUp.speed = 0.2f;
	animation = &moveUp;

	path.PushBack({ 0.0f, 0.0f }, 1, animation);
	path2.PushBack({ -0.6f,-0.75 }, 1, animation);

	collider = App->collision->AddCollider({ 0, 0, 18, 22 }, COLLIDER_TYPE::COLLIDER_PRISONER, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

	death_animation.PushBack({ 271, 217, 29,26 });
	death_animation.loop = false;
	death_animation.speed = 0.1;
	dead_animation_life = 40;
	score = 1000;
	death = &death_animation;
}

void PrisonerEnemies::Move()
{
	if (App->player->position.y >= -490 && App->player->counter<1 && (App->player_2->position.y >= -490 || App->scene_start->player_2 == false)) {
		position.x = original_pos.x + (float)path.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path.GetCurrentPosition(&animation).y;
	}
	else
	{
		position.x = original_pos.x + (float)path2.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path2.GetCurrentPosition(&animation).y;
	}

}



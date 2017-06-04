#include <math.h>
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInit.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "PrisonerEnemies.h"
#include "Prisoner.h"


Prisoner::Prisoner(int x, int y) : Enemy(x, y)
{
	moveUp.PushBack({ 181,109,29,26 });
	moveUp.PushBack({ 211, 109, 29, 26 });
	moveUp.PushBack({ 181,109,29,26 });
	moveUp.PushBack({ 241, 109, 29 , 26 });
	moveUp.loop = true;

	moveUp.speed = 0.2f;


		hello.PushBack({ 271,109,29,26 });
		hello.PushBack({ 301, 109, 29, 26 });
	//	hello.PushBack({ 116,432,14,21 });
	//	hello.PushBack({ 139,385,16,25 });
	//	hello.PushBack({ 116, 408, 16, 22 });
	//	hello.PushBack({ 116,432,14,21 });
		hello.loop = true;
	//hello.PushBack({ 91, 408, 22, 24 });
	hello.speed = 0.05f;
	score = 1000;
	disappear.PushBack({ 0,0,0,0 });


	animation = &moveUp;
	path.PushBack({ 0.0f, 0.0f }, 100, animation);
	path2.PushBack({ -0.3f,-0.38f }, 100, animation);
	animation = &hello;
	path3.PushBack({ 0.0f, 0.0f }, 100, animation);
	animation = &disappear;
	path4.PushBack({ 0.0f,0.0f }, 100, animation);
	

	collider = App->collision->AddCollider({ 0, 0, 16, 22 }, COLLIDER_TYPE::COLLIDER_NONE, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Prisoner::Move()
{
	if (App->player->position.y >= -490 && App->player->counter==0 && (App->player_2->position.y>=-490|| App->scene_start->player_2==false)) {
		position.x = original_pos.x + (float)path.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path.GetCurrentPosition(&animation).y;
	}
	else if (App->player->counter == 2 && App->player->position.y >= position.y)
	{
		position.x = position.x + (float)path3.GetCurrentPosition(&animation).x;
		position.y = position.y + (float)path3.GetCurrentPosition(&animation).y;
	}
	else if (App->player->counter == 2 && App->player->position.y < position.y)
	{
		position.x = position.x + (float)path4.GetCurrentPosition(&animation).x;
		position.y = position.y + (float)path4.GetCurrentPosition(&animation).y;
	}
	else
	{
		position.x = original_pos.x + (float)path2.GetCurrentPosition(&animation).x;
		position.y = original_pos.y + (float)path2.GetCurrentPosition(&animation).y;
	}
	if (App->player->position.y == 0 && App->player->counter!=0)
	{
		position.x = -200;
	}

}
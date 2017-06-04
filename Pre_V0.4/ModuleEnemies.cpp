#include <stdlib.h>  
#include <time.h>  
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInit.h"
#include "Enemy.h"
#include "RifleMan.h"
#include "PrisonerEnemies.h"
#include "Prisoner.h"
#include "BikeEnemy.h"
#include "ModuleElements1.h"
#include "Granadier.h"
#include "BarricadeTrooper.h"
#include "FinalBossRifleMan.h"
#include "Commander.h"
#include "Bike_M2.h"
#include "CarEnemy.h"
#include "HoleTrooper.h"
#include "Bunker.h"
//#include "Enemy_RedBird.h"


ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("assets/PlaceHolder_Sprites.png");

	srand(time(NULL));

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) {
			if (enemies[i]->alive) {
				enemies[i]->Move();
			}
			if (App->scene_start->player_2 == false)
			{
				if (App->player->anim) {
					enemies[i]->position.x = 100000;
					enemies[i]->behaviour = Enemy::STAY;
					enemies_on_action = 0;
				}
			}
			else
			{
				if (App->player->anim || App->player_2->anim) {
					enemies[i]->position.x = 100000;
					enemies[i]->behaviour = Enemy::STAY;
					enemies_on_action = 0;
				}
			}
		}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) {
			if (enemies[i]->alive)
				enemies[i]->Draw(sprites);
			else
				eliminateEnemy(enemies[i], i);
		}


	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				/*LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;*/
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleEnemies::eliminateEnemy(Enemy * e, int i)
{
	App->render->Blit(sprites, e->position.x - 8, e->position.y - 8, &e->death->GetCurrentFrame(), 0.75f);

	if (e->dead_animation_current_life < e->dead_animation_life) {
		e->alive = false;
		enemies[i]->GetCollider()->SetPos(2000, 2000);
		e->dead_animation_current_life++;
	}
	else {
		enemies[i]->position.x = 2000;
		enemies[i]->position.y = 2000;
		enemies[i]->behaviour = Enemy::STAY;
		enemies[i] = nullptr;
		enemies_on_action--;
	}
}

void ModuleEnemies::spawnCommonEnemies()
{
	
	if (automated_rifleman_spawn_current_time < automated_rifleman_spawn_time) {
		automated_rifleman_spawn_current_time+=5;
	}
	else {
		rand_rifle_man_spawn_behaviour = rand() % 8;
		rand_spawn_y_offset = rand() % 40;
		switch (rand_rifle_man_spawn_behaviour) {
		case 0:
			AddEnemy(RIFLEMAN, 220, App->player->position.y - 200, Enemy::WANDER);
			break;
		case 1:
			AddEnemy(RIFLEMAN, -20, App->player->position.y - 200, Enemy::WANDER);
			break;
		case 2:
			AddEnemy(RIFLEMAN, 230, App->player->position.y - 150 - rand_spawn_y_offset, Enemy::WALK_LEFT);
			break;
		case 3:
			AddEnemy(RIFLEMAN, -20, App->player->position.y - 150 - rand_spawn_y_offset, Enemy::WALK_RIGHT);
			break;
		case 4:
			AddEnemy(GRANADIER, 220, App->player->position.y - 200, Enemy::WANDER);
			break;
		case 5:
			AddEnemy(GRANADIER, -20, App->player->position.y - 200, Enemy::WANDER);
			break;
		case 6:
			AddEnemy(GRANADIER, 230, App->player->position.y - 150 - rand_spawn_y_offset, Enemy::WALK_LEFT);
			break;
		case 7:
			AddEnemy(GRANADIER, -20, App->player->position.y - 150 - rand_spawn_y_offset, Enemy::WALK_RIGHT);
			break;
		}
		enemies_on_action++;
		automated_rifleman_spawn_current_time = 0;
	}
	//if (automated_rifleman_spawn_time > automated_rifleman_min_time) {
	//	automated_rifleman_spawn_time--;
	//}
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, Enemy::Behaviour behaviour = Enemy::STAY)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].behaviour = behaviour;
			queue[i].previous_behaviour = behaviour;
			ret = true;
			break;
		}
	}

	return ret;
}



void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::RIFLEMAN:
			enemies[i] = new RifleMan(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::PRISONER_ENEMIES:
			enemies[i] = new PrisonerEnemies(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::PRISONER:
			enemies[i] = new Prisoner(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BIKEENEMY:
			enemies[i] = new BikeEnemy(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::GRANADIER:
			enemies[i] = new Granadier(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BARRICADE_TROOPER:
			enemies[i] = new BarricadeTrooper(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BOSS_TROOPER:
			enemies[i] = new FinalBossRifleMan(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::COMMANDER:
			enemies[i] = new Commander(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BIKE_M2:
			enemies[i] = new Bike_M2(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::CARENEMY:
			enemies[i] = new CarEnemy(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::HOLE_TROOPER:
			enemies[i] = new HoleTrooper(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		case ENEMY_TYPES::BUNKER:
			enemies[i] = new Bunker(info.x, info.y);
			enemies[i]->behaviour = info.behaviour;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{

	if (c2->type == COLLIDER_MAP_LIMIT_FOR_ENEMIES) {
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				{
					enemies[i]->behaviour = Enemy::STAY;
				}
				break;
			}
		}
	}

	//esborra l'enemic quan es tocat per una bullet del player
	if (c2->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_GRENADE_EXPLOSION)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				{
					if (enemies[i]->alive) {
						App->elements1->num_score += enemies[i]->score;
						enemies[i]->OnCollision(c2);
						if (enemies[i]->type == 1) {
							enemies[i]->position.x = 2000;
							enemies[i]->position.y = 2000;
							enemies[i]->behaviour = Enemy::STAY;
							enemies[i] = nullptr;
						}
						else
						eliminateEnemy(enemies[i], i);
					}
				}
				break;
			}
		}
	}

	if (c2->type == COLLIDER_WALL) {
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				enemies[i]->OnCollision(c2);
				if (fabsf(enemies[i]->position.DistanceTo({ (float)App->player->position.x,(float)App->player->position.y })) < 10) {
					
				}
				if (enemies[i]->behaviour != Enemy::DODGING_WALL) {
					rand_bounce_angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (M_PI*0.5)));
					enemies[i]->time_of_collision = 0;
					enemies[i]->behaviour = Enemy::DODGING_WALL;
					enemies[i]->walk_direction += (M_PI*0.5)+rand_bounce_angle ;
				}
				break;
			}
		}
	}
}
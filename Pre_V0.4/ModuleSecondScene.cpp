#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInit.h"
#include "ModuleSecondScene.h"
#include "ModuleEndScene.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"
#include <time.h>
#include <stdlib.h>
#include "ModuleIntermission.h"

ModuleSecondScene::ModuleSecondScene()
{}

ModuleSecondScene::~ModuleSecondScene()
{}

// Load assets
bool ModuleSecondScene::Start()
{
	LOG("Loading space scene");

	srand(time(NULL));

	background = App->textures->Load("assets/Area2.png");
	textures = App->textures->Load("assets/PlaceHolder_Sprites.png");
	music = App->music->Load("assets/Commando_02_Start_Demo.ogg");
	inter = App->textures->Load("assets/Intermission.png");
	Mix_PlayMusic(music, -1);
	music_boss = true;
	
	intermission.PushBack({ 1,1,31,62 });
	intermission.PushBack({ 33,1,31,62 });
	intermission.PushBack({ 68,1,31,62 });
	intermission.PushBack({ 33,1,31,62 });
	intermission.speed = 0.001f;

	if (App->scene_start->player_2 == false)
	{
		App->player->Enable();
		App->player->position.x = 100;
		App->player->position.y = 150;
	}
	
	if (App->scene_start->player_2 == true)
	{
			App->player->Enable();
			App->player->position.x = 70;
			App->player->position.y = 150;
			App->player_2->Enable();
			App->player_2->position.x = 120;
			App->player_2->position.y = 150;
	}
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->elements1->Enable();

	//CAVES COLLIDERS
	App->collision->AddCollider({ 16 - 16, 52 - 1900 + 248,41,116 }, COLLIDER_WALL);
	App->collision->AddCollider({ 16 - 16, 168 - 1900 + 248,36,15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 16 - 16, 183 - 1900 + 248,31,10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 16 - 16, 193 - 1900 + 248,13,12 }, COLLIDER_WALL);

	App->collision->AddCollider({ 214 - 16, 53 - 1900 + 248,26,199 }, COLLIDER_WALL);
	App->collision->AddCollider({ 209 - 16, 56 - 1900 + 248,5,194 }, COLLIDER_WALL);
	App->collision->AddCollider({ 198 - 16, 59 - 1900 + 248,11,19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 194 - 16, 60 - 1900 + 248,4,16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 205 - 16, 78 - 1900 + 248,4,166 }, COLLIDER_WALL);
	App->collision->AddCollider({ 194 - 16, 122 - 1900 + 248,11,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 199 - 16, 97 - 1900 + 248,6,25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 200 - 16, 158 - 1900 + 248,5,38 }, COLLIDER_WALL);
	App->collision->AddCollider({ 194 - 16, 179 - 1900 + 248,6,17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 194 - 16, 160 - 1900 + 248,6,8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 196 - 16, 218 - 1900 + 248,9,10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 200 - 16, 228 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 226 - 16, 252 - 1900 + 248,14,14 }, COLLIDER_WALL);

	//HOLE TRENCH
	App->collision->AddCollider({ 19-16,1445 - 1900 + 248,74,12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 133 - 16,1400 - 1900 + 248,104,14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0 - 16,1341 - 1900 + 248,104,14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 152 - 16,1326 - 1900 + 248,104,14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 68 - 16,1281 - 1900 + 248,100,14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 151 - 16,1222 - 1900 + 248,105,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 21 - 16,1091 - 1900 + 248,70,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 86 - 16,1047 - 1900 + 248,132,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 23 - 16,987 - 1900 + 248,66,13 }, COLLIDER_WALL);

	//BRIDGE
	App->collision->AddCollider({ 0 - 16,821 - 1900 + 248,96,74 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160 - 16,821 - 1900 + 248,96,74 }, COLLIDER_WALL);

	//BUNKER
	App->collision->AddCollider({ 16 - 16,642 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20 - 16,644 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 24 - 16,646 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 28 - 16,648 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32 - 16,650 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 36 - 16,652 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 40 - 16,654 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 44 - 16,656 - 1900 + 248,4,63 }, COLLIDER_WALL);
	App->collision->AddCollider({ 48 - 16,658 - 1900 + 248,3,60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 51 - 16,660 - 1900 + 248,3,54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 54 - 16,662 - 1900 + 248,3,50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 57 - 16,663 - 1900 + 248,2,46 }, COLLIDER_WALL);
	App->collision->AddCollider({ 59 - 16,664 - 1900 + 248,3,23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 62 - 16,665 - 1900 + 248,2,19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64 - 16,666 - 1900 + 248,3,16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 67 - 16,668 - 1900 + 248,3,12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 70 - 16,669 - 1900 + 248,1, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 71 - 16,670 - 1900 + 248,2,24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 73 - 16,670 - 1900 + 248,2,22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 75 - 16,671 - 1900 + 248,3,20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 78 - 16,674 - 1900 + 248,2,14 }, COLLIDER_WALL);

	//LAKE
	App->collision->AddCollider({ 1 - 16,493 - 1900 + 248,22,86 }, COLLIDER_LAKE);
	App->collision->AddCollider({ 1 - 16,493 - 1900 + 248,22,82 }, COLLIDER_WALL);
	App->collision->AddCollider({ 24 - 16,486 - 1900 + 248,40,85 }, COLLIDER_LAKE);
	App->collision->AddCollider({ 24 - 16,486 - 1900 + 248,40,81 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160 - 16,485 - 1900 + 248,17,94 }, COLLIDER_LAKE);
	App->collision->AddCollider({ 160 - 16,485 - 1900 + 248,17,90 }, COLLIDER_WALL);
	App->collision->AddCollider({ 176 - 16,490 - 1900 + 248,52,84 }, COLLIDER_LAKE);
	App->collision->AddCollider({ 176 - 16,490 - 1900 + 248,52,80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 228 - 16,494 - 1900 + 248,28,83 }, COLLIDER_LAKE);
	App->collision->AddCollider({ 228 - 16,494 - 1900 + 248,28,79 }, COLLIDER_WALL);

	//ENEMY
	addStaticEnemies();

	//BUNKERS

	App->collision->AddCollider({ 33 -16,479-1902+SCREEN_HEIGHT,6, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 26 - 16,477 - 1902 + SCREEN_HEIGHT,15, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 23 - 16,474 - 1902 + SCREEN_HEIGHT,20, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 17 - 16,471 - 1902 + SCREEN_HEIGHT,28, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 17 - 16,455 - 1902 + SCREEN_HEIGHT,39, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 17 - 16,458 - 1902 + SCREEN_HEIGHT,30, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 17 - 16,458 - 1902 + SCREEN_HEIGHT,30, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 17 - 16,458 - 1902 + SCREEN_HEIGHT,30, 13 }, COLLIDER_WALL);



	bridge.h = 70;
	bridge.w = 64;
	bridge.x = 1;
	bridge.y = 449;

	return true;
}

// UnLoad assets
bool ModuleSecondScene::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->elements1->Disable();

	if (App->scene_start->player_2 == true)
	{
		App->player_2->Disable();
	}
	return true;
}

void ModuleSecondScene::addStaticEnemies() {

	App->enemies->AddEnemy(ENEMY_TYPES::BIKE_M2, 216, -100, Enemy::STAY);
	App->enemies->AddEnemy(ENEMY_TYPES::CARENEMY, 16, 300, Enemy::STAY);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 145, -251, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 175, -251, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 15, -311, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 55, -311, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 165, -326, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 75, -370, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 115, -370, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 195, -430, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 30, -560, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 90, -605, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 130, -605, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 170, -605, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 30, -665, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::HOLE_TROOPER, 150, -1130, Enemy::WATER_UP);

	App->enemies->AddEnemy(ENEMY_TYPES::BUNKER, 0, -1220, Enemy::WALK_LEFT);

	App->enemies->AddEnemy(ENEMY_TYPES::BUNKER, 182, -1282, Enemy::WALK_RIGHT);

	App->enemies->AddEnemy(ENEMY_TYPES::BUNKER, 0, -1392, Enemy::WALK_LEFT);
}

// Update: draw background
update_status ModuleSecondScene::Update()
{
	// Move camera forward ----------------------------------


	// Draw everything --------------------------------------
	App->render->Blit(background, -16, -1908 + SCREEN_HEIGHT, NULL);
	App->render->Blit(textures, 96-16 ,821-1908+SCREEN_HEIGHT , &bridge, NULL);
	App->render->Blit(cave, 16 - 16, 52 - 1908 + SCREEN_HEIGHT, &caves); //sprite caves	

	if (App->input->keyboard[SDL_SCANCODE_C] == 1 && fading == false)
	{
		App->fade->FadeToBlack(this, App->end_scene, 2.0f);
		fading = true;
	}

	//enemies 
		
	//Final boss

	if (App->player->position.y == -1400)  //per saber si esta a la primera porta
	{
		enteredBossArea = true;
	}
	//Intermission

	if ((App->player->position.y <= (-1900 + 240) || App->player_2->position.y <= (-1900 + 240)) && fading == false)
	{
		enteredBossArea = false;
		finished = false;
		App->fade->FadeToBlack(this, App->end_scene, 2.0f);
		fading = true;
	}

	if ((App->player->position.y <= (-1900 + 241) || App->player_2->position.y <= (-1900 + 241)) && fading == false)
	{
		finished = true;
	}


	if (enteredBossArea) {
		App->elements1->open_doors.speed = 0.04f;
		if (current_boss_spawn_time < boss_max_spawn_time) {
			current_boss_spawn_time += 3;
		}
		else {
			if (boss_enemies_current_spawned == 3) {
				App->enemies->AddEnemy(COMMANDER, 100, -1660, Enemy::WANDER);
				current_boss_spawn_time = 0;
			}
			else if (boss_enemies_current_spawned < FINAL_BOSS_ENEMIES_2) {
				final_boss_rand = rand() % 50;
				App->enemies->AddEnemy(BOSS_TROOPER, 75 + final_boss_rand, -1700, Enemy::ENTER_DOOR);
				rand_spawn_gate = rand() % 5;
				switch (rand_spawn_gate)
				{
				case 0:
					App->enemies->AddEnemy(BOSS_TROOPER, 30, -1585, Enemy::WANDER);
					break;
				case 1:
					App->enemies->AddEnemy(BOSS_TROOPER, 180, -1585, Enemy::WANDER);
					break;
				case 2:
					App->enemies->AddEnemy(BOSS_TROOPER, 30, -1530, Enemy::WANDER);
					break;
				case 3:
					App->enemies->AddEnemy(BOSS_TROOPER, 180, -1530, Enemy::WANDER);
					break;
				case 4:
					App->enemies->AddEnemy(BOSS_TROOPER, 180, -1470, Enemy::WANDER);
					break;
				default:
					break;
				}
				current_boss_spawn_time = 0;
				
			}
			boss_enemies_current_spawned++;
		}
	}
	if (enteredBossArea && music_boss)
	{
		App->music->Unload(App->scene_map2->music);
		music = music = App->music->Load("assets/Commando_04_Fortress.ogg");
		Mix_PlayMusic(music, 100);
		music_boss = false;
	}
	else if (App->player->position.y > -1200) {
		App->enemies->spawnCommonEnemies();

	}

	return UPDATE_CONTINUE;
}
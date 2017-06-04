#include "Globals.h"
#include <time.h>
#include <stdlib.h>  
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFirstScene.h"
#include "ModuleInit.h"
#include "ModuleEndScene.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"
#include "ModuleSecondScene.h"
#include "ModuleIntermission.h"


ModuleFirstScene::ModuleFirstScene()
{}

ModuleFirstScene::~ModuleFirstScene()
{}

// Load assets
bool ModuleFirstScene::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("assets/Area1.png");
	music = App->music->Load("assets/Commando_02_Start_Demo.ogg");
	Mix_PlayMusic(music, 100);
	

	srand(time(NULL));

	App->player->position.x = 100;
	App->player->position.y = 150;
	if (App->scene_start->player_2 == true)
	{
		App->player_2->Enable();
		App->player->position.x = 70;
		App->player->position.y = 150;
		App->player_2->position.x = 120;
		App->player_2->position.y = 150;
	}
	App->render->camera.x = 0;
	App->render->camera.y = 0;


	App->player->Enable();
	if (App->scene_start->player_2 == true)
	{
		App->player_2->Enable();
		App->player_2->alive = true;
	}
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->elements1->Enable();
	
	
	//COLLIDERS LAKES------------------------------------------------------------------------
	App->collision->AddCollider({ 0,1861 - 1900 + 248,17,30 }, COLLIDER_WALL);				// 1st LAKE A
	App->collision->AddCollider({ 33-16,1847 - 1900 + 248,47,44 }, COLLIDER_WALL);			// 1st LAKE B
	App->collision->AddCollider({ 80-16,1862 - 1900 + 248,12,28 }, COLLIDER_WALL);			// 1st LAKE C
	App->collision->AddCollider({ 0,1891 - 1900 + 248,81,17 }, COLLIDER_LAKE);				// 1st LAKE WATER

	App->collision->AddCollider({ 0,1476 - 1900 + 248,7,28 }, COLLIDER_LAKE);				// 2nd LAKE WATER A
	App->collision->AddCollider({ 23-16,1484 - 1900 + 248,21,18 }, COLLIDER_LAKE);			// 2nd LAKE WATER B

	//COLLIDERS ROCKS------------------------------------------------------------------------
	App->collision->AddCollider({ 207 - 16,1717 - 1900 + 248,49,45 }, COLLIDER_WALL);		// 1st RIGHT ROCK A
	App->collision->AddCollider({ 200 - 16,1727 - 1900 + 248,7,25 }, COLLIDER_WALL);		// 1st RIGHT ROCK B

	App->collision->AddCollider({ 0,1661 - 1900 + 248,16,34 }, COLLIDER_WALL);				// 1st LEFT ROCK A
	App->collision->AddCollider({ 32 - 16, 1670 - 1900 + 248,9,20 }, COLLIDER_WALL);		// 1st LEFT ROCK B

	App->collision->AddCollider({ 218 - 16, 1484 - 1900 + 248,22,71 }, COLLIDER_WALL);		// 2nd RIGHT ROCK A
	App->collision->AddCollider({ 207 - 16, 1490 - 1900 + 248,11,58 }, COLLIDER_WALL);		// 2nd RIGHT ROCK B
	App->collision->AddCollider({ 199 - 16, 1506 - 1900 + 248,8,32 }, COLLIDER_WALL);		// 2nd RIGHT ROCK C

	App->collision->AddCollider({ 0, 1224 - 1900 + 248,53,30 }, COLLIDER_WALL);				// 2nd LEFT ROCK A
	App->collision->AddCollider({ 0, 1253 - 1900 + 248,28,36 }, COLLIDER_WALL);			// 2nd LEFT ROCK B
	App->collision->AddCollider({ 44 - 16, 1253 - 1900 + 248,14,16 }, COLLIDER_WALL);		// 2nd LEFT ROCK C
	App->collision->AddCollider({ 0, 1213 - 1900 + 248,34,10 }, COLLIDER_WALL);		// 2nd LEFT ROCK C

	App->collision->AddCollider({ 86 - 16, 1167 - 1900 + 248,8,26 }, COLLIDER_WALL);		// 1st CENTERED ROCK A
	App->collision->AddCollider({ 94 - 16, 1157 - 1900 + 248,24,43 }, COLLIDER_WALL);		// 1st CENTERED ROCK B
	App->collision->AddCollider({ 118 - 16, 1147 - 1900 + 248,29,53 }, COLLIDER_WALL);		// 1st CENTERED ROCK C
	App->collision->AddCollider({ 147 - 16, 1147 - 1900 + 248,6,46 }, COLLIDER_WALL);		// 1st CENTERED ROCK D
	App->collision->AddCollider({ 153 - 16, 1158 - 1900 + 248,13,30 }, COLLIDER_WALL);		// 1st CENTERED ROCK E
	App->collision->AddCollider({ 166 - 16, 1166 - 1900 + 248,6,12 }, COLLIDER_WALL);		// 1st CENTERED ROCK F

	App->collision->AddCollider({ 114 - 16, 738 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 1st SMALL ROCK
	App->collision->AddCollider({ 18 - 16, 706 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 2ns SMALL ROCK
	App->collision->AddCollider({ 226 - 16, 674 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 3rd SMALL ROCK
	App->collision->AddCollider({ 66 - 16, 642 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 4th SMALL ROCK
	App->collision->AddCollider({ 162 - 16, 609 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 5th SMALL ROCK
	App->collision->AddCollider({ 18 - 16, 513 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 6th SMALL ROCK
	App->collision->AddCollider({ 114 - 16, 513 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 7th SMALL ROCK
	App->collision->AddCollider({ 210 - 16, 513 - 1900 + 248,27,13 }, COLLIDER_WALL);		// 8th SMALL ROCK


	//BRIDGE COLLIDERS-----------------------------------------------------------------------
	App->collision->AddCollider({ 0, 802 - 1900 + 248,83,79 }, COLLIDER_WALL);				// 1st BRIDGE A
	App->collision->AddCollider({ 157-16, 802 - 1900 + 248,83,79 }, COLLIDER_WALL);			// 1st BRIDGE B
																							
	//COLLIDERS PALM TREES-------------------------------------------------------------------
	App->collision->AddCollider({ 219 - 16, 1812 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 164 - 16+9, 1893 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 152 - 16 + 9, 1877 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 24 - 16 + 9, 1813 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 87 - 16 + 9, 1685 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 136 - 16 + 9, 1636 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 164 - 16 + 9, 1635 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 150 - 16 + 9, 1620 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 87 - 16 + 9, 1555 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 37 - 16 + 9, 1443 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ -5 + 9, 1443 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 24 - 16 + 9, 1428 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 148 - 16 + 9, 1427 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 88 - 16 + 9, 1363 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 151 - 16 + 9, 1299 - 1900 + 248, 5, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 215 - 16 + 9, 1235 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 148 - 16 + 9,1041 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 24 - 16 + 9, 1041 - 1900 + 248,5,13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 87 - 16 + 9, 978 - 1900 + 248,5,13 }, COLLIDER_WALL);

	//COLLIDERS BARRICADES-------------------------------------------------------------------
	App->collision->AddCollider({ 133 - 16,1364 - 1900 + 248,51,15 }, COLLIDER_WALL);		// 1st BARRICADE
	App->collision->AddCollider({ 197 - 16, 915 - 1900 + 248,51,15 }, COLLIDER_WALL);		// 2nd BARRICADE
	App->collision->AddCollider({ 134 - 16,450 - 1900 + 248,80,15 }, COLLIDER_WALL);		// 3rd BARRICADE
	App->collision->AddCollider({ -13,418 - 1900 + 248,51,15 }, COLLIDER_WALL);				// 4th BARRICADE
	App->collision->AddCollider({ 102 - 16,322 - 1900 + 248,51,15 }, COLLIDER_WALL);		// 5th BARRICADE
	App->collision->AddCollider({ 0,290 - 1900 + 248,71,15 }, COLLIDER_WALL);				// 6th BARRICADE
	App->collision->AddCollider({ 198 - 16, 226 - 1900 + 248,51,15 }, COLLIDER_WALL);		// 7th BARRICADE

	//COLLIDERS GRENADE BOX------------------------------------------------------------------

	box = App->collision->AddCollider({ 153 - 16, 1332 - 1652, 20, 16 }, COLLIDER_GRENADE_BOX);		// 1st BOX
	box1 = App->collision->AddCollider({ 187 - 16, 899 - 1652, 20, 16 }, COLLIDER_GRENADE_BOX);		// 2nd BOX
	box2 = App->collision->AddCollider({ 26 - 16, 255 - 1652, 20, 16 }, COLLIDER_GRENADE_BOX);		// 3rd BOX
	box3 = App->collision->AddCollider({ 190 - 16, 210 - 1652, 14, 12 }, COLLIDER_GRENADE_BOX);		// 4rd BOX



	//COLLIDERS FINAL WALL-------------------------------------------------------------------
	App->collision->AddCollider({ 0, 0 - 1900 + 228,76,83 }, COLLIDER_WALL);				//FINAL WALL LEFT
	App->collision->AddCollider({ 165-16, 0 - 1900 + 228,76,83 }, COLLIDER_WALL);			//FINAL WALL RIGHT	
	App->collision->AddCollider({ 0, 0 - 1900 + 228,76,83 }, COLLIDER_FINAL_WALL);				//FINAL WALL LEFT
	App->collision->AddCollider({ 165 - 16, 0 - 1900 + 228,76,83 }, COLLIDER_FINAL_WALL);			//FINAL WALL RIGHT
	
	//ENEMIES-----------------------------------------------------------------------
	/*App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_1, 160, -300);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_1, 160, -100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_1, 160, -50);*/
	//App->enemies->AddEnemy(ENEMY_TYPES::RIFLEMAN, 140, 80, Enemy::LEAVE); //aquest el faig servir per veure com es comporten els enemics, si el voleu treure comenteulo pero no borreu -pol
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONER_ENEMIES, 140, -543, Enemy::STAY);
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONER, 155, -543, Enemy::STAY);
	App->enemies->AddEnemy(ENEMY_TYPES::PRISONER_ENEMIES, 170, -543, Enemy::STAY);

	App->enemies->AddEnemy(ENEMY_TYPES::BIKEENEMY, 200, -850, Enemy::STAY);

	//App->enemies->AddEnemy(ENEMY_TYPES::GRANADIER, 50, 80, Enemy::WANDER);

	////////ENEMIES BEHIND COVER

	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 135, -300, Enemy::HOLD_POSITION); //First trench
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 97, -935, Enemy::HOLD_POSITION); //first rock
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 2, -970, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 200, -1000, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 47, -1033, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 143, -1064, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 2, -1161, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 96, -1161, Enemy::HOLD_POSITION);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 187, -1161, Enemy::HOLD_POSITION);

	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 167, -1211, Enemy::TURRET);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 10, -1244, Enemy::TURRET);
	App->enemies->AddEnemy(ENEMY_TYPES::BARRICADE_TROOPER, 117, -1339, Enemy::TURRET);

	//make the player alive
	App->player->alive = true;
	

	return true;
}

// UnLoad assets
bool ModuleFirstScene::CleanUp()
{
	LOG("Unloading space scene");
	App->textures->Unload(background);
	
	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();
	if (App->scene_start->player_2 == true)
	{
		App->player_2->Disable();
	}
	App->elements1->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleFirstScene::Update()
{
	// Move camera forward -----------------------------

	// Draw everything --------------------------------------
	App->render->Blit(background, -16, -1908+SCREEN_HEIGHT, NULL);

	if ((App->input->keyboard[SDL_SCANCODE_C] == 1))
	{
		App->fade->FadeToBlack(this, App->scene_map2, 2.0f);
		fading = true;
	}

	//Intermissions	
	if ((App->player->position.y <= (-1900 + 240)|| App->player_2->position.y <= (-1900 + 240)) && fading == false)
	{
		enteredBossArea = false;
		App->fade->FadeToBlack(this, App->inter_scene, 2.0f);
		fading = true;
	}

	//Final boss

	if (App->player->position.y == -1500 || App->player_2->position.y == -1500)  //per saber si esta a la primera porta
	{
		enteredBossArea = true;
	}
	if (App->player->position.y == -1400 || App->player_2->position.y == -1400)  //per saber si esta a la primera porta
	{
		music_boss = true;
	}


	if (enteredBossArea) {
		App->elements1->open_doors.speed = 0.04f;
		if (current_boss_spawn_time < boss_max_spawn_time) {
			current_boss_spawn_time += 5;
		}
		else {
			if (boss_enemies_current_spawned == 3) {
				App->enemies->AddEnemy(COMMANDER, 100, -1660, Enemy::WANDER);
				current_boss_spawn_time = 0;
			}
			else if (boss_enemies_current_spawned < FINAL_BOSS_ENEMIES_1) {
				final_boss_rand = rand() % 50;
				App->enemies->AddEnemy(BOSS_TROOPER, 75 + final_boss_rand, -1700, Enemy::ENTER_DOOR);
			}
			current_boss_spawn_time = 0;
			boss_enemies_current_spawned++;
		}
	}
	if (enteredBossArea && music_boss)
	{
		App->music->Unload(App->first_scene->music);
		music = music = App->music->Load("assets/Commando_04_Fortress.ogg");
		Mix_PlayMusic(music, 100);
		music_boss = false;
	}
	else if (App->player->position.y > -1200) {
		App->enemies->spawnCommonEnemies();                                     // Comenteu aixo si voleu desactivar els enemics
	}
	
	return UPDATE_CONTINUE;
}
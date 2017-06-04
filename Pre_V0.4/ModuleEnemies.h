#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Enemy.h"

#define MAX_ENEMIES 10000
#define ENEMY_BULLET_SPEED 1
#define ENEMY_SHOT_DELAY 150
#define ENEMY_GRENADE_DELAY 400

#define SPAWN_MARGIN 1000

enum ENEMY_TYPES
{
	NO_TYPE,
	RIFLEMAN,
	PRISONER_ENEMIES,
	PRISONER,
	BIKEENEMY,
	GRANADIER,
	BARRICADE_TROOPER,
	BOSS_TROOPER,
	COMMANDER,
	BIKE_M2,
	CARENEMY,
	HOLE_TROOPER,
	BUNKER,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	Enemy::Behaviour behaviour = Enemy::STAY;
	Enemy::Behaviour previous_behaviour;
	int x, y;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	Animation* current_animation;

	bool AddEnemy(ENEMY_TYPES type, int x, int y, Enemy::Behaviour behaviour);
	void eliminateEnemy(Enemy* e, int i);
	void spawnCommonEnemies();

	int rand_rifle_man_spawn_behaviour;
	int rand_spawn_y_offset;
	float rand_bounce_angle;

	int enemies_on_action = 0;

private:

	void SpawnEnemy(const EnemyInfo& info);

	int automated_rifleman_spawn_time = 370;
	int automated_rifleman_spawn_current_time = 0;

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__
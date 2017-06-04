#include <math.h>
#include "Application.h"
#include "Bunker.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Bunker::Bunker(int x, int y) : Enemy (x, y) {

	type = 1;
	collider = App->collision->AddCollider({ (int)position.x + 5, (int)position.y, 34, 54 }, COLLIDER_TYPE::COLLIDER_ENEMY_BEHIND_COVER, (Module*)App->enemies);

	death = &aimDownLEFT;

	aimStraightLEFT.PushBack({42, 398, 40, 50 });
	aimStraightLEFT.loop = false;

	aimDownLEFT.PushBack({ 42, 398, 40, 50 });
	aimDownLEFT.PushBack({83, 398, 40, 50 });
	aimDownLEFT.PushBack({124, 398, 40, 50 });
	aimDownLEFT.loop = false;
	aimDownLEFT.speed = 0.5;
		
	aimUpLEFT.PushBack({ 42, 398, 40, 50 });
	aimUpLEFT.PushBack({ 1, 398, 40, 50 });
	aimUpLEFT.loop = false;
	aimUpLEFT.speed = 0.5;

	aimStraightRIGHT.PushBack({ 329, 398, 40, 50 });
	aimStraightRIGHT.loop = false;

	aimDownRIGHT.PushBack({ 329, 398, 40, 50 });
	aimDownRIGHT.PushBack({ 288, 398, 40, 50 });
	aimDownRIGHT.PushBack({247, 398, 40, 50 });
	aimDownRIGHT.loop = false;
	aimDownRIGHT.speed = 0.5;

	aimUpRIGHT.PushBack({ 329, 398, 40, 50 });
	aimUpRIGHT.PushBack({ 370, 398, 40, 50 });
	aimUpRIGHT.loop = false;
	aimUpRIGHT.speed = 0.5;

	//POL, HI HA UN SPRITE PER QUAN REBEN UN DISPAR, QUE S'HAURIA DE FER UN BLIT() IF HIT 1 GRENADE O UNA ANIMACIO A SOBRE?, 
	//I SI LI DONEN DUES GRENADES DESAPAREIX EL BLIT I LES ANIMACIONS I ES QUEDA LA IMATGE DEL BACKGROUND DEL BUNKER DESTROSSAT
	//ET DEIXO LES COORDS:
	// leftHit ({165, 398, 40, 50 }); rightHit ({206, 398, 40, 50});
}

void Bunker::Move() {
	switch (behaviour)
	{
	case Enemy::WALK_LEFT:
		break;
	case Enemy::WALK_RIGHT:
		break;
	default:
		break;
	}
	update_animation();
	aim_to_player();
	shoot();
	
}
float Bunker::aim_to_player() {
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
void Bunker::update_animation(){
	switch (behaviour)
	{
	case Enemy::WALK_LEFT:
		if (aim_to_player()> 0.64) {
			animation = &aimDownLEFT;
		}
		else if (aim_to_player()< 0.18) {
			animation = &aimUpLEFT;
		}
		else {
			animation = &aimStraightLEFT;
		}
		break;
	case Enemy::WALK_RIGHT:
		if (aim_to_player() <2.54) {
			animation = &aimDownRIGHT;
		}
		else if (aim_to_player() >3.18) {
			animation = &aimUpRIGHT;
		}
		else {
			animation = &aimStraightRIGHT;
		}
		break;
	default:
		break;
	}
}
void Bunker::shoot() {
	shoot_direction = aim_to_player();
	App->particles->enemy_bullet.speed.y = sin(shoot_direction) * ENEMY_BULLET_SPEED;
	App->particles->enemy_bullet.speed.x = cos(shoot_direction) * ENEMY_BULLET_SPEED;

	//App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);

	if (shot_current_delay < ENEMY_SHOT_DELAY)
		shot_current_delay++;
	else {
		App->particles->AddParticle(App->particles->enemy_bullet, position.x + 11, position.y + 22, COLLIDER_ENEMY_SHOT);
		shot_current_delay = 0;
	}
}
#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer2.h"
#include "ModulePlayer.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "ModuleFirstScene.h"
#include "ModuleSecondScene.h"
#include "ModuleEnemies.h" 

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 120;
	position.y = 150;

	// idle animation 
	idleUP.PushBack({ 1, 28, 29, 26 });
	idleDown.PushBack({ 91, 28, 29, 26 });
	idleRight.PushBack({ 1,1,29,26 });
	idleLeft.PushBack({ 91,1,29,26 });
	idleRightUP.PushBack({ 1, 82, 29, 26 });
	idleRightDOWN.PushBack({ 1, 109, 29, 26 });
	idleLeftUP.PushBack({ 1, 55, 29, 26 });
	idleLeftDOWN.PushBack({ 1, 136, 29, 26 });

	// Move up
	up.PushBack({ 1, 28, 29, 26 });
	up.PushBack({ 31, 28, 29, 26 });
	up.PushBack({ 1, 28, 29, 26 });
	up.PushBack({ 61, 28, 29, 26 });
	up.loop = true;
	up.speed = 0.1f;

	// Move down
	down.PushBack({ 421-330, 28, 29, 26 });
	down.PushBack({ 451 - 330, 28, 29, 26 });
	down.PushBack({ 421 - 330, 28, 29, 26 });
	down.PushBack({ 481 - 330, 28, 29, 26 });
	down.loop = true;
	down.speed = 0.1f;

	// Move Right
	right.PushBack({ 331 - 330,1,29,26 });
	right.PushBack({ 361 - 330,1,29,26 });
	right.PushBack({ 331 - 330,1,29,26 });
	right.PushBack({ 391 - 330,1,29,26 });

	right.loop = true;
	right.speed = 0.1f;

	// Move Left
	left.PushBack({ 421 - 330,1,29,26 });
	left.PushBack({ 451 - 330,1,29,26 });
	left.PushBack({ 421 - 330,1,29,26 });
	left.PushBack({ 481 - 330,1,29,26 });

	left.loop = true;
	left.speed = 0.1f;

	// Move RightUP;
	rightUP.PushBack({ 361 - 330, 82, 29,26 });
	rightUP.PushBack({ 391 - 330, 82,29,26 });
	rightUP.PushBack({ 361 - 330,82, 29,26 });
	rightUP.PushBack({ 421 - 330,82,29,26 });
	rightUP.loop = true;
	rightUP.speed = 0.1f;

	// Move LeftUP
	leftUP.PushBack({ 361 - 330,55, 29,26 });
	leftUP.PushBack({ 391 - 330, 55,29,26 });
	leftUP.PushBack({ 361 - 330,55,29,26 });
	leftUP.PushBack({ 421 - 330,55,29,26 });
	leftUP.loop = true;
	leftUP.speed = 0.1f;

	// Move RightDOWN
	rightDOWN.PushBack({ 361 - 330,109, 29,26 });
	rightDOWN.PushBack({ 391 - 330, 109,29,26 });
	rightDOWN.PushBack({ 361 - 330,109,29,26 });
	rightDOWN.PushBack({ 421 - 330,109,29,26 });
	rightDOWN.loop = true;
	rightDOWN.speed = 0.1f;

	// Move LeftDOWN
	leftDOWN.PushBack({ 361 - 330,136, 29,26 });
	leftDOWN.PushBack({ 391 - 330, 136,29,26 });
	leftDOWN.PushBack({ 361 - 330,136,29,26 });
	leftDOWN.PushBack({ 421 - 330,136,29,26 });
	leftDOWN.loop = true;
	leftDOWN.speed = 0.1f;

	//DIE
	die.PushBack({ 331 - 330,190,29,26 });
	die.PushBack({ 361 - 330,190,29,26 });
	die.PushBack({ 391 - 330,190,29,26 });
	die.loop = false;
	die.speed = 0.05f;

	//lake death
	waterDie.PushBack({ 421 - 330,190,29,26 });
	waterDie.PushBack({ 451 - 330,190,29,26 });
	waterDie.PushBack({ 481 - 330,190,29,26 });
	waterDie.loop = false;
	waterDie.speed = 0.1f;

	//grenade throw
	grenadeThrow.PushBack({ 331 - 330,163,29,26 });
	grenadeThrow.PushBack({ 361 - 330,163,29,26 });
	grenadeThrow.PushBack({ 391 - 330,163,29,26 });
	grenadeThrow.loop = false;
	grenadeThrow.speed = 0.1f;

}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/player_2.png");
	//graphics2= App->textures->Load("assets/Superjoes12.png");

	playercoll = App->collision->AddCollider({ position.x + 7, position.y, 14, 23 }, COLLIDER_PLAYER, this);
	feetcoll = App->collision->AddCollider({ position.x + 7, position.y, 14, 10 }, COLLIDER_FEET, this);
	font_score = App->fonts->Load("fonts/Lletres_1.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ./\ ", 2);
	bridge = App->textures->Load("assets/Bridge.png");

	stop = false;
	anim = false;
	water = false;
	grenade = false;
	god = false;
	counter = 0;
	only = true;
	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);
	App->textures->Unload(bridge);
	if (playercoll != nullptr)
		playercoll->to_delete = true;

	return true;
}
// Update: draw background
update_status ModulePlayer2::Update()
{
	int speed=1;

	if (abs(App->player->position.y - position.y) >= (248 - 165) && App->player->position.y > position.y &&  App->elements1->num_lives_play_1>0)
	{
		distance = true;;
	}
	else
	{
		distance = false;
	}
	

	//DOWNLEFT
	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT ||
		App->input->P2_controll[1] == KEY_STATE::KEY_REPEAT && App->input->P2_controll[3] == KEY_STATE::KEY_REPEAT)
		&& position.x>-5 && position.y <= 232 - (App->render->camera.y / SCREEN_SIZE) && anim == false && water == false)
	{
		if (current_animation != &leftDOWN && App->input->keyboard[SDL_SCANCODE_W] != KEY_STATE::KEY_REPEAT
			&& (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[1] == KEY_STATE::KEY_REPEAT) && grenade == false)
		{   //Cal canviar les animacions
			leftDOWN.Reset();
			current_animation = &leftDOWN;
		}
		direction = transitionToDirection(direction, 0.75 * M_PI);
		position.x -= speed;
		position.y += speed;
		player_last_direction = DOWNLEFT;

	}
	//DOWNRIGHT
	else if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT ||
		App->input->P2_controll[1] == KEY_STATE::KEY_REPEAT && App->input->P2_controll[2] == KEY_STATE::KEY_REPEAT)
		&& position.x <= SCREEN_WIDTH - 23 && position.y <= 232 - (App->render->camera.y / SCREEN_SIZE) && anim == false && water == false)
	{
		if (current_animation != &rightDOWN && App->input->keyboard[SDL_SCANCODE_W] != KEY_STATE::KEY_REPEAT
			&& (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[1] == KEY_STATE::KEY_REPEAT) && grenade == false)
		{   //Cal canviar les animacions
			rightDOWN.Reset();
			current_animation = &rightDOWN;
		}
		direction = transitionToDirection(direction, 0.25 * M_PI);
		position.x += speed;
		position.y += speed;
		player_last_direction = DOWNRIGHT;

	}
	//UPLEFT
	else if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT ||
		App->input->P2_controll[0] == KEY_STATE::KEY_REPEAT && App->input->P2_controll[3] == KEY_STATE::KEY_REPEAT )
		&& position.x>-5 && anim == false && water == false)
	{
		if (current_animation != &leftUP && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[0] == KEY_STATE::KEY_REPEAT)
			&& App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT && grenade == false)
		{   //Cal canviar les animacions
			leftUP.Reset();
			current_animation = &leftUP;
		}
		direction = transitionToDirection(direction, 1.25 * M_PI);
		if (distance == false)
		{
			position.x -= speed;
			position.y -= speed;
		}
		player_last_direction = UPLEFT;

	}
	//UPRIGHT
	else if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT ||
		App->input->P2_controll[0] == KEY_STATE::KEY_REPEAT && App->input->P2_controll[2] == KEY_STATE::KEY_REPEAT)
		&& position.x <= SCREEN_WIDTH - 23 && anim == false && water == false )
	{
		if (current_animation != &rightUP && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[0] == KEY_STATE::KEY_REPEAT)
			&& App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT && grenade == false)
		{//Cal canviar les animacions
			rightUP.Reset();
			current_animation = &rightUP;
		}
		direction = transitionToDirection(direction, 1.75 * M_PI);
		if (distance == false)
		{
			position.x += speed;
			position.y -= speed;
		}
		player_last_direction = UPRIGHT;

	}

	//LEFT  <- Oye ho he canviat perque el d'abans era tot lios, crec que ara es mes eficient (pol)
	else if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[3] == KEY_STATE::KEY_REPEAT)
		&& position.x>-5 && anim == false && water == false)
	{
		if (current_animation != &left && App->input->keyboard[SDL_SCANCODE_W] != KEY_STATE::KEY_REPEAT
			&& App->input->keyboard[SDL_SCANCODE_S] != KEY_STATE::KEY_REPEAT  && grenade == false)
		{
			left.Reset();
			current_animation = &left;
		}
		direction = transitionToDirection(direction, M_PI);
		position.x -= speed;
		player_last_direction = LEFT;

	}

	//RIGHT
	else if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[2] == KEY_STATE::KEY_REPEAT)
		&& position.x <= SCREEN_WIDTH - 23 && anim == false && water == false)
	{
		if (current_animation != &right  && grenade == false)
		{
			right.Reset();
			current_animation = &right;
		}
		direction = transitionToDirection(direction, 2 * M_PI);
		position.x += speed;
		player_last_direction = RIGHT;

	}
	//DOWN
	else if ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[1] == KEY_STATE::KEY_REPEAT)
		&& anim == false && position.y <= 232 - (App->render->camera.y / SCREEN_SIZE) && water == false)
	{
		if (current_animation != &down && grenade == false)
		{
			down.Reset();
			current_animation = &down;
		}
		direction = transitionToDirection(direction, M_PI / 2);
		position.y += speed;
		player_last_direction = DOWN;

	}
	//UP
	else if ((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->P2_controll[0] == KEY_STATE::KEY_REPEAT)
		&& anim == false && water == false)
	{
		if (current_animation != &up && grenade == false)
		{
			up.Reset();
			current_animation = &up;
		}
		direction = transitionToDirection(direction, 1.5 * M_PI);
		if (distance == false)
		{
			position.y -= speed;
		}
		player_last_direction = UP;

	}

	//SHOT 
	App->particles->bullet.speed.y = sin(direction) * BULLET_SPEED;
	App->particles->bullet.speed.x = cos(direction) * BULLET_SPEED;
	shot();

	if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN ||
		App->input->P2_controll[4] == KEY_STATE::KEY_REPEAT)
	{   //Mes maco que lo de dalt no? (lo de dalt es pot borrar ja que ja no funciona )
		shooting = true;
	}


	if (anim == true)
	{
		current_animation = &die;
		if (current_animation->Finished() == true)
		{
			current_animation->Reset();
			if (App->elements1->num_lives_play_1 > 0)
			{
					position.x = App->player->position.x - 16;
					position.y = App->player->position.y;

				anim = false;
				alive = true;
				only = true;
				//RELOADING GRENADE BOXES TO THEIR POSITIONS
				App->elements1->pickupBox = false;
				App->elements1->pickupBox1 = false;
				App->elements1->pickupBox2 = false;
				App->elements1->pickupBox3 = false;
				App->first_scene->box->SetPos(153 - 16, 1332 - 1652);		// 1st BOX
				App->first_scene->box1->SetPos(187 - 16, 899 - 1652);		// 2nd BOX
				App->first_scene->box2->SetPos(26 - 16, 255 - 1652);		// 3rd BOX
				App->first_scene->box3->SetPos(190 - 16, 210 - 1652);		// 4rd BOX
			}
			else
			{

				if (App->first_scene->IsEnabled() == true)
				{
					App->fade->FadeToBlack((Module*)App->first_scene, (Module*)App->end_scene);
					App->elements1->num_score = 0;
					anim = false;
					counter = 0;
				}
				if(App->scene_map2->IsEnabled() == true)
				{
					App->fade->FadeToBlack((Module*)App->scene_map2, (Module*)App->end_scene);
					App->elements1->num_score = 0;
					anim = false;
					counter = 0;
				}


			}
		}
	}

	if (water == true)
	{
		current_animation = &waterDie;
		if (current_animation->Finished() == true)
		{
			current_animation->Reset();
			if (App->elements1->num_lives_play_1 >0)
			{
					position.x = App->player->position.x - 16;
					position.y = App->player->position.y;
				
					if (App->first_scene->IsEnabled() == true)
					{
						position.x = position.x + 50;
						position.y = position.y;
					}
				
				water = false;
				alive = true;
				only = true;
			}
			else
			{
				if (App->first_scene->IsEnabled() == true && App->elements1->num_lives_play_1 == 0)
				{
					App->fade->FadeToBlack((Module*)App->first_scene, (Module*)App->end_scene);
					App->elements1->num_score = 0;
					counter = 0;
				}
				if (App->scene_map2->IsEnabled() == true && App->elements1->num_lives_play_1 == 0)
				{
					App->fade->FadeToBlack((Module*)App->scene_map2, (Module*)App->end_scene);
					App->elements1->num_score = 0;
					counter = 0;
				}
			}

		}
	}

	// Grenade

	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN ||
		App->input->P2_controll[5] == KEY_STATE::KEY_DOWN) {   //Mes maco que lo de dalt no? (lo de dalt es pot borrar ja que ja no funciona )
		if (App->elements1->num_grenades > 0) {
			current_animation = &grenadeThrow;
			if (grenade == false)
				App->particles->AddParticle(App->particles->grenade, position.x + 11, position.y + 3, COLLIDER_NONE);
		}
		grenade = true;
	}
	if (grenade) {
		if (current_animation->Finished() == true) {
			current_animation->Reset();
			grenade = false;
		}
	}

	//IDLE ANIMATIONS
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->P2_controll[0] == KEY_STATE::KEY_IDLE
		&& App->input->P2_controll[1] == KEY_STATE::KEY_IDLE
		&& App->input->P2_controll[2] == KEY_STATE::KEY_IDLE
		&& App->input->P2_controll[3] == KEY_STATE::KEY_IDLE
		&& anim == false && water == false && grenade == false)
	{
		switch (player_last_direction)
		{
		case ModulePlayer::UP:
			current_animation = &idleUP;
			direction = 1.5 * M_PI;
			break;
		case ModulePlayer::DOWN:
			current_animation = &idleDown;
			direction = M_PI / 2;
			break;
		case ModulePlayer::LEFT:
			current_animation = &idleLeft;
			direction = M_PI;
			break;
		case ModulePlayer::RIGHT:
			current_animation = &idleRight;
			direction = 2 * M_PI;
			break;
		case ModulePlayer::UPLEFT:
			current_animation = &idleLeftUP;
			direction = 1.25 * M_PI;
			break;
		case ModulePlayer::UPRIGHT:
			current_animation = &idleRightUP;
			direction = 1.75 * M_PI;
			break;
		case ModulePlayer::DOWNLEFT:
			current_animation = &idleLeftDOWN;
			direction = 0.75 * M_PI;
			break;
		case ModulePlayer::DOWNRIGHT:
			current_animation = &idleRightDOWN;
			direction = 0.25 * M_PI;
			break;
		default:
			break;
		}
	}

	if (App->input->P2_controll[6] == KEY_STATE::KEY_DOWN)
	{
		if (god == true && App->player->god == true)
		{
			god = false;
			App->player->god = false;
		}
		else
		{
			god = true;
			App->player->god = true;
		}
	}
	if (god == true)
	{
		App->fonts->BlitText(0, 230 - (App->render->camera.y / SCREEN_SIZE), font_score, "G");
	}



	playercoll->SetPos(position.x + 7, position.y);
	feetcoll->SetPos(position.x + 7, position.y + 13);


	// Draw everything --------------------------------------
	if (current_animation != nullptr) {
		if (anim == false && water == false)
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		else
			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	}
	if (App->first_scene->IsEnabled() == true)
		App->render->Blit(bridge, 80, -850, NULL);
	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_WALL)
	{
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT
			|| App->input->P2_controll[0] == KEY_STATE::KEY_REPEAT))
		{
			position.y += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT
			|| App->input->P2_controll[1] == KEY_STATE::KEY_REPEAT))
		{
			position.y -= 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
			|| App->input->P2_controll[3] == KEY_STATE::KEY_REPEAT))
		{
			position.x += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
			|| App->input->P2_controll[2] == KEY_STATE::KEY_REPEAT))
		{
			position.x -= 1;
		}
	}
	if (c2->type == COLLIDER_LAKE && god == false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			water = true;
		}
	}
	if (c2->type == COLLIDER_ENEMY_SHOT && god == false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			anim = true;
		}
	}
	if (c2->type == COLLIDER_ENEMY && god == false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			anim = true;
		}
	}
	if (c2->type == COLLIDER_GRENADE_BOX)
	{
		if (App->elements1->num_grenades < 100) { //ADDS GRENADES 
			if (c2->rect.x == App->first_scene->box->rect.x && c2->rect.y == App->first_scene->box->rect.y || c2->rect.x == App->first_scene->box2->rect.x && c2->rect.y == App->first_scene->box2->rect.y) { //CHECKING WHICH BOX IT IS, HOW MANY GRENADES ARE IN IT
				for (int i = 0; i < 3; ++i) {
					++App->elements1->num_grenades;
				}
			}
			if (c2->rect.x == App->first_scene->box1->rect.x && c2->rect.y == App->first_scene->box1->rect.y) { //CHECKING WHICH BOX IT IS, HOW MANY GRENADES ARE IN IT
				for (int i = 0; i < 5; ++i) {
					++App->elements1->num_grenades;
				}
			}
			if (c2->rect.x == App->first_scene->box3->rect.x && c2->rect.y == App->first_scene->box3->rect.y) { //CHECKING WHICH BOX IT IS, HOW MANY GRENADES ARE IN IT
				for (int i = 0; i < 1; ++i) {
					++App->elements1->num_grenades;
				}
			}
		}
		if (c2->rect.x == App->first_scene->box->rect.x && c2->rect.y == App->first_scene->box->rect.y) { //MOVES THE GRENADE BOX TEXTURE AND COLLIDER AWAY FROM WINDOW
			App->first_scene->box->SetPos(2000, 0);
			App->elements1->pickupBox = true;

		}
		if (c2->rect.x == App->first_scene->box1->rect.x && c2->rect.y == App->first_scene->box1->rect.y) { //MOVES THE GRENADE BOX TEXTURE AND COLLIDER AWAY FROM WINDOW
			App->first_scene->box1->SetPos(2000, 0);
			App->elements1->pickupBox1 = true;
		}
		if (c2->rect.x == App->first_scene->box2->rect.x && c2->rect.y == App->first_scene->box2->rect.y) { //MOVES THE GRENADE BOX TEXTURE AND COLLIDER AWAY FROM WINDOW
			App->first_scene->box2->SetPos(2000, 0);
			App->elements1->pickupBox2 = true;
		}
		if (c2->rect.x == App->first_scene->box3->rect.x && c2->rect.y == App->first_scene->box3->rect.y) { //MOVES THE GRENADE BOX TEXTURE AND COLLIDER AWAY FROM WINDOW
			App->first_scene->box3->SetPos(2000, 0);
			App->elements1->pickupBox3 = true;
		}
	}
}

float ModulePlayer2::transitionToDirection(float current_direction, float final_direction) {
	float speed = 0.1;
	float closer_direction;
	float margin = 0.15;

	if ((final_direction - current_direction) >= M_PI) {
		final_direction += 2 * M_PI;
	}
	if (fabsf(current_direction - final_direction) < margin) {
		closer_direction = final_direction;
	}
	else if (current_direction > (final_direction))
		closer_direction = current_direction - speed;
	else if (current_direction < (final_direction))
		closer_direction = current_direction + speed;
	else
		closer_direction = final_direction;

	return closer_direction;
}

void ModulePlayer2::shot() {

	if (shots_fired < SHOTS_PER_BURST && shooting == true) {
		if (shot_current_delay < SHOT_DELAY)
			shot_current_delay++;
		else {
			App->particles->AddParticle(App->particles->bullet, position.x + 11, position.y + 3, COLLIDER_PLAYER_SHOT);
			shots_fired++;
			shot_current_delay = 0;
		}
	}
	else {
		shots_fired = 0;
		shooting = false;
	}
}

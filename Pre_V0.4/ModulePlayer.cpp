#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "ModuleInit.h"
#include "ModuleFirstScene.h"
#include "ModuleSecondScene.h"
#include "ModuleEnemies.h" 
	
ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 150;
	

	// idle animation 
	idleUP.PushBack({ 331, 28, 29, 26 });
	idleDown.PushBack({ 421, 28, 29, 26 });
	idleRight.PushBack({ 331,1,29,26 });
	idleLeft.PushBack({ 421,1,29,26 });
	idleRightUP.PushBack({331, 82, 29, 26 });
	idleRightDOWN.PushBack({331, 109, 29, 26 });
	idleLeftUP.PushBack({331, 55, 29, 26 });
	idleLeftDOWN.PushBack({331, 136, 29, 26 });

	// Move up
	up.PushBack({ 331, 28, 29, 26 });
	up.PushBack({361, 28, 29, 26 });
	up.PushBack({ 331, 28, 29, 26 });
	up.PushBack({391, 28, 29, 26 });
	up.loop = true;  
	up.speed = 0.1f;

	// Move down
	down.PushBack({ 421, 28, 29, 26 });
	down.PushBack({ 451, 28, 29, 26 });
	down.PushBack({421, 28, 29, 26 });
	down.PushBack({ 481, 28, 29, 26 });
	down.loop = true;
	down.speed = 0.1f;

	// Move Right
	right.PushBack({ 331,1,29,26 });
	right.PushBack({361,1,29,26 });
	right.PushBack({331,1,29,26 });
	right.PushBack({ 391,1,29,26 });

	right.loop = true;
	right.speed = 0.1f;

	// Move Left
	left.PushBack({421,1,29,26 });
	left.PushBack({451,1,29,26 });
	left.PushBack({421,1,29,26 });
	left.PushBack({ 481,1,29,26 });

	left.loop = true;
	left.speed = 0.1f;

	// Move RightUP;
	rightUP.PushBack({ 361, 82, 29,26 });
	rightUP.PushBack({ 391, 82,29,26 });
	rightUP.PushBack({ 361,82, 29,26 });
	rightUP.PushBack({ 421,82,29,26 });
	rightUP.loop = true;
	rightUP.speed = 0.1f;

	// Move LeftUP
	leftUP.PushBack({ 361,55, 29,26 });
	leftUP.PushBack({ 391, 55,29,26 });
	leftUP.PushBack({ 361,55,29,26 });
	leftUP.PushBack({ 421,55,29,26 });
	leftUP.loop = true;
	leftUP.speed = 0.1f;

	// Move RightDOWN
	rightDOWN.PushBack({ 361,109, 29,26 });
	rightDOWN.PushBack({ 391, 109,29,26 });
	rightDOWN.PushBack({ 361,109,29,26 });
	rightDOWN.PushBack({ 421,109,29,26 });
	rightDOWN.loop = true;
	rightDOWN.speed = 0.1f;

	// Move LeftDOWN
	leftDOWN.PushBack({ 361,136, 29,26 });
	leftDOWN.PushBack({ 391, 136,29,26 });
	leftDOWN.PushBack({ 361,136,29,26 });
	leftDOWN.PushBack({ 421,136,29,26 });
	leftDOWN.loop = true;
	leftDOWN.speed = 0.1f;

	//DIE
	die.PushBack({331,190,29,26});
	die.PushBack({ 361,190,29,26 });
	die.PushBack({ 391,190,29,26 });
	die.loop = false;
	die.speed = 0.05f;	

	//lake death
	waterDie.PushBack({ 421,190,29,26 });
	waterDie.PushBack({ 451,190,29,26 });
	waterDie.PushBack({ 481,190,29,26 });
	waterDie.loop = false;
	waterDie.speed = 0.1f;

	//grenade throw
	grenadeThrow.PushBack({ 331,163,29,26 });
	grenadeThrow.PushBack({ 361,163,29,26 });
	grenadeThrow.PushBack({ 391,163,29,26 });	
	grenadeThrow.loop = false;
	grenadeThrow.speed = 0.1f;


	open_doors.PushBack({ 511,1,98,42 });
	open_doors.PushBack({ 511,44,98,56 });
	open_doors.PushBack({ 511,101,98,59 });
	open_doors.speed = 0.1f;
	open_doors.loop = false;

	close_doors.PushBack({ 511,44,98,56 });
	close_doors.PushBack({ 511,1,98,42 });
	close_doors.speed = 0.04f;
	close_doors.loop = false;

	bridgerino.PushBack({ 1,449,64,70 });
	bridgerino.speed = 0.1f;
	bridgerino.loop = false;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");



	graphics = App->textures->Load("assets/PlaceHolder_Sprites.png");
	//graphics2= App->textures->Load("assets/Superjoes12.png");
	
	playercoll = App->collision->AddCollider({ position.x+7, position.y, 14, 23 }, COLLIDER_PLAYER,this);
	feetcoll= App->collision->AddCollider({ position.x+7, position.y, 14, 10 }, COLLIDER_FEET, this);
	font_score = App->fonts->Load("fonts/Lletres_1.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ./\ ", 2);
	textures = App->textures->Load("assets/PlaceHolder_Sprites.png");

	bridge.x = 511; bridge.y = 161; bridge.h = 70; bridge.w = 98;

	if (App->scene_start->player_2 == true)
	{
		position.x = 70;
		position.y = 150;
	}

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
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);
	App->textures->Unload(textures);
	if (playercoll != nullptr)
		playercoll->to_delete = true;

	return true;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	if (App->scene_start->player_2 == true )
	{
		if (abs(App->player_2->position.y - position.y) >= (248 - 165) && App->player_2->position.y > position.y)
		{
			distance = true;;
		}
		else
		{
			distance = false;
		}

	}

	//DOWNLEFT
	if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT ||
		App->input->controll[1] == KEY_STATE::KEY_REPEAT && App->input->controll[3] == KEY_STATE::KEY_REPEAT)
		&& position.x>-5 && position.y <= 232 - (App->render->camera.y / SCREEN_SIZE) && anim==false && water == false)
	{
		if (current_animation != &leftDOWN && App->input->keyboard[SDL_SCANCODE_UP] != KEY_STATE::KEY_REPEAT
			&& (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || App->input->controll[1] == KEY_STATE::KEY_REPEAT) && grenade == false)
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
	else if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT ||
				App->input->controll[1] == KEY_STATE::KEY_REPEAT && App->input->controll[2] == KEY_STATE::KEY_REPEAT)
		          && position.x<=SCREEN_WIDTH-23 && position.y <= 232 - (App->render->camera.y / SCREEN_SIZE) && anim == false && water == false)
	{
		if (current_animation != &rightDOWN && App->input->keyboard[SDL_SCANCODE_UP] != KEY_STATE::KEY_REPEAT
			&& (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || App->input->controll[1] == KEY_STATE::KEY_REPEAT) && grenade == false)
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
	else if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT ||
				App->input->controll[0] == KEY_STATE::KEY_REPEAT && App->input->controll[3] == KEY_STATE::KEY_REPEAT)
					&& position.x>-5 && anim == false && water == false )
	{
		if (current_animation != &leftUP && (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || App->input->controll[0] == KEY_STATE::KEY_REPEAT)
			&& App->input->keyboard[SDL_SCANCODE_DOWN] != KEY_STATE::KEY_REPEAT && grenade == false)
		{   //Cal canviar les animacions
			leftUP.Reset();
			current_animation = &leftUP;
		}
		direction = transitionToDirection(direction, 1.25 * M_PI);
		if(distance == false)
		{
			position.x -= speed;
			position.y -= speed;
		}
		player_last_direction = UPLEFT;

	}
	//UPRIGHT
	else if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT ||
			App->input->controll[0] == KEY_STATE::KEY_REPEAT && App->input->controll[2] == KEY_STATE::KEY_REPEAT)
		&& position.x <= SCREEN_WIDTH - 23 && anim == false && water == false)
	{
		if (current_animation != &rightUP && (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || App->input->controll[0] == KEY_STATE::KEY_REPEAT)
			&& App->input->keyboard[SDL_SCANCODE_DOWN] != KEY_STATE::KEY_REPEAT && grenade == false)
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
	else if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->controll[3] == KEY_STATE::KEY_REPEAT)
		&& position.x>-5  && anim == false && water == false)
	{
		if (current_animation != &left && App->input->keyboard[SDL_SCANCODE_UP] != KEY_STATE::KEY_REPEAT
			&& App->input->keyboard[SDL_SCANCODE_DOWN] != KEY_STATE::KEY_REPEAT  && grenade == false)
			{
				left.Reset();
				current_animation = &left;
			}
		direction = transitionToDirection(direction, M_PI);
		position.x -= speed;
		player_last_direction = LEFT;

	}

	//RIGHT
	else if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->controll[2] == KEY_STATE::KEY_REPEAT)
		&& position.x<=SCREEN_WIDTH-23 && anim == false && water == false)
	{
		if (current_animation != &right  && grenade == false)
		{
			right.Reset();
			current_animation = &right;
		}
		direction = transitionToDirection(direction, 2*M_PI);
		position.x += speed;
		player_last_direction = RIGHT;
	
	}
	//DOWN
	else if ((App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || App->input->controll[1] == KEY_STATE::KEY_REPEAT)
		&& anim == false && position.y<=232-(App->render->camera.y/ SCREEN_SIZE) && water == false)
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
	else if ((App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || App->input->controll[0] == KEY_STATE::KEY_REPEAT)
		&& anim == false && water == false)
	{
		if (current_animation != &up && grenade == false)
		{
			up.Reset();
			current_animation = &up;
		}
		direction = transitionToDirection(direction,  1.5 * M_PI);
		
		if(distance == false)
		{
			position.y -= speed;
		}
		player_last_direction = UP;

	}

	//SHOT 
	App->particles->bullet.speed.y = sin(direction) * BULLET_SPEED;
	App->particles->bullet.speed.x = cos(direction) * BULLET_SPEED;
	shot();

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN ||
		App->input->controll[4] == KEY_STATE::KEY_REPEAT)
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
				if (App->first_scene->IsEnabled()==true && App->scene_start->player_2==false)
				{
					if (position.y> 1450 - 1900 +248)
					{
						position.x = 100;
						position.y = 150;
						App->render->camera.x = 0;
						App->render->camera.y = 0;
					}
					else if(position.y< 1450 - 1900 + 248 && position.y>1085-1900+248)
					{
						position.x = 100;
						position.y = 1450 - 1900+248;
						App->render->camera.x = 0;
						App->render->camera.y = 1100;
					}
					else if (position.y<1085 - 1900 + 248 && position.y> 632-1900+248)
					{
						position.x = 100;
						position.y = 1085 - 1900 + 248;
						App->render->camera.x = 0;
						App->render->camera.y = 2200;
					}
					else if (position.y < 632 - 1900 + 248 && position.y>350-1900+248)
					{
						position.x = 100;
						position.y = 632 - 1900 + 248;
						App->render->camera.x = 0;
						App->render->camera.y = 3600;
					}
					else
					{
						position.x = 100;
						position.y = 350 - 1900 + 248;
						App->render->camera.x = 0;
						App->render->camera.y = 4500;
					}					
				}
				if(App->scene_start->player_2 == true)
				{
					position.x =App->player_2->position.x-16;
					position.y =App->player_2->position.y;
				}
				/*else
				{
					position.x = App->player_2->position.x - 16;
					position.y = App->player_2->position.y;
				}*/
				
				
				if (App->scene_map2->IsEnabled() == true)
				{
					if (App->scene_start->player_2 == false)
					{
						position.x = 100;
						position.y = 150;
						App->render->camera.x = 0;
						App->render->camera.y = 0;
					}
				}

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


				//Add enemies
				if (App->first_scene->IsEnabled()) {
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
				}
				else if (App->scene_map2->IsEnabled()) {
					App->scene_map2->addStaticEnemies();
				}
			}
			else
			{
				anim = false;
				Disable();
				if (App->first_scene->IsEnabled() == true)
				{
					App->fade->FadeToBlack((Module*)App->first_scene, (Module*)App->end_scene);
					App->elements1->num_score = 0;
					counter = 0;
				}
				if(App->scene_map2->IsEnabled()==true)
				{
					App->fade->FadeToBlack((Module*)App->scene_map2, (Module*)App->end_scene);
					App->elements1->num_score = 0;
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
				if (App->scene_start->player_2 == false)
				{
					position.x = 100;
					position.y = 150;
					App->render->camera.x = 0;
					App->render->camera.y = 0;
				}
				else
				{
					if (App->first_scene->IsEnabled() == true)
					{
						position.x = position.x + 50;
						position.y = position.y;
					}
					else
					{
						position.x = App->player_2->position.x - 16;
						position.y = App->player_2->position.y;
					}
				}
				water = false;
				alive = true;
				only = true;
			}
			else
			{
				if (App->first_scene->IsEnabled() == true)
				{
					App->fade->FadeToBlack((Module*)App->first_scene, (Module*)App->end_scene);
					App->elements1->num_score = 0;
					counter = 0;
				}
				if (App->scene_map2->IsEnabled() == true)
				{
					App->fade->FadeToBlack((Module*)App->scene_map2, (Module*)App->end_scene);
					App->elements1->num_score = 0;
					counter = 0;
				}
			}
				
		}
	}

	// Grenade

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN ||
		App->input->controll[5] == KEY_STATE::KEY_DOWN) {   //Mes maco que lo de dalt no? (lo de dalt es pot borrar ja que ja no funciona )
		if (App->elements1->num_grenades > 0){
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
	if(App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE 
	   && App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE 
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		 && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE 
		  && App->input->controll[0] == KEY_STATE::KEY_IDLE
		   && App->input->controll[1] == KEY_STATE::KEY_IDLE
			&& App->input->controll[2] == KEY_STATE::KEY_IDLE
		     && App->input->controll[3] == KEY_STATE::KEY_IDLE
		      && anim == false && water==false && grenade == false)
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

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN || App->input->controll[6] == KEY_STATE::KEY_DOWN)
	{
		if (god == true && App->player_2->god ==true)
		{
			god = false;
			App->player_2->god = false;
		}
			
		else
		{
			god = true;
			App->player_2->god = true;
		}
	}
	if (god == true)
	{
		App->fonts->BlitText(0, 230 - (App->render->camera.y / SCREEN_SIZE), font_score, "G");
	}



	playercoll->SetPos(position.x + 7, position.y);
	feetcoll->SetPos(position.x+7 , position.y + 13);


	// Draw everything --------------------------------------
	if(anim == false && water==false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	else
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	if(App->first_scene->IsEnabled()==true)
		App->render->Blit(textures, 80-17, -850, &bridge); 

	if (App->scene_map2->IsEnabled()) {
		if (App->scene_map2->enteredBossArea) {
			if (App->scene_map2->finishedBossArea)
				App->render->Blit(textures, 85 - 22, 1 - 1908 + SCREEN_HEIGHT, &(close_doors.GetCurrentFrame()), 0.75f);
			else {
				App->render->Blit(textures, 85 - 22, 1 - 1908 + SCREEN_HEIGHT, &(open_doors.GetCurrentFrame()), 0.75f);
			}
		}
		App->render->Blit(textures, 80, -831, &(bridgerino.GetCurrentFrame()), 0.75f);
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_WALL)
	{
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[0] == KEY_STATE::KEY_REPEAT))
		{
			position.y += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[1] == KEY_STATE::KEY_REPEAT))
		{
			position.y -= 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[3] == KEY_STATE::KEY_REPEAT))
		{
			position.x += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[2] == KEY_STATE::KEY_REPEAT))
		{
			position.x -= 1;
		}
	}
	if (c2->type == COLLIDER_LAKE && god==false)
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
	if (c2->type == COLLIDER_BULLET_BEHIND_COVER && god == false)
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

float ModulePlayer::transitionToDirection(float current_direction, float final_direction) {
	float speed = 0.1;
	float closer_direction;
	float margin = 0.15;

	if ((final_direction - current_direction) >= M_PI) {
		final_direction += 2* M_PI;
	}
	if (fabsf(current_direction - final_direction) < margin) {
		closer_direction = final_direction;
	}
	else if (current_direction > (final_direction)  )
		closer_direction = current_direction - speed;
	else if (current_direction < (final_direction) )
		closer_direction = current_direction + speed;
	else
  		closer_direction = final_direction;

 	return closer_direction;
}

void ModulePlayer::shot() {

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

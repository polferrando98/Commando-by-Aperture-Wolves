#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInit.h"
#include "ModuleFirstScene.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleSecondScene.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"
#include "ModuleHelicopterScene.h"

#include<stdio.h>

ModuleElements1::ModuleElements1()
{}

ModuleElements1::~ModuleElements1()
{}

// Load assets
bool ModuleElements1::Start()
{	
		LOG("Loading space scene");
		textures = App->textures->Load("assets/PlaceHolder_Sprites.png");
		//cannon = App->textures->Load("assets/Cannons1.png");
		num_1 = App->fonts->Load("fonts/num_1.png", "abcdefghij 0123456789=", 2);
		num_2 = App->fonts->Load("fonts/num_2.png", "abcdefghij 0123456789=", 2);
		let_2 = App->fonts->Load("fonts/Lletres_2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,! ", 2);


		if (loaded < 3) {

			palm_trees.PushBack({ 1, 365, 32, 32 });
			palm_trees.PushBack({ 34, 365, 32, 32 });
			palm_trees.PushBack({ 67, 365, 32, 32 });
			palm_trees.PushBack({ 34, 365, 32, 32 });
			palm_trees.speed = 0.01f;

			open_doors.PushBack({ 511,1,98,42 });
			open_doors.PushBack({ 511,44,98,56 });
			open_doors.PushBack({ 511,101,98,59 });
			open_doors.speed = 0.0f;
			open_doors.loop = false;

			close_doors.PushBack({ 511,44,98,56 });
			close_doors.PushBack({ 511,1,98,42 });
			close_doors.speed = 0.04f;
			close_doors.loop = false;

			boxes.PushBack({ 181, 245, 32, 16 });
			boxes.PushBack({ 214, 245, 32, 16 });
			boxes1.PushBack({ 181, 262, 32, 16 });
			boxes1.PushBack({ 214, 262, 32, 16 });
			boxes2.PushBack({ 181, 279, 32, 16 });
			boxes2.PushBack({ 214, 279, 32, 16 });
			boxes.speed = 0.09f;
			boxes1.speed = 0.09f;
			boxes2.speed = 0.09f;

			heli.PushBack({ 1, 520, 64, 84 });
			heli.loop = false;

			heliMedium.PushBack({ 66, 520, 64, 84 });
			heliMedium.loop = false;

			heliSmall.PushBack({ 131, 520, 64, 84 });
			heliSmall.loop = false;

			heliWings.PushBack({ 411,244,186, 70 });
			heliWings.PushBack({ 598,244,186, 70 });
			heliWings.PushBack({ 411,315,186, 70 });
			heliWings.PushBack({ 598,315,186, 70 });
			heliWings.PushBack({ 411,386,186, 70 });
			heliWings.PushBack({ 598,386,186, 70 });
			heliWings.loop = true;
			heliWings.speed = 1;

			heliWingsMedium.PushBack({ 375, 605, 186, 70 });
			heliWingsMedium.PushBack({ 562, 605, 186, 70 });
			heliWingsMedium.PushBack({ 375,676, 186, 70 });
			heliWingsMedium.PushBack({ 562, 676, 186, 70 });
			heliWingsMedium.PushBack({ 375, 747, 186, 70 });
			heliWingsMedium.PushBack({ 562, 747, 186, 70 });
			heliWingsMedium.loop = true;
			heliWingsMedium.speed = 1;

			heliWingsSmall.PushBack({ 1, 605, 186, 70 });
			heliWingsSmall.PushBack({ 188, 605, 186, 70 });
			heliWingsSmall.PushBack({ 1, 676, 186, 70 });
			heliWingsSmall.PushBack({ 188, 676, 186, 70 });
			heliWingsSmall.PushBack({ 1, 747, 186, 70 });
			heliWingsSmall.PushBack({ 188, 747, 186, 70 });
			heliWingsSmall.loop = true;
			heliWingsSmall.speed = 1;

			superJoeJump.PushBack({ 421, 163, 29,26 });
			superJoeJump.PushBack({ 451, 163, 29,23 });
			superJoeJump.PushBack({ 481, 163, 29,26 });
			superJoeJump.loop = false;
			superJoeJump.speed = 0.7;

			superJoeBye.PushBack({ 451, 136, 29, 26 });
			superJoeBye.PushBack({ 391, 163, 29, 26 });
			superJoeBye.loop = true;
			superJoeBye.speed = 0.1;			

			idleUP.PushBack({ 331, 28, 29, 26 });

			smallDoor.PushBack({183,449, 12, 30});
			smallDoor.PushBack({170 ,449, 12, 30 });
			smallDoor.PushBack({157 ,449, 12, 30 });
			smallDoor.PushBack({ 144,449, 12, 30 });
			smallDoor.PushBack({131 ,449, 12, 30 });
			smallDoor.PushBack({118 ,449, 12, 30 });
			smallDoor.PushBack({ 105,449, 12, 30 });
			smallDoor.PushBack({ 92,449, 12, 30 });
			smallDoor.PushBack({ 79,449, 12, 30 });
			smallDoor.PushBack({66 ,449, 12, 30 });
			smallDoor.PushBack({ 79,449, 12, 30 });
			smallDoor.PushBack({ 92,449, 12, 30 });
			smallDoor.PushBack({ 105,449, 12, 30 });
			smallDoor.PushBack({ 118 ,449, 12, 30 });
			smallDoor.PushBack({ 131 ,449, 12, 30 });
			smallDoor.PushBack({ 144,449, 12, 30 });
			smallDoor.PushBack({ 157 ,449, 12, 30 });
			smallDoor.PushBack({ 170 ,449, 12, 30 });
			smallDoor.PushBack({ 183,449, 12, 30 });
			smallDoor.PushBack({ 196,449, 12, 30 });

			smallDoor.loop = true;
			smallDoor.speed = 0.1;

			loaded++;
		}

		palmTree.x = 1;	palmTree.y = 365; palmTree.h = 32; palmTree.w = 32;
		palmTree_2.x = 100;	palmTree_2.y = 365;	palmTree_2.h = 32; palmTree_2.w = 32;
		rock.x = 391; rock.y = 217; rock.h = 26; rock.w = 29;
		lifeLogo.x = 368; lifeLogo.y = 220; lifeLogo.h = 18; lifeLogo.w = 13;
		grenadeLogo.x = 340; grenadeLogo.y = 222; grenadeLogo.h = 21; grenadeLogo.w = 20;

		heliPos = 1853;
		timer = 0;
		num_grenades = 6;
		superJoePosY = 1759;
		superJoePosX = 147;
	
	return true;
}

// UnLoad assets
bool ModuleElements1::CleanUp()
{
	LOG("Unloading space scene");
	App->textures->Unload(textures);
//	App->textures->Unload(cannon);
	App->fonts->UnLoad(num_1);
	App->fonts->UnLoad(num_2);
	App->fonts->UnLoad(let_2);
	
	return true;
}

// Update: draw background
update_status ModuleElements1::Update()
{
	// Move camera forward -----------------------------

	// Draw everything ---------------------------------

	//helicopter wings
	//App->render->Blit(heli_wings, 50-16, 1800-1908+SCREEN_HEIGHT, &(heliWings.GetCurrentFrame()), 0.75f); 
	//WORKS, I JUST COMMENTED IT SO IT DOESN'T BOTHER US
	//WE NEED TO ADD THE HELI AND MAKE IT MOVE UPWARDS WITH IT

	//Helicopter
	//App->render->Blit(helicopter_texture, 127 - 16, 1762 - 1908 + SCREEN_HEIGHT, &(helicopter_texture.GetCurrentFrame()), 0.75f);


	if (App->first_scene->IsEnabled() == true)
	{

		App->render->Blit(textures, 128, -63 + SCREEN_HEIGHT, &palmTree, 0.75f);
		App->render->Blit(textures, 138, -47 + SCREEN_HEIGHT, &palmTree, 0.75f);
		App->render->Blit(textures, 112, -47 + SCREEN_HEIGHT, &palmTree, 0.75f);

		App->render->Blit(textures, 65, 0 + NULL, &palmTree, 0.75f);
		App->render->Blit(textures, 1, -128 + SCREEN_HEIGHT, &palmTree, 0.75f);
		App->render->Blit(textures, 185, -128 + SCREEN_HEIGHT, &palmTree, 0.75f);

		//doors

		if (App->first_scene->finishedBossArea)
			App->render->Blit(textures, 85 - 22, 1 - 1908 + SCREEN_HEIGHT, &(close_doors.GetCurrentFrame()), 0.75f);
		else {
			App->render->Blit(textures, 85 - 22, 1 - 1908 + SCREEN_HEIGHT, &(open_doors.GetCurrentFrame()), 0.75f);
		}


		//boxes
		if (pickupBox == false) {
			App->render->Blit(textures, 153 - 16, 1332 - 1652, &(boxes1.GetCurrentFrame()), 0.09f);
		}
		else if (pickupBox == true) {
			App->render->Blit(textures, 2000, 1332 - 1652, &(boxes1.GetCurrentFrame()), 0.09f);
		}
		if (pickupBox1 == false) {
			App->render->Blit(textures, 187 - 16, 899 - 1652, &(boxes2.GetCurrentFrame()), 0.09f);
		}
		else if (pickupBox1 == true) {
			App->render->Blit(textures, 2000, 899 - 1652, &(boxes2.GetCurrentFrame()), 0.09f);
		}
		if (pickupBox2 == false) {
			App->render->Blit(textures, 26 - 16, 255 - 1652, &(boxes1.GetCurrentFrame()), 0.09f);
		}
		else if (pickupBox2 == true) {
			App->render->Blit(textures, 2000, 899 - 1652, &(boxes1.GetCurrentFrame()), 0.09f);
		}
		if (pickupBox3 == false) {
			App->render->Blit(textures, 190 - 16, 210 - 1652, &(boxes.GetCurrentFrame()), 0.09f);
		}
		else if (pickupBox3 == true) {
			App->render->Blit(textures, 2000, 899 - 1652, &(boxes.GetCurrentFrame()), 0.09f);			
		}

		//cannons
		//App->render->Blit(cannon, 210 - 16, 899 - 1652, NULL);

		//static palm trees 
		//App->render->Blit(static_palm_tree, 65, 0, NULL);
		//App->render->Blit(static_palm_tree, 1, 128, NULL);
		//App->render->Blit(static_palm_tree2, 192, 129, NULL);
		App->render->Blit(textures, 112, -49, &palmTree, NULL);
		App->render->Blit(textures, 128, -65, &palmTree, NULL);
		App->render->Blit(textures, 144, -51, &palmTree_2, NULL);
		App->render->Blit(textures, 65, -129, &palmTree, NULL);
		App->render->Blit(textures, -16, -241, &palmTree, NULL);
		App->render->Blit(textures, 0, -257, &palmTree, NULL);
		App->render->Blit(textures, 17, -241, &palmTree_2, NULL);
		App->render->Blit(textures, 129, -257, &palmTree_2, NULL);
		App->render->Blit(textures, 65, -321, &palmTree, NULL);
		App->render->Blit(textures, 129, -385, &palmTree, NULL);
		App->render->Blit(textures, 193, -449, &palmTree, NULL);
		App->render->Blit(textures, 128, -642, &palmTree_2, NULL);
		App->render->Blit(textures, 1, -640, &palmTree, NULL);
		App->render->Blit(textures, 64, -706, &palmTree, NULL);



		//Rocks
		App->render->Blit(textures, 97, -925, &rock);		//-1652   //-16			
		App->render->Blit(textures, 1, -957, &rock);
		App->render->Blit(textures, 209, -989, &rock);
		App->render->Blit(textures, 49, -1021, &rock);
		App->render->Blit(textures, 145, -1054, &rock);
		App->render->Blit(textures, 1, -1150, &rock);
		App->render->Blit(textures, 97, -1150, &rock);
		App->render->Blit(textures, 193, -1150, &rock);
	}
	if (App->heli_scene->IsEnabled() == true) {

		App->render->Blit(textures, 128, -63 + SCREEN_HEIGHT, &(palm_trees.GetCurrentFrame()), 0.75f);
		App->render->Blit(textures, 138, -47 + SCREEN_HEIGHT, &(palm_trees.GetCurrentFrame()), 0.75f);
		App->render->Blit(textures, 112, -47 + SCREEN_HEIGHT, &(palm_trees.GetCurrentFrame()), 0.75f);
		App->render->Blit(textures, 65, 0 + NULL, &(palm_trees.GetCurrentFrame()), 0.75f);
		App->render->Blit(textures, 1, -128 + SCREEN_HEIGHT, &(palm_trees.GetCurrentFrame()), 0.75f);
		App->render->Blit(textures, 185, -128 + SCREEN_HEIGHT, &(palm_trees.GetCurrentFrame()), 0.75f);

	//HELI 
		if (heliPos > 1586){
			if (heliPos > 1726) {
				--heliPos;
				App->render->Blit(textures, 120 - 16 - 31, heliPos - 1908 + SCREEN_HEIGHT, &(heli.GetCurrentFrame()), NULL);
				App->render->Blit(textures, 120 - 32 - 16 - 60, heliPos - 1908 + SCREEN_HEIGHT - 30, &(heliWings.GetCurrentFrame()), NULL);
	
			}
			else if(heliPos == 1726) {
			
				if (timer < 50) {
				App->render->Blit(textures, 120 - 16 - 31, heliPos - 1908 + SCREEN_HEIGHT, &(heliMedium.GetCurrentFrame()), NULL);
				App->render->Blit(textures, 120 - 32 - 16 - 60, heliPos - 1908 + SCREEN_HEIGHT - 30 + 14, &(heliWingsMedium.GetCurrentFrame()), NULL);				
				}
				if (timer >= 50 && timer < 160) {
				App->render->Blit(textures, 120 - 16 - 31, heliPos - 1908 + SCREEN_HEIGHT, &(heliSmall.GetCurrentFrame()), NULL);
				App->render->Blit(textures, 120 - 32 - 16 - 60, heliPos - 1908 + SCREEN_HEIGHT, &(heliWingsSmall.GetCurrentFrame()), NULL);
				}
				if (timer >= 160 && timer < 200) {
					App->render->Blit(textures, 120 - 16 - 31, heliPos - 1908 + SCREEN_HEIGHT, &(heliMedium.GetCurrentFrame()), NULL);
					App->render->Blit(textures, 120 - 32 - 16 - 60, heliPos - 1908 + SCREEN_HEIGHT - 30 + 14, &(heliWingsMedium.GetCurrentFrame()), NULL);
				}
				++timer;		
			}

			if (timer == 200) { heliPos--; timer++; }	

			else if (heliPos <= 1726 && timer > 200 && heliPos >= 1583) 
			{
				--heliPos;
				
				App->render->Blit(textures, 120 - 16 - 31, heliPos - 1908 + SCREEN_HEIGHT, &(heli.GetCurrentFrame()), NULL);
				App->render->Blit(textures, 120 - 32 - 16 - 60, heliPos - 1908 + SCREEN_HEIGHT - 30, &(heliWings.GetCurrentFrame()), NULL);

				if (heliPos < 1590) {
					App->heli_scene->endScene = true;
				}
			}			
			
		}
		//SUPER JOE JUMP

		if (timer > 70 && timer < 120) {
			if (superJoePosY > 1700 && superJoePosX < 156) {
				if (timer % 2 == 0) {
					superJoePosX++;
					superJoePosY--;
				}
				App->render->Blit(textures, superJoePosX - 30, superJoePosY - 1908 + SCREEN_HEIGHT, &(superJoeJump.GetCurrentFrame()), NULL);
			}
			if (superJoePosX < 167 && superJoePosX >= 156 ){
				if (timer % 2 == 0) {
					++superJoePosY;
					++superJoePosX;
				}
				App->render->Blit(textures, superJoePosX - 30, superJoePosY - 1908 + SCREEN_HEIGHT, &(superJoeJump.GetCurrentFrame()), NULL);
			}
		}


		if (superJoePosX >= 167 && timer < 200) {
			App->render->Blit(textures, superJoePosX - 30, superJoePosY - 1908 + SCREEN_HEIGHT, &(superJoeBye.GetCurrentFrame()), NULL);
			++timer;
		}
		else if (timer > 200 && superJoePosX >= 132 && superJoePosY >= 150) {
			App->render->Blit(textures, superJoePosX - 30, superJoePosY - 1908 + SCREEN_HEIGHT, &(App->player->up.GetCurrentFrame()), NULL);
			++superJoePosY;
			--superJoePosX;
		}
		else if (timer > 200 && timer < 210) {
			App->render->Blit(textures, superJoePosX - 30, superJoePosY - 1908 + SCREEN_HEIGHT, &(App->player->up.GetCurrentFrame()), NULL);
			++superJoePosY;
			++timer;
		}
		else if (timer > 200) {
			App->render->Blit(textures, superJoePosX - 30, superJoePosY - 1908 + SCREEN_HEIGHT, &(App->player->up.GetCurrentFrame()), NULL);
		}
		
	}

	if (App->scene_map2->IsEnabled() == true) {

		App->render->Blit(textures, 59-16, 676 -1908 + SCREEN_HEIGHT, &smallDoor.GetCurrentFrame(), NULL);
	}

	//Grenade Logo
	App->render->Blit(textures, 95, 242 - ((App->render->camera.y) / SCREEN_SIZE), &grenadeLogo);
	//Grenade number
	sprintf_s(grenade_num, 10, "=%2d", num_grenades);
	App->fonts->BlitText(108, 247 - (App->render->camera.y / SCREEN_SIZE),num_1, grenade_num);

	//1UP
	App->fonts->BlitText(18, 0 - (App->render->camera.y / SCREEN_SIZE), num_2, "1");
	App->fonts->BlitText(27, 0 - (App->render->camera.y / SCREEN_SIZE), let_2, "UP");

	//Top Score
	sprintf_s(score, 10, "%7d", num_score);
	sprintf_s(high_score, 10, "% 7d", high_scores[0]);
	App->fonts->BlitText(75, 0 - (App->render->camera.y / SCREEN_SIZE), let_2, "TOP SCORE");
	App->fonts->BlitText(80, 9 - (App->render->camera.y / SCREEN_SIZE), num_1, high_score);

	//SDL_strlcpy(score,(char*)App->player->score,10); No se com fer aixo -p
	App->fonts->BlitText(0, 9 - (App->render->camera.y / SCREEN_SIZE), num_1, score);

	if ((App->input->keyboard[SDL_SCANCODE_G] == 1 || App->input->keyboard[SDL_SCANCODE_X] == 1 || App->input->controll[5] == KEY_STATE::KEY_DOWN || App->input->P2_controll[5] == KEY_STATE::KEY_DOWN)
		&& num_grenades > 0) {
		--num_grenades;
	}

	//Life Logo
	for (int j = 0; j < num_lives_play_1-1; j++)
	{
		App->render->Blit(textures, j*11, 240 - ((App->render->camera.y) / SCREEN_SIZE), &lifeLogo);
	}
	
	

	if (App->input->keyboard[SDL_SCANCODE_C] == 1 && fading == false)
	{
		App->fade->FadeToBlack(this, App->scene_map2, 2.0f);
		fading = true;
	}
	
	if (num_score==10000)
	{
		num_lives_play_1++;
		num_score += 100;
	}
	if ( num_score!=0 && num_score%50000 == 0)
	{
		num_lives_play_1++;
		num_score += 100;
	}

	if (num_lives_play_1 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (num_score > high_scores[i])
			{
				int a = high_scores[i];
				high_scores[i] = num_score;
				num_score = a;
				
			}
		}
	}

	if (App->scene_map2->finished) {
		for (int i = 0; i < 10; i++)
		{
			if (num_score > high_scores[i])
			{
				int a = high_scores[i];
				high_scores[i] = num_score;
				num_score = a;

			}
		}
	}

	return UPDATE_CONTINUE;
}
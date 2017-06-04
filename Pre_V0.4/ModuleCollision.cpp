#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_LAKE] = false;
	matrix[COLLIDER_WALL][COLLIDER_FEET] = false;
	matrix[COLLIDER_WALL][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_WALL][COLLIDER_PRISONER] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_LAKE] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_FEET] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_GRENADE_BOX] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_FINAL_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BULLET_BEHIND_COVER] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_GRENADE_EXPLOSION] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_LAKE] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_FEET] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_MAP_LIMIT_FOR_ENEMIES] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PRISONER] = false;


	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_LAKE] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_FEET] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PRISONER] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_LAKE] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_FEET] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_BEHIND_COVER] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;

	matrix[COLLIDER_LAKE][COLLIDER_WALL] = false;
	matrix[COLLIDER_LAKE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_LAKE][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_LAKE][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_LAKE][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_LAKE][COLLIDER_LAKE] = false;
	matrix[COLLIDER_LAKE][COLLIDER_FEET] = false;
	matrix[COLLIDER_LAKE][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_LAKE][COLLIDER_PRISONER] = false;

	matrix[COLLIDER_FEET][COLLIDER_FEET] = false;
	matrix[COLLIDER_FEET][COLLIDER_WALL] = true;
	matrix[COLLIDER_FEET][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_FEET][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_FEET][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_FEET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_FEET][COLLIDER_LAKE] = true;
	matrix[COLLIDER_FEET][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_FEET][COLLIDER_PRISONER] = false;

	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_FEET] = false;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_WALL] = false;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_LAKE] = false;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_GRENADE_EXPLOSION][COLLIDER_PRISONER] = false;

	matrix[COLLIDER_GRENADE_BOX][COLLIDER_WALL] = false;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_LAKE] = false;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_FEET] = false;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_GRENADE_EXPLOSION] = false;
	matrix[COLLIDER_GRENADE_BOX][COLLIDER_PRISONER] = false;

	matrix[COLLIDER_PRISONER][COLLIDER_WALL] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_PRISONER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_LAKE] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_FEET] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_GRENADE_EXPLOSION] = false;
	matrix[COLLIDER_PRISONER][COLLIDER_PRISONER] = false;

	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_GRENADE_EXPLOSION] = true;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_LAKE] = true;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_FEET] = true;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_MAP_LIMIT_FOR_ENEMIES] = true;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_ENEMY_BEHIND_COVER][COLLIDER_BULLET_BEHIND_COVER] = false;

	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_WALL] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_LAKE] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_FEET] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_GRENADE_BOX] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_PRISONER] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_ENEMY_BEHIND_COVER] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BULLET_BEHIND_COVER][COLLIDER_PLAYER_SHOT] = false;




	matrix[COLLIDER_FINAL_WALL][COLLIDER_PLAYER] = true;
	

}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (c1->to_delete == false && c2->to_delete != true) {
					if (matrix[c1->type][c2->type] && c1->callback)
						c1->callback->OnCollision(c1, c2);
					if (c1->to_delete == false) {
						if (matrix[c2->type][c1->type] && c2->callback)
							c2->callback->OnCollision(c2, c1);
					}
				}
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false){
		return;
	}
	else {
	
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_LAKE: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case COLLIDER_FEET: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_GRENADE_EXPLOSION: // orange
			App->render->DrawQuad(colliders[i]->rect, 255, 170, 0, alpha);
			break;
		case COLLIDER_GRENADE_BOX: // light blue
			App->render->DrawQuad(colliders[i]->rect, 135, 206, 250, alpha);
			break;
		case COLLIDER_MAP_LIMIT_FOR_ENEMIES: //magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_PRISONER:
			App->render->DrawQuad(colliders[i]->rect, 100, 100, 255, alpha);
			break;
		case COLLIDER_FINAL_WALL:
			App->render->DrawQuad(colliders[i]->rect, 50, 100, 50, alpha);
			break;
		case COLLIDER_BULLET_BEHIND_COVER:
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_ENEMY_BEHIND_COVER:
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}

		}
	}
}

bool ModuleCollision::checkColisionList(Collider * enemCollider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		if (colliders[i] == nullptr)
			continue;
		if (enemCollider->CheckCollision(colliders[i]->rect))
			return true;
	}
	return false;
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (rect.x <= r.x + r.w && rect.x + rect.w >= r.x)
	{
		if (rect.y <= r.y + r.h && rect.y + rect.h >= r.y)
		{
			return true;
		}
	}
	return false;
}

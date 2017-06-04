#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_ACTIVE_PARTICLES 10000

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	// a partir d'aqui son atributs que he afegit jo -pol
	bool display_dead_animation = false;
	Animation dead_animation;
	int dead_animation_life;
	int dead_animation_current_life = 0;
	iPoint last_position;
	bool alive = true;
	Collider* dead_collider = nullptr;
	bool has_dead_collider = false;
	enum ParticleType {ENEMY_GRANANDE,PLAYER_GRANADE};
	ParticleType type;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

	void eliminateParticle(Particle* p, int i);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;
	Mix_Chunk* music;
public:

	Particle grenade;
	Particle enemy_grenade;
	Particle explosion;
	Particle bullet;
	Particle enemy_bullet;
	Particle Enemy_bullet_down;
	Particle Enemy_bullet_up;
	Particle Enemy_bullet_left;
	Particle Enemy_bullet_right;
};

#endif // __MODULEPARTICLES_H__
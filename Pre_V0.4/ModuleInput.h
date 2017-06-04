#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define CONTROLLER_DEAD_ZONE 8000
#define MAX_BUTTONS 20

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	KEY_STATE controll[MAX_BUTTONS];
	KEY_STATE P2_controll[MAX_BUTTONS];
	SDL_GameController *controller = nullptr;
	SDL_GameController *P2_controller = nullptr;

};

#endif // __ModuleInput_H__
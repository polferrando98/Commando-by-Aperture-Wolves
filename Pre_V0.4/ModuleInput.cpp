#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleInit.h"
#include "SDL/include/SDL.h"
#include <iostream>

ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_BUTTONS; ++i)
		controll[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_BUTTONS; ++i)
		P2_controll[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
 
	if (SDL_NumJoysticks() < 1)
	{
		LOG("Warning: No joysticks connected!\n");
	}
	else
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i))
			{
				if (i == 0)
				{
					controller = SDL_GameControllerOpen(i);
					std::cout << SDL_GameControllerMapping(controller) << std::endl;
				}
				
				if (i==1)
				{
					P2_controller = SDL_GameControllerOpen(i);
					std::cout << SDL_GameControllerMapping(P2_controller) << std::endl;
					break;
				}
			}
			else
			{
				LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	Uint8 buttons[MAX_BUTTONS];
	Uint8 P2_buttons[MAX_BUTTONS];

	buttons[0] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	buttons[1] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	buttons[2] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	buttons[3] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	buttons[4] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A);
	buttons[5] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	buttons[6] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_BACK);

	if (App->scene_start->player_2 == true)
	{
		P2_buttons[0] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
		P2_buttons[1] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		P2_buttons[2] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		P2_buttons[3] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		P2_buttons[4] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_A);
		P2_buttons[5] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
		P2_buttons[6] = SDL_GameControllerGetButton(App->input->P2_controller, SDL_CONTROLLER_BUTTON_BACK);
	}
	


	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (buttons[i] == 1)
		{
			if (controll[i] == KEY_IDLE)
				controll[i] = KEY_DOWN;
			else
				controll[i] = KEY_REPEAT;
		}
		else
		{
			if (controll[i] == KEY_REPEAT || controll[i] == KEY_DOWN)
				controll[i] = KEY_UP;
			else
				controll[i] = KEY_IDLE;
		}
	}
	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (P2_buttons[i] == 1)
		{
			if (P2_controll[i] == KEY_IDLE)
				P2_controll[i] = KEY_DOWN;
			else
				P2_controll[i] = KEY_REPEAT;
		}
		else
		{
			if (P2_controll[i] == KEY_REPEAT || P2_controll[i] == KEY_DOWN)
				P2_controll[i] = KEY_UP;
			else
				P2_controll[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_GameControllerClose(controller);
	controller = NULL;
	SDL_GameControllerClose(P2_controller);
	P2_controller = NULL;

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
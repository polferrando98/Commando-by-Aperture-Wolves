#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() :Module()
{
	for (int i = 0; i <= MAX_TRACKS; i++) {
		musica[i] = nullptr;
		effects[i] = nullptr;
	}

}

//Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the OGG audio format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize music lib. IMG_Init: %s", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing Sound library");

	for (uint i = 0; i < MAX_TRACKS; ++i)
	{
		if (musica[i] != nullptr)
			Mix_FreeMusic(musica[i]);
		if (musica[i] != nullptr)
			Mix_FreeChunk(effects[i]);
	}

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}

Mix_Music* const ModuleAudio::Load(const char* path)
{
	Mix_Music* music = Mix_LoadMUS(path);;
	if (music == nullptr)
	{
		LOG("Error with the music %s", path);
	}
	else {
		musica[last_track++] = music;
	}
	return music;
}

Mix_Chunk* const ModuleAudio::LoadChunk(const char* path)
{
	Mix_Chunk* music = Mix_LoadWAV(path);;
	if (music == nullptr)
	{
		LOG("Error with the music %s", path);
	}
	else {
		effects[last_effect++] = music;
	}
	return music;
}

bool ModuleAudio::Unload(Mix_Music* music)
{
	bool ret = false;

	for (uint i = 0; i < MAX_TRACKS; ++i)
	{
		if (music == musica[i])
		{
			Mix_FreeMusic(musica[i]);
			musica[i] = nullptr;
			ret = true;
			break;
		}
	}

	return ret;
}
#ifndef _ModuleAudio_H_
#define _ModuleAudio_H_

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_TRACKS 50

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	virtual~ModuleAudio();

	bool Init();
	bool CleanUp();
	Mix_Music* const Load(const char* path);
	Mix_Chunk* const LoadChunk(const char* path);
	bool Unload(Mix_Music* music);

public:
	Mix_Music* musica[MAX_TRACKS];
	Mix_Chunk* effects[MAX_TRACKS];
	int last_track = 0;
	int last_effect = 0;
};
#endif


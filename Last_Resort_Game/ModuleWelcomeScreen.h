#ifndef __ModuleWelcomeScreen_H__
#define __ModuleWelcomeScreen_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;


class ModuleWelcomeScreen : public Module
{
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* Menu = nullptr;
	SDL_Rect menuplace;
};

#endif
#include "ModuleBall.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
ModuleBall::ModuleBall()
{
	//right
	for (int i=0;i<8;++i)
		blueball_0.PushBack({ 195,2+i*16, 22, 16 });
	blueball_0.speed = 0.2;
	//up & right
	for (int i = 0; i < 8; ++i)
		blueball_45.PushBack({ 240, 2 + i * 22, 21, 21 });
	blueball_45.speed = 0.1;
	//up
	for (int i = 0; i < 8; ++i)
		blueball_90.PushBack({ 278, 2 + i * 22, 16, 22});
	blueball_90.speed = 0.1;
	//up and left
	for (int i = 0; i < 8; ++i)
		blueball_135.PushBack({ 311, 2 + i * 22, 21, 21 });
	blueball_135.speed = 0.1;
	//lwft
	for (int i = 0; i < 8; ++i)
		blueball_180.PushBack({ 354, 2 + i * 16, 22, 16 });
	blueball_180.speed = 0.1;
	//left & downards
	for (int i = 0; i < 8; ++i)
		blueball_225.PushBack({ 398, 2 + i * 22, 21, 21 });
	blueball_225.speed = 0.1;
	//downwards
	for (int i = 0; i < 8; ++i)
		blueball_270.PushBack({ 436, 2 + i * 22, 16, 22 });
	blueball_270.speed = 0.1;

	//downwards & right
	for (int i = 0; i < 8; ++i)
		blueball_315.PushBack({ 469, 2 + i * 22,21, 21 });
	blueball_315.speed = 0.1;

};

ModuleBall::~ModuleBall()
{

}

bool ModuleBall::Start()
{
	position = { App->player->position.x + 37, App->player->position.y };
	return true;
}
bool ModuleBall::CleanUp()
{
	return true;
}
update_status ModuleBall::Update()
{
	Move();
	App->render->Blit(App->player->graphics, position.x, position.y, &blueball_315.GetCurrentFrame());
	return UPDATE_CONTINUE;
}

void ModuleBall::Move()
{
	uint speed =2;
	
	//Ship goes down  -  ball moves to the sides
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y >= App->player->position.y - 25 || position.x != App->player->position.x +8)
		{
			if (position.x >= App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.x -= speed;
			}
			else if (position.x >= App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.x += speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.x += speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.x -= speed;
			}
		}
	}
	//Ship goes up, ball moves to the sides
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y <= App->player->position.y + 30 || position.x != App->player->position.x + 8)
		{
			if (position.x >= App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.x += speed;
			}
			else if (position.x >= App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.x -= speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.x -= speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.x += speed;
			}
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x <= App->player->position.x + 42)
		{
			if (position.x >= App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.y += speed;
			}
			else if (position.x >= App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.y -= speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.y -= speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.y += speed;
			}
		}
		
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x >= App->player->position.x - 26)
		{
			if (position.x >= App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.y -= speed;
			}
			else if (position.x >= App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.y += speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y <= App->player->position.y - 1)
			{
				position.y += speed;
			}
			else if (position.x < App->player->position.x + 8 && position.y > App->player->position.y - 1)
			{
				position.y -= speed;
			}
		}
	}
	
	if (position.x <= App->player->position.x - 26)
		position.x = App->player->position.x - 26;

	if (position.y >= App->player->position.y + 30)
		position.y = App->player->position.y + 30;

	if (position.y <= App->player->position.y - 25)
		position.y = App->player->position.y - 25;

	if (position.x >= App->player->position.x + 42)
		position.x = App->player->position.x + 42;
}
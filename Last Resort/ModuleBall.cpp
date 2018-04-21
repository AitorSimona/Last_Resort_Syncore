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
	position = { App->player->position.x +42, App->player->position.y};
	ball1_collider = App->collision->AddCollider({ position.x, position.y, 22, 22 }, COLLIDER_BALL);
	current_animation = &blueball_0;
	return true;
}

bool ModuleBall::CleanUp()
{
	
	if (ball1_collider != nullptr)
		ball1_collider->to_delete = true;
	return true;
	
}

update_status ModuleBall::Update()
{
	
	if (ball_thrown == false)
	{
		if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN)
			fixed = !fixed;

		if (fixed == false)
			MoveAround();

		if (fixed == true)
			BallFixed();

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
			ChargeBall();

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP)
			ReleaseBall();

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
			Shot();
		
	}

	if (ball_thrown == true)
	{
		if (back_to_player == false)
		{
			Path();
		}
		else if (back_to_player == true)
		{
			ReturnBall();
		}
	}

	App->render->Blit(App->player->graphics, position.x, position.y, &current_animation->GetCurrentFrame());
	
	ball1_collider->SetPos(position.x, position.y);
	
	return UPDATE_CONTINUE;
}

void ModuleBall::MoveAround()
{
	uint speed =2;
	//Ship goes down  -  ball moves to the sides
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y >= App->player->position.y - 35 || position.x != App->player->position.x +8)
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
		if (position.y <= App->player->position.y + 35 || position.x != App->player->position.x + 8)
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
	//We change the animation depending on the position of the ball
	if (getPosition() == TOP)
		current_animation = &blueball_90;

	else if (getPosition() == BOTTOM)
		current_animation = &blueball_270;

	else if (getPosition() == RIGHT_SIDE)
		current_animation = &blueball_0;

	else if (getPosition() == RIGHT_TOP)
		current_animation = &blueball_45;

	else if (getPosition() == RIGHT_BOTTOM)
		current_animation = &blueball_315;

	else if (getPosition() == LEFT_SIDE)
		current_animation = &blueball_180;
	
	else if (getPosition() == LEFT_TOP)
		current_animation = &blueball_135;
	
	else if (getPosition() == LEFT_BOTTOM)
		current_animation = &blueball_225;

	//Limits
	if (position.x <= App->player->position.x - 26)
		position.x = App->player->position.x - 26;

	if (position.x >= App->player->position.x + 42)
		position.x = App->player->position.x + 42;

	if (position.y >= App->player->position.y + 35)
		position.y = App->player->position.y + 35;

	if (position.y <= App->player->position.y - 35)
		position.y = App->player->position.y - 35;
}

void ModuleBall::BallFixed()
{
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= App->player->speed;
		current_animation = &blueball_0;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += App->player->speed;
		current_animation = &blueball_180;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= App->player->speed;
		current_animation = &blueball_270;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &blueball_90;
		position.y += App->player->speed;
	}

}

void ModuleBall::ChargeBall()
{
	charge+=2;
	if (charge > 80)
		shot_charged = true;
}

void ModuleBall::ReleaseBall()
{
	if (!shot_charged)
		charge = 0;
	if (shot_charged)
	{
		shot_charged = false;
		if (getPosition() == RIGHT_SIDE)
		{
			velocity = { 8,0 };
		}
		if (getPosition() == RIGHT_TOP)
		{
			velocity = { 6,-6 };
		}
		if (getPosition() == RIGHT_BOTTOM)
		{
			velocity = { 6,6 };
		}
		if (getPosition() == LEFT_SIDE)
		{
			velocity = { -8,0 };
		}
		if (getPosition() == LEFT_TOP)
		{
			velocity = { -8,-6 };
		}
		if (getPosition() == LEFT_BOTTOM)
		{
			velocity = { -8,6 };
		}
		if (getPosition() == BOTTOM)
		{
			velocity = {0 ,8 };
		}
		if (getPosition() == TOP)
		{
			velocity = { 0,-8 };
		}
		ball_thrown = true;
	}
	
}

void ModuleBall::Path()
{
	position += velocity;
	if (abs(position.x-App->player->position.x)>=300|| abs(position.y - App->player->position.y) >= 300)
		back_to_player = true;
}

void ModuleBall::ReturnBall()
{
	if (position.x > App->player->position.x + 24)
		position.x -= 5;
	else if (position.x < App->player->position.x + 8)
		position.x += 5;

	if (position.y > App->player->position.y + 14)
		position.y -= 5;

	else if (position.y < App->player->position.y - 16)
		position.y += 5;

	if (position.x <= App->player->position.x + 24 && position.x >= App->player->position.x + 16 && position.y >= App->player->position.y - 16 && position.y <= App->player->position.y + 14)
	{
		back_to_player = false;
		ball_thrown = false;
		charge = 0;
	}
}

BALL_POSITION ModuleBall::getPosition()
{
	BALL_POSITION ret = NONE;
	if (position.x < App->player->position.x + 15 && position.x >= App->player->position.x - 10 &&position.y < App->player->position.y - 1 && position.y > App->player->position.y - 25)
		ret = LEFT_TOP;
	
	else if (position.x < App->player->position.x + 10 && position.x >= App->player->position.x - 10 && position.y>App->player->position.y - 1 && position.y < App->player->position.y + 25)
		ret = LEFT_BOTTOM;
	
	else if (position.x <= App->player->position.x - 10)
		ret = LEFT_SIDE;
	
	else if (position.x >= App->player->position.x + 15 && position.y < App->player->position.y - 1&& position.y > App->player->position.y - 25&& position.x < App->player->position.x + 41)
		ret = RIGHT_TOP;
	
	else if (position.x >= App->player->position.x + 10 && position.y > App->player->position.y - 1 && position.y < App->player->position.y + 25 && position.x < App->player->position.x + 41)
		ret = RIGHT_BOTTOM;
	
	else if (position.x >= App->player->position.x + 41)
		ret = RIGHT_SIDE;
	
	else if (position.y <= App->player->position.y - 25)
		ret = TOP;
	
	else if (position.y >= App->player->position.y + 25)
		ret = BOTTOM;

	return ret;
}

void ModuleBall::Shot()
{
	if (current_animation == &blueball_0)
		App->particles->ball_shot.speed = { 7,0 };
	
	else if (current_animation == &blueball_45)
		App->particles->ball_shot.speed = { 5,-5 };
	
	else if (current_animation == &blueball_90)
		App->particles->ball_shot.speed = { 0,-7 };
	
	else if (current_animation == &blueball_135)
		App->particles->ball_shot.speed = { -5,-5 };
	
	else if (current_animation == &blueball_180)
		App->particles->ball_shot.speed = { -7,0 };
	
	else if (current_animation == &blueball_225)
		App->particles->ball_shot.speed = { -5,5 };
	
	else if (current_animation == &blueball_270)
		App->particles->ball_shot.speed = { 0,7 };
	
	else if (current_animation == &blueball_315)
		App->particles->ball_shot.speed = { 5,5 };
	
	App->particles->AddParticle(App->particles->ball_shot, position.x, position.y, COLLIDER_PLAYER_SHOT);
}


void OnCollision(Collider* c1, Collider* c2) 
{
	true;
}
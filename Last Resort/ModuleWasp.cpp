#include "Application.h"
#include "ModuleWasp.h"
#include "ModuleCollision.h"

Enemy_Wasp::Enemy_Wasp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,178,32,16 });
	fly.PushBack({ 0, 194, 32, 15 });
	fly.PushBack({ 0, 209, 32, 16 });
	fly.PushBack({ 0, 225, 32, 15 });
	fly.PushBack({ 0, 240, 32, 16 });
	fly.speed = 0.1f;
	fly.loop = true;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Wasp::Move()
{
	
	position.x -= 1;
}
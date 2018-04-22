#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "ModuleWasp.h"
#include "ModuleRhino.h"
#include "PowerUp.h"
#include "PowerUpBomb.h"


#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("assets/sprites/Common_enemyes_Sprite.png");
	//powerups = App->textures->Load("assets/sprites/PowerUps_Sprite.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			/*if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{*/
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			/*}*/
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to despawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE +75 < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}

		queue[i].type = NO_TYPE;
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::WASP:
			enemies[i] = new Enemy_Wasp(info.x, info.y);
			break;

		case ENEMY_TYPES::RHINO:
			enemies[i] = new Enemy_Rhino(info.x, info.y);
			break;

		case ENEMY_TYPES::POWER_UP:
			enemies[i] = new Power_Up(info.x, info.y);
			break;

		case ENEMY_TYPES::POWER_UP_BOMB:
			enemies[i] = new Power_Up_Bomb(info.x, info.y);
			break;
		}
		
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (enemies[i]->life > 1)
			{
				if (c2->type == COLLIDER_BALL || c2->type == COLLIDER_BALL2)
				{
					enemies[i]->life -= 0.1f;
				}

				else 
					enemies[i]->life -= 1;
			}

			
			else
			{
				
					if (c1->type != COLLIDER_BOSS)
					{
						if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
							App->player->score += enemies[i]->score;
						if (c1->type == COLLIDER_PLAYER2_SHOT || c2->type == COLLIDER_PLAYER2_SHOT)
							App->player->score2 += enemies[i]->score;
						if (c1->type == COLLIDER_BALL || c2->type == COLLIDER_BALL)
							App->player->score += enemies[i]->score;
						if (c1->type == COLLIDER_BALL2 || c2->type == COLLIDER_BALL2)
							App->player->score2 += enemies[i]->score;
					}

					else
					{
						if (c1->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_SHOT)
							App->player->score += 5000;
						if (c1->type == COLLIDER_PLAYER2_SHOT || c2->type == COLLIDER_PLAYER2_SHOT)
							App->player->score2 += 5000;
						if (c1->type == COLLIDER_BALL || c2->type == COLLIDER_BALL)
							App->player->score += 5000;
						if (c1->type == COLLIDER_BALL2 || c2->type == COLLIDER_BALL2)
							App->player->score2 += 5000;
					}

					
			    App->particles->AddParticle(App->particles->enemy_explosion, enemies[i]->position.x, enemies[i]->position.y);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}
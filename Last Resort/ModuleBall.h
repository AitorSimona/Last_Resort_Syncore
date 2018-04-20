#ifndef __ModuleBall_H__
#define __ModuleBall_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h" 
#include "ModuleParticles.h"
enum BALL_POSITION {
	NONE,
	LEFT_SIDE,
	LEFT_TOP,
	LEFT_BOTTOM,
	TOP,
	BOTTOM,
	RIGHT_SIDE,
	RIGHT_TOP,
	RIGHT_BOTTOM
};
class ModuleBall :public Module
{
public:
	ModuleBall();
	~ModuleBall();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	void ModuleBall::Move();
	void ModuleBall::ChargeBall();
	void ModuleBall::ReleaseBall();
	void ModuleBall::ReturnBall();
	BALL_POSITION ModuleBall::getPosition();

public:
	iPoint position;
private:
	uint charge=0;

	bool movement_allowed=true, shot_charged=false, back_to_player=false;

	Collider *ball1_collider;
	
	

	Animation blueball_0;
	Animation blueball_45;
	Animation blueball_90;
	Animation blueball_135;
	Animation blueball_180;
	Animation blueball_225;
	Animation blueball_270;
	Animation blueball_315;


};
#endif // !1

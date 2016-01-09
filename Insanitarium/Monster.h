#pragma once

class Monster :public Object
{
public:
	bool CheckIfMonsterInSight(float,float,float, float, float, float);
	vec3 MoveTowardsPlayer(float,float,float,float);
	bool CheckIfMonsterTouchPlayer(float, float, float);
	void Render(float,float,float,float,float,float);
	
	Monster();
	Monster(char*);
	~Monster();

private:
	int HP;
};


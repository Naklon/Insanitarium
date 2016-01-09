#include "stdafx.h"



bool Monster::CheckIfMonsterInSight(float playerX, float playerY, float playerZ, float camX, float camY, float camZ)
{
	vec3 startPoint(playerX,playerY,playerZ);
	vec3 monsterPoint(this->x, this->y+0.6, this->z);
	vec3 playerPoint(camX,camY,camZ);
	float angle;
	float cosAngle = ((monsterPoint.x - startPoint.x)*(playerPoint.x - startPoint.x) + (monsterPoint.y - startPoint.y)*(playerPoint.y - startPoint.y) + (monsterPoint.z - startPoint.z)*(playerPoint.z - startPoint.z))
		/ (sqrt(pow((monsterPoint.x - startPoint.x), 2) + pow((monsterPoint.y - startPoint.y), 2) + pow((monsterPoint.z - startPoint.z), 2))*sqrt(pow((playerPoint.x - startPoint.x), 2) + pow((playerPoint.y - startPoint.y), 2)
			+ pow((playerPoint.z - startPoint.z), 2)));

	angle = acos(cosAngle) * 180 / PI;

	if (angle < 50)
		return true;
	else
		return false;
}

vec3 Monster::MoveTowardsPlayer(float playerX,float playerY,float playerZ,float multiply)
{
	vec3 moveVector(playerX-this->x, playerY-this->y, playerZ-this->z);
	vec3 newMonsterPos(this->x + moveVector.x*0.015*multiply, this->y, this->z + moveVector.z*0.015*multiply);

	return newMonsterPos;
}

bool Monster::CheckIfMonsterTouchPlayer(float playerX, float playerY, float playerZ)
{
	if (sqrt(pow(playerX - this->x, 2) + pow(playerY - this->y, 2) + pow(playerZ - this->z, 2)) < 0.7)
		return true;
	else
		return false;
}
bool ifMonsterRotated = false;

void Monster::Render(float x, float y, float z, float rx, float ry, float rz)
{
	this->x = x;
	this->y = y;
	this->z = z;
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(-atan2(z - rz, x - rx) * 180 / PI, 0, 1, 0);
	glCallList(list);
	glPopMatrix();
}

Monster::Monster()
{
}

Monster::Monster(char * path) :Object(path, "Potwor", false)
{
	this->HP = 100;
}


Monster::~Monster()
{
}

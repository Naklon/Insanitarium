#include "stdafx.h"
#include "Player.h"

void CPlayer::SetPlayerRunningSpeed(float newSpeed)
{
	this->speed = newSpeed;
}

void CPlayer::SetPlayerNormalSpeed()
{
	this->speed = 0.5;
}

void CPlayer::SetPlayerCrouchSpeed(float newSpeed)
{
	this->speed = newSpeed;
}

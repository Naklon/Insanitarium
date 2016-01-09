#include "stdafx.h"
#include "Player.h"

TextBox *DeadScreen;

irrklang::ISoundEngine *button;
Audio Button(button);

bool ifShowDeadScreen = true;
bool ifShowBlood = true;
bool ifPlayBtnSound1 = true;
bool ifPlayBtnSound2 = true;

void ShowEndScreen(int);

void GamePlayer::SetPlayerRunningSpeed(float newSpeed)
{
	this->speed = newSpeed;
}

void GamePlayer::SetPlayerNormalSpeed()
{
	this->speed = 0.5;
}

void GamePlayer::SetPlayerCrouchSpeed(float newSpeed)
{
	this->speed = newSpeed;
}

void GamePlayer::KillPlayer()
{
	if (ifShowBlood)
		HUD::KillPlayer();
	else
	{
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		HUD::ShowDeathScreen();
		if (mouseX > 0 && mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.4 && mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.8 &&mouseY < glutGet(GLUT_WINDOW_HEIGHT))
		{
			ifPlayBtnSound2 = true;
			if (ifPlayBtnSound1)
			{
				ifPlayBtnSound1 = false;
				Button.Play2D("Resources/Sounds/menu_nav.ogg", 1 * (sound / 100), false);
			}
			if (ifLMBPressed)
			{
				system("start restart.cmd");
				glutLeaveMainLoop();
			}
		}
		else if (mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.6 && mouseX<glutGet(GLUT_WINDOW_WIDTH) && mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.8 &&mouseY < glutGet(GLUT_WINDOW_HEIGHT))
		{
			ifPlayBtnSound1 = true;
			if (ifPlayBtnSound2)
			{
				ifPlayBtnSound2 = false;
				Button.Play2D("Resources/Sounds/menu_nav.ogg", 1 * (sound / 100), false);
			}
			if (ifLMBPressed)
				glutLeaveMainLoop();
		}
		else
		{
			ifPlayBtnSound1 = true;
			ifPlayBtnSound2 = true;
		}
	}

	if (ifShowDeadScreen)
	{
		glutTimerFunc(1000, ShowEndScreen, 0);
		Button.Play2D("Resources/Sounds/Monster_kill.ogg", 1, false);
		ifShowDeadScreen = false;
	}
}

void GamePlayer::PickUpKey()
{
	keysCollected++;
}

void ShowEndScreen(int)
{
	ifShowBlood = false;
}


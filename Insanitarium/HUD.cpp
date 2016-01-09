#include "stdafx.h"

TextBox *Cam3;
TextBox *Cam2;
TextBox *Cam1;
TextBox *Cam0;
TextBox *BatteryCounter1;
TextBox *BatteryCounter2;
TextBox *BatteryCounter3;
TextBox *BatteryCounter4;
TextBox *BatteryCounter5;
TextBox *BatteryCounter6;
TextBox *BatteryCounter7;
TextBox *BatteryCounter8;
TextBox *BatteryCounter9;

TextBox *PickMessage;
TextBox *BatteryPick;
TextBox *PickMessageCam;
TextBox *BatteryPickCam;
TextBox *DeadScreenMenu;
TextBox *KeyPick;
TextBox *KeyPickCam;

float redDotTimer = 0;

void HUD::DrawCrossHair()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

	glutSetCursor(GLUT_CURSOR_NONE);

	float radius;

	glClear(GL_DEPTH_BUFFER_BIT);
	radius = glutGet(GLUT_WINDOW_WIDTH)*0.001;

	glColor4f(169, 169, 169, 0.5);////Kolor Celownika(R,G,B,A)

	glTranslatef(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, 0);
	glBegin(GL_POLYGON);
	for (double i = 0; i < 2 * PI; i += PI / 24)
		glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();
}

void HUD::DrawCameraView()
{

	if (redDotTimer < 5 && redDotTimer >= 0)
	{
		glTranslatef(glutGet(GLUT_WINDOW_WIDTH)*0.95, glutGet(GLUT_WINDOW_HEIGHT)*0.085, 0);
		glBegin(GL_POLYGON);
		glColor4f(1, 0, 0, 0.3);
		for (double i = 0; i < 2 * PI; i += PI / 24)
			glVertex3f(cos(i) * glutGet(GLUT_WINDOW_WIDTH)*0.01, sin(i) * glutGet(GLUT_WINDOW_WIDTH)*0.01, 0.0);
		glEnd();
		glTranslatef(-glutGet(GLUT_WINDOW_WIDTH)*0.95, -glutGet(GLUT_WINDOW_HEIGHT)*0.085, 0);
		redDotTimer += 0.2;
	}
	else if (redDotTimer >= 5)
		redDotTimer = -5;
	else if (redDotTimer < 0)
		redDotTimer += 0.2;

	int counter = Cam->GetBatteryInfo("Count");

	switch (counter)
	{
	case 1:
		BatteryCounter1->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 2:
		BatteryCounter2->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 3:
		BatteryCounter3->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 4:
		BatteryCounter4->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 5:
		BatteryCounter5->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 6:
		BatteryCounter6->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 7:
		BatteryCounter7->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 8:
		BatteryCounter8->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	case 9:
		BatteryCounter9->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
			glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08);
		break;
	}

	if (Cam->GetBatteryInfo("Power") > 66)
	{
		Cam3->Render(0.3, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);
	}
	else if (Cam->GetBatteryInfo("Power") > 33)
	{
		Cam2->Render(0.3, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);
	}
	else if (Cam->GetBatteryInfo("Power") > 10)
	{
		Cam1->Render(0.3, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);
	}
	else if (Cam->GetBatteryInfo("Power") > 0)
	{
		Cam0->Render(0.3, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);
	}
}

void HUD::ShowPickMessage(Object *obj)
{
	glTranslatef(-glutGet(GLUT_WINDOW_WIDTH) / 2, -glutGet(GLUT_WINDOW_HEIGHT) / 2, 0);

	if (obj != NULL)
	{
		if (ifCameraOn)
			PickMessageCam->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
				glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55);
		else
			PickMessage->Render(0.5, glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
				glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55);

		if (obj->Name == "Bateria1" || obj->Name=="Bateria2")
		{
			if (ifCameraOn)
				BatteryPickCam->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
					glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55);
			else
				BatteryPick->Render(0.5, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
					glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55);
		}
		else if (obj->Name == "Klucz1" || obj->Name == "Klucz2" || obj->Name == "Klucz3")
		{
			if (ifCameraOn)
				KeyPickCam->Render(0.3, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
					glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55);
			else
				KeyPick->Render(0.5, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
					glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55);
		}
	}
}

void HUD::KillPlayer()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

	DeadScreen->Render(0.6, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);
}

void HUD::ShowDeathScreen()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);

	DeadScreenMenu->Render(0.6, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);
}

HUD::HUD()
{
}

HUD::~HUD()
{
}
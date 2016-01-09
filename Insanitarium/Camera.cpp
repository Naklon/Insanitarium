#include "stdafx.h"
#include "Camera.h"

GamePlayer Player;
float CameraX = Player.pos.x+0.25, CameraY = Player.pos.y-0.2, CameraZ = Player.pos.z-0.5;
irrklang::ISoundEngine* camera;
Audio CamVoice(camera);

void Camera::Render(float x, float y, float z, float rx, float ry, float rz)
{
	glPushMatrix();
	glTranslatef(x, y+0.2, z);
	glRotatef(-atan2(rz, rx) * 180 / PI, 0, 1, 0);
	float d = sqrt(pow(rx, 2) + pow(rz, 2));
	float pitch = atan2(ry, d);
	glRotatef(pitch * 180 / PI, 0, 0, 1);
	glTranslatef(0.25, 0, -0.22);
	glCallList(list);
	glPopMatrix();
}

void Camera::DechargeBattery()
{
	if (ifCameraOn)
	{
		if (this->battery > 0)
			battery -= 0.02;
		else
			this->PutCameraDown();
	}
}

void Camera::PickUpCamera()
{
	if (this->battery > 0)
	{
		ifCameraOn = true;
		CamVoice.Stop('S');
		CamVoice.Play2D("Resources/Sounds/Camera_On.ogg", 1 * (sound / 100), false);
	}
	else
		CamVoice.Play2D("Resources/Sounds/Beep_wrong.ogg", 0.5*(sound / 100), false);
}

void Camera::PutCameraDown()
{
	FOV = 60;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, viewPortWidth, viewPortHeight);
	gluPerspective(70.0f, (float)Sizex / Sizey, .01f, 100.0f);
	CamVoice.Stop('S');
	CamVoice.Play2D("Resources/Sounds/Camera_Off.ogg", 1* (sound / 100), false);
	ifCameraOn = false;
}

float Camera::GetBatteryInfo(char* c)
{
	if (c == "Power")
		return this->battery;
	else if (c == "Count")
		return this->batteries;
}

void Camera::Update()
{
		Cam->Render(CameraX,CameraY,CameraZ, Player.dir.x, Player.dir.y, Player.dir.z);
}

void Camera::ChangeCameraBattery()
{
	if (this->battery < 66 && this->batteries > 0)
	{
		CamVoice.Play2D("Resources/Sounds/Camera_battery_change.ogg", 1* (sound / 100), false);
		this->battery = 100;
		this->batteries--;
	}
	else
		CamVoice.Play2D("Resources/Sounds/Beep_wrong.ogg", 0.5*(sound / 100), false);
}

bool Camera::PickUpBattery()
{
	if (this->batteries < 9)
	{
		this->batteries++;
		return true;
	}
	else
	{
		CamVoice.Play2D("Resources/Sounds/Beep_wrong.ogg", 0.5*(sound / 100), false);
		return false;
	}
}

Camera::Camera(char * path) :Object(path,"Kamera",false)
{
	this->battery = 100;
	this->batteries = 0;
}

Camera::Camera()
{
	this->battery = 100;
	this->batteries = 0;
}

Camera::~Camera()
{
}

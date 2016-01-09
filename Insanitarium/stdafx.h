// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define PI 3.14159265
#define Game 1
#define GameMenu 2
#define Menu 3
#define Options 4

#include "targetver.h"

#include <string>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <cassert>
#include <map>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdarg.h>			

using namespace std;

#include <GL/freeglut.h>


#include "Vec3.h"
#include "Bitmap.h"
#include "Texture.h"
#include "Audio.h"
#include "CollisionDetection.h"
#include "Collision.h"
#include "CollisionEllipsoid.h"
#include "CollisionPlane.h"
#include "CollisionPolygon.h"
#include "MainMenu.h"
#include "TextBox.h"
#include "Camera.h"
#include "HUD.h"
#include "Player.h"
#include "Monster.h"
#include "SceneObject.h"
#include "Skydome.h"


#include "Scene.h"
//#include "StaticObject.h"
#include "Insanitarium.h"

#pragma region Zmienne globalne

	extern float T;
	extern bool firstLaunch;

	extern int mouseX;
	extern int mouseY;

	extern bool captureMouse;
	extern bool free3DMovement;
	extern bool ifPlayerAlive;
	extern bool Window;
	extern bool res1;
	extern bool res2;
	extern bool ifCameraOn;

	extern int gameState;
	extern int keysCollected;
	extern int viewPortWidth;
	extern int viewPortHeight;

	extern float mouseSensitivity;

	extern Scene *Scene1;

	extern POINT mousePoint;

	extern POINT musicLeft1;
	extern POINT musicLeft2;
	extern POINT musicLeft3;

	extern POINT musicRight1;
	extern POINT musicRight2;
	extern POINT musicRight3;

	extern POINT soundLeft1;
	extern POINT soundLeft2;
	extern POINT soundLeft3;

	extern POINT soundRight1;
	extern POINT soundRight2;
	extern POINT soundRight3;

	extern POINT mouseLeft1;
	extern POINT mouseLeft2;
	extern POINT mouseLeft3;

	extern POINT mouseRight1;
	extern POINT mouseRight2;
	extern POINT mouseRight3;

	extern POINT resolution1;
	extern POINT resolution2;
	
	extern Audio *Soundtrack;

	extern bool keystate[255];
	extern bool ifQPressed;
	extern bool ifLMBPressed;

	extern float radius;
	extern float sound;
	extern float music;	
	extern float FOV;
	extern int Sizex;
	extern int Sizey;

	extern Monster *Monster1;

	extern Camera *Cam;

	extern Object *Bed1;
	extern Object *Toliet01;
	extern Object *Castle;
	extern Object *Battery1;
	extern Object *ObjToPick;
	extern Object *Battery2;
	extern Object *Key1;
	extern Object *Key2;
	extern Object *ExitDoor;
	extern Object *Bulb;

	extern TextBox *Cam3;
	extern TextBox *Cam2;
	extern TextBox *Cam1;
	extern TextBox *Cam0;
	extern TextBox *BatteryCounter1;
	extern TextBox *BatteryCounter2;
	extern TextBox *BatteryCounter3;
	extern TextBox *BatteryCounter4;
	extern TextBox *BatteryCounter5;
	extern TextBox *BatteryCounter6;
	extern TextBox *BatteryCounter7;
	extern TextBox *BatteryCounter8;
	extern TextBox *BatteryCounter9;
	extern TextBox *PickMessage;
	extern TextBox *BatteryPick;
	extern TextBox *PickMessageCam;
	extern TextBox *BatteryPickCam;
	extern TextBox *DeadScreen;
	extern TextBox *DeadScreenMenu;
	extern TextBox *KeyPick;
	extern TextBox *KeyPickCam;

	extern std::vector<Object*> Interactable;

	extern GamePlayer Player;
	extern std::string Map;

#pragma endregion

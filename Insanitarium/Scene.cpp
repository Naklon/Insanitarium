#include "stdafx.h"


void ResumeMonsterScare(int);
void MakeRandomness(int);
void StartDeathCountdown();
void FinishTired(int);
void ReleaseMonster(int);

bool ifjump = false;
bool iffall = false;
bool ifcrouch = false;
bool playingrunning = true;
bool playingsteps = true;
bool playingcrouch = true;
bool ifShowPickMsg = false;
bool ifRenderBattery1 = true;
bool ifRenderBattery2 = true;
bool ifPlayMonsterJumpscare = true;
bool ifReleaseMonster = false;;
bool ifMonsterSoundReady = false;
bool ifInstantPlayerKill = false;
bool ifPlayInstantDeathSound = true;
bool ifStartMonsterBreathe = true;
bool ifRenderKey1 = true;
bool ifRenderKey2 = true;
bool ifTiredFinished = true;
bool ifPlayTiredSound = true;
bool ifGameStart = true;

float visionspeedx = 1, visionspeedz = 1;
float visionstate = 0.013;
float visionspeed = 12;
float tempheigh;
float visionx = 0.0f, visiony = 1.0f, visionz = 0.0f;//wspó³rzêdne pionu

vec3 monsterPos((rand()%60)-30, 0, (rand() % 60) - 30);
vec3 exitPos(0, 0, 0);
vec3 key1Pos(0, 0, 0);
vec3 key2Pos(0, 0, 0);


int AngleofCamera = 0;
int jumpCounter = 0;
int deathCountdown = 0;
int tiredCountdown = 0;

irrklang::ISoundEngine* soundtrack;
Audio *Soundtrack = new Audio(soundtrack);

irrklang::ISoundEngine* steps;
Audio Steps(steps);

irrklang::ISoundEngine* running;
Audio Running(running);

irrklang::ISoundEngine* jump;
Audio Jumping(jump);

irrklang::ISoundEngine* items;
Audio Items(items);

irrklang::ISoundEngine* tire;
Audio Tire(tire);

irrklang::ISoundEngine* monster;
Audio MonsterSound(monster);

irrklang::ISoundEngine* monsterbreath=irrklang::createIrrKlangDevice();
irrklang::ISound* MonsterBreath = monsterbreath->play3D("Resources/Sounds/MonsterBreathe.ogg", irrklang::vec3df(monsterPos.x, monsterPos.y, monsterPos.z), true, false, true);


Object *ObjToPick;
Monster *Monster1;
Camera *Cam;
Object *Bed1;
Object *Toliet01;
Object *Battery1;
Object *Battery2;
Object *Key1;
Object *Key2;
Object *ExitDoor;
Object *Bulb;

std::vector<StaticObject*> monsterWalls;
std::vector<SceneObject*> *ceiling;

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
	if (Skydome != NULL)
		delete Skydome;
}

void Scene::Initialize(void) 
{
	for (int i = 0; i < 100000000; i++)
	MakeRandomness((rand() % 10000) *(rand()%1000));

	monsterPos.z = ((monsterPos.z+(rand()%1000)-400))/10;
	monsterPos.x = (monsterPos.x / 3)*(rand() % 6) - 3;

	#pragma region Settings
	
		glEnable(GL_LIGHT0);
		glEnable(GL_FOG);
		float gl_fogcolor[] = { 0.1f, 0.15f, 0.2f, 1.0f };
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, gl_fogcolor);
		glFogf(GL_FOG_START, 2.0f);
		glFogf(GL_FOG_END, 18.0f);

		Player.pos.x = 3.5f;
		Player.pos.y = 0.3f;
		Player.pos.z = -1.5f;

		Player.dir.x = 1.0f;
		Player.dir.y = 0.0f;
		Player.dir.z = .0f;

		Player.speed = .45f;

	#pragma endregion

	#pragma region Scene
	
		Skydome = new CSkydome();
		Skydome->Initialize();

		
	
		Objects = new vector<SceneObject *>();
		ceiling = new std::vector<SceneObject*>();
		StaticObject *w;
		if (Map == "Hospital")
		{
			/////////////////////////////////////Wygl¹d mapy:
			//Wysokoœæ œciany 1
			//Gruboœæ œciany 0.1
			//Szerokoœæ drzwi 0.5
			/////////////////////////////////////

			vec3 walls[][4] =
			{
				{ vec3(3.0f,  0.0f, -3.0f), vec3(3.0f,  1.0f, -3.0f), vec3(0.0f,  1.0f, -3.0f), vec3(0.0f,  0.0f, -3.0f) },
				{ vec3(6.0f,  0.0f, -3.0f), vec3(6.0f,  1.0f, -3.0f), vec3(3.0f,  1.0f, -3.0f), vec3(3.0f,  0.0f, -3.0f) },
				{ vec3(6.0f,  0.0f, 0.0f), vec3(6.0f,  1.0f, 0.0f), vec3(6.0f,  1.0f, -3.0f), vec3(6.0f,  0.0f, -3.0f) },
				{ vec3(3.0f,  0.0f, 0.0f), vec3(3.0f,  1.0f, 0.0f), vec3(6.0f,  1.0f, 0.0f), vec3(6.0f,  0.0f, 0.0f) },
				{ vec3(3.0f,  0.0f, -3.0f), vec3(3.0f,  1.0f, -3.0f), vec3(3.0f,  1.0f, -1.75f), vec3(3.0f,  0.0f, -1.75f) },
				{ vec3(3.0f,  0.0f, -1.25f), vec3(3.0f,  1.0f, -1.25f), vec3(3.0f,  1.0f, 0.0f), vec3(3.0f,  0.0f, 0.0f) },
				{ vec3(2.9f,  0.0f, -1.75f), vec3(2.9f,  1.0f, -1.75f), vec3(2.9f,  1.0f, -3.0f), vec3(2.9f,  0.0f, -3.0f) },
				{ vec3(2.9f,  0.0f, 0), vec3(2.9f,  1.0f, 0), vec3(2.9f,  1.0f, -1.25f), vec3(2.9f,  0.0f, -1.25f) },
				{ vec3(2.9,  0.0f, -1.25), vec3(2.9,  1.0f, -1.25), vec3(3,  1.0f, -1.25f), vec3(3,  0.0f, -1.25f) },
				{ vec3(3,  0.0f, -1.75), vec3(3,  1.0f, -1.75), vec3(2.9,  1.0f, -1.75f), vec3(2.9,  0.0f, -1.75f) },
				{ vec3(3,  0.75f, -1.75), vec3(3,  1.0f, -1.75), vec3(3,  1.0f, -1.25f), vec3(3,  0.75f, -1.25f) },
				{ vec3(2.9,  0.75f, -1.75), vec3(3,  0.75f, -1.75), vec3(3,  .75f, -1.25f), vec3(2.9,  0.75f, -1.25f) },
				{ vec3(2.9,  0.75f, -1.25), vec3(2.9,  1.0f, -1.25), vec3(2.9,  1.0f, -1.75f), vec3(2.9,  0.75f, -1.75f) },
				{ vec3(0.0f,  0.0f, -3.0f), vec3(0.0f,  1.0f, -3.0f), vec3(-3.0f,  1.0f, -3.0f), vec3(-3.0f,  0.0f, -3.0f) },
				{ vec3(-3.0f,  0.0f, -3.0f), vec3(-3.0f,  1.0f, -3.0f), vec3(-6.0f,  1.0f, -6.0f), vec3(-6.0f,  0.0f, -6.0f) },
				{ vec3(-6.0f,  0.0f, -6.0f), vec3(-6.0f,  1.0f, -6.0f), vec3(-6.5f,  1.0f, -6.0f), vec3(-6.5f,  0.0f, -6.0f) },
				{ vec3(2.9f,  0.0f, 3.0f), vec3(2.9f,  1.0f, 3.0f), vec3(2.9f,  1.0f, 0.0f), vec3(2.9f,  0.0f, 0.0f) },
				{ vec3(0.0f,  0.0f, 3.0f), vec3(0.0f,  1.0f, 3.0f), vec3(2.9f,  1.0f, 3.0f), vec3(2.9f,  0.0f, 3.0f) },
				{ vec3(-0.5f,  0.75f, 3.0f), vec3(-0.5f,  1.0f, 3.0f), vec3(0.0f,  1.0f, 3.0f), vec3(0.0f,  0.75f, 3.0f) },
				{ vec3(-0.6f,  0.0f, 3.0f), vec3(-0.6f,  1.0f, 3.0f), vec3(-0.5f,  1.0f, 3.0f), vec3(-0.5f,  0.0f, 3.0f) },
				{ vec3(-0.5f,  0.0f, 3.0f), vec3(-0.5f,  1.0f, 3.0f), vec3(-0.5f,  1.0f, 6.0f), vec3(-0.5f,  0.0f, 6.0f) },
				{ vec3(-0.5f,  0.0f, 6.0f), vec3(-0.5f,  1.0f, 6.0f), vec3(3.0f,  1.0f, 6.0f), vec3(3.0f,  0.0f, 6.0f) },
				{ vec3(3.0f,  0.0f, 6.0f), vec3(3.0f,  1.0f, 6.0f), vec3(3.0f,  1.0f, 9.0f), vec3(3.0f,  0.0f, 9.0f) },
				{ vec3(0.0f,  0.0f, 3.1f), vec3(0.0f,  1.0f, 3.1f), vec3(0.0f,  1.0f, 3.0f), vec3(0.0f,  0.0f, 3.0f) },
				{ vec3(3.0f,  0.0f, 3.1f), vec3(3.0f,  1.0f, 3.1f), vec3(0.0f,  1.0f, 3.1f), vec3(0.0f,  0.0f, 3.1f) },
				{ vec3(6.0f,  0.0f, 3.1f), vec3(6.0f,  1.0f, 3.1f), vec3(3.0f,  1.0f, 3.1f), vec3(3.0f,  0.0f, 3.1f) },
				{ vec3(6.0f,  0.0f, 6.0f), vec3(6.0f,  1.0f, 6.0f), vec3(6.0f,  1.0f, 3.0f), vec3(6.0f,  0.0f, 3.0f) },
				{ vec3(6.0f,  0.0f, 9.0f), vec3(6.0f,  1.0f, 9.0f), vec3(6.0f,  1.0f, 6.0f), vec3(6.0f,  0.0f, 6.0f) },
				{ vec3(6.0f,  0.75f, 9.5f), vec3(6.0f,  1.0f, 9.5f), vec3(6.0f,  1.0f, 9.0f), vec3(6.0f,  0.75f, 9.0f) },
				{ vec3(3.0f,  0.0f, 9.5f), vec3(3.0f,  1.0f, 9.5f), vec3(6.0f,  1.0f, 9.5f), vec3(6.0f,  0.0f, 9.5f) },
				{ vec3(0.0f,  0.0f, 9.5f), vec3(0.0f,  1.0f, 9.5f), vec3(3.0f,  1.0f, 9.5f), vec3(3.0f,  0.0f, 9.5f) },
				{ vec3(3.0f,  0.0f, 9.0f), vec3(3.0f,  1.0f, 9.0f), vec3(0.0f,  1.0f, 9.0f), vec3(0.0f,  0.0f, 9.0f) },
				{ vec3(-3.0f,  0.0f, 9.5f), vec3(-3.0f,  1.0f, 9.5f), vec3(0.0f,  1.0f, 9.5f), vec3(0.0f,  0.0f, 9.5f) },
				{ vec3(0.0f,  0.0f, 9.0f), vec3(0.0f,  1.0f, 9.0f), vec3(0.0f,  1.0f, 6.0f), vec3(0.0f,  0.0f, 6.0f) },
				{ vec3(0.0f,  0.0f, 6.0f), vec3(0.0f,  1.0f, 6.0f), vec3(-0.6f,  1.0f, 6.0f), vec3(-0.6f,  0.0f, 6.0f) },
				{ vec3(-3.0f,  0.0f, 8.0f), vec3(-3.0f,  1.0f, 8.0f), vec3(-3.0f,  1.0f, 9.5f), vec3(-3.0f,  0.0f, 9.5f) },
				{ vec3(-6.0f,  0.0f, 8.0f), vec3(-6.0f,  1.0f, 8.0f), vec3(-3.0f,  1.0f, 8.0f), vec3(-3.0f,  0.0f, 8.0f) },
				{ vec3(-6.0f,  0.0f, 3.0f), vec3(-6.0f,  1.0f, 3.0f), vec3(-3.0f,  1.0f, 3.0f), vec3(-3.0f,  0.0f, 3.0f) },
				{ vec3(-3.0f,  0.0f, 3.0f), vec3(-3.0f,  1.0f, 3.0f), vec3(-3.0f,  1.0f, 6.0f), vec3(-3.0f,  0.0f, 6.0f) },
				{ vec3(-3.0f,  0.0f, 6.0f), vec3(-3.0f,  1.0f, 6.0f), vec3(-6.0f,  1.0f, 6.0f), vec3(-6.0f,  0.0f, 6.0f) },
				{ vec3(-6.0f,  0.0f, 6.0f), vec3(-6.0f,  1.0f, 6.0f), vec3(-8.0f,  1.0f, 6.0f), vec3(-8.0f,  0.0f, 6.0f) },
				{ vec3(-8.0f,  0.0f, 6.0f), vec3(-8.0f,  1.0f, 6.0f), vec3(-8.0f,  1.0f, 9.0f), vec3(-8.0f,  0.0f, 9.0f) },
				{ vec3(-6.0f,  0.0f, 11.0f), vec3(-6.0f,  1.0f, 11.0f), vec3(-6.0f,  1.0f, 8.0f), vec3(-6.0f,  0.0f, 8.0f) },
				{ vec3(-9.0f,  0.0f, 11.0f), vec3(-9.0f,  1.0f, 11.0f), vec3(-6.0f,  1.0f, 11.0f), vec3(-6.0f,  0.0f, 11.0f) },
				{ vec3(-12.0f,  0.0f, 11.0f), vec3(-12.0f,  1.0f, 11.0f), vec3(-9.0f,  1.0f, 11.0f), vec3(-9.0f,  0.0f, 11.0f) },
				{ vec3(-15.0f,  0.0f, 11.0f), vec3(-15.0f,  1.0f, 11.0f), vec3(-12.0f,  1.0f, 11.0f), vec3(-12.0f,  0.0f, 11.0f) },


				{ vec3(-0.6f,  0.0f, 6.0f), vec3(-0.6f,  1.0f, 6.0f), vec3(-0.6f,  1.0f, 3.0f), vec3(-0.6f,  0.0f, 3.0f) },

			};

			vec3 collisions[][4] =
			{
				//Bed1->Render(-2.7, 0, 4, 0, 0, 0, 0);
				{ vec3(-0.506480 + 4, 0.343890 + 0.3, 0.154960 - 2.7 + 0.03), vec3(-0.506480 + 4, 0.343890 + 0.3, -0.234238 - 2.7 - 0.03), vec3(-0.506480 + 4, -0.045307, -0.234238 - 2.7 - 0.03), vec3(-0.506480 + 4, -0.045307, 0.154960 - 2.7 + 0.03) },
				{ vec3(0.506480 + 4, 0.343890 + 0.3,0.154960 - 2.7 + 0.03), vec3(0.506480 + 4, -0.045307, 0.154960 - 2.7 + 0.03), vec3(0.506480 + 4, -0.045307 ,-0.234238 - 2.7 - 0.03), vec3(0.506480 + 4, 0.343890 + 0.3 ,-0.234238 - 2.7 - 0.03)  },
				{ vec3(-0.470392 + 4 - 0.03, -0.086616 ,-0.252996 - 2.7),  vec3(-0.470392 + 4 - 0.03, 0.343635 + 0.3, -0.252996 - 2.7),vec3(0.470392 + 4 + 0.03, 0.343635 + 0.3, -0.252996 - 2.7),vec3(0.470392 + 4 + 0.03,-0.086616, -0.252996 - 2.7) },
				{ vec3(-0.470772 + 4 - 0.03, 0.350059 + 0.3, 0.182670 - 2.7),vec3(-0.470772 + 4 - 0.03 ,-0.080193 ,0.182670 - 2.7), vec3(0.470012 + 4 + 0.03, -0.080193, 0.182670 - 2.7) ,vec3(0.470012 + 4 + 0.03, 0.350059 + 0.3, 0.182670 - 2.7) }
				///////////////////////////////////////

			};

			int colCounter = sizeof(collisions) / sizeof(collisions[0]);

			for (int i = 0; i < colCounter; i++)
			{
				w = new StaticObject(collisions[i][0], collisions[i][1], collisions[i][2], collisions[i][3], "None");
				w->Initialize();
				Objects->push_back(w);
			}

			int wallsCounter = sizeof(walls) / sizeof(walls[0]);

			char *tex;

			for (float i = -20;i < 20;i++)
			{
				for (float j = -20; j < 20;j++)
				{
					w = new StaticObject({ i,0,j }, { i,0,j + 1 }, { i + 1,0,j + 1 }, { i + 1,0,j }, "Resources/Floor01.bmp");
					sprintf(w->Name, "Floor %d", i);
					w->Initialize();
					Objects->push_back(w);

				}
			}

			for (float i = -20;i < 20;i++)
			{
				for (float j = -20; j < 20;j++)
				{
					w = new StaticObject({ i,1,j }, { i + 1,1,j }, { i + 1,1,j + 1 }, { i,1,j + 1 } , "Resources/Ceiling.bmp");
					sprintf(w->Name, "Ceiling %d", i);
					w->Initialize();
					ceiling->push_back(w);
				}
			}

			for (int i = 0; i < wallsCounter; i++)
			{
				if (i == 2)
					tex = "Resources/Wall_controls.bmp";
				else if (i == 10 || i == 11 || i == 12 || i==18 || i==28)
					tex = "Resources/Wall_upper.bmp";
				else
					tex = "Resources/Wall.bmp";

				w = new StaticObject(walls[i][0], walls[i][1], walls[i][2], walls[i][3], tex);
				sprintf(w->Name, "Wall %d", i);
				w->Initialize();
				Objects->push_back(w);
				monsterWalls.push_back(w);
			}
			
#pragma endregion
		}
		monsterPos.x = (monsterPos.x / 3)*(rand() % 6) - 3;
		monsterPos.x = (monsterPos.x / 3)*(rand() % 120) - 100;
		monsterPos.z = (monsterPos.z / 2)*(rand() % 7) - 4;
		monsterPos.z = ((monsterPos.z + (rand() % 1000) - 400)) / 10;
		
		float doorPos = rand() % 10000;
		float key1PosRand = rand() % 10000;
		float key2PosRand = rand() % 10000;

		if (doorPos > 0 && doorPos <= 3333)
			exitPos.Set(-13, 0, 11);
		else if (doorPos > 3333 && doorPos <= 6666)
			exitPos.Set(0, 0, 1);
		else
			exitPos.Set(0, 0, 0);

		if (key1PosRand > 0 && key1PosRand < 3333)
			key1Pos.Set(0, 0, 3);
		else if (key1PosRand > 0 && key1PosRand < 3333)
			key1Pos.Set(1, 0, 1);
		else 
			key1Pos.Set(0, 0, 0);

		if (key2PosRand > 0 && key2PosRand < 3333)
			key2Pos.Set(0, 0, 3);
		else if (key2PosRand > 0 && key2PosRand < 3333)
			key2Pos.Set(1, 0, 1);
		else
			key2Pos.Set(0, 0, 0);
}

void Scene::Update(float sound, int gameState)
{
	bool ifItemNear = false;
	if (gameState == 1)
	{
		if (ifPlayerAlive)
		{
			if (Map == "Hospital")
			{
#pragma region Interaction

				ifItemNear = false;

				if (ifRenderBattery1 && sqrt((Player.pos.x - Battery1->x)*(Player.pos.x - Battery1->x) +
					(Player.pos.y - Battery1->y)*(Player.pos.y - Battery1->y) +
					(Player.pos.z - Battery1->z)*(Player.pos.z - Battery1->z)) < 0.7)
				{
					ifItemNear = true;
					ObjToPick = Battery1;
					if (ifQPressed)
					{
						if (Cam->PickUpBattery())
						{
							Items.Play2D("Resources/Sounds/PickUp.ogg", 1 * (sound / 100), false);
							ifRenderBattery1 = false;
						}
					}
				}

				if (ifRenderBattery2 && sqrt((Player.pos.x - Battery2->x)*(Player.pos.x - Battery2->x) +
					(Player.pos.y - Battery2->y)*(Player.pos.y - Battery2->y) +
					(Player.pos.z - Battery2->z)*(Player.pos.z - Battery2->z)) < 0.7)
				{
					ifItemNear = true;
					ObjToPick = Battery2;
					if (ifQPressed)
					{
						if (Cam->PickUpBattery())
						{
							Items.Play2D("Resources/Sounds/PickUp.ogg", 1 * (sound / 100), false);
							ifRenderBattery2 = false;
						}
					}
				}

				if (ifRenderKey1 && sqrt((Player.pos.x - Key1->x)*(Player.pos.x - Key1->x) +
					(Player.pos.y - Key1->y)*(Player.pos.y - Key1->y) +
					(Player.pos.z - Key1->z)*(Player.pos.z - Key1->z)) < 0.7)
				{
					ifItemNear = true;
					ObjToPick = Key1;
					if (ifQPressed)
					{
						Items.Play2D("Resources/Sounds/PickUp.ogg", 1 * (sound / 100), false);
						ifRenderKey1 = false;
						Player.PickUpKey();
					}
				}

				if (!ifItemNear)
					ObjToPick = NULL;

#pragma endregion
			}

			if (!ifInstantPlayerKill)
			{
#pragma region Movement

				if (ifTiredFinished && captureMouse)
				{
					Player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX) * 30;
					Player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY) * 30;
					glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
				}

				if (ifTiredFinished && (GetKeyState(VK_LSHIFT) == -127 || GetKeyState(VK_LSHIFT) == -128) && !ifcrouch)
				{
					if (tiredCountdown <= 350)
					{
						ifPlayTiredSound = true;
						Player.SetPlayerRunningSpeed();
						visionstate = 0.03;
						visionspeed = 10;
						tiredCountdown++;
					}
					else
					{
						if (ifPlayTiredSound)
						{
							ifPlayTiredSound = false;
							Tire.Play2D("Resources/Sounds/Player_tired.ogg", 0.3 * (sound / 100), false);
						}
						ifTiredFinished = false;
						Player.SetPlayerCrouchSpeed(0.0);
						visionstate = 0.0;
						visionspeed = 12;
						glutTimerFunc(2000, FinishTired, 0);
					}
				}
				else if (ifTiredFinished && (GetKeyState(VK_LCONTROL) == -127 || GetKeyState(VK_LCONTROL) == -128))
				{
					tiredCountdown = 0;
					visionstate = 0.009;
					visionspeed = 17;
					Player.SetPlayerCrouchSpeed();
					ifcrouch = true;
				}
				else if (ifTiredFinished)
				{
					tiredCountdown = 0;
					visionstate = 0.013;
					visionspeed = 12;
					ifcrouch = false;
					Player.SetPlayerNormalSpeed();
				}

				if (keystate['w'])
				{
					if (!keystate['s'])/////////Jeœli gracz nie chce poruszaæ siê jednoczeœnie w przód i ty³, inicjalizuj bujanie siê kamery
					{
						Player.velM = Player.speed;
						if (Player.dir.x > 0.6 || Player.dir.x < -0.6)
							visionz = sin(AngleofCamera / visionspeed)*visionstate;
						else
							visionx = sin(AngleofCamera / visionspeed)*visionstate;

						AngleofCamera += 2;
					}
					visionspeedx = 1;
					visionspeedz = 1;
				}
				else
				{
					if (visionspeedz >= 0)
					{
						visionz = visionspeedz*visionz;
						visionspeedz -= 0.08;
					}

					if (visionspeedx >= 0)
					{
						visionx = visionspeedx*visionx;
						visionspeedx -= 0.08;
					}
				}
				if (keystate['s'])
				{
					if (!keystate['w'])/////////Jeœli gracz nie chce poruszaæ siê jednoczeœnie w przód i ty³, inicjalizuj bujanie siê kamery
					{
						Player.velM = -Player.speed;
						if (Player.dir.x > 0.6 || Player.dir.x < -0.6)
							visionz = sin(AngleofCamera / visionspeed)*visionstate;
						else
							visionx = sin(AngleofCamera / visionspeed)*visionstate;

						AngleofCamera += 2;
					}
					visionspeedx = 1;
					visionspeedz = 1;
				}
				else
				{
					if (visionspeedz >= 0)
					{
						visionz = visionspeedz*visionz;
						visionspeedz -= 0.08;
					}

					if (visionspeedx >= 0)
					{
						visionx = visionspeedx*visionx;
						visionspeedx -= 0.08;
					}
				}
				if (keystate['a'])
					Player.velS = -Player.speed;

				if (keystate['d'])
					Player.velS = Player.speed;

				if (keystate[' '] && !ifjump && !iffall)
				{
					jumpCounter = 0;
					ifjump = true;
					tempheigh = Player.pos.y;
				}

#pragma region Jump
				if (ifjump)
				{
					if (jumpCounter == 1)
						Jumping.Play2D("Resources/Sounds/jump_sound.ogg", 0.6*(sound / 100), false);

					if (jumpCounter <= 9)
					{
						Player.pos.y += 0.08;
						jumpCounter++;
					}
					else
					{
						ifjump = false;
						iffall = true;
					}
				}

				if (iffall)
				{
					if (jumpCounter >= 0)
						jumpCounter--;
					else
					{
						Jumping.Play2D("Resources/Sounds/fall_sound.ogg", 0.4*(sound / 100), false);
						iffall = false;
					}
				}
#pragma endregion

				float T = acos(Player.dir.y);
				float G = atan2(Player.dir.z, Player.dir.x);
				T -= Player.velRX * .03f;
				G += Player.velRY * .03f;
				Player.dir.x = sin(T) * cos(G);
				Player.dir.y = cos(T);
				Player.dir.z = sin(T) * sin(G);

				vec3 per;
				per.x = -Player.dir.z;
				per.y = 0;
				per.z = Player.dir.x;
				vec3 nextPlayerPos = Player.pos;

				nextPlayerPos.x += Player.dir.x * Player.velM * .1f;
				nextPlayerPos.y -= 0.04f;
				nextPlayerPos.z += Player.dir.z * Player.velM * .1f;
				nextPlayerPos.x += per.x * Player.velS * .1f;
				nextPlayerPos.z += per.z * Player.velS * .1f;

				Player.dir.y = __max(-0.9, Player.dir.y);
				Player.dir.y = __min(0.9, Player.dir.y);

#pragma region Crouch

				if (ifcrouch)
				{
					Player.collisionEllipsoid = new CCollisionEllipsoid(.15f, .1f, .15f);

				}
				else
				{
					Player.pos.y = 0.31f;
					Player.collisionEllipsoid = new CCollisionEllipsoid(.15f, .3f, .15f);
				}

#pragma endregion

				Player.pos = CCollisionDetection::GetPositionAfterWorldCollisions(Player.pos, nextPlayerPos, Player, Objects);

				Player.velRX /= 1.5;
				Player.velRY /= 1.5;
				Player.velM /= 1.5;
				Player.velS /= 1.5;

#pragma endregion
			}

#pragma region Sounds

			if (Player.speed > .5f && (keystate['w'] || keystate['a'] || keystate['d'] || keystate['s']))
			{
				Steps.Stop('S');
				if (playingrunning)
				{
					if (!(keystate['w'] && keystate['s']))
					{
						Running.Play2D("Resources/Sounds/Footsteps_running_01.ogg", 0.5*(sound / 100), true);
						playingrunning = false;
					}
					else
						Running.Stop('S');
				}

				playingsteps = true;
			}
			else if (Player.speed == .5f && (keystate['w'] || keystate['a'] || keystate['d'] || keystate['s']))
			{
				Running.Stop('S');

				if (playingsteps)
				{
					if (!(keystate['w'] && keystate['s']))
					{
						Steps.Play2D("Resources/Sounds/Footsteps_walking_01.ogg", 0.9*(sound / 100), true);
						playingsteps = false;
					}
					else
						Steps.Stop('S');
				}

				playingrunning = true;
			}
			else if (Player.speed < .5f && (keystate['w'] || keystate['a'] || keystate['d'] || keystate['s']))
			{
				Running.Stop('S');
				Steps.Stop('S');
				if (playingcrouch)
				{
					//Steps.Play2D("Resources/Sounds/");
				}
			}
			else if ((!keystate['w'] && !keystate['a'] && !keystate['d'] && !keystate['s']))
			{
				Running.Stop('S');
				Steps.Stop('S');
				playingrunning = true;
				playingsteps = true;
			}

#pragma endregion

#pragma region Camera

			Cam->DechargeBattery();

#pragma endregion
		}
		else
		{
			monsterbreath->setAllSoundsPaused(true);
			ifCameraOn = false;
			Player.collisionEllipsoid = new CCollisionEllipsoid(.15f, .1f, .15f);
			Player.pos.y = 0.02;
			visiony = 0.3;
			visionz = 0.8;
			Scene1->PauseAllSounds();
		}

#pragma region Objects update

		for (int i = 0; i < Objects->size(); ++i)
			Objects->at(i)->Update();

		Skydome->Update();

#pragma endregion

#pragma region Monster
		
		if (ifReleaseMonster)
		{
			monsterbreath->setAllSoundsPaused(false);
			MonsterBreath->setMinDistance(1);

			monsterbreath->setListenerPosition(irrklang::vec3df(Player.pos.x, Player.pos.y, Player.pos.z), irrklang::vec3df(0, 1, 0));
			MonsterBreath->setPosition(irrklang::vec3df(monsterPos.x, monsterPos.y, monsterPos.z));

			ifStartMonsterBreathe = false;
			if (ifPlayerAlive && !Monster1->CheckIfMonsterInSight(Player.pos.x, Player.pos.y, Player.pos.z, Player.pos.x + Player.cam.x + Player.dir.x,
				Player.pos.y + Player.cam.y + Player.dir.y, Player.pos.z + Player.cam.z + Player.dir.z))
			{
				switch (keysCollected)
				{
				case 0:
					monsterPos = Monster1->MoveTowardsPlayer(Player.pos.x, Player.pos.y, Player.pos.z, 0.6);
					break;
				case 1:
					monsterPos = Monster1->MoveTowardsPlayer(Player.pos.x, Player.pos.y, Player.pos.z, 1);
					break;
				case 2:
					monsterPos = Monster1->MoveTowardsPlayer(Player.pos.x, Player.pos.y, Player.pos.z, 3);
					break;
				}
				deathCountdown = 0;

				if (ifMonsterSoundReady)
				{
					ifMonsterSoundReady = false;
					glutTimerFunc((rand() % 45000) + 5000, ResumeMonsterScare, 0);
				}
			}
			else
			{
				if (sqrt(pow(monsterPos.x - Player.pos.x, 2) + pow(monsterPos.z - Player.pos.z, 2)) <= 4)
					StartDeathCountdown();
				else
					deathCountdown = 0;

				if (ifPlayMonsterJumpscare && sqrt(pow(monsterPos.x - Player.pos.x, 2) + pow(monsterPos.z - Player.pos.z, 2)) <= 4)
				{
					ifPlayMonsterJumpscare = false;
					MonsterSound.Play2D("Resources/Sounds/MonsterPopUp.ogg", 1 * (sound / 100), false);
					ifMonsterSoundReady = true;
				}
			}

			if (Monster1->CheckIfMonsterTouchPlayer(Player.pos.x, Player.pos.y, Player.pos.z))
				ifPlayerAlive = false;

			if (ifInstantPlayerKill && ifPlayerAlive)
				monsterPos = Monster1->MoveTowardsPlayer(Player.pos.x, Player.pos.y, Player.pos.z, 9);
		}
		else
			monsterbreath->setAllSoundsPaused(true);

#pragma endregion
	}
}

void Scene::Render(void)
{
	
#pragma region CameraView

	gluLookAt(
		Player.pos.x + Player.cam.x, Player.pos.y + Player.cam.y, Player.pos.z + Player.cam.z,
		Player.pos.x + Player.cam.x + Player.dir.x, Player.pos.y + Player.cam.y + Player.dir.y, Player.pos.z + Player.cam.z + Player.dir.z,
		visionx, visiony, visionz
		);
	
#pragma endregion

	if (Map == "Hospital")
	{

#pragma region Light

		GLfloat light1_ambient[] = { 255 / 255,255 / 255,0.7,1.0 };
		GLfloat light1_diffuse[] = { 255 / 255,255 / 255,0.7,1.0 };
		GLfloat light1_specular[] = { 0,0,0,1 };
		GLfloat light1_position[] = { 5,0.8,-1.5,1 };


		glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light1_position);

		if (ifCameraOn)
		{
			float gl_amb[] = { 0.6f, 0.8f, 0.6f, 1.0f };
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);
		}
		else
		{
			float gl_amb[] = { 0.5,0.5,0.5,1 };
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);
		}
		

		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);

		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

		if (ifGameStart && Player.pos.x < 3)
		{
			ifGameStart = false;
			Items.Play2D("Resources/Sounds/Bulb_smash.ogg", 1 * (sound / 100), false);
			glDisable(GL_LIGHT0);
			glutTimerFunc((rand() % 40000) + 20000, ReleaseMonster, 0);
		}

#pragma endregion

#pragma region Skydome

		glDisable(GL_FOG);

		Skydome->Position = Player.pos;
		Skydome->Render();

		glEnable(GL_FOG);

#pragma endregion

#pragma region Objects		
		
		for (int i = 0; i < Objects->size(); ++i)
			Objects->at(i)->Render();
		for (int i = 0; i < ceiling->size(); ++i)
			ceiling->at(i)->Render();

		Monster1->Render(monsterPos.x,monsterPos.y,monsterPos.z, Player.pos.x,Player.pos.y,Player.pos.z);
		Bed1->Render(4, 0, -2.7, 0, 0, 0, 0);
		ExitDoor->Render(exitPos.x, exitPos.y, exitPos.z, 0, 0, 0, 0);
		Bulb->Render(5, 1, -1.5, 0, 0, 0, 0);
		Toliet01->Render(5.85, 0, -2.4, -90, 0, 1, 0);
		if (gameState==Game && !ifCameraOn)
			Cam->Render(Player.pos.x, Player.pos.y, Player.pos.z, Player.dir.x, Player.dir.y, Player.dir.z);
		if (ifRenderBattery1)
			Battery1->Render(4.3, 0.32, -2.6, 0, 0, 0, 0);
		if (ifRenderBattery2)
			Battery2->Render(0, 0, 3, 0, 0, 0, 0);
		if (ifRenderKey1)
			Key1->Render(key1Pos.x,key1Pos.y,key1Pos.z, 45, 0, 1, 0);

#pragma endregion
	}
	else if (Map == "Outside")
	{

	}
}

void Scene::PauseAllSounds()
{
	Soundtrack->Stop('P');
	Steps.Stop('P');
	Running.Stop('P');
	Jumping.Stop('P');
}

void Scene::ResumeAllSounds()
{
	Soundtrack->Resume();
	Steps.Resume();;
	Running.Resume();
	Jumping.Resume();
}

void ResumeMonsterScare(int)
{
		ifPlayMonsterJumpscare = true;
}

void MakeRandomness(int n)
{
	int c, first = 0, second = 1, next;

	for (c = 0; c < n; c++)
	{
		if (c <= 1)
			next = c;
		else
		{
			next = first + second;
			first = second;
			second = next;
		}
		
	}
}

void StartDeathCountdown()
{
	if (ifPlayerAlive)
	{
		if (deathCountdown <= 350)
			deathCountdown++;
		else
		{
			ifInstantPlayerKill = true;
			if (ifPlayInstantDeathSound)
			{
				ifPlayInstantDeathSound = false;
				MonsterSound.Play2D("Resources/Sounds/InstantDeath.ogg", 1 * (sound / 100), false);
			}
		}
	}
}

void FinishTired(int)
{
	ifTiredFinished = true;
}

void ReleaseMonster(int)
{
	ifReleaseMonster = true;
}
#include "Stdafx.h"

bool ifjump = false;
bool iffall = false;
bool ifcrouch = false;
bool playingrunning = true;
bool playingsteps = true;
bool playingcrouch = true;

float visionspeedx = 1, visionspeedz = 1;
float visionstate = 0.013;
float visionspeed = 12;
float tempheigh;
float visionx = 0.0f, visiony = 1.0f, visionz = 0.0f;//wspó³rzêdne pionu

int AngleofCamera = 0;
int jumpCounter = 0;

irrklang::ISoundEngine* soundtrack;
Audio *Soundtrack = new Audio(soundtrack);

irrklang::ISoundEngine* steps;
Audio Steps(steps);

irrklang::ISoundEngine* running;
Audio Running(running);

irrklang::ISoundEngine* jump;
Audio Jumping(jump);

irrklang::ISoundEngine* flashlight;
Audio Flashlight(flashlight);

CScene::CScene(void)
{
	DrawCollisions = false;
	DrawNormals = false;
	MarkCollision = false;

}


CScene::~CScene(void)
{
	if (Skydome != NULL)
		delete Skydome;

	if (Terrain != NULL)
		delete Terrain;
}


void CScene::Initialize(void) 
{
	
	#pragma region Settings
	glEnable(GL_LIGHT1);
	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { Player.pos.x, Player.pos.y - 0.3, Player.pos.z, 1 };
	GLfloat spot_direction[] = { Player.dir.x, Player.dir.y, Player.dir.z };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.3);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10);
		

		glEnable(GL_LIGHT0);

		glEnable(GL_FOG);
		float gl_fogcolor[] = { 0.875f, 0.957f, 1.0f, 1.0f };
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, gl_fogcolor);
		glFogf(GL_FOG_START, 2.0f);
		glFogf(GL_FOG_END, 18.0f);

		Player.pos.x = 0.0f;
		Player.pos.y = 0.3f;
		Player.pos.z = 0.0f;

		Player.dir.x = 0.0f;
		Player.dir.y = 0.0f;
		Player.dir.z = -1.0f;

		Player.speed = .45f;

	#pragma endregion

	#pragma region Scene
	
		Skydome = new CSkydome();
		Skydome->Initialize();

		
		Terrain = new CTerrain();
		Terrain->Initialize();

		
		Objects = new vector<CSceneObject *>();

		
		vec3 walls[][4] =
		{
			{ vec3( 3.0f,  0.0f, -3.0f), vec3( 3.0f,  1.0f, -3.0f), vec3( 0.0f,  1.0f, -3.0f), vec3( 0.0f,  0.0f, -3.0f) },
			{ vec3(6.0f,  0.0f, -3.0f), vec3(6.0f,  1.0f, -3.0f), vec3(3.0f,  1.0f, -3.0f), vec3(3.0f,  0.0f, -3.0f) },
			{ vec3(6.0f,  0.0f, 0.0f), vec3(6.0f,  1.0f, 0.0f), vec3(6.0f,  1.0f, -3.0f), vec3(6.0f,  0.0f, -3.0f) },
			{ vec3(6.0f,  0.0f, 3.0f), vec3(6.0f,  1.0f, 3.0f), vec3(6.0f,  1.0f, 0.0f), vec3(6.0f,  0.0f, 0.0f) },
			{ vec3(6.0f,  0.0f, 3.0f), vec3(6.0f,  1.0f, 3.0f), vec3(6.0f,  1.0f, 0.0f), vec3(6.0f,  0.0f, 0.0f) }
		};
		
		
		int wallsCounter = sizeof(walls) / sizeof(walls[0]);

	
		for (int i = 0; i < 5; ++i)
		{
			CWall *w = new CWall(walls[i][0], walls[i][1], walls[i][2], walls[i][3]);
			sprintf(w->Name, "Wall %d", i); 
			w->Initialize();
			Objects->push_back(w); 
		}

	#pragma endregion
	
}


void CScene::Update(float sound,int gameState)
{
	if (gameState == 1)
	{
		
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

#pragma region Movement

		if (captureMouse)
		{
			Player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX) * 30;
			Player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY) * 30;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		}

		if ((GetKeyState(VK_LSHIFT) == -127 || GetKeyState(VK_LSHIFT) == -128) && !ifcrouch)
		{
			Player.SetPlayerRunningSpeed();
			visionstate = 0.03;
			visionspeed = 10;
		}
		else if (GetKeyState(VK_LCONTROL) == -127 || GetKeyState(VK_LCONTROL) == -128)
		{
			visionstate = 0.009;
			visionspeed = 17;
			Player.SetPlayerCrouchSpeed();
			ifcrouch = true;
		}
		else
		{
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

		if (free3DMovement)
			nextPlayerPos.y += Player.dir.y * Player.velM * .1f;

		nextPlayerPos.z += per.z * Player.velS * .1f;

		Player.dir.y = __max(-0.8, Player.dir.y);
		Player.dir.y = __min(0.9, Player.dir.y);

#pragma region Crouch

		if (ifcrouch)
			nextPlayerPos.y = __max(0.01f, nextPlayerPos.y);
		else
			nextPlayerPos.y = __max(0.3f, nextPlayerPos.y);

#pragma endregion

		Player.pos = CCollisionDetection::GetPositionAfterWorldCollisions(Player.pos, nextPlayerPos, Player, Objects);

		Player.velRX /= 1.2;
		Player.velRY /= 1.2;
		Player.velM /= 1.2;
		Player.velS /= 1.2;

#pragma endregion

#pragma region Objects update

		for (int i = 0; i < Objects->size(); ++i)
			Objects->at(i)->Update();
	}

		Terrain->Update();
		Skydome->Update();

	#pragma endregion

}


void CScene::Render(void)
{

	#pragma region Camera

		gluLookAt(
			Player.pos.x + Player.cam.x, Player.pos.y + Player.cam.y, Player.pos.z + Player.cam.z,
			Player.pos.x + Player.cam.x + Player.dir.x, Player.pos.y + Player.cam.y + Player.dir.y, Player.pos.z + Player.cam.z + Player.dir.z,
			visionx,visiony,visionz
		);

	#pragma endregion

	#pragma region Light
	
		float l0_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { -1.0f, .2f, 0.5f, 0.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	#pragma endregion

	#pragma region Skydome

		glDisable(GL_FOG);

		Skydome->Position = Player.pos;
		Skydome->Render();
		
		glEnable(GL_FOG);

	#pragma endregion

	#pragma region Terrain

		Terrain->Render();

	#pragma endregion

	#pragma region Objects

		
		for (int i = 0; i < Objects->size(); ++i) 
			Objects->at(i)->Render();
		

	#pragma endregion

}

void CScene::PauseAllSounds()
{
	Soundtrack->Stop('P');
	Steps.Stop('P');
	Running.Stop('P');
	Jumping.Stop('P');
}

void CScene::ResumeAllSounds()
{
	Soundtrack->Resume();
	Steps.Resume();;
	Running.Resume();
	Jumping.Resume();
}

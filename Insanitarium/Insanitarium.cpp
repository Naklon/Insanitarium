#include "stdafx.h"

#pragma region Globals

	int mouseX = 0;
	int mouseY = 0;
	int gameState;
	int keysCollected = 0;
	int Sizex, Sizey;//Rozmiar okna (Jeœli w³¹czono tryb okienkowy)
	int viewPortWidth;
	int viewPortHeight;

	bool captureMouse = true;
	bool free3DMovement = false;
	
	float sound, music;//////////////////G³oœnoœæ muzyki i dŸwiêku
	float mouseSensitivity;
	float FOV = 60;

	Scene *Scene1;
	
	bool ifLogo = true;
	bool keystate[255];
	bool Window;////W³¹czenie lub wy³¹czenie trybu okienkowego
	bool firstLaunch;
	bool ifSetMouse = true;
	bool ifQPressed;
	bool ifGameLoaded = false;
	bool ifPlayerAlive = true;
	bool ifLMBPressed = false;

	irrklang::ISoundEngine* menuClick;
	Audio MenuClick(menuClick);

	bool ifCameraOn = false;

	std::vector<Object*> Interactable;

	Object *Batteries;
	TextBox *LoadingScreen;
	TextBox *LoadingScreenWorldGen;
	std::string Map;
	
#pragma endregion

int main(int argc, char* argv[])
{
	FreeConsole();
	glutInit(&argc, argv);
	
	LoadSettings();

	srand(time(NULL));

	if (firstLaunch)
	{
		Sizex = glutGet(GLUT_SCREEN_WIDTH);
		Sizey = glutGet(GLUT_SCREEN_HEIGHT);
		firstLaunch = false;
	}
	
	if (Window)
	{
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(Sizex, Sizey);
	}
	
	glutInitWindowSize(Sizex, Sizey);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	
	glEnable(GL_BLEND);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glutCreateWindow("Insanitarium");
	
	glutMouseFunc(OnMousePress);
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);

	if (!Window)
		glutFullScreen();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_NORMALIZE);



	
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);

	gameState = Menu;

	Map = "Hospital";
	LoadingScreen = new TextBox(0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0, "Resources/LoadingScreen.bmp");
	Soundtrack->Play2D("Resources/Music/menu_soundtrack.ogg", 1 * music / 100, true);
	LoadingScreen->Render(0.7, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);

	glutMainLoop();
	return 0;
}

#pragma region Settings

void LoadGame()
{
	std::vector<Object*> objList;
	std::vector<TextBox*> texList;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glEnd();

	LoadingScreen->Render(0.7, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);
	
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

#pragma region Objects

	Cam = new Camera("Camera");
	//Cam = new Camera();

	Monster1 = new Monster("Creature");
	
	Battery1 = new Object("Battery", "Bateria1", true);
	Battery2 = new Object("Battery", "Bateria2", true);
	Bed1 = new Object("Bed01", "Lozko", false);
	Toliet01 = new Object("Toilet01", "Toaleta", false);
	Key1 = new Object("Key", "Klucz1", true);
	Key2 = new Object("Key", "Klucz2", true);
	ExitDoor = new Object("ExitDoor", "Drzwi Wyjsciowe", false);
	Bulb = new Object("Bulb", "¯arówka", false);
	
	objList.push_back(Battery1);
	objList.push_back(Cam);
	objList.push_back(Battery2);
	objList.push_back(Monster1);
	objList.push_back(Bed1);
	objList.push_back(Toliet01);
	objList.push_back(Key1);
	objList.push_back(Key2);
	objList.push_back(ExitDoor);
	objList.push_back(Bulb);

#pragma endregion

#pragma region Textboxes

	Cam3 = new TextBox(0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0, "Resources/Cam3.bmp");
	Cam2 = new TextBox(0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0, "Resources/Cam2.bmp");
	Cam1 = new TextBox(0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0, "Resources/Cam1.bmp");
	Cam0 = new TextBox(0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0, "Resources/Cam0.bmp");

	BatteryCounter1 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/One.bmp");
	BatteryCounter2 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Two.bmp");
	BatteryCounter3 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Three.bmp");
	BatteryCounter4 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Four.bmp");
	BatteryCounter5 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Five.bmp");
	BatteryCounter6 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Six.bmp");
	BatteryCounter7 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Seven.bmp");
	BatteryCounter8 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Eight.bmp");
	BatteryCounter9 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.08, glutGet(GLUT_WINDOW_WIDTH)*0.04, glutGet(GLUT_WINDOW_HEIGHT)*0.12,
		glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.12, glutGet(GLUT_WINDOW_WIDTH)*0.07, glutGet(GLUT_WINDOW_HEIGHT)*0.08, "Resources/Nine.bmp");

	PickMessage = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
		glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, "Resources/PickMessage.bmp");
	BatteryPick = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
		glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55, "Resources/BatteryPick.bmp");
	KeyPick = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
		glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55,"Resources/KeyPick.bmp");

	PickMessageCam = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.35, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
		glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, "Resources/PickMessageCam.bmp");
	BatteryPickCam = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
		glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55, "Resources/BatteryPickCam.bmp");
	KeyPickCam = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.55, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.58,
		glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.58, glutGet(GLUT_WINDOW_WIDTH)*0.626, glutGet(GLUT_WINDOW_HEIGHT)*0.55, "Resources/KeyPickCam.bmp");
	
	DeadScreen = new TextBox(0,0,0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH),0,"Resources/DeadScreen.bmp");
	DeadScreenMenu = new TextBox(0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0, "Resources/DeadScreenMenu.bmp");

	LoadingScreenWorldGen = new TextBox(0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0,"Resources/LoadingScreenWorldGen.bmp");

	texList.push_back(LoadingScreenWorldGen);
	texList.push_back(Cam3);
	texList.push_back(Cam2);
	texList.push_back(Cam1);
	texList.push_back(Cam0);
	texList.push_back(BatteryCounter1);
	texList.push_back(BatteryCounter2);
	texList.push_back(BatteryCounter3);
	texList.push_back(BatteryCounter4);
	texList.push_back(BatteryCounter5);
	texList.push_back(BatteryCounter6);
	texList.push_back(BatteryCounter7);
	texList.push_back(BatteryCounter8);
	texList.push_back(BatteryCounter9);
	texList.push_back(PickMessage);
	texList.push_back(BatteryPick);
	texList.push_back(PickMessageCam);
	texList.push_back(BatteryPickCam);
	texList.push_back(DeadScreen);
	texList.push_back(DeadScreenMenu);
	texList.push_back(KeyPick);
	texList.push_back(KeyPickCam);

#pragma endregion

	int loadingLength = objList.size()+texList.size();
	float barLength = (glutGet(GLUT_WINDOW_WIDTH)*0.7 - glutGet(GLUT_WINDOW_WIDTH)*0.3);
	float oneElementLength = barLength / loadingLength;

	for (int i = 0;i < objList.size();i++)
	{
		objList[i]->Load();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_CULL_FACE);
		
		glBegin(GL_QUADS);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3+(i+1)*oneElementLength, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3 + (i + 1)*oneElementLength, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glEnd();

		LoadingScreen->Render(0.7, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);

		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glFlush();
		glutSwapBuffers();
		glutPostRedisplay();
	}

	for (int i = 0; i < texList.size(); i++)
	{
		texList[i]->Load();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_CULL_FACE);

		glBegin(GL_QUADS);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3 + (objList.size()+1 + i)*oneElementLength, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3 + (objList.size()+1 + i)*oneElementLength, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
		glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
		glEnd();

		LoadingScreen->Render(0.7, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);

		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		glFlush();
		glutSwapBuffers();
		glutPostRedisplay();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glBegin(GL_QUADS);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3 + barLength, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3 + barLength, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.3, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glEnd();

	LoadingScreenWorldGen->Render(0.7, 0, 0, 0, glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), glutGet(GLUT_WINDOW_WIDTH), 0);

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();


	Scene1 = new Scene();
	Scene1->Initialize();


}

void LoadSettings()
{
	std::ifstream settings("Settings/settings.txt");
	std::string option = "", mode = "";
	while (!settings.eof())
	{
		settings >> option;
		if (option == "Window")
		{
			settings >> mode;
			switch (mode[0])
			{
			case 't':
				Window = true;
				break;
			case 'f':
				Window = false;
				break;
			}
		}
		else if (option == "Sensitivity")
		{
			settings >> mode;
			std::istringstream iss(mode);
			iss >> mouseSensitivity;
			mouseSensitivity = (mouseSensitivity / 100)*0.001;
		}
		else if (option == "Sizex")
		{
			settings >> mode;
			std::istringstream iss(mode);
			iss >> Sizex;
		}
		else if (option == "Sizey")
		{
			settings >> mode;
			std::istringstream iss(mode);
			iss >> Sizey;
		}
		else if (option == "Sound")
		{
			settings >> mode;
			std::istringstream iss(mode);
			iss >> sound;
		}
		else if (option == "Music")
		{
			settings >> mode;
			std::istringstream iss(mode);
			iss >> music;
		}
		else if (option == "FirstLaunch")
		{
			settings >> mode;
			std::istringstream iss(mode);
			switch (mode[0])
			{
			case 't':
				firstLaunch = true;
				break;
			case 'f':
				firstLaunch = false;
				break;
			}
		}
		if (Sizex == 1920 && Sizey == 1080)
		{
			res1 = false;
			res2 = true;
		}
		else
		{
			res2 = false;
			res1 = true;
		}
	}
	settings.close();
}

void SaveSettings()
{
	if (res1)
	{
		Sizex = 1280;
		Sizey = 720;
	}
	else
	{
		Sizex = 1920;
		Sizey = 1080;
	}
	std::string str = "";

	std::ostringstream ss[6];
	std::ofstream settings("Settings/settings.txt");
	if (Window)
		settings << "Window true" << std::endl;
	else
		settings << "Window false" << std::endl;

	int i = 0;

	ss[i] << mouseSensitivity * 100000;
	str = ss[i].str();
	settings << "Sensitivity " + str << std::endl;
	i++;
	ss[i] << Sizex;
	str = ss[i].str();
	settings << "Sizex " + str << std::endl;
	i++;
	ss[i] << Sizey;
	str = ss[i].str();
	settings << "Sizey " + str << std::endl;
	i++;
	ss[i] << sound;
	str = ss[i].str();
	settings << "Sound " + str << std::endl;
	i++;
	ss[i] << music;
	str = ss[i].str();
	settings << "Music " + str << std::endl;
	settings << "FirstLaunch false";

	settings.close();
}

#pragma endregion

#pragma region Controls

	void OnKeyPress(unsigned char key, int x, int y) 
	{
		if (!keystate[key])
		{
			if (key == 23 || key == 19 || key == 1 || key == 4)//Naprawia problem chodzenia z CTRL 
				keystate[key + 96] = true;

			if (key == 65 || key == 68 || key == 83 || key == 87)//To co wy¿ej dla SHIFT
				keystate[key + 32] = true;

			keystate[key] = true;
			OnKeyDown(key, x, y);
		}
	}

	void OnKeyDown(unsigned char key, int x, int y) 
	{
		if (ifPlayerAlive && key == 27) 
		{
			if (gameState == Game)
			{
				gameState = GameMenu;
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
				Scene1->PauseAllSounds();
			}
			else if (gameState == GameMenu)
			{
				gameState = Game;
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
				Scene1->ResumeAllSounds();
			}
		}
		if (ifPlayerAlive && (key == 101 || key==69||key==5) && gameState==Game)
		{
			if (!ifCameraOn)
				Cam->PickUpCamera();
			else
			{
				Cam->PutCameraDown();
			}

		}
		if (ifPlayerAlive && (key == 114 || key == 82 || key==18) && gameState == Game)
			Cam->ChangeCameraBattery();
		if (key == 113 || key == 81 || key == 17)
			ifQPressed = true;
	}

	void OnKeyUp(unsigned char key, int x, int y)
	{
		if (key == 23 || key == 19 || key == 1 || key == 4)
			keystate[key + 96] = false;

		if (key == 65 || key == 68 || key == 83 || key == 87)
			keystate[key + 32] = false;

		if (key == 97 || key == 100 || key == 114 || key == 119)
			keystate[key - 32] = false;

		if (key == 113 || key==81 || key==17)
			ifQPressed = false;

		keystate[key] = false;
	}

	void OnMouseMove(int x, int y)
	{
		mouseX = x;
		mouseY = y;
	}
	void OnMousePress(int button, int state, int x, int y)
	{
		switch (gameState)
		{
		case Game:
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
				ifLMBPressed = true;
			else
				ifLMBPressed = false;
			if ((button == 3) || (button == 4)) //Kó³ko myszy
			{
				if (ifCameraOn)
				{
					if (state != GLUT_UP)
					{
						if (button == 3)
						{
							if (FOV >= 40)
							{
								FOV -= 5;
								if(!MenuClick.ifSoundCurrentlyPlayed("Resources/Cam_ZoomIn.ogg"))
								{
									MenuClick.Stop('S');
									MenuClick.Play2D("Resources/Sounds/Cam_ZoomIn.ogg", 0.2*(sound / 100), false);
								}
							}
							
						}
						else
						{
							if (FOV < 60)
							{
								FOV += 5;
								if (!MenuClick.ifSoundCurrentlyPlayed("Resources/Cam_ZoomOut.ogg"))
								{
									MenuClick.Stop('S');
									MenuClick.Play2D("Resources/Sounds/Cam_ZoomOut.ogg", 0.2*(sound / 100), false);
								}
							}
						}
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();
						glViewport(0, 0, viewPortWidth, viewPortHeight);
						gluPerspective(FOV, (float)Sizex / Sizey, .01f, 100.0f);
					}
				}
			}
			break;
		case GameMenu:
			if ((button == GLUT_LEFT_BUTTON) && (x > (glutGet(GLUT_WINDOW_WIDTH)*0.43) && (x<glutGet(GLUT_WINDOW_WIDTH)*0.57) && (y>glutGet(GLUT_WINDOW_HEIGHT)*0.39) && (y < glutGet(GLUT_WINDOW_HEIGHT)*0.46)))
			{
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				gameState = Game;
				Scene1->ResumeAllSounds();
			}
			else if ((button == GLUT_LEFT_BUTTON) && (x > (glutGet(GLUT_WINDOW_WIDTH)*0.43) && (x<glutGet(GLUT_WINDOW_WIDTH)*0.57) && (y>glutGet(GLUT_WINDOW_HEIGHT)*0.52) && (y < glutGet(GLUT_WINDOW_HEIGHT)*0.59)))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				glutLeaveMainLoop();
			}
			break;
		case Menu:
			if ((button == GLUT_LEFT_BUTTON) && (x > glutGet(GLUT_WINDOW_WIDTH)*0.05) && (x<glutGet(GLUT_WINDOW_WIDTH)*0.2) && (y>glutGet(GLUT_WINDOW_HEIGHT)*0.6) && (y < glutGet(GLUT_WINDOW_HEIGHT)*0.65))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				MainMenu::FadeMainMenu();
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (x > glutGet(GLUT_WINDOW_WIDTH)*0.05) && (x<glutGet(GLUT_WINDOW_WIDTH)*0.2) && (y>glutGet(GLUT_WINDOW_HEIGHT)*0.7) && (y < glutGet(GLUT_WINDOW_HEIGHT)*0.75))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				gameState = Options;
			}
			else if ((button == GLUT_LEFT_BUTTON) && (x > glutGet(GLUT_WINDOW_WIDTH)*0.05) && (x<glutGet(GLUT_WINDOW_WIDTH)*0.2) && (y>glutGet(GLUT_WINDOW_HEIGHT)*0.8) && (y < glutGet(GLUT_WINDOW_HEIGHT)*0.85))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				glutLeaveMainLoop();
			}
			break;
		case Options:
			if ((button == GLUT_LEFT_BUTTON) && (mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.25) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.4) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.83) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.88))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				SaveSettings();
				gameState = Menu;
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.6) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.75) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.83) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.88))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				LoadSettings();
				
				if (Window)
					glutLeaveFullScreen();
				else
					glutFullScreen();
				
				Soundtrack->SetVolume(music / 100);
				gameState = Menu;
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (MainMenu::IfMouseInTriangle(mousePoint, musicLeft1, musicLeft2, musicLeft3)))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				if (music > 0)
					music -= 10;
				Soundtrack->SetVolume(1 * music / 100);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (MainMenu::IfMouseInTriangle(mousePoint, musicRight1, musicRight2, musicRight3)))
			{
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				if (music < 100)
					music += 10;
				Soundtrack->SetVolume(1 * music / 100);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (MainMenu::IfMouseInTriangle(mousePoint, soundLeft1, soundLeft2, soundLeft3)))
			{
				if (sound > 0)
					sound -= 10;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (MainMenu::IfMouseInTriangle(mousePoint, soundRight1, soundRight2, soundRight3)))
			{
				if (sound < 100)
					sound += 10;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (MainMenu::IfMouseInTriangle(mousePoint, mouseLeft1, mouseLeft2, mouseLeft3)))
			{
				if (mouseSensitivity * 100000>=10)
					mouseSensitivity -= 0.0001;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && (MainMenu::IfMouseInTriangle(mousePoint, mouseRight1, mouseRight2, mouseRight3)))
			{
				if (mouseSensitivity * 100000 < 100)
					mouseSensitivity += 0.0001;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && MainMenu::IfMouseInCircle(mousePoint, resolution1, radius) && Window)
			{
				res1 = true;
				res2 = false;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && MainMenu::IfMouseInCircle(mousePoint, resolution2, radius) && Window)
			{
				res2 = true;
				res1 = false;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
			}
			else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.58 && mouseX< glutGet(GLUT_WINDOW_WIDTH)*0.68 && mouseY> glutGet(GLUT_WINDOW_HEIGHT)*0.7 && mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.75)
			{
				Window = true;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				glutLeaveFullScreen();
			}
			if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.7 && mouseX< glutGet(GLUT_WINDOW_WIDTH)*0.8 && mouseY> glutGet(GLUT_WINDOW_HEIGHT)*0.7 && mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.75)
			{
				Window = false;
				MenuClick.Play2D("Resources/Sounds/menu_click.ogg", 0.2 * sound / 100, false);
				glutFullScreen();
			}
			break;
		}
	}

#pragma endregion

void OnTimer(int) 
{
	glutTimerFunc(17, OnTimer, 0);

	if (res2)
	{
		Sizex = 1980;
		Sizey = 1020;
	}
	else
	{
		Sizex = 1280;
		Sizey = 720;
	}

	
	if(gameState==1)
	Scene1->Update(sound,gameState);
}

void OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (!ifGameLoaded)
	{
		LoadGame();
		ifGameLoaded = true;
	}

	
	Scene1->Render();	
	
	switch (gameState)
	{
	case Game:
		if (ifPlayerAlive)
		{
			HUD::DrawCrossHair();
			HUD::ShowPickMessage(ObjToPick);
		}
		if (ifCameraOn)
			HUD::DrawCameraView();
		if (!ifPlayerAlive)
			Player.KillPlayer();
		break;
	case GameMenu:
		MainMenu::DrawMenu();
		break;
	case Menu:
		MainMenu::DrawMainMenu();
		break;
	case Options:
		MainMenu::DrawOptions();
		break;
	}

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OnReshape(int width, int height) 
{
	if (glutGet(GLUT_WINDOW_WIDTH)<1300)
	{
		res1 = true;
		res2 = false;
	}
	else
	{
		res2 = true;
		res1 = false;
	}
	viewPortHeight = height;
	viewPortWidth = width;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)Sizex /Sizey, .01f, 100.0f);
}
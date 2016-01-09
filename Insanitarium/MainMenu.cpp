#include "stdafx.h"
#include "MainMenu.h"

float radius;
float alphamenu = 0.8;

bool iffade = false;
bool ifSound1 = true;
bool ifSound2 = true;
bool ifSoundMain1 = true;
bool ifSoundMain2 = true;
bool ifSoundMain3 = true;
bool ifSoundOptions1 = true;
bool ifSoundOptions2 = true;
bool ifSoundOptions3 = true;
bool ifSoundOptions4 = true;
bool ifSoundOptions5 = true;
bool ifSoundOptions6 = true;
bool ifSoundOptions7 = true;
bool ifSoundOptions8 = true;
bool ifSoundOptions9 = true;
bool ifSoundOptions10 = true;
bool ifSoundOptions11 = true;
bool ifSoundOptions12 = true;
bool res1;
bool res2;
bool loaded = false;
bool loadedOptions = false;

int mouseRightColor;
int mouseLeftColor;
int musicLeftColor;
int musicRightColor;
int soundLeftColor;
int soundRightColor;
int res1Color;
int res2Color;
int musicOption;
int soundOption;
int mouseOption;

irrklang::ISoundEngine* menuelement;
Audio MenuElement(menuelement);

TextBox* Insanitarium = new TextBox();

TextBox* Play = new TextBox();

TextBox* Option = new TextBox();

TextBox* Option1 = new TextBox();

TextBox* Exit = new TextBox();

TextBox* Save=new TextBox();

TextBox* Cancel=new TextBox();

TextBox* MusicVol = new TextBox();

TextBox* SoundVol = new TextBox();

TextBox* MouseSen = new TextBox();

TextBox* WindowedYes = new TextBox();

TextBox* WindowedNo = new TextBox();

TextBox* Windowed = new TextBox();

TextBox* Resolution = new TextBox();

TextBox* ResHD = new TextBox();

TextBox* Res1280x720 = new TextBox();

POINT mousePoint;

POINT musicLeft1;
POINT musicLeft2;
POINT musicLeft3;

POINT musicRight1;
POINT musicRight2;
POINT musicRight3;

POINT soundLeft1;
POINT soundLeft2;
POINT soundLeft3;

POINT soundRight1;
POINT soundRight2;
POINT soundRight3;

POINT mouseLeft1;
POINT mouseLeft2;
POINT mouseLeft3;

POINT mouseRight1;
POINT mouseRight2;
POINT mouseRight3;

POINT resolution1;
POINT resolution2;

MainMenu::MainMenu()
{
}

void MainMenu::DrawMenu()
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

	TextBox ResumeButton(glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.39, glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.46,
		glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.46, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.39, "Resources\\Resume.bmp");

	TextBox ExitButton(glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.52, glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.59,
		glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.59, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.52, "Resources\\Exit.bmp");

		if (mouseX > (glutGet(GLUT_WINDOW_WIDTH)*0.43) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.57) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.39) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.46))
		{
			ResumeButton.ChangeTexture("Resources/Resume_choice.bmp");
			if (ifSound1)
			{
				MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound/100, false);
				ifSound1 = false;
			}
		}
		else
			ifSound1 = true;

		if (mouseX > (glutGet(GLUT_WINDOW_WIDTH)*0.43) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.57) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.52) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.59))
		{
			ExitButton.ChangeTexture("Resources/Exit_choice.bmp");
			if (ifSound2)
			{
				MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound/100, false);
				ifSound2 = false;
			}
		}
		else
			ifSound2 = true;

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	glClear(GL_DEPTH_BUFFER_BIT);

	////////////////////////////Rysowanie elementów menu

	ResumeButton.Render(0.8, glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.39, glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.46,
		glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.46, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.39);
	ExitButton.Render(0.8, glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.52, glutGet(GLUT_WINDOW_WIDTH)*0.43, glutGet(GLUT_WINDOW_HEIGHT)*0.59,
		glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.59, glutGet(GLUT_WINDOW_WIDTH)*0.57, glutGet(GLUT_WINDOW_HEIGHT)*0.52);

	/////////////////////////////Czarny pasek z elementami menu
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 0.8);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.35);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.65);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.65);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.35);
	glEnd();
	

	////////////////////////////Rysowanie t³a gry
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void MainMenu::DrawMainMenu()
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

	if (!loaded) //Wczytywanie obiektów tekstu
	{
		Insanitarium = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.02, glutGet(GLUT_WINDOW_HEIGHT)*0.07, glutGet(GLUT_WINDOW_WIDTH)*0.02, glutGet(GLUT_WINDOW_HEIGHT)*0.37,
			glutGet(GLUT_WINDOW_WIDTH)*0.98, glutGet(GLUT_WINDOW_HEIGHT)*0.37, glutGet(GLUT_WINDOW_WIDTH)*0.98, glutGet(GLUT_WINDOW_HEIGHT)*0.07, "Resources/Logo.bmp");

		Play = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.6, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.65,
			glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.65, glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.6, "Resources/Play.bmp");

		Option = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
			glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.7, "Resources/Options.bmp");

		Exit = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.8, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.85,
			glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.85, glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.8, "Resources/ExitMain.bmp");
		loaded = true;
	}

#pragma region MousePointing

	if ((mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.05) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.2) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.6) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.65))
	{
		Play->ChangeTexture("Resources\\Play_choice.bmp");
		if (ifSoundMain1)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundMain1 = false;
		}
	}
	else
	{
		ifSoundMain1 = true;
		Play->ChangeTexture("Resources\\Play.bmp");
	}

	if ((mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.05) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.2) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.7) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.75))
	{
		Option->ChangeTexture("Resources\\Options_choice.bmp");
		if (ifSoundMain2)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundMain2 = false;
		}
	}
	else
	{
		ifSoundMain2 = true;
		Option->ChangeTexture("Resources\\Options.bmp");
	}

	if ((mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.05) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.2) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.8) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.85))
	{
		Exit->ChangeTexture("Resources\\ExitMain_choice.bmp");
		if (ifSoundMain3)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundMain3 = false;
		}
	}
	else
	{
		ifSoundMain3 = true;
		Exit->ChangeTexture("Resources\\ExitMain.bmp");
	}

#pragma endregion

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

	glClear(GL_DEPTH_BUFFER_BIT);

	Play->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.6, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.65,
		glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.65, glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.6);

	Option->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
		glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.7);

	Exit->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.8, glutGet(GLUT_WINDOW_WIDTH)*0.05, glutGet(GLUT_WINDOW_HEIGHT)*0.85,
		glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.85, glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.8);

	Insanitarium->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.02, glutGet(GLUT_WINDOW_HEIGHT)*0.03, glutGet(GLUT_WINDOW_WIDTH)*0.02, glutGet(GLUT_WINDOW_HEIGHT)*0.33,
		glutGet(GLUT_WINDOW_WIDTH)*0.98, glutGet(GLUT_WINDOW_HEIGHT)*0.33, glutGet(GLUT_WINDOW_WIDTH)*0.98, glutGet(GLUT_WINDOW_HEIGHT)*0.03);

	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, alphamenu);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.03);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.33);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.33);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.03);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, alphamenu);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.6);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.65);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.65);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.6);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, alphamenu);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.75);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.7);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, alphamenu);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.8);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.85);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.85);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.2, glutGet(GLUT_WINDOW_HEIGHT)*0.8);
	glEnd();
	if (iffade)
	{
		alphamenu -= 0.01;
		glutSetCursor(GLUT_CURSOR_NONE);
		if ((1 * music / 100) > alphamenu);
		Soundtrack->SetVolume(alphamenu);
	}
	if (alphamenu <= 0)
	{
		iffade = false;
		glutSetCursor(GLUT_CURSOR_NONE);
		Soundtrack->Stop('S');
		Soundtrack->Play2D("Resources/Music/ambience_02.mp3", 1 * music / 100, true);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		gameState = 1;
	}
}

void MainMenu::FadeMainMenu()
{
	iffade = true;
}

void MainMenu::DrawOptions()
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

	musicOption = music / 10;
	soundOption = sound / 10;
	mouseOption = mouseSensitivity * 10000;

#pragma region Points

	mousePoint.x = mouseX;
	mousePoint.y = mouseY;

	musicLeft1.x = glutGet(GLUT_WINDOW_WIDTH)*0.55;
	musicLeft1.y = glutGet(GLUT_WINDOW_HEIGHT)*0.5;

	musicLeft2.x = glutGet(GLUT_WINDOW_WIDTH)*0.58;
	musicLeft2.y = glutGet(GLUT_WINDOW_HEIGHT)*0.52;

	musicLeft3.x = glutGet(GLUT_WINDOW_WIDTH)*0.58;
	musicLeft3.y = glutGet(GLUT_WINDOW_HEIGHT)*0.48;

	musicRight1.x = glutGet(GLUT_WINDOW_WIDTH)*0.8;
	musicRight1.y = glutGet(GLUT_WINDOW_HEIGHT)*0.52;

	musicRight2.x = glutGet(GLUT_WINDOW_WIDTH)*0.8;
	musicRight2.y = glutGet(GLUT_WINDOW_HEIGHT)*0.48;

	musicRight3.x = glutGet(GLUT_WINDOW_WIDTH)*0.83;
	musicRight3.y = glutGet(GLUT_WINDOW_HEIGHT)*0.5;

	soundLeft1.x = glutGet(GLUT_WINDOW_WIDTH)*0.55;
	soundLeft1.y = glutGet(GLUT_WINDOW_HEIGHT)*0.57;

	soundLeft2.x = glutGet(GLUT_WINDOW_WIDTH)*0.58;
	soundLeft2.y = glutGet(GLUT_WINDOW_HEIGHT)*0.59;

	soundLeft3.x = glutGet(GLUT_WINDOW_WIDTH)*0.58;
	soundLeft3.y = glutGet(GLUT_WINDOW_HEIGHT)*0.55;

	soundRight1.x = glutGet(GLUT_WINDOW_WIDTH)*0.8;
	soundRight1.y = glutGet(GLUT_WINDOW_HEIGHT)*0.59;

	soundRight2.x = glutGet(GLUT_WINDOW_WIDTH)*0.8;
	soundRight2.y = glutGet(GLUT_WINDOW_HEIGHT)*0.55;

	soundRight3.x = glutGet(GLUT_WINDOW_WIDTH)*0.83;
	soundRight3.y = glutGet(GLUT_WINDOW_HEIGHT)*0.57;

	mouseLeft1.x = glutGet(GLUT_WINDOW_WIDTH)*0.55;
	mouseLeft1.y = glutGet(GLUT_WINDOW_HEIGHT) * 0.64;

	mouseLeft2.x = glutGet(GLUT_WINDOW_WIDTH)*0.58;
	mouseLeft2.y = glutGet(GLUT_WINDOW_HEIGHT)*0.66;

	mouseLeft3.x = glutGet(GLUT_WINDOW_WIDTH)*0.58;
	mouseLeft3.y = glutGet(GLUT_WINDOW_HEIGHT)*0.62;

	mouseRight1.x = glutGet(GLUT_WINDOW_WIDTH)*0.8;
	mouseRight1.y = glutGet(GLUT_WINDOW_HEIGHT)*0.66;

	mouseRight2.x = glutGet(GLUT_WINDOW_WIDTH)*0.8;
	mouseRight2.y = glutGet(GLUT_WINDOW_HEIGHT)*0.62;

	mouseRight3.x = glutGet(GLUT_WINDOW_WIDTH)*0.83;
	mouseRight3.y = glutGet(GLUT_WINDOW_HEIGHT)*0.64;

	resolution1.x = glutGet(GLUT_WINDOW_WIDTH)*0.6;
	resolution1.y = glutGet(GLUT_WINDOW_HEIGHT)*0.77;

	resolution2.x = glutGet(GLUT_WINDOW_WIDTH)*0.78;
	resolution2.y = glutGet(GLUT_WINDOW_HEIGHT)*0.77;
#pragma endregion

	if (!loadedOptions)
	{
		Save = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.25, glutGet(GLUT_WINDOW_HEIGHT)*0.83, glutGet(GLUT_WINDOW_WIDTH)*0.25, glutGet(GLUT_WINDOW_HEIGHT)*0.88,
			glutGet(GLUT_WINDOW_WIDTH)*0.4, glutGet(GLUT_WINDOW_HEIGHT)*0.88, glutGet(GLUT_WINDOW_WIDTH)*0.4, glutGet(GLUT_WINDOW_HEIGHT)*0.83, "Resources/Save.bmp");

		Option1 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.425, glutGet(GLUT_WINDOW_HEIGHT)*0.37, glutGet(GLUT_WINDOW_WIDTH)*0.425, glutGet(GLUT_WINDOW_HEIGHT)*0.42,
			glutGet(GLUT_WINDOW_WIDTH)*0.575, glutGet(GLUT_WINDOW_HEIGHT)*0.42, glutGet(GLUT_WINDOW_WIDTH)*0.575, glutGet(GLUT_WINDOW_HEIGHT)*0.37, "Resources/Options.bmp");

		Cancel = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.6, glutGet(GLUT_WINDOW_HEIGHT)*0.83, glutGet(GLUT_WINDOW_WIDTH)*0.6, glutGet(GLUT_WINDOW_HEIGHT)*0.88,
			glutGet(GLUT_WINDOW_WIDTH)*0.75, glutGet(GLUT_WINDOW_HEIGHT)*0.88, glutGet(GLUT_WINDOW_WIDTH)*0.75, glutGet(GLUT_WINDOW_HEIGHT)*0.83, "Resources/Cancel.bmp");

		MusicVol = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.47, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.52,
			glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.52, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.47, "Resources/MusicVol.bmp");

		SoundVol = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.54, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.59,
			glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.59, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.54, "Resources/SoundVol.bmp");

		MouseSen = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.61, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.66,
			glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.66, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.61, "Resources/MouseSen.bmp");

		WindowedYes = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
			glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.7, "Resources/Yes.bmp");

		WindowedYes = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
			glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.7, "Resources/Yes.bmp");

		WindowedNo = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
			glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.7, "Resources/No.bmp");

		Windowed = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.68, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.73,
			glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.73, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.68, "Resources/Windowed.bmp");

		Resolution = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.74, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.79,
			glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.79, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.74, "Resources/Resolution.bmp");
		
		Res1280x720 = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.61, glutGet(GLUT_WINDOW_HEIGHT)*0.74, glutGet(GLUT_WINDOW_WIDTH)*0.61, glutGet(GLUT_WINDOW_HEIGHT)*0.78,
			glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.78, glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.74, "Resources/resHD.bmp");
		
		ResHD = new TextBox(glutGet(GLUT_WINDOW_WIDTH)*0.79, glutGet(GLUT_WINDOW_HEIGHT)*0.74, glutGet(GLUT_WINDOW_WIDTH)*0.79, glutGet(GLUT_WINDOW_HEIGHT)*0.8,
			glutGet(GLUT_WINDOW_WIDTH)*0.86, glutGet(GLUT_WINDOW_HEIGHT)*0.8, glutGet(GLUT_WINDOW_WIDTH)*0.86, glutGet(GLUT_WINDOW_HEIGHT)*0.74, "Resources/res1280x720.bmp");
		
		loadedOptions = true;
	}//£adowanie tekstów

#pragma region MousePointing

	if ((mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.25) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.4) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.83) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.88))
	{
		Save->ChangeTexture("Resources/Save_choice.bmp");
		if (ifSoundOptions1)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions1 = false;
		}
	}
	else
	{
		ifSoundOptions1 = true;
		Save->ChangeTexture("Resources/Save.bmp");
	}

	if ((mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.6) && (mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.75) && (mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.83) && (mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.88))
	{
		Cancel->ChangeTexture("Resources/Cancel_choice.bmp");
		if (ifSoundOptions2)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions2 = false;
		}
	}
	else
	{
		ifSoundOptions2 = true;
		Cancel->ChangeTexture("Resources/Cancel.bmp");
	}

#pragma endregion

	Save->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.25, glutGet(GLUT_WINDOW_HEIGHT)*0.83, glutGet(GLUT_WINDOW_WIDTH)*0.25, glutGet(GLUT_WINDOW_HEIGHT)*0.88,
		glutGet(GLUT_WINDOW_WIDTH)*0.4, glutGet(GLUT_WINDOW_HEIGHT)*0.88, glutGet(GLUT_WINDOW_WIDTH)*0.4, glutGet(GLUT_WINDOW_HEIGHT)*0.83);

	Option1->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.425, glutGet(GLUT_WINDOW_HEIGHT)*0.37, glutGet(GLUT_WINDOW_WIDTH)*0.425, glutGet(GLUT_WINDOW_HEIGHT)*0.42,
		glutGet(GLUT_WINDOW_WIDTH)*0.575, glutGet(GLUT_WINDOW_HEIGHT)*0.42, glutGet(GLUT_WINDOW_WIDTH)*0.575, glutGet(GLUT_WINDOW_HEIGHT)*0.37);
	
	Cancel->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.6, glutGet(GLUT_WINDOW_HEIGHT)*0.83, glutGet(GLUT_WINDOW_WIDTH)*0.6, glutGet(GLUT_WINDOW_HEIGHT)*0.88,
		glutGet(GLUT_WINDOW_WIDTH)*0.75, glutGet(GLUT_WINDOW_HEIGHT)*0.88, glutGet(GLUT_WINDOW_WIDTH)*0.75, glutGet(GLUT_WINDOW_HEIGHT)*0.83);

	Insanitarium->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.02, glutGet(GLUT_WINDOW_HEIGHT)*0.03, glutGet(GLUT_WINDOW_WIDTH)*0.02, glutGet(GLUT_WINDOW_HEIGHT)*0.33,
		glutGet(GLUT_WINDOW_WIDTH)*0.98, glutGet(GLUT_WINDOW_HEIGHT)*0.33, glutGet(GLUT_WINDOW_WIDTH)*0.98, glutGet(GLUT_WINDOW_HEIGHT)*0.03);

	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, alphamenu);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.03);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.33);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.33);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.03);
	glEnd();

#pragma region MusicVol

	if (MainMenu::IfMouseInTriangle(mousePoint, musicLeft1, musicLeft2, musicLeft3))
	{
		musicLeftColor = 0;
		if (ifSoundOptions3)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions3 = false;
		}
	}
	else
	{
		musicLeftColor = 1;
		ifSoundOptions3 = true;
	}

	if (MainMenu::IfMouseInTriangle(mousePoint, musicRight1, musicRight2, musicRight3))
	{
		musicRightColor = 0;
		if (ifSoundOptions4)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions4 = false;
		}
	}
	else
	{
		musicRightColor = 1;
		ifSoundOptions4 = true;
	}

	for (float i = 0;i < 10;i++)
	{
		if (musicOption > 0)
		{
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.48);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.52);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.52);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.48);
			glEnd();
			musicOption--;
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.48);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.52);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.52);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.48);
			glEnd();
		}
	}

	MusicVol->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.47, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.52,
		glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.52, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.47);

	///////////////////////////Pasek zmiany opcji
	//Muzyka
	glBegin(GL_TRIANGLES);
	glColor3f(1, musicLeftColor, musicLeftColor);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.55, glutGet(GLUT_WINDOW_HEIGHT)*0.5);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.52);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.48);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, musicRightColor, musicRightColor);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.52);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.48);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.83, glutGet(GLUT_WINDOW_HEIGHT)*0.5);
	glEnd();

	///////////////////////////

#pragma endregion

#pragma region SoundVol

	if (MainMenu::IfMouseInTriangle(mousePoint, soundLeft1, soundLeft2, soundLeft3))
	{
		soundLeftColor = 0;
		if (ifSoundOptions5)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions5 = false;
		}
	}
	else
	{
		soundLeftColor = 1;
		ifSoundOptions5 = true;
	}

	if (MainMenu::IfMouseInTriangle(mousePoint, soundRight1, soundRight2, soundRight3))
	{
		soundRightColor = 0;
		if (ifSoundOptions6)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions6 = false;
		}
	}
	else
	{
		soundRightColor = 1;
		ifSoundOptions6 = true;
	}

	for (float i = 0;i < 10;i++)
	{
		if (soundOption > 0)
		{
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.55);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.59);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.59);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.55);
			glEnd();
			soundOption--;
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.55);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.59);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.59);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.55);
			glEnd();
		}
	}

	SoundVol->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.54, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.59,
		glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.59, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.54);

	///////////////////////////Pasek zmiany opcji
	//Muzyka
	glBegin(GL_TRIANGLES);
	glColor3f(1, soundLeftColor, soundLeftColor);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.55, glutGet(GLUT_WINDOW_HEIGHT)*0.57);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.59);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.55);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, soundRightColor, soundRightColor);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.59);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.55);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.83, glutGet(GLUT_WINDOW_HEIGHT)*0.57);
	glEnd();

	///////////////////////////

#pragma endregion

#pragma region MouseSensitivity

	if (MainMenu::IfMouseInTriangle(mousePoint, mouseLeft1, mouseLeft2, mouseLeft3))
	{
		mouseLeftColor = 0;
		if (ifSoundOptions7)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions7 = false;
		}
	}
	else
	{
		mouseLeftColor = 1;
		ifSoundOptions7 = true;

	}

	if (MainMenu::IfMouseInTriangle(mousePoint, mouseRight1, mouseRight2, mouseRight3))
	{
		mouseRightColor = 0;
		if (ifSoundOptions8)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions8 = false;
		}
	}
	else
	{
		mouseRightColor = 1;
		ifSoundOptions8 = true;

	}

	MouseSen->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.61, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.66,
		glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.66, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.61);

	for (float i = 0;i < 10;i++)
	{
		if (mouseOption> 0)
		{
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.62);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.66);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.66);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.62);
			glEnd();
			mouseOption--;
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.62);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.595 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.66);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.66);
			glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*(0.605 + (i / 100) * 2), glutGet(GLUT_WINDOW_HEIGHT)*0.62);
			glEnd();
		}
	}

	SoundVol->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.54, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.59,
		glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.59, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.54);

	///////////////////////////Pasek zmiany opcji
	glBegin(GL_TRIANGLES);
	glColor3f(1, mouseLeftColor, mouseLeftColor);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.55, glutGet(GLUT_WINDOW_HEIGHT)*0.64);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.66);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.62);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, mouseRightColor, mouseRightColor);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.66);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.62);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH)*0.83, glutGet(GLUT_WINDOW_HEIGHT)*0.64);
	glEnd();
	
	///////////////////////////

#pragma endregion

#pragma region Windowed

	WindowedYes->Render(alphamenu,glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.58, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
		glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.7);

	WindowedNo->Render(alphamenu,glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.7, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
		glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.8, glutGet(GLUT_WINDOW_HEIGHT)*0.7);

	Windowed->Render(alphamenu,glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.7, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.75,
		glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.75, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.7);

	if (Window || (mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.58 && mouseX< glutGet(GLUT_WINDOW_WIDTH)*0.68 && mouseY> glutGet(GLUT_WINDOW_HEIGHT)*0.7 && mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.75))
	{
		WindowedYes->ChangeTexture("Resources/Yes_choice.bmp");
		if (ifSoundOptions9)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions9 = false;
		}
	}
	else
	{
		WindowedYes->ChangeTexture("Resources/Yes.bmp");
		ifSoundOptions9 = true;
	}

	if (!Window || (mouseX > glutGet(GLUT_WINDOW_WIDTH)*0.7 && mouseX< glutGet(GLUT_WINDOW_WIDTH)*0.8 && mouseY> glutGet(GLUT_WINDOW_HEIGHT)*0.7 && mouseY < glutGet(GLUT_WINDOW_HEIGHT)*0.75))
	{
		WindowedNo->ChangeTexture("Resources/No_choice.bmp");
		if (ifSoundOptions10)
		{
			MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
			ifSoundOptions10 = false;
		}
	}
	else
	{
		WindowedNo->ChangeTexture("Resources/No.bmp");
		ifSoundOptions10 = true;
	}

#pragma endregion

#pragma region Resoultion

	radius = glutGet(GLUT_WINDOW_WIDTH)*0.005;

	if (Window)
	{
		Resolution->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.76, glutGet(GLUT_WINDOW_WIDTH)*0.15, glutGet(GLUT_WINDOW_HEIGHT)*0.81,
			glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.81, glutGet(GLUT_WINDOW_WIDTH)*0.44, glutGet(GLUT_WINDOW_HEIGHT)*0.76);

		ResHD->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.61, glutGet(GLUT_WINDOW_HEIGHT)*0.76, glutGet(GLUT_WINDOW_WIDTH)*0.61, glutGet(GLUT_WINDOW_HEIGHT)*0.82,
			glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.82, glutGet(GLUT_WINDOW_WIDTH)*0.68, glutGet(GLUT_WINDOW_HEIGHT)*0.76);

		Res1280x720->Render(alphamenu, glutGet(GLUT_WINDOW_WIDTH)*0.79, glutGet(GLUT_WINDOW_HEIGHT)*0.76, glutGet(GLUT_WINDOW_WIDTH)*0.79, glutGet(GLUT_WINDOW_HEIGHT)*0.81,
			glutGet(GLUT_WINDOW_WIDTH)*0.86, glutGet(GLUT_WINDOW_HEIGHT)*0.81, glutGet(GLUT_WINDOW_WIDTH)*0.86, glutGet(GLUT_WINDOW_HEIGHT)*0.76);		

		if (MainMenu::IfMouseInCircle(mousePoint, resolution1, radius))
		{
			res1Color = 0;
			if (ifSoundOptions11)
			{
				MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
				ifSoundOptions11 = false;
			}
		}
		else
		{
			res1Color = 1;
			ifSoundOptions11 = true;
		}


		if (MainMenu::IfMouseInCircle(mousePoint, resolution2, radius))
		{
			res2Color = 0;
			if (ifSoundOptions12)
			{
				MenuElement.Play2D("Resources/Sounds/menu_nav.ogg", 0.2*sound / 100, false);
				ifSoundOptions12 = false;
			}
		}
		else
		{
			res2Color = 1;
			ifSoundOptions12 = true;
		}

		glColor3f(1, res1Color, res1Color);
		glTranslatef(glutGet(GLUT_WINDOW_WIDTH)*0.6, glutGet(GLUT_WINDOW_HEIGHT)*0.78, 0);
		if (res1)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINE_LOOP);
		for (double i = 0; i < 2 * PI; i += PI / 24)
			glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
		glEnd();
		glTranslatef(-glutGet(GLUT_WINDOW_WIDTH)*0.6, -glutGet(GLUT_WINDOW_HEIGHT)*0.78, 0);

		glColor3f(1, res2Color, res2Color);
		glTranslatef(glutGet(GLUT_WINDOW_WIDTH)*0.78, glutGet(GLUT_WINDOW_HEIGHT)*0.78, 0);
		if (res2)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINE_LOOP);
		for (double i = 0; i < 2 * PI; i += PI / 24)
			glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
		glEnd();
		glTranslatef(-glutGet(GLUT_WINDOW_WIDTH)*0.78, -glutGet(GLUT_WINDOW_HEIGHT)*0.78, 0);
	}

#pragma endregion
	
	//Pasek menu
	glBegin(GL_POLYGON);
	glColor4f(0, 0, 0, alphamenu);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.35);
	glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT)*0.9);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.9);
	glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)*0.35);
	glEnd();
}

bool MainMenu::IfMouseInTriangle(POINT pt, POINT v1, POINT v2, POINT v3)
{
	bool b1, b2, b3;

	b1 = MainMenu::Sign(pt, v1, v2) < 0.0f;
	b2 = MainMenu::Sign(pt, v2, v3) < 0.0f;
	b3 = MainMenu::Sign(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

float MainMenu::Sign(POINT p1, POINT p2, POINT p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool MainMenu::IfMouseInCircle(POINT pt, POINT v0, float r)
{
	if (mouseX>glutGet(GLUT_WINDOW_WIDTH)*0.595 && mouseX<glutGet(GLUT_WINDOW_WIDTH)*0.785 && mouseY>glutGet(GLUT_WINDOW_HEIGHT)*0.76 && mouseY<glutGet(GLUT_WINDOW_HEIGHT)*0.79)
		return sqrt((pt.x - v0.x) *(pt.x - v0.x) + (pt.y - v0.y) *(pt.y - v0.y)) <= r;
	else
		return false;
}

MainMenu::~MainMenu()
{
}

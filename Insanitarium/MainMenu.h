#pragma once
#include "TextBox.h"
class MainMenu
{
public:
	static void DrawMenu();
	static void DrawMainMenu();
	static void FadeMainMenu();
	static void DrawOptions();
	static bool IfMouseInTriangle(POINT pt, POINT v1, POINT v2, POINT v3);
	static float Sign(POINT p1, POINT p2, POINT p3);

	MainMenu();
	~MainMenu();
	
private:
	
};


#pragma once
#include "TextBox.h"
class MainMenu
{
public:
	static void DrawMenu();
	static void DrawMainMenu();
	static void FadeMainMenu();
	static void DrawOptions();
	static bool IfMouseInTriangle(POINT, POINT, POINT, POINT);
	static float Sign(POINT, POINT, POINT);
	static bool IfMouseInCircle(POINT, POINT, float);

	MainMenu();
	~MainMenu();
	
private:
	
};
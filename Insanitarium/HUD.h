#pragma once
class HUD
{
public:
	static void DrawCrossHair();
	static void DrawCameraView();
	static void ShowPickMessage(Object*);
	static void KillPlayer();
	static void ShowDeathScreen();

	HUD();
	~HUD();
};


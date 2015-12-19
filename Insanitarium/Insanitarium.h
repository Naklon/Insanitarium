#pragma once
#include "Audio.h"
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnMouseMove(int, int);
void OnTimer(int);
void OnMousePress(int button, int state, int x, int y);
void LoadSettings();


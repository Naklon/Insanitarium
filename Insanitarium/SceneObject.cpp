#include "StdAfx.h"
#include "SceneObject.h"

// Uniwersalny konstruktor, ustawia podstawowe rzeczy.
SceneObject::SceneObject(void)
{
	Position.Set(0.0f, 0.0f, 0.0f);
	Rotation.Set(0.0f, 0.0f, 0.0f);
	Name = new char[128];
	strcpy(Name, "(unnamed object)");
}

// Destruktor - sprz¹tamy po sobie.
SceneObject::~SceneObject(void)
{
	delete[] Name;
}

#pragma once
#include"Audio.h"

class CScene
{
public:
	
	CSkydome * Skydome; // Skydome - niebo.
	CTerrain * Terrain; // Teren - czyli w naszym przyk�adzie trawiasty quad.
	CPlayer Player; // Stan gracza.

	// Wszystkie obiekty na scenie, wektor na podstawie kt�rego b�dzie mo�na
	// po nich �atwo iterowa�, np. w celu ich narysowania.
	vector<CSceneObject *> * Objects;

	CScene(void); // Konstruktor.
	~CScene(void); // Destruktor.
	void Initialize(void); // Inicjalizacja (wywo�ywana raz).
	void Update(float,int); // Aktualizacja �wiata.
	void Render(void); // Rysowanie ca�ej sceny.
	void PauseAllSounds();
	void ResumeAllSounds();
	bool DrawCollisions; // Czy maj� by� rysowane kolizje (do debugowania, klawisz "K")?
	bool DrawNormals; // Czy maj� by� rysowane wektory normalne (do debugowania, klawisz "N")?
	vec3 LastCollisionPoint; // Pozycja ostatniej kolizji.
	bool MarkCollision; // Czy ju� zaistnia�a jakakolwiek kolizja warta narysowania?

	

};


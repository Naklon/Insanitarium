#pragma once
#include"Audio.h"

class CScene
{
public:
	
	CSkydome * Skydome; // Skydome - niebo.
	CTerrain * Terrain; // Teren - czyli w naszym przyk³adzie trawiasty quad.
	CPlayer Player; // Stan gracza.

	// Wszystkie obiekty na scenie, wektor na podstawie którego bêdzie mo¿na
	// po nich ³atwo iterowaæ, np. w celu ich narysowania.
	vector<CSceneObject *> * Objects;

	CScene(void); // Konstruktor.
	~CScene(void); // Destruktor.
	void Initialize(void); // Inicjalizacja (wywo³ywana raz).
	void Update(float,int); // Aktualizacja œwiata.
	void Render(void); // Rysowanie ca³ej sceny.
	void PauseAllSounds();
	void ResumeAllSounds();
	bool DrawCollisions; // Czy maj¹ byæ rysowane kolizje (do debugowania, klawisz "K")?
	bool DrawNormals; // Czy maj¹ byæ rysowane wektory normalne (do debugowania, klawisz "N")?
	vec3 LastCollisionPoint; // Pozycja ostatniej kolizji.
	bool MarkCollision; // Czy ju¿ zaistnia³a jakakolwiek kolizja warta narysowania?

	

};


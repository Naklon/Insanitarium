#pragma once
#include "SceneObject.h"
// �ciana. Jedyny element sceny w przyk�adzie, z kt�rym wykrywane b�d� kolizje.
// Jest to dowolny quad kt�rego wszystkie wierzcho�ki le�� na jednej p�aszczy�nie (wa�ne!).
// �ciana b�dzie rysowana oraz zostanie utworzony i zapami�tany czworok�t na potrzeby
// wykrywania kolizji.
class StaticObject : public SceneObject
{
public:
	void Initialize(void); // Inicjalizacja (wywo�ana raz).
	void Update(void); // Aktualizacja stanu.
	void Render(void); // Rysowanie �ciany

	StaticObject(vec3 a, vec3 b, vec3 c, vec3 d,char*);
	StaticObject(vec3 a, vec3 b, vec3 c, char*);
	~StaticObject(void); // Destruktor.

	CCollisionPolygon * collisionPolygon; // Polygon (a tak naprawd� po prostu czworok�t), z kt�rym b�d� wykrywane kolizje.
	vec3 v[4]; // Pozycje wierzcho�k�w.
	vec3 v1[3];
	vec3 n; // Wektor normalny �ciany.

protected:
	GLuint _displayListId; // Id displaylisty.
	static bool _isLoaded; // Czy tekstura zosta�a ju� za�adowana (jest identyczna dla wszystkich instancji klasy)?
	static Textures * _wallTexture; // Tekstura.
	Textures * customText1; // Tekstura.
	std::string primitive;
	char* text;
};


#pragma once
#include "SceneObject.h"
// Œciana. Jedyny element sceny w przyk³adzie, z którym wykrywane bêd¹ kolizje.
// Jest to dowolny quad którego wszystkie wierzcho³ki le¿¹ na jednej p³aszczyŸnie (wa¿ne!).
// Œciana bêdzie rysowana oraz zostanie utworzony i zapamiêtany czworok¹t na potrzeby
// wykrywania kolizji.
class StaticObject : public SceneObject
{
public:
	void Initialize(void); // Inicjalizacja (wywo³ana raz).
	void Update(void); // Aktualizacja stanu.
	void Render(void); // Rysowanie œciany

	StaticObject(vec3 a, vec3 b, vec3 c, vec3 d,char*);
	StaticObject(vec3 a, vec3 b, vec3 c, char*);
	~StaticObject(void); // Destruktor.

	CCollisionPolygon * collisionPolygon; // Polygon (a tak naprawdê po prostu czworok¹t), z którym bêd¹ wykrywane kolizje.
	vec3 v[4]; // Pozycje wierzcho³ków.
	vec3 v1[3];
	vec3 n; // Wektor normalny œciany.

protected:
	GLuint _displayListId; // Id displaylisty.
	static bool _isLoaded; // Czy tekstura zosta³a ju¿ za³adowana (jest identyczna dla wszystkich instancji klasy)?
	static Textures * _wallTexture; // Tekstura.
	Textures * customText1; // Tekstura.
	std::string primitive;
	char* text;
};


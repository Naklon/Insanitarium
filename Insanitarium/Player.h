#pragma once

// Stan gracza.
class CPlayer
{

public:
	vec3 pos;
	vec3 dir;
	vec3 cam; // Przesuni�cie punktu zaczepienia kamery wzgl�dem pozycji gracza.
	float speed;
	float velRX, velRY, velM, velS;
	CCollisionEllipsoid * collisionEllipsoid; // Elipsoida s�u��ca do wykrywania kolizji.
	void SetPlayerRunningSpeed(float newSpeed = 0.8f);
	void SetPlayerNormalSpeed();
	void SetPlayerCrouchSpeed(float newSpeed = 0.2f);

	CPlayer()
	{
		pos.Set(0.0f, 0.0f, 0.0f);
		dir.Set(0.0f, 0.0f, -1.0f);
		cam.Set(0.0f, 0.25f, 0.0f);
		speed = 0.0f;
		velRX = 0.0f;
		velRY = 0.0f;
		velM = 0.0f;
		velS = 0.0f;
		collisionEllipsoid = new CCollisionEllipsoid(.15f, .3f, .15f);
	}

};

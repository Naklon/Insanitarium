#pragma once
#include "Object.h"
class Camera:public Object
{
public:
	void Render(float, float , float , float , float , float );
	void DechargeBattery();
	void PickUpCamera();
	void PutCameraDown();
	float GetBatteryInfo(char*);
	void Update();
	void ChangeCameraBattery();
	bool PickUpBattery();

	Camera(char*);
	Camera();
	~Camera();

private:
	int batteries;
	float battery;
};


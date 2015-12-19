#pragma once

class CSceneObject
{
public:
	

	CSceneObject(void); 
	~CSceneObject(void); 
	virtual void Initialize(void) = 0; 
	virtual void Update(void) = 0; 
	virtual void Render(void) = 0; 

	vec3 Position;
	vec3 Rotation;
	char *Name;
};


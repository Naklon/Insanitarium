#pragma once

class CTerrain : public CSceneObject
{
public:
	CTerrain(void);
	~CTerrain(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

protected:
	GLuint _displayListId;
	CTexture * _grassTexture;
};


#pragma once


class CSkydome : public SceneObject
{
public:
	CSkydome(void);
	~CSkydome(void);
	void Initialize(void);
	void Update(void);
	void Render(void);

protected:
	GLuint _displayListId;
	Textures * _skyTexture;
};


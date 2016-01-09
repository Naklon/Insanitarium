#pragma once

class TextBox
{
public:
	TextBox();
	TextBox(float, float, float, float, float, float, float, float, char*);
	~TextBox();

	void Render(float,float,float,float,float,float,float,float,float);
	void Load();
	void ChangeTexture(char*);
	void Resize(float, float, float, float, float, float, float, float);

private:
	float x1, y1, x2, y2, x3, y3, x4, y4;
	Textures *textTexture;
	bool ifLoaded;
};


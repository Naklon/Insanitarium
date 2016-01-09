#include "stdafx.h"
#include "TextBox.h"



TextBox::TextBox()
{
}

TextBox::TextBox(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4,char * tex)
{
		x1 = X1;
		y1 = Y1;

		x2 = X2;
		y2 = Y2;

		x3 = X3;
		y3 = Y3;

		x4 = X4;
		y4 = Y4;

		textTexture = new Textures(tex, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		
}

TextBox::~TextBox()
{
}

void TextBox::Render(float alpha, float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4)
{

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textTexture->GetId());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_POLYGON);
	glColor4f(1, 1, 1, alpha);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x1,y1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x2, y2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x3, y3);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x4, y4);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	x1 / glutGet(GLUT_WINDOW_WIDTH);
	this->Resize(X1,Y1,X2,Y2,X3,Y3,X4,Y4);
}

void TextBox::Load()
{
	textTexture->Load();
}

void TextBox::ChangeTexture(char *newTex)
{
	Textures* tempTex = new Textures(newTex, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	tempTex->Load();
	this->textTexture = tempTex;
}

void TextBox::Resize(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4)
{
	x1 = X1;
	y1 = Y1;

	x2 = X2;
	y2 = Y2;

	x3 = X3;
	y3 = Y3;

	x4 = X4;
	y4 = Y4;
}

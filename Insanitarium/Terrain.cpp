#include "StdAfx.h"
#include "Terrain.h"


CTerrain::CTerrain(void) : CSceneObject()
{
}


CTerrain::~CTerrain(void)
{
}

void CTerrain::Initialize(void)
{
	
	

	_displayListId = glGenLists(1);

	float size = 50.0f;
	int N = 10;
	
	glNewList(_displayListId, GL_COMPILE);
		glBegin(GL_QUADS);

			for (int x = 0; x < N; ++x) {

				for (int y = 0; y < N; ++y) {
			
					glTexCoord2f(size * (x + 1) / N, size * y / N);
					glVertex3f(size * (x + 1 - N/2) / N, 0.0f, size * (y - N/2) / N);
			
					glTexCoord2f(size * x / N, size * y / N);
					glVertex3f(size * (x - N/2) / N, 0.0f, size * (y - N/2) / N);
			
					glTexCoord2f(size * x / N, size * (y + 1) / N);
					glVertex3f(size * (x - N/2) / N, 0.0f, size * (y + 1 - N/2) / N);
			
					glTexCoord2f(size * (x + 1) / N, size * (y + 1) / N);
					glVertex3f(size * (x + 1 - N/2) / N, 0.0f, size * (y + 1 - N/2) / N);

				}

			}

		glEnd();
	glEndList();
	_grassTexture = new CTexture("Resources\\Floor01.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_grassTexture->Load();
}

void CTerrain::Update(void)
{
}

void CTerrain::Render(void)
{
	
	glPushMatrix();

	

	glTranslatef(Position.x, Position.y, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);


	float mA[] = { 0.0f, 0.0f, 0.0f };
	float mS[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mA);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mS);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _grassTexture->GetId());
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glCallList(_displayListId);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

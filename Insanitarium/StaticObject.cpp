#include "StdAfx.h"

bool StaticObject::_isLoaded = false;
bool ifFloorLoaded = false;
bool ifCeilingLoaded = false;
Textures * StaticObject::_wallTexture = NULL;
Textures * floorTex;
Textures * ceilingTex;

StaticObject::StaticObject(vec3 a, vec3 b, vec3 c, vec3 d,char *texture) : SceneObject()
{
	_displayListId = -1; 
	v[0] = a;
	v[1] = b;
	v[2] = c;
	v[3] = d;
	collisionPolygon = new CCollisionPolygon(v, 4); 
	collisionPolygon->parent = this; 
	vec3::Cross((c-b), (a-b), n); 
	n.Normalize(); 
	text = texture;
	primitive = "Quad";
}

StaticObject::StaticObject(vec3 a, vec3 b, vec3 c, char * texture)
{
	_displayListId = -1; 
	v1[0] = a;
	v1[1] = b;
	v1[2] = c;
	
	collisionPolygon = new CCollisionPolygon(v1, 3);
	collisionPolygon->parent = this; 
	vec3::Cross((c - b), (a - b), n);
	n.Normalize();
	text = texture;
	primitive = "Triangle";
}

StaticObject::~StaticObject(void)
{
	delete collisionPolygon;
}

void StaticObject::Initialize()
{
	if (text != "None")
	{
		_displayListId = glGenLists(1);
		glColor4f(0, 0, 0, 1);
		glNewList(_displayListId, GL_COMPILE);
		if (primitive == "Quad")
		{
			glBegin(GL_QUADS);

			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(v[0].x, v[0].y, v[0].z);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(v[1].x, v[1].y, v[1].z);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(v[2].x, v[2].y, v[2].z);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(v[3].x, v[3].y, v[3].z);

			glEnd();
		}
		else if (primitive == "Triangle")
		{
			glBegin(GL_TRIANGLES);
			glNormal3f(n.x, n.y, n.z);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(v1[0].x, v1[0].y, v1[0].z);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(v1[1].x, v1[1].y, v1[1].z);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(v1[2].x, v1[2].y, v1[2].z);
			glEnd();
		}
		glEndList();

		if (!ifFloorLoaded)
		{
			ifFloorLoaded = true;
			floorTex = new Textures("Resources/Floor01.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
			floorTex->Load();
		}

		if (!ifCeilingLoaded)
		{
			ifCeilingLoaded = true;
			ceilingTex = new Textures("Resources/Ceiling.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
			ceilingTex->Load();
		}

		if (_isLoaded && text == "Resources/Wall.bmp")
			return;

		if (text == "Resources/Wall.bmp")
		{
			_wallTexture = new Textures(text, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
			_wallTexture->Load();
		}
		else if(this->text !="Resources/Floor01.bmp" && this->text!="Resources/Ceiling.bmp")
		{
			this->customText1 = new Textures(text, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
			this->customText1->Load();
		}
	}
}

void StaticObject::Update(void)
{

}

void StaticObject::Render(void)
{
	if (text != "None")
	{
		glPushMatrix();

		float mA[] = { 0.2f, 0.2f, 0.2f };
		float mD[] = { 0.6f, 0.6f, 0.6f };
		float mS[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mA);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mD);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mS);
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		if (this->customText1 != NULL)
			glBindTexture(GL_TEXTURE_2D, this->customText1->GetId());
		else if(this->text!="Resources/Floor01.bmp" && this->text!="Resources/Ceiling.bmp")
			glBindTexture(GL_TEXTURE_2D, _wallTexture->GetId());
		else if(this->text == "Resources/Floor01.bmp")
			glBindTexture(GL_TEXTURE_2D, floorTex->GetId());
		else
			glBindTexture(GL_TEXTURE_2D, ceilingTex->GetId());

		glCallList(_displayListId);

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}
}


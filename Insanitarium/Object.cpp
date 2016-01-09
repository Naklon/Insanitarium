#include "stdafx.h"

Object::Object()
{
}

Object::Object(string objName,std::string name,bool ifPickable)
{

	this->pickable = ifPickable;
	this->Name = name;
	this->objName = objName;
	int k = 0;
	
		filename = "Resources/Objects/" + objName + "/" + objName + ".obj";

}

Object::~Object() {
	glDeleteLists(list, 1);
}

GLuint Object::LoadTexture(string file, int magFilter, int minFilter) {
	char * temp = _strdup(file.c_str());
	printf("%s", temp);

	// Odczytanie bitmapy
	Bitmap *tex = new Bitmap();
	if (!tex->loadBMP(temp)) {
		printf("ERROR: Cannot read texture file \"%s\".\n", file);
		return -1;
	}

	// Utworzenie nowego id wolnej tekstury
	GLuint texId;
	glGenTextures(1, &texId);

	// "Bindowanie" tekstury o nowoutworzonym id
	glBindTexture(GL_TEXTURE_2D, texId);

	// Okreœlenie parametrów filtracji dla tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powiêkszana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana

																	  // Wys³anie tekstury do pamiêci karty graficznej zale¿nie od tego, czy chcemy korzystaæ z mipmap czy nie
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		// Automatyczne zbudowanie mipmap i wys³anie tekstury do pamiêci karty graficznej
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}
	else {
		// Wys³anie tekstury do pamiêci karty graficznej
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}

	// Zwolnienie pamiêci, usuniêcie bitmapy z pamiêci - bitmapa jest ju¿ w pamiêci karty graficznej
	delete tex;

	// Zwrócenie id tekstury
	return texId;
}

void Object::compileList() {

	int x = 0, j = 0;



	glNewList(list, GL_COMPILE);

	if (texture.size() > 0)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, texture[0]);
	}

	for (int i = 0; i < faces.size(); i++) {
		if (texture.size() > 0)
		{
			if (counter[x] <= 0)
			{
				x++;
				j++;
				glBindTexture(GL_TEXTURE_2D, texture[j]);
			}
			counter[x]--;
		}

		if (faces[i].vertex.size() == 3) { // triangle
			if (faces[i].normal.size() == 3) { // with normals
				glBegin(GL_TRIANGLES);
				if (texcoords[faces[i].texture[0]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1], texcoords[faces[i].texture[0]].v[2]);
				else if (texcoords[faces[i].texture[0]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glNormal3f(normals[faces[i].normal[0]].v[0], normals[faces[i].normal[0]].v[1], normals[faces[i].normal[0]].v[2]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);


				if (texcoords[faces[i].texture[1]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1], texcoords[faces[i].texture[1]].v[2]);
				else if (texcoords[faces[i].texture[1]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glNormal3f(normals[faces[i].normal[1]].v[0], normals[faces[i].normal[1]].v[1], normals[faces[i].normal[1]].v[2]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);


				if (texcoords[faces[i].texture[2]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1], texcoords[faces[i].texture[2]].v[2]);
				else if (texcoords[faces[i].texture[2]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glNormal3f(normals[faces[i].normal[2]].v[0], normals[faces[i].normal[2]].v[1], normals[faces[i].normal[2]].v[2]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);
				glEnd();
			}
			else { // without normals -- evaluate normal on quad
				vertex v = (vertices[faces[i].vertex[1]] - vertices[faces[i].vertex[0]]).cross(vertices[faces[i].vertex[2]] - vertices[faces[i].vertex[0]]);
				v.normalize();
				glBegin(GL_TRIANGLES);
				glNormal3f(v.v[0], v.v[1], v.v[2]);

				if (texcoords[faces[i].texture[0]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1], texcoords[faces[i].texture[0]].v[2]);
				else if (texcoords[faces[i].texture[0]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);

				if (texcoords[faces[i].texture[1]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1], texcoords[faces[i].texture[1]].v[2]);
				else if (texcoords[faces[i].texture[1]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);

				if (texcoords[faces[i].texture[2]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1], texcoords[faces[i].texture[2]].v[2]);
				else if (texcoords[faces[i].texture[2]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);
				glEnd();
			}
		}
		else if (faces[i].vertex.size() == 4) { // quad
			if (faces[i].normal.size() == 4) { // with normals


				glBegin(GL_QUADS);
				if (texcoords[faces[i].texture[0]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1], texcoords[faces[i].texture[0]].v[2]);
				else if (texcoords[faces[i].texture[0]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glNormal3f(normals[faces[i].normal[0]].v[0], normals[faces[i].normal[0]].v[1], normals[faces[i].normal[0]].v[2]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);

				if (texcoords[faces[i].texture[1]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1], texcoords[faces[i].texture[1]].v[2]);
				else if (texcoords[faces[i].texture[1]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glNormal3f(normals[faces[i].normal[1]].v[0], normals[faces[i].normal[1]].v[1], normals[faces[i].normal[1]].v[2]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);

				if (texcoords[faces[i].texture[2]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1], texcoords[faces[i].texture[2]].v[2]);
				else if (texcoords[faces[i].texture[2]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glNormal3f(normals[faces[i].normal[2]].v[0], normals[faces[i].normal[2]].v[1], normals[faces[i].normal[2]].v[2]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);

				if (texcoords[faces[i].texture[3]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[3]].v[0], texcoords[faces[i].texture[3]].v[1], texcoords[faces[i].texture[3]].v[2]);
				else if (texcoords[faces[i].texture[3]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[3]].v[0], texcoords[faces[i].texture[3]].v[1]);
				glNormal3f(normals[faces[i].normal[3]].v[0], normals[faces[i].normal[3]].v[1], normals[faces[i].normal[3]].v[2]);
				glVertex3f(vertices[faces[i].vertex[3]].v[0], vertices[faces[i].vertex[3]].v[1], vertices[faces[i].vertex[3]].v[2]);
				glEnd();

			}
			else { // without normals -- evaluate normal on quad
				vertex v = (vertices[faces[i].vertex[1]] - vertices[faces[i].vertex[0]]).cross(vertices[faces[i].vertex[2]] - vertices[faces[i].vertex[0]]);
				v.normalize();
				glBegin(GL_QUADS);

				if (texcoords[faces[i].texture[0]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1], texcoords[faces[i].texture[0]].v[2]);
				else if (texcoords[faces[i].texture[0]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[0]].v[0], texcoords[faces[i].texture[0]].v[1]);
				glNormal3f(v.v[0], v.v[1], v.v[2]);
				glVertex3f(vertices[faces[i].vertex[0]].v[0], vertices[faces[i].vertex[0]].v[1], vertices[faces[i].vertex[0]].v[2]);

				if (texcoords[faces[i].texture[1]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1], texcoords[faces[i].texture[1]].v[2]);
				else if (texcoords[faces[i].texture[1]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[1]].v[0], texcoords[faces[i].texture[1]].v[1]);
				glVertex3f(vertices[faces[i].vertex[1]].v[0], vertices[faces[i].vertex[1]].v[1], vertices[faces[i].vertex[1]].v[2]);

				if (texcoords[faces[i].texture[2]].v.size() == 3)
					glTexCoord3f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1], texcoords[faces[i].texture[2]].v[2]);
				else if (texcoords[faces[i].texture[2]].v.size() == 2)
					glTexCoord2f(texcoords[faces[i].texture[2]].v[0], texcoords[faces[i].texture[2]].v[1]);
				glVertex3f(vertices[faces[i].vertex[2]].v[0], vertices[faces[i].vertex[2]].v[1], vertices[faces[i].vertex[2]].v[2]);
				glVertex3f(vertices[faces[i].vertex[3]].v[0], vertices[faces[i].vertex[3]].v[1], vertices[faces[i].vertex[3]].v[2]);
				glEnd();
			}
		}
	}
	if (texture.size() > 0)
	{
		glDisable(GL_TEXTURE_2D);
	}
	glEndList();

}

void Object::Render(float x,float y, float z,float angle, float rx, float ry,float rz)
{
	if (this->Name == "¯arówka")
	{
		float mD[] = { 0.2f, 0.2f, 0 };
		float mS[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mD);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mS);
		glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
	}
		this->x = x;
		this->y = y;
		this->z = z;
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(angle, rx, ry, rz);
		glCallList(list);
		glPopMatrix();
}

void Object::Load()
{
	std::ifstream ifs(filename.c_str(), std::ifstream::in);
	std::string line, key;
	while (ifs.good() && !ifs.eof() && std::getline(ifs, line)) {
		key = "";
		std::stringstream stringstream(line);
		stringstream >> key >> std::ws;

		if (key == "v") { // vertex
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}

			vertices.push_back(v);
		}
		else if (key == "vp") { // parameter
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			parameters.push_back(v);
		}
		else if (key == "vt") { // texture coordinate
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}

			texcoords.push_back(v);

		}
		else if (key == "vn") { // normal
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			v.normalize();
			normals.push_back(v);
		}
		else if (key == "f") { // face
			face f; int v, t, n;
			counter[counter.size() - 1]++;
			while (!stringstream.eof()) {

				stringstream >> v >> std::ws;
				f.vertex.push_back(v - 1);
				if (stringstream.peek() == '/') {
					stringstream.get();
					if (stringstream.peek() == '/') {
						stringstream.get();
						stringstream >> n >> std::ws;
						f.normal.push_back(n - 1);
					}
					else {
						stringstream >> t >> std::ws;
						f.texture.push_back(t - 1);
						if (stringstream.peek() == '/') {
							stringstream.get();
							stringstream >> n >> std::ws;
							f.normal.push_back(n - 1);
						}
					}
				}
			}
			faces.push_back(f);
		}
		else if (key == "o")
		{
			string newTexture = "", tmp;
			while (!stringstream.eof())
			{
				stringstream >> tmp;
				newTexture += tmp;
			}
			texture.push_back(LoadTexture("Resources/Objects/" + objName + "/" + newTexture + ".bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR));
			counter.push_back(0);
		}
		else {

		}
	}
	ifs.close();
	printf("               Name: %d\n", filename);
	printf("           Vertices: %d\n", vertices.size());
	printf("         Parameters: %d\n", parameters.size());
	printf("Texture Coordinates: %d\n", texcoords.size());
	printf("            Normals: %d\n", normals.size());
	printf("              Faces: %d\n\n", faces.size());
	list = glGenLists(1);
	compileList();
	vertices.clear();
	texcoords.clear();
	normals.clear();
	faces.clear();

}

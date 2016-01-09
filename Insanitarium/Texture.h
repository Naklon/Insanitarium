#pragma once
class Textures
{
public:
	bool IsLoaded;

	Textures(char *);
	Textures(char *, int, int);
	~Textures(void);
	bool Load(void);
	GLuint GetId(void);

protected:
	int _magFilter;
	int _minFilter;
	char * _file;
	GLuint _id;
};


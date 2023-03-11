#pragma once

#include <string>
#include <glew.h>
#include <SDL_image.h>
#include <assert.h>
#include <iostream>

class texture
{


public:
	texture(const std::string& filename);

	void Bind(unsigned int unit);

	virtual ~texture();

protected:


private:
	texture(const texture& other) {}
	void operator=(const texture& other) {}

	GLuint m_texture;




};


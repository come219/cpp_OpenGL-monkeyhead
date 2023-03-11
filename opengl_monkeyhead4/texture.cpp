#include "texture.h"



texture::texture(const std::string& filename)
{
	unsigned int width, height, numComponents;

	auto surface = IMG_Load(filename.c_str());

	if (!surface) {

		std::cerr << "Failed to create surface!" << std::endl;

	}

	glGenTextures(1, &m_texture);

	if (!m_texture)
	{
		std::cerr << "Failed to create texture!" << std::endl;

	}

	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
								
	glTexImage2D(GL_TEXTURE, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface);

	SDL_FreeSurface(surface);

}



texture::~texture()
{
	
	glDeleteTextures(1, &m_texture);



}



void texture::Bind(unsigned int unit)
{

	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);

	glBindTexture(GL_TEXTURE_2D, m_texture);

}
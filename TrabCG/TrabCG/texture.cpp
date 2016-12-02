#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

void Texture::Bind(unsigned int unit)
{
	//assert(unit >= 0 && unit <= 31);

	this->m_unit = unit;

	glActiveTexture(GL_TEXTURE0 + this->m_unit);
	glBindTexture(GL_TEXTURE_2D, this->m_texture);
}

void Texture::Bind(unsigned int unit, Shader* shader)
{
	//assert(unit >= 0 && unit <= 31);
	this->m_unit = unit;

	std::string location;

	switch (unit)
	{
	case 0:
		location = "material.diffuse";
		break;
	case 1:
		location = "material.specular";
		break;
	}

	glUniform1i(glGetUniformLocation(shader->Program(), location.c_str()), this->m_unit);

	glActiveTexture(GL_TEXTURE0 + this->m_unit);
	glBindTexture(GL_TEXTURE_2D, this->m_texture);
}

void Texture::Unbind()
{
	glActiveTexture(GL_TEXTURE0 + this->m_unit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->m_texture);
}

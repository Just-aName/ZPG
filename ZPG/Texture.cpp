#include "Texture.h"

Texture::Texture(const char* filename) : ITexture()
{
	this->filename = filename;
}

void Texture::bind()
{
	layerId = SOIL_load_OGL_texture(filename, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (layerId == 0)
	{
		fprintf(stderr, "Texture %s not found.\n", filename);
		return;
	}

	glActiveTexture(GL_TEXTURE0 + layerId);

	glBindTexture(GL_TEXTURE_2D, layerId);
	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	printf("INFO: Texture %s bind with to layer %d.\n", filename, layerId);

	layerId--;
	this->is_loaded = true;
}

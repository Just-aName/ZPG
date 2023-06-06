#include "Cubemap.h"

Cubemap::Cubemap(const char* x_pos_file, const char* x_neg_file, const char* y_pos_file, const char* y_neg_file, const char* z_pos_file, const char* z_neg_file) : ITexture()
{
	this->filenames[0] = x_pos_file;
	this->filenames[1] = x_neg_file;
	this->filenames[2] = y_pos_file;
	this->filenames[3] = y_neg_file;
	this->filenames[4] = z_pos_file;
	this->filenames[5] = z_neg_file;
}

void Cubemap::bind()
{
	layerId = SOIL_load_OGL_cubemap(
		this->filenames[0],
		this->filenames[1],
		this->filenames[2],
		this->filenames[3],
		this->filenames[4],
		this->filenames[5],
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS
	);

	if (layerId == 0)
	{
		fprintf(stderr, "Cubemap %s not found.\n", filenames[0]);
		return;
	}

	glActiveTexture(GL_TEXTURE0 + layerId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, layerId);

	printf("INFO: Texture %s bind to layer %d.\n", filenames[0], layerId);

	layerId -= 1;
	is_loaded = true;
}

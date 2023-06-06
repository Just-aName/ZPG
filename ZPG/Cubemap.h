#pragma once
#include "ITexture.h"

class Cubemap : public ITexture
{
private:
	const char* filenames[6];
public:
	Cubemap(const char* x_pos_file, const char* x_neg_file, const char* y_pos_file, const char* y_neg_file, const char* z_pos_file, const char* z_neg_file);

	virtual void bind() override;
};


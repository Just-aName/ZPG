#pragma once
#include "ITexture.h"

class Texture : public ITexture
{
private:
	const char* filename = nullptr;
public:
	Texture(const char* filename);

	virtual void bind() override;
};


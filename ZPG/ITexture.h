#pragma once
#include <GL/glew.h>
#include <SOIL2.h>
#include <cstdio>

class ITexture
{
protected:
	unsigned int layerId = 0;
	bool is_loaded = false;
public:
	ITexture() {}

	int getLayerId() const
	{
		return layerId;
	}

	bool isLoaded() const
	{
		return is_loaded;
	}

	virtual void bind() = 0;
	virtual void unbind() {}
};


#include "TextureManager.h"


TextureManager::~TextureManager()
{
	for (auto pair : cubemaps)
	{
		pair.second->unbind();
	}

	for (auto pair : textures)
	{
		pair.second->unbind();
	}
}

void TextureManager::load()
{
	for (auto pair : cubemaps)
	{
		pair.second->bind();
	}

	for (auto pair : textures)
	{
		pair.second->bind();
	}
}

void TextureManager::add(string name, shared_ptr<Texture> texture)
{
	textures.emplace(name, texture);
}

void TextureManager::add(string name, shared_ptr<Cubemap> cubemap)
{
	cubemaps.emplace(name, cubemap);
}

const shared_ptr<Texture>& TextureManager::getTexture(string name) const
{
	try
	{
		return textures.at(name);
	}
	catch (exception e)
	{
		std::cerr << "TextureManager ERROR: " + string(e.what()) + "(" + name + ")" << std::endl;
		exit(1);
	}
}

const shared_ptr<Cubemap>& TextureManager::getCubemap(string name) const
{
	try
	{
		return cubemaps.at(name);
	}
	catch (exception e)
	{
		std::cerr << "TextureManager ERROR: " + string(e.what()) + "(" + name + ")" << std::endl;
		exit(1);
	}
}

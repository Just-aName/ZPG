#pragma once
#include "Texture.h"
#include "Cubemap.h"

#include <map>
#include <memory>
#include <string>
#include <exception>
#include <iostream>

using std::map;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::exception;

class TextureManager
{
private:
	/// <summary>
	/// App textures
	/// </summary>
	map<string, shared_ptr<Texture>> textures;

	/// <summary>
	/// App cubemaps
	/// </summary>
	map<string, shared_ptr<Cubemap>> cubemaps;
public:
	TextureManager() {}
	~TextureManager();

	void load();

	void add(string name, shared_ptr<Texture> texture);

	void add(string name, shared_ptr<Cubemap> cubemap);

	const shared_ptr<Texture>& getTexture(string name) const;

	const shared_ptr<Cubemap>& getCubemap(string name) const;
};


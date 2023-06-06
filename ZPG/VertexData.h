#pragma once

typedef struct {
	float x, y, z;
}Point;

typedef struct {
	float x, y, z;
}Normal;

typedef struct {
	float x, y;
}TexturePoint;

typedef struct {
	float x, y, z;
} Tangent;

typedef struct {
	Point point;
	Normal normal;
}VertexData;

typedef struct {
	Point point;
	Normal normal;
	TexturePoint texPoint;
}VertexDataTexture;

typedef struct {
	Point point;
	Normal normal;
	TexturePoint texture;
	Tangent tangent;
}VertexDataAssimp;

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};


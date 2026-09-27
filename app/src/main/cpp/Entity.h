#include <raylib.h>

#pragma once

class Entity
{
public:
	Texture2D texture;
	Vector2 position;

	void Init();
	void Update();
	void Draw();
};
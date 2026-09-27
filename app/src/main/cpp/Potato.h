#include <raylib.h>

#pragma once

class Potato : public Entity
{
public:
	float rotation;
	Vector2 center;

	Vector2 acceleration;
	Vector2 velocity;

	Vector2 rel;
	float mag;

	Rectangle rectangle;

	Sound PopSound;

	virtual void Init();
	virtual void Update();
	virtual void Draw();
};
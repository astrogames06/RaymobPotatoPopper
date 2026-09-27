#include "Game.h"
#include "Potato.h"
#include "Utils.h"
#include "Potato_img.h"

#include <raymath.h>

#include <iostream>

void Potato::Init()
{
	rotation = 0.0f;
	position = { (float)Game::WIDTH / 2, (float)Game::HEIGHT / 2 };

	Image img = { 0 };
	img.width = POTATO_IMG_WIDTH;
	img.height = POTATO_IMG_HEIGHT;
	img.format = POTATO_IMG_FORMAT;
	img.data = POTATO_IMG_DATA;
	img.mipmaps = 1;

	texture = LoadTextureFromImage(img);

	rectangle = Rectangle {
		0, 0,
		(float)texture.width, (float)texture.height
	};
	center = { (float)texture.width / 2, (float)texture.height / 2 };
	acceleration = { 0, 0.1 };
	PopSound = LoadSound("pop.mp3");
	velocity = Vector2Zero();
	SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
}

void Potato::Update()
{
	if (IsKeyDown(KEY_A))
		rotation += 0.3f;
	if (IsKeyDown(KEY_D))
		rotation -= 0.3f;

	this->rel = Vector2{ GetMouseX() - position.x, GetMouseY() - position.y };
	this->mag = Utils::magnitude(rel);

	velocity.x += (acceleration.x * 100) * GetFrameTime();
	velocity.y += (acceleration.y * 100) * GetFrameTime();

	position.x += velocity.x * 30 * GetFrameTime();
	position.y += velocity.y * 30 * GetFrameTime();

	rotation = atan2(position.y - GetMouseY(), position.x - GetMouseX()) * RAD2DEG + 90;

	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		velocity.x += (-(rel.x / mag) * 1000) * GetFrameTime();
		velocity.y += (-(rel.y / mag) * 1000) * GetFrameTime();

		PlaySound(PopSound);
	}

	if (position.y <= texture.height / 2)
	{
		position.y = texture.height / 2;
		velocity.y *= -1;

		// if (acceleration.y > 0)
		// {
		// 	if (velocity.y > 0)
		// 		acceleration.y += 0.3;
		// 	if (velocity.y < 0)
		// 		acceleration.y -= 0.3;
		// }
	}
	if (position.y > Game::HEIGHT)
	{
		// if (score > Utils::GetLocal("high_score"))
		// {
		// 	Utils::SetLocal("high_score", score);
		// }
		Game::Setup();
		Game::state = Game::MENU;
	}
	
	// Run();

	if (position.x > Game::WIDTH - texture.width / 2)
	{
		position.x = Game::WIDTH - texture.width / 2;
		velocity.x *= -1;
	}
		//position.x = 0;
	if (position.x < texture.width / 2)
	{
		position.x = texture.width / 2;

		velocity.x *= -1;
	}
		//position.x = Game::WIDTH;
}

void Potato::Draw()
{
	DrawFPS(10, Game::HEIGHT-20);

	DrawTexturePro(texture,
		rectangle,
		Rectangle { position.x, position.y, rectangle.width, rectangle.height },
		center,
		rotation,
		WHITE
	);
}
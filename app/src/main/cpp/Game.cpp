#include <raylib.h>
#include <string>

#include "Game.h"
#include "Potato.h"
#include "FrenchFries_img.h"
#include "Utils.h"

#ifdef PLATFORM_WEB

    #include <emscripten/emscripten.h>
    #include <emscripten/val.h>
    #include <emscripten/bind.h>

#endif

Potato potato;

Texture2D FryTexture;
std::vector<Vector2> fries;

void Game::Setup()
{
    potato.Init();

    state = State::MENU;
    score = 0;

	Image FryImg = { 0 };
	FryImg.width = FRENCHFRIES_IMG_WIDTH;
	FryImg.height = FRENCHFRIES_IMG_HEIGHT;
	FryImg.format = FRENCHFRIES_IMG_FORMAT;
	FryImg.data = FRENCHFRIES_IMG_DATA;
	FryImg.mipmaps = 1;

	FryTexture = LoadTextureFromImage(FryImg);
    //FryTexture = LoadTexture("images/FrenchFries.png");

    fries = { Vector2 {
        (float)GetRandomValue(FryTexture.width, WIDTH-FryTexture.width), 
        (float)GetRandomValue(HEIGHT-FryTexture.height, HEIGHT/2)
    } };
}

void Game::Init()
{
    InitWindow(Game::WIDTH, Game::HEIGHT, "Potato Popper!");
    WIDTH = GetScreenWidth()/2;
    HEIGHT = GetScreenHeight()/2;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitAudioDevice();
    SetWindowIcon(LoadImage("images/Potato.png"));

    SetTargetFPS(60);

    GameTexture = LoadRenderTexture(WIDTH, HEIGHT);

    Game::Setup();
}

void Game::Update()
{
    if (state == State::GAME)
    {
        potato.Update();
    }
    if (IsKeyDown(KEY_ESCAPE))
    {
        CloseWindow();
    }
    SetConfigFlags(FLAG_MSAA_4X_HINT);
}

void Game::Draw()
{
    BeginTextureMode(GameTexture);

    ClearBackground(RAYWHITE);

    if (state == State::MENU)
    {
        // std::string high_score_str = "High Score: " + std::to_string(Utils::GetLocal("high_score"));
        // DrawText(high_score_str.c_str(), Game::WIDTH / 2 - MeasureText(high_score_str.c_str(), 20)/2, HEIGHT/2-100, 20, BLACK);
        DrawText("Tap To Start!", Game::WIDTH / 2 - 125, Game::HEIGHT / 2 - 150, 20, BLACK);

        if (IsKeyDown(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            state = State::GAME;
    }
    if (state == State::GAME)
    {
        DrawText(std::to_string(score).c_str(), Game::WIDTH / 2 - 10 / 2, Game::HEIGHT / 2 - 10 / 2, 50, LIGHTGRAY);

        for (int i = 0; i < (int)fries.size(); i++)
        {
            DrawTextureV(FryTexture, fries[i], WHITE);

            // Drawing lines
            // DrawRectangleLines(fries[i].x, fries[i].y, FryTexture.width, FryTexture.height, GREEN);
            // DrawRectangleLinesEx(Rectangle{
            //     potato.position.x-potato.texture.width/2, potato.position.y-potato.texture.height/2, (float)potato.texture.width, (float)potato.texture.height
            // }, 1.f, GREEN);

            if (CheckCollisionRecs(Rectangle{
                potato.position.x-potato.texture.width/2, potato.position.y-potato.texture.height/2, (float)potato.texture.width, (float)potato.texture.height
            }, Rectangle{fries[i].x, fries[i].y, (float)FryTexture.width, (float)FryTexture.height}))
            {
                score++;
                fries[i] = Vector2{ 
                    (float)GetRandomValue(FryTexture.width, WIDTH-FryTexture.width), 
                    (float)GetRandomValue(HEIGHT-FryTexture.height, HEIGHT/4) 
                };
                //fries.erase(fries.begin() + i);
            }
        }
    }
    potato.Draw();

    EndTextureMode();
}
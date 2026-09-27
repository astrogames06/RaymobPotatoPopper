#include "Game.h"
#include "Potato.h"

#include <iostream>
#include <raylib.h>
#include <sstream>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


void UpdateDrawFrame()
{
    Game::Update();

    BeginDrawing();

    ClearBackground(RAYWHITE);

    Game::Draw();

    DrawTexturePro(
        Game::GameTexture.texture,
        Rectangle{
            0,
            0,
            (float)Game::GameTexture.texture.width,
            -(float)Game::GameTexture.texture.height
        },
        Rectangle{
            0,
            0,
            (float)GetScreenWidth(),
            (float)GetScreenHeight()
        },
        Vector2{0, 0},
        0,
        WHITE
    );

    EndDrawing();
}

int main(void)
{
    Game::Init();
    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
        SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------

        // Main game loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            UpdateDrawFrame();
        }
    #endif
}
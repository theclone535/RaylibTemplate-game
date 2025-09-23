
#include "raylib.h"
#include "raymath.h"

#include "game.h"   // an external header in this project
#include "lib.h"	// an external header in the static lib project

#include "RakNet.h"

Rectangle player1;
Vector2 position;

void GameInit()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitialWidth, InitialHeight, "Example");
    SetTargetFPS(144);
    /*
    active = false;

    InitAudioDevice();
     temp = LoadWave("resources/sound.wav");
     soundy = LoadSoundFromWave(temp);

    // load resources */

    player1.x = 25;
    player1.y = 25;
    player1.width = 25;
    player1.height = 25;

}

void GameCleanup()
{
    // unload resources

    CloseWindow();
}

bool GameUpdate()
{
    position = { 0, 0 };

    //Player controls
    if (IsKeyDown(KEY_W))
    {
        player1.y -= 1;
    }
    else if (IsKeyDown(KEY_A))
    {
        player1.x -= 1;
    }
    else if (IsKeyDown(KEY_S))
    {
        player1.y += 1;
    }
    else if (IsKeyDown(KEY_D))
    {
        player1.x += 1;
    }
    
    return true;
}

void GameDraw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    //previous testing
    /*
    DrawText("Hello Connor!", 10, 10, 20, GetTextColor());

    Texture2D scope = LoadTextureFromImage(LoadImage("resources/Scope.png"));

    Texture2D trump = LoadTextureFromImage(LoadImage("resources/trump.jpg"));
    
    DrawTexture(trump, 250, 250, WHITE);
    DrawTextureEx(scope, { (float)GetMouseX() - scope.width / 2 * 0.33f, (float)GetMouseY() - (scope.height / 2) * 0.33f }, 0, 0.33f, WHITE);
    
   

  
    Image clippy = GetClipboardImage();

    Texture2D throwitback = LoadTextureFromImage(clippy);
    for (int x = 0; x < 20; x++)
    {
        for (int i = 0; i < 10; i++)
        {
            DrawTexture(throwitback, i * 100 + (x * 150), i * 100, WHITE);
        }
    }
    /*if (!IsSoundPlaying(soundy))
    {
        DrawText("Yes", 50, 100, 50, GREEN);
        PlaySound(soundy);
    }
    if (!active)
    {
        PlaySound(soundy);
        active = true;
    }
    else
    {
        
    }

    if (IsSoundPlaying(soundy))
    {
        
    }
    
    
        //DrawText("No Audio Init", 50, 100, 50, RED);
    
    */ // //previous contraption
    //DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);
    DrawRectanglePro(player1, Vector2{0, 0}, 0.0f, WHITE);

    


    EndDrawing();
}

int main()
{
    GameInit();

    while (!WindowShouldClose())
    {
        if (!GameUpdate())
            break;

        GameDraw();
    }
    GameCleanup();

    return 0;
}
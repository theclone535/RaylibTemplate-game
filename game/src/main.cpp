
#include "raylib.h"
#include "raymath.h"

#include "game.h"   // an external header in this project
#include "lib.h"	// an external header in the static lib project


Sound soundy;
bool active;
Wave temp;

void GameInit()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitialWidth, InitialHeight, "Example");
    SetTargetFPS(144);

    active = false;

    InitAudioDevice();
     temp = LoadWave("resources/sound.wav");
     soundy = LoadSoundFromWave(temp);

    // load resources
}

void GameCleanup()
{
    // unload resources

    CloseWindow();
}

bool GameUpdate()
{
    
    if (IsMouseButtonDown)
    {
        if (GetMouseX() >= 250 && GetMouseY() >= 250)
        {
            DrawText("YES!!!", 50, 100, 50, GREEN);
        }
        else
        {
            DrawText("NO!!!", 50, 100, 50, RED);
        }
    }


    return true;
}

void GameDraw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawText("Hello Connor!", 10, 10, 20, GetTextColor());

    Texture2D scope = LoadTextureFromImage(LoadImage("resources/Scope.png"));

    Texture2D trump = LoadTextureFromImage(LoadImage("resources/trump.jpg"));
    
    DrawTexture(trump, 250, 250, WHITE);
    DrawTextureEx(scope, { (float)GetMouseX() - scope.width / 2 * 0.33f, (float)GetMouseY() - (scope.height / 2) * 0.33f }, 0, 0.33f, WHITE);
    
   

  /*
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
    }*/
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
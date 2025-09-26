#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#define NOUSER
#define NODRAWTEXT
#define NOBITMAP
#define NOMCX
#define NOSERVICE
#define NOHELP


#include "raylib.h"
#include "raymath.h"

#include "game.h"   // an external header in this project
#include "lib.h"	// an external header in the static lib project



#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"

#include <iostream>

RakNet::RakPeerInterface* peer = nullptr;
Rectangle player1;
Vector2 position;

enum GameMessages {
    ID_GAME_UPDATE = ID_USER_PACKET_ENUM + 1
};

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

bool GameUpdate() {
    position = { 0, 0 };

    if (IsKeyDown(KEY_W)) player1.y -= 1;
    if (IsKeyDown(KEY_A)) player1.x -= 1;
    if (IsKeyDown(KEY_S)) player1.y += 1;
    if (IsKeyDown(KEY_D)) player1.x += 1;

    // Send updated position each frame
    SendPlayerPosition();

    // Handle incoming packets
    HandleNetwork();

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

void StartServer() {
    peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor sd(60000, 0); // Port 60000
    peer->Startup(10, &sd, 1);            // Max 10 clients
    peer->SetMaximumIncomingConnections(10);

    printf("Server started on port 60000\n");
}

void StartClient(const char* serverIP) {
    peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor sd;
    peer->Startup(1, &sd, 1);
    peer->Connect(serverIP, 60000, 0, 0);

    printf("Connecting to server %s:60000\n", serverIP);
}

void HandleNetwork() {
    for (RakNet::Packet* p = peer->Receive(); p; peer->DeallocatePacket(p), p = peer->Receive()) {
        switch (p->data[0]) {
        case ID_CONNECTION_REQUEST_ACCEPTED:
            printf("Connected to server!\n");
            break;
        case ID_NEW_INCOMING_CONNECTION:
            printf("A client has connected.\n");
            break;
        case ID_GAME_UPDATE: {
            // Deserialize player position
            RakNet::BitStream bsIn(p->data, p->length, false);
            bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

            float x, y;
            bsIn.Read(x);
            bsIn.Read(y);

            player1.x = x;
            player1.y = y;
            break;
        }
        default:
            printf("Received message id %d\n", p->data[0]);
            break;
        }
    }
}

void SendPlayerPosition() {
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)ID_GAME_UPDATE);
    bsOut.Write(player1.x);
    bsOut.Write(player1.y);

    peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
        RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

int main() {
    //server setup



    
    char answer;
    std::cout << "client(c) or server(s)\n";
    std::cin >> answer; std::cout << "\n";
    
    if (answer == 'c')
    {
        StartClient("127.0.0.1");
    }
    else
    {
        StartServer();
    }

    GameInit();
    // Run as server
    // StartServer();

    // Or as client (replace with actual server IP)
    

    while (!WindowShouldClose()) {
        if (!GameUpdate())
            break;
        GameDraw();
    }

    GameCleanup();
    RakNet::RakPeerInterface::DestroyInstance(peer);
    return 0;
}
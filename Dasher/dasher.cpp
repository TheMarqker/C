#include "raylib.h"

int main() 
{
    // window dimensions
    // const cannot be changed later
    const int windowWidth{800};
    const int windowHeight{450};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dasher");

    // acceleration due to gravity (pixels/second)/second
    int gravity{ 1'000 }; 

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // nebula X velocity (pixels/second)
    int nebVel{-200};


    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation frame
    int frame{};
    // amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime{};

    // is the rectangle in the air
    bool isInAir{};
    // jump velocity (pixels/second)
    const int jumpVel{-600};

    int velocity{0}; // (pixels/sec)

    SetTargetFPS(60);
    // the same as window should close == false
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height) 
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula position
        nebPos.x += nebVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        if (!isInAir)
        {
        // update running time
        runningTime += dT;
        if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

         // stop drawing
        EndDrawing();
    }
    // unload textures
    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
       
}
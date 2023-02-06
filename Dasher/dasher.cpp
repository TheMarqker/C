#include "raylib.h"

int main() 
{
    // window dimensions
    // const cannot be changed later
    const int windowWidth{800};
    const int windowHeight{450};
    // initialize window
    InitWindow(windowWidth, windowHeight, "Dasher");

    // acceleration due to gravity (pixels/frame)/frame
    int gravity{ 1 }; // (p/f)/f

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    Vector2 scarfyPos;

    //  rectangle dimensions
    const int width{50};
    const int height{80};

    // is the rectangle in the air
    bool isInAir{};
    // jump velocity
    const int jumpVel{-22};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    // the same as window should close == false
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (posY >= windowHeight - height) 
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            //rectangle is in the air
            velocity += gravity;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update Y position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

         // stop drawing
        EndDrawing();
    }
    CloseWindow();
       
}
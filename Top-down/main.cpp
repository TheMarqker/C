#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{

    const int windowWidth{384};
    const int windowHeight{384};
    // start window
    InitWindow(windowWidth, windowHeight, "Top-Down");

    Texture2D map = LoadTexture("nature_tileset/GrasslandsMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};

    Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset/Rock.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        rock.Render(knight.getWorldPos());

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x  < 0.f ||
            knight.getWorldPos().y  < 0.f ||
            knight.getWorldPos().x  + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y  + windowHeight > map.height * mapScale)
            {
                knight.undoMovement();
            }

        EndDrawing();
    }
    CloseWindow();

    UnloadTexture(map);
}
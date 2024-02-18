#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //Vector2 ballPosition = {(float)screenWidth/2, (float)screenHeight/2};
    Camera3D camera = { 0 };
    camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
    SetTargetFPS(60);
    

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) cubePosition.x += 1.0f;
        if (IsKeyDown(KEY_LEFT)) cubePosition.x -= 1.0f;
        if (IsKeyDown(KEY_UP)) cubePosition.z -= 1.0f;
        if (IsKeyDown(KEY_DOWN)) cubePosition.z += 1.0f;
        BeginDrawing();

            ClearBackground(GetColor(0x2e1038FF));
            DrawText("Move Cube Using Arrow Keys", (screenWidth / 4), 40, 20, GetColor(0xe5c7efFF));
            

            BeginMode3D(camera);
   
                //DrawRectangle(100, 100, 100, 100, RED);
                //DrawTriangle((Vector2){200, 100}, (Vector2){250, 75}, (Vector2){100, 100}, BLUE);
                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, GREEN);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKGREEN);
                //DrawSphere((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, BLUE);
                //DrawSphereWires((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, 20, 20, DARKBLUE);
                //DrawCircleV(ballPosition, 50, BLUE);
                DrawGrid(20, 1.0f);

            EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

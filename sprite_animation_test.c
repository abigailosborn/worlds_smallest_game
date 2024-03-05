#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Sprite Animation test");
    
    Vector2 position = {350.0f, 280.0f};

    Texture2D frog = LoadTexture("Pictures/cat.png");
    Rectangle frameRec = {0.0f, 0.0f, (float)frog.width/13, (float)frog.height};
    
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        framesCounter++;
        if(framesCounter >= (60/framesSpeed)){
            framesCounter = 0;
            currentFrame++;
        
            if(currentFrame > 12) currentFrame = 0;
            frameRec.x = (float)currentFrame*(float)frog.width/13;
        }
        
        if(IsKeyPressed(KEY_RIGHT)) framesSpeed++;
        else if(IsKeyPressed(KEY_LEFT)) framesSpeed--;

        if(framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
        else if(framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;

        //Draw everything now 
        BeginDrawing();
            ClearBackground(RAYWHITE);

        DrawTexture(frog, 64, 64, WHITE);
        DrawRectangleLines(64, 64, frog.width, frog.height, LIME);
        DrawRectangleLines(64 + (int)frameRec.x, 64 + (int)frameRec.y, (int)frameRec.width, (int)frameRec.height, RED);
        
        DrawText("Frame Speed", 165, 210, 10, DARKGRAY);
        DrawText(TextFormat("%2i FPS", framesSpeed), 575, 210, 10, DARKGRAY);
        DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED", 290, 240, 10, DARKGRAY);
        
        for(int i =0; i < MAX_FRAME_SPEED; i++){
            if(i < framesSpeed) DrawRectangle(250 + 21*i, 205, 20, 20, RED);
            DrawRectangleLines(250 +21*i, 205, 20, 20, MAROON); 
        }

        DrawTextureRec(frog, frameRec, position, WHITE);
        DrawText("Frog sprite", screenWidth -200, screenHeight -20, 10, GRAY);
        EndDrawing();
    }
    UnloadTexture(frog);
    CloseWindow();

    return 0; 
}

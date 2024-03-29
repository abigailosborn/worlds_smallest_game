#include "raylib.h"
#include <stdint.h>
void wallCollision(Vector3* cubePosition){
    if(cubePosition->x <= -15.0f){
            cubePosition->x += 1;
        }
        if(cubePosition->x >= 15.0f){
            cubePosition->x -= 1;
        }
        if(cubePosition->z <= -15.0f){
            cubePosition->z += 1;
        }        
        if(cubePosition->z >= 15.0f){
            cubePosition->z -= 1;
        }
}
bool checkObjectCollision(Vector3* cubePosition, Vector3* playerSize, Vector3* objPosition, Vector3* objSize){
    if(CheckCollisionBoxes((BoundingBox){(Vector3){cubePosition->x - playerSize->x / 2,
                                                       cubePosition->y - playerSize->y / 2,
                                                       cubePosition->z - playerSize->z / 2},
                                             (Vector3){cubePosition->x + playerSize->z / 2,
                                                       cubePosition->y + playerSize->z / 2,
                                                       cubePosition->z + playerSize->z / 2}},
                              (BoundingBox){(Vector3){objPosition->x - objSize->x / 2,
                                                      objPosition->y - objSize->y / 2,
                                                      objPosition->z - objSize->z / 2},
                                            (Vector3){objPosition->x + objSize->x / 2,
                                                      objPosition->y + objSize->y / 2,
                                                      objPosition->z + objSize->z / 2}})) return true;;
}
void movePlayer(Vector3* cubePosition, int velocity, int cubeJumpHeight){
    
        if (IsKeyDown(KEY_D)) cubePosition->x += velocity;
        if (IsKeyDown(KEY_A)) cubePosition->x -= velocity;
        if (IsKeyDown(KEY_W)) cubePosition->z -= velocity;
        if (IsKeyDown(KEY_S)) cubePosition->z += velocity;
        if (IsKeyDown(KEY_SPACE)) cubePosition->y += cubeJumpHeight;
}
void changeCameraMode(int* cameraMode, Camera3D* camera){ 
        //switch the camera mode
        if(IsKeyPressed(KEY_ONE)) {
            cameraMode = CAMERA_FREE;
            camera->up = (Vector3){0.0f, 1.0f, 0.0f};
        }
        if(IsKeyPressed(KEY_TWO)) {
            cameraMode = CAMERA_FIRST_PERSON;
            camera->up = (Vector3){0.0f, 1.0f, 0.0f};
        }
        if(IsKeyPressed(KEY_THREE)) {
            cameraMode = CAMERA_THIRD_PERSON;
            camera->up = (Vector3){0.0f, 1.0f, 0.0f};
        }
        if(IsKeyPressed(KEY_FOUR)) {
            cameraMode = CAMERA_ORBITAL;
            camera->up = (Vector3){0.0f, 1.0f, 0.0f};
        }
}

int main() {
    //set window width and height
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //Vector2 ballPosition = {(float)screenWidth/2, (float)screenHeight/2};
    //intialize camera x, y, and z positions
    float cx = 0.0f;
    float cy = 0.0f;
    float cz = 0.0f;
    
    //setup initial camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){cx, cy, cz};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    //set camera mode as third person to start, I don't think the mode here actually matters
    int cameraMode = CAMERA_THIRD_PERSON;
    
    //set position and other necesities for the cube 
    Vector3 cubePosition = {0.0f, 1.0f, 0.0f};
    Vector3 playerSize = {2.0f, 2.0f, 2.0f};
    Color playerColor = GetColor(0x004d00FF);
    int cubeJumpHeight = 1.0f;
    int velocity = 1.0f;
    
    Vector3 bonnieBoxPosition = {-8.0f, 2.5f, 8.0f};
    Vector3 bonnieBoxSize = {16.0f, 5.0f, 1.0f};
    
    Vector3 bonnieTwoBoxPosition = {8.0f, 2.5f, -8.0f};
    Vector3 bonnieTwoBoxSize = {16.0f, 5.0f, 1.0f};

    Vector3 cylinderPosition = {-10.0f, 0.0f, 2.0f};
    Vector3 cylinderSize = {2.0f, 2.0f, 2.5f};
    bool collision = false;
    
    //add texture
    Texture2D cubeTexture = LoadTexture("images/cubeTexture.png"); 
    //set the fps
    SetTargetFPS(60);
    

    while (!WindowShouldClose())
    {
        //switch the camera mode
        //if(IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_FOUR)){
          //  changeCameraMode(&cameraMode, &camera);
        //}
        // || IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_FOUR)
       //set starting position to false
       collision = false;
       //camera.projection = CAMERA_ORTHOGRAPHIC;
       if(IsKeyPressed(KEY_ONE)) {
           cameraMode = CAMERA_FREE;
           camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        }
        if(IsKeyPressed(KEY_TWO)) {
            cameraMode = CAMERA_FIRST_PERSON;
            camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        }
        if(IsKeyPressed(KEY_THREE)) {
            cameraMode = CAMERA_THIRD_PERSON;
            camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        }
        if(IsKeyPressed(KEY_FOUR)) {
            cameraMode = CAMERA_ORBITAL;
            camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        }

        //change the camera projection using p 
        if(IsKeyPressed(KEY_P)){
            if(camera.projection == CAMERA_PERSPECTIVE){
                //create isometric view 
                cameraMode = CAMERA_THIRD_PERSON;
                camera.position = (Vector3){0.0f, 2.0f, -100.0f};
                camera.target = (Vector3){0.0f, 2.0f, 0.0f};
                camera.projection = CAMERA_ORTHOGRAPHIC;
                camera.fovy = 20.0f; //near plane width in camera orthographic
                CameraYaw(&camera, -135 * DEG2RAD, true);
                CameraPitch(&camera, -45 * DEG2RAD, true, true, false);
            }
            else if(camera.projection == CAMERA_ORTHOGRAPHIC){
                //Reset to default view
                cameraMode = CAMERA_THIRD_PERSON;
                camera.position = (Vector3){0.0f, 2.0f, 10.0f};
                camera.target = (Vector3){0.0f, 2.0f, 0.0f};
                camera.projection = CAMERA_PERSPECTIVE;
                camera.fovy = 60.0f; //near plane width in camera orthographic
            } 
        }
        //stop player going through wall
        wallCollision(&cubePosition);
        //collision = checkObjectCollision(&cubePosition, &playerSize, &bonnieBoxPosition, &bonnieBoxSize);
        //collision = checkObjectCollision(&cubePosition, &playerSize, &bonnieTwoBoxPosition, &bonnieTwoBoxSize);
        if(checkObjectCollision(&cubePosition, &playerSize, &bonnieBoxPosition, &bonnieBoxSize) 
           || checkObjectCollision(&cubePosition, &playerSize, &bonnieTwoBoxPosition, &bonnieTwoBoxSize)
           || checkObjectCollision(&cubePosition, &playerSize, &cylinderPosition, &cylinderSize)){
            playerColor = RED;
        }
        //if(collision) playerColor = RED;
        else playerColor =  GetColor(0x004d00FF);
        //Pretty self explanatory but this updates the camera
        UpdateCamera(&camera, cameraMode);

        //move the player appropriately for third or first person perspectives
        if(cameraMode == CAMERA_THIRD_PERSON){
            movePlayer(&cubePosition, velocity, cubeJumpHeight);
        }       
        if(cameraMode == CAMERA_FIRST_PERSON){
            if(IsKeyDown(KEY_SPACE)) camera.position.y += 1.0f;
        }
        //woooo time to draw things
        BeginDrawing();
            //set background color
            ClearBackground(GetColor(0x2e1038FF));
            //make text on the screen
            DrawText("Start By Pressing P", (screenWidth / 4), 40, 20, GetColor(0xe5c7efFF));            
            //Turn on 3d mode THINGS IN HERE MUST ONLY BE 3D
            BeginMode3D(camera);
                //The walls and floor
                DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY);
                DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE);
                DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, PINK);
                DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, YELLOW);
                DrawCube((Vector3){0.0f, 2.5f, -16.0f}, 32.0f, 5.0f, 1.0f, RED);

                //TODO: put all objects within the level (including walls) in an array, that way you can iterate over that array
                //to check for object collisions

                //objects and player in the area 
                DrawCube(bonnieTwoBoxPosition, bonnieTwoBoxSize.x, bonnieTwoBoxSize.y, bonnieTwoBoxSize.z, GREEN);
                DrawCubeWires(bonnieTwoBoxPosition, bonnieTwoBoxSize.x, bonnieTwoBoxSize.y, bonnieTwoBoxSize.z, BLACK);
                DrawCube(bonnieBoxPosition, bonnieBoxSize.x, bonnieBoxSize.y, bonnieBoxSize.z, GREEN);
                DrawCubeWires(bonnieBoxPosition, bonnieBoxSize.x, bonnieBoxSize.y, bonnieBoxSize.z, BLACK);
                DrawCylinder(cylinderPosition, cylinderSize.x, cylinderSize.y, cylinderSize.z, 30, GREEN);
                DrawCylinderWires(cylinderPosition, cylinderSize.x, cylinderSize.y, cylinderSize.z, 30, BLACK);
                if(cameraMode == CAMERA_THIRD_PERSON){
                    DrawCube(cubePosition, playerSize.x, playerSize.y, playerSize.z, playerColor);
                    DrawCubeWires(cubePosition, playerSize.x, playerSize.y, playerSize.z, GREEN);
                }
                
                if(cameraMode == CAMERA_FIRST_PERSON){
                    DrawCube(cubePosition, playerSize.x, playerSize.y, playerSize.z, playerColor);
                    DrawCubeWires(cubePosition, playerSize.x, playerSize.y, playerSize.z, GREEN);
                }
                //DrawSphere((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, BLUE);
                //DrawSphereWires((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, 20, 20, DARKBLUE);
                //DrawCircleV(ballPosition, 50, BLUE);
                DrawGrid(32, 1.0f);

            EndMode3D();
            
            //write to the screen what perspective and pov the player is in 
            DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(600, 5, 195, 100, BLUE);

            DrawText("Camera status:", 610, 15, 10, BLACK);
            DrawText(TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" :
                                              (cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                              (cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                              (cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, BLACK);
            DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                    (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);

        EndDrawing();
    }
    
    UnloadTexture(cubeTexture);

    CloseWindow();

    return 0;
}

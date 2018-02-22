/*******************************************************************************************
*
*   raylib [core] example - Initialize 3d camera free
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_STYLE_SAVE_LOAD  // uses image as a style
#include "raygui.h"

#include <stdlib.h>

typedef struct _segment_t {
    unsigned char label[128];
    int verticalPosition;
    int verticalSize;
    bool hot;
} segment_t;

typedef struct _board_t {
    int segmentsCount;
    int interSegmentsMargin;
    segment_t* segments;
} board_t;


const int windowWidth = 800;
const int windowHeight = 450;


void DrawSegment(segment_t segment)
{
    Color color = {128, 128, 128, 128};
    if (segment.hot)
    {
        color.a = 255;
    }
    DrawRectangle( 10, segment.verticalPosition, windowWidth - 20, segment.verticalSize, color);
    DrawText(
        segment.label,
        50,
        segment.verticalPosition + segment.verticalSize/2 - 20/2,
        20,
        BLACK);
}

void DrawBoard(board_t* board)
{
    for (int i = 0; i < board->segmentsCount; ++i)
    {
        DrawSegment(board->segments[i]);
    }
}

void AddToBoard(board_t* board, unsigned char* text)
{
    board->segmentsCount++;
    board->segments = realloc(board->segments, board->segmentsCount * sizeof(segment_t));
    segment_t seg = {
        "...",
        10 + 40*(board->segmentsCount-1) + (board->segmentsCount-1)*board->interSegmentsMargin,
        40,
        false};
    memcpy(seg.label, text, strlen(text));
    board->segments[board->segmentsCount - 1] = seg;
}

void RemoveFromBoard(board_t* board, int index)
{
    memcpy(board->segments[index].label, "mango", strlen("mango"));
}


int main(int argc, char * argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    bool running = true;

    InitWindow(windowWidth, windowHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera camera;
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    GuiLoadStyleImage("rguistyle_default_dark.png");
    Rectangle panel = { 20, windowHeight/2 - 390/2, 200, 390 };

    int hotElement = 0;
    bool checked = false;

    board_t board = {0, 10, 0};
    AddToBoard(&board, "10 pushups");
    AddToBoard(&board, "10s of planking");
    AddToBoard(&board, "test3");
    AddToBoard(&board, "test8");
    AddToBoard(&board, "test9");
    AddToBoard(&board, "test1");
    AddToBoard(&board, "test6");
    board.segments[hotElement].hot = true;
    //--------------------------------------------------------------------------------------


    while (running)
    {
        if (WindowShouldClose())
        {
            running = false;
        }

        // Update
        //----------------------------------------------------------------------------------

        hotElement = (hotElement > 255) ? 255 : hotElement;
        hotElement = (hotElement <   0) ? 0   : hotElement;


        if (IsKeyPressed('J'))
        {
            for (int i = 0; i < board.segmentsCount; ++i)
            {
                board.segments[i].hot = false;
            }
            hotElement++;
            board.segments[hotElement].hot = true;
        }
        if (IsKeyPressed('K'))
        {
            for (int i = 0; i < board.segmentsCount; ++i)
            {
                board.segments[i].hot = false;
            }
            hotElement--;
            board.segments[hotElement].hot = true;
        }
        if (IsKeyPressed(' '))
        {
            RemoveFromBoard(&board, hotElement);
        }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            // GUI
            DrawRectangle( 10, 10, windowWidth - 20, windowHeight - 20, (Color){128, 128, 128, 128});

            checked = GuiCheckBox((Rectangle){20, 20, 20, 20}, checked);

            DrawBoard(&board);

            if(GuiButton((Rectangle){ windowWidth - 80, windowHeight - 80, 70, 30 }, FormatText("EXIT")))
            {
                running = false;
            }

            /*
            DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 133, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);
            */

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

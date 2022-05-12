
/*
    Dice Roller
*/

// includes

// c
#include "stdio.h"
#include "math.h"
#include "time.h"
#include "stdlib.h"

// raylib
#include "raylib.h"

// wlib

// src

// definitions
#define screenWidth 800
#define screenHeight 600
#define screenName "DICE ROLLER"

// mousepos
static Vector2 mousePos;

// dice amount
static int diceAmount = 1;
static int roll;
static int last;

// button boxes
#define boxSize 50
#define buttonSizeWidth 200
#define buttonSizeHeight 100

Rectangle bIncrease = {220, 50, boxSize, boxSize};
Rectangle bDecrease = {70, 50, boxSize, boxSize};

Rectangle bDFour = {50, 200, buttonSizeWidth, buttonSizeHeight};
Rectangle bDSix = {300, 200, buttonSizeWidth, buttonSizeHeight};
Rectangle bDEight = {550, 200, buttonSizeWidth, buttonSizeHeight};

Rectangle bDTen = {50, 400, buttonSizeWidth, buttonSizeHeight};
Rectangle bDTwelve = {300, 400, buttonSizeWidth, buttonSizeHeight};
Rectangle bdTwenty = {550, 400, buttonSizeWidth, buttonSizeHeight};

// bool to control window exit
bool exitWindow;

bool RollDice(int amount, int type)
{
    static int rolled = 0;

    // add all rolls
    for (int i = 0; i < amount; i++)
    {
        rolled += rand() % type + 1;
    }

   // store dice
    last = roll;
    roll = rolled;
    rolled = 0;

    return false;
}

int main(void)
{
    // initialization

    // seed
    srand(time(NULL));

    // debug log
    SetTraceLogLevel(LOG_ERROR);
    // actual window creation, size and name
    InitWindow(screenWidth, screenHeight, screenName);

    SetTargetFPS(60); // target fps

    diceAmount = 1;

    while (!exitWindow)
    {
        if (WindowShouldClose())
        {
            exitWindow = true;
        }
        // update loop
        mousePos = GetMousePosition();

        // watch for click
        // dice amount
        if (CheckCollisionPointRec(mousePos, bIncrease) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            diceAmount++;
        }

        if (CheckCollisionPointRec(mousePos, bDecrease) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (diceAmount != 1)
            {
                diceAmount--;
            }
        }

        // dice type
        if (CheckCollisionPointRec(mousePos, bDFour) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            RollDice(diceAmount, 4);
        }

        if (CheckCollisionPointRec(mousePos, bDSix) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            RollDice(diceAmount, 6);
        }

        if (CheckCollisionPointRec(mousePos, bDEight) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            RollDice(diceAmount, 8);
        }

        if (CheckCollisionPointRec(mousePos, bDTen) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            RollDice(diceAmount, 10);
        }

        if (CheckCollisionPointRec(mousePos, bDTwelve) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            RollDice(diceAmount, 12);
        }

        if (CheckCollisionPointRec(mousePos, bdTwenty) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            RollDice(diceAmount, 20);
        }     

        // draw loop
        BeginDrawing();

        // background colour
        ClearBackground(BLACK);

        // Draw Roll and dice amount
        DrawText(TextFormat("ROLL: %i", roll), 500, 70, 50, WHITE);
        DrawText(TextFormat("LAST: %i", last), 500, 30, 50, WHITE);
        DrawText(TextFormat("%i", diceAmount), 150, 50, 50, WHITE);

        // buttons
        // increase
        DrawRectangle(bDecrease.x, bDecrease.y, bDecrease.width, bDecrease.height, WHITE);
        DrawText("<", 85, 45, 70, BLACK);

        // decrease
        DrawRectangle(bIncrease.x, bIncrease.y, bIncrease.width, bIncrease.height, WHITE);
        DrawText(">", 240, 45, 70, BLACK);
        // d4
        DrawRectangle(bDFour.x, bDFour.y, bDFour.width, bDFour.height, WHITE);
        DrawText("D4", 100, 230, 80, BLACK);

        // d6
        DrawRectangle(bDSix.x, bDSix.y, bDSix.width, bDSix.height, WHITE);
        DrawText("D6", 350, 230, 80, BLACK);

        // d8
        DrawRectangle(bDEight.x, bDEight.y, bDEight.width, bDEight.height, WHITE);
        DrawText("D8", 600, 230, 80, BLACK);

        // d10
        DrawRectangle(bDTen.x, bDTen.y, bDTen.width, bDTen.height, WHITE);
        DrawText("D10", 80, 410, 80, BLACK);

        // d12
        DrawRectangle(bDTwelve.x, bDTwelve.y, bDTwelve.width, bDTwelve.height, WHITE);
        DrawText("D12", 340, 410, 80, BLACK);

        // d20
        DrawRectangle(bdTwenty.x, bdTwenty.y, bdTwenty.width, bdTwenty.height, WHITE);
        DrawText("D20", 580, 410, 80, BLACK);

        EndDrawing();
    }

    // De initialization
    CloseWindow();

    return 0;
}
/*
    ASTEROIDS

    VVonder
*/

// includes

// c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// raylib
#include <raylib.h>

// wlib
#include "wlib/timer.h"

// definitions
#define screenWidth 800
#define screenHeight 600
#define screenName "Asteroids"
#define maxFps 60

// GAMESTATE
typedef enum mainState
{
    Splash,
    Title,
    Game,
    Score,
    End
} mainState;

mainState currentState;

enum cursorPos
{
    start,
    score,
    quit
};

static int cursorPt = 0;

struct player
{
    int score;
    int lives;
    Vector2 pos;
    Vector2 dest;
    Vector2 speed;
    Vector2 maxSpeed;
    int velocity;
    int rotate;
    int rSpeed;
    bool invinc;
};
struct player player;

// bool to control window exit
bool exitWindow;

bool StartGame()
{
    // assign stats
    player.score = 0;
    player.lives = 3;
    player.pos.x = 200;
    player.pos.y = 400;
    player.dest.x = 0;
    player.dest.y = 0;
    player.speed.x = 0;
    player.speed.y = 0;
    player.maxSpeed.x = 4;
    player.maxSpeed.y = 4;
    player.velocity  = 0;
    player.rotate = 0;
    player.rSpeed = 0;
    player.invinc = false;

    // switch game
    currentState = Game;
    return false;
}
/*
https://byjus.com/physics/velocity-vectors/
*/


bool VelocityDeterminer()
{
    player.velocity = sqrtf(pow(player.speed.x,2)) + sqrtf(pow(player.speed.y,2));
    player.rotate = tanhf(player.speed.y / player.speed.x);

    return false;
}


bool SplashControl()
{
    currentState = Title;

    return false;
}

bool cursorControl(bool add)
{
    if (add)
    {
        if (cursorPt == quit)
        {
            cursorPt = start;
        }
        else
        {
            cursorPt++;
        }
    }
    else
    {
        if (cursorPt == start)
        {
            cursorPt = quit;
        }
        else
        {
            cursorPt--;
        }
    }

    return false;
}

int main(void)
{
    // initialization

    // debug log
    SetTraceLogLevel(LOG_ERROR);
    // actual window creation, size and name
    InitWindow(screenWidth, screenHeight, screenName);

    SetTargetFPS(60); // target fps

    printf("test");

    Rectangle playerCol = {player.pos.x, player.pos.y, 32, 32};

    // TEXTURES
    Texture2D splashImg = LoadTexture("assets/Splash.png");
    Texture2D ship = LoadTexture("assets/ship.png");


    currentState = Splash;

    while (!exitWindow)
    {
        if (WindowShouldClose())
        {
            exitWindow = true;
        }

        // update loop
        switch (currentState)
        {
        case Splash:
            StopWatch(maxFps, 2, &SplashControl);
            break;
        case Title:
            // cursor control
            if (IsKeyReleased(KEY_DOWN))
            {
                cursorControl(true);
            }
            if (IsKeyReleased(KEY_UP))
            {
                cursorControl(false);
            }
            //
            if (IsKeyReleased(KEY_ENTER))
            {
                if (cursorPt == start)
                {
                    StartGame();
                }
                else if (cursorPt == score)
                {
                    currentState = Score;
                }
                else
                {
                    exitWindow = true;
                }
            }
            break;
        case Game:
            break;
        case Score:
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = Title;
            }
            break;
        case End:
            break;
        }

        // draw loop
        BeginDrawing();
        switch (currentState)
        {
        case Splash:
            // SPLASHY
            DrawTexture(splashImg, 0, 0, WHITE);
            DrawText("SPLASH", screenWidth / 3.5, screenHeight / 2, 30, WHITE);
            break;
        case Title:
            // SPLASHY
            DrawTexture(splashImg, 0, 0, WHITE);
            // TITLE
            DrawText("ASTEROIDS!", 205, 10, 60, WHITE);
            DrawText("PRESENTED, BY INDIANA-GRD", screenWidth / 3.5, 60, 20, WHITE);
            // MENU
            DrawText("START", 360, 260, 50, WHITE);
            DrawText("SCORE", 360, 320, 50, WHITE);
            DrawText("QUIT", 360, 380, 50, WHITE);
            // CURSOR
            if (cursorPt == start)
            {
                DrawText(">", 320, 248, 80, WHITE);
            }
            else if (cursorPt == score)
            {
                DrawText(">", 320, 308, 80, WHITE);
            }
            else
            {
                DrawText(">", 320, 368, 80, WHITE);
            }
            break;
        case Game:
            // SPLASHY
            DrawTexture(splashImg, 0, 0, WHITE);
            // score
            DrawText(TextFormat("SCORE: %i", player.score), 10, 10, 30, WHITE);
            // player
            DrawTexture(ship, player.pos.x, player.pos.y, WHITE);
            DrawRectanglePro(playerCol, player.pos, player.rotate, PINK);
            
            break;
        case Score:
            // SPLASHY
            DrawTexture(splashImg, 0, 0, WHITE);
            DrawText("Score", 340, 10, 60, WHITE);

            break;
        case End:
            DrawText("GAME OVER", screenWidth / 3.5, screenHeight / 2, 30, WHITE);
            break;
        }
        // background colour
        ClearBackground(BLACK);
        // test text

        EndDrawing();
    }

    // De initialization
    CloseWindow();

    return 0;
}
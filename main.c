/* 
    PROJECT DOCS
*/


// includes

// c 
#include "stdio.h"

// raylib
#include "raylib.h"

// wlib

// src


// definitions
#define screenWidth 800
#define screenHeight 1000
#define screenName "BLACK HACK GAMING PRROTOTYPE"
#define MAX_INPUT_CHARS 12
#define MAX_INPUT_STATS 3
#define _x_text 240
#define _y_text 130
#define _sz_text 10
#define _x_stat 100
#define _y_strn 160 + 80
#define _y_dex 200 + 80
#define _y_con 240 + 80
#define _y_int 280 + 80
#define _y_wis 320 + 80
#define _y_cha 360 + 80
#define _text_size 20
#define _y_h_es 440
#define _x_hd 100
#define _x_hp 240
// window size

// bool to control window exit
bool exitWindow;


// initialize mouse position
static Vector2 mousePos;

//stat names
#define strgView "STR"
#define dextView "DEX"
#define consView "CON"
#define inteView "INT"
#define wiseView "WIS"
#define chamView "CHR"


// buttons
Rectangle button = {20, 180, 120, 30};

Rectangle buttonPower = {20, 350, 120, 40};

Rectangle buttonAuto = {150, 350, 120, 40};

int main(void)
{
    // initialization
    //---------------------------------------------------
    char namePlayer[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;

    //stats
    char strengthSet[3] = "\0";
    int letterCountStr = 0;
    char dexteritySet[3] = "\0";
    char constitutionSet[3] = "\0";
    char intelligenceSet[3] = "\0";
    char wisdomSet[3] = "\0";



    //naming
    Rectangle textBox = { screenWidth/2.0f - 250, 180, 270, 20};
    //stats
    Rectangle strBox = { _x_stat + 50, _y_strn, 30, 20};
    Rectangle dexBox = { _x_stat + 50, _y_dex, 30, 20};
    Rectangle conBox = { _x_stat + 50, _y_con, 30, 20};
    Rectangle intBox = { _x_stat + 50, _y_int, 30, 20};
    Rectangle wisBox = { _x_stat + 50, _y_wis, 30, 20};
    //dice wierd thing
    Rectangle hdBox = { _x_stat + 50, _y_h_es, 30, 20};
    Rectangle hpBox = { _x_stat + 140 + 50, _y_h_es, 30, 20};


    bool mouseOnStr = false;
    bool mouseOnText = false;

    int framesCounter = 0;
    SetTargetFPS(10);
    // debug log
    SetTraceLogLevel(LOG_ERROR);
    // actual window creation, size and name
    InitWindow(screenWidth, screenHeight, screenName);

    SetTargetFPS(60); // target fps

    printf("test");

    while (!exitWindow)
    {

        if (WindowShouldClose())
        {

            exitWindow = true;

        }
        // update loop
        //------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;
        if (CheckCollisionPointRec(GetMousePosition(), strBox)) mouseOnStr = true;
        else mouseOnStr = false;

        if (mouseOnStr)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
                        //Get char pressed (unicode character) on the queue
            int keyStr = GetCharPressed();

            //check if more characters have been pressed on the same frame
            while (keyStr > 0)
            {
                    //NOTE: Only allow keys in range [32..125]
                    if ((keyStr>= 32) && (keyStr <= 125) && (letterCountStr < MAX_INPUT_STATS))
                    {
                        strengthSet[letterCountStr] = (char)keyStr;
                        strengthSet[letterCountStr+1] = '\0';
                        letterCountStr++;
                    }

                    keyStr = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCountStr--;
                    if (letterCountStr < 0) letterCountStr = 0;
                    strengthSet[letterCountStr] = '\0';
                }
        }


        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            //Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            //check if more characters have been pressed on the same frame
            while (key > 0)
            {
                //NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    namePlayer[letterCount] = (char)key;
                    namePlayer[letterCount+1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                namePlayer[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        // get mouse position
        mousePos = GetMousePosition();


        // draw loop
        BeginDrawing();
            // background colour
            ClearBackground(BLACK);
            // test text
            DrawText("BLACK HACK", screenWidth / 3.5, screenHeight / 15, 50, WHITE);
            //DrawText("NAME YOUR CHARACTER!",_x_text,_y_text,_sz_text,GRAY);
            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(namePlayer, (int)textBox.x + 5, (int)textBox.y, 20, MAROON);

            //DrawText(TextFormat("CHAR CAP: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    //Draw a blinking curser
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(namePlayer, 20), (int)textBox.y + 4, 20, MAROON);
                }
                else DrawText("Pres BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }
        

            DrawRectangle(button.x, button.y, button.width, button.height, DARKGRAY);
            DrawText("MY NAME:", (button.x + 3), (button.y + 10), 20, LIGHTGRAY);

            //Draw the boxes for stats
            DrawRectangleRec(strBox, LIGHTGRAY);
            DrawText(strengthSet, (int)strBox.x + 3, (int)strBox.y, 20, MAROON);
            DrawRectangleRec(dexBox, LIGHTGRAY);
            DrawRectangleRec(conBox, LIGHTGRAY);
            DrawRectangleRec(intBox, LIGHTGRAY);
            DrawRectangleRec(wisBox, LIGHTGRAY);

            //Draw the hit suff boxes
            DrawRectangleRec(hdBox, LIGHTGRAY);
            DrawRectangleRec(hpBox, LIGHTGRAY);



            //Draw the text of stat naming.
            DrawText(strgView, _x_stat, _y_strn, _text_size, WHITE);
            DrawText(dextView, _x_stat, _y_dex, _text_size, WHITE);
            DrawText(consView, _x_stat, _y_con, _text_size, WHITE);
            DrawText(inteView, _x_stat, _y_int, _text_size, WHITE);
            DrawText(wiseView, _x_stat, _y_wis, _text_size, WHITE);

            //Draw the hit stuff
            DrawText("HD", _x_hd, _y_h_es, _text_size, WHITE);
            DrawText("HP", _x_hp, _y_h_es, _text_size, WHITE);


            ShowCursor();



        EndDrawing();
    }

    // De initialization
    CloseWindow();

    return 0;
}

// Check if any key is pressed
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
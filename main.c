
/* 
    PROJECT DOCS
*/


// includes

// c 
#include "stdio.h"
#include "math.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"

// raylib
#include "raylib.h"

// wlib

// src


// dice amount
static int diceAmount = 1;
static int roll;
static int last;

// button boxes
#define boxSize 50
#define buttonSizeWidth 100
#define buttonSizeHeight 50

Rectangle bIncrease = {220, 50, boxSize, boxSize};
Rectangle bDecrease = {70, 50, boxSize, boxSize};

Rectangle rollStats = {500, 150, buttonSizeWidth, buttonSizeHeight};

Rectangle bDFour = {50, 200, buttonSizeWidth, buttonSizeHeight};
Rectangle bDSix = {300, 200, buttonSizeWidth, buttonSizeHeight};
Rectangle bDEight = {550, 200, buttonSizeWidth, buttonSizeHeight};

Rectangle bDTen = {50, 400, buttonSizeWidth, buttonSizeHeight};
Rectangle bDTwelve = {300, 400, buttonSizeWidth, buttonSizeHeight};
Rectangle bdTwenty = {550, 400, buttonSizeWidth, buttonSizeHeight};

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
#define _y_h_es 480
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

int statsListing[5];
int hitD;

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

bool RollStats(void)
{
    int amount;
    for ( int i = 0; i < 6; i++ )
    {
        RollDice(3, 6);
        amount = roll;
        statsListing[i] = amount;
        printf("stats: %d = %d\n", i, statsListing[i]);
    }
    return false;
}

bool RollHitDice(void)
{
    int amountHD;
    printf("%i \n", roll);
    RollDice(1,6);
    printf("%i \n", roll);

    amountHD = roll;
    hitD = amountHD + 2;
    return false;
}

typedef enum State { LOGO = 0, TITLE, GAMEPLAY, ENDING } State;
State currentState = GAMEPLAY;

int main(void)
{
    // initialization
    //---------------------------------------------------
    char namePlayer[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;

    //stats
    //int strengthSet = 0;
    // int dexteritySet = 0;
    // int constitutionSet = 0;bool RollDice(int amount, int type, int *statsListing)
            bool declareStatCounts = false;
            bool exchangeStats = false;
            bool midStatsEx = false;
            int tempStatSet1, tempStatSet2;
            int tempSwapStat1, tempSwapStat2;
            int rollHD = 0;
    // int intelligenceSet = 0;
    // int wisdomSet = 0;
    srand(time(NULL));

    //naming
    Rectangle textBox = { screenWidth/2.0f - 250, 180, 270, 20};
    //stats
    Rectangle strBox = { _x_stat + 50, _y_strn, 30, 20};
    Rectangle dexBox = { _x_stat + 50, _y_dex, 30, 20};
    Rectangle conBox = { _x_stat + 50, _y_con, 30, 20};
    Rectangle intBox = { _x_stat + 50, _y_int, 30, 20};
    Rectangle wisBox = { _x_stat + 50, _y_wis, 30, 20};
    Rectangle chaBox = { _x_stat + 50, _y_cha, 30, 20};
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
        switch(currentState)
        {
            case GAMEPLAY:
            {
                // update loop
                //------------------------
                if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
                else mouseOnText = false;


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

                // dice type rolling thingy for stuff
                    if (CheckCollisionPointRec(mousePos, rollStats) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        printf("\nHIT D%i \n", rollHD);
                        if (rollHD == 1)
                        {
                            RollHitDice();
                            rollHD = 2;
                            printf("HITD");
                        }
                        if (declareStatCounts == false && rollHD == 0)
                        {
                            RollStats();
                            printf("REDO!");
                            declareStatCounts = true;
                        } 
                    }
                if (exchangeStats == false && declareStatCounts && rollHD == 0)
                {
                    if (CheckCollisionPointRec(mousePos, strBox) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        if (!midStatsEx)
                        {
                            tempStatSet1 = statsListing[0];
                            tempSwapStat1 = 0;
                            midStatsEx = true;
                        }
                        else 
                        {
                            tempStatSet2 = statsListing[0];
                            statsListing[0] = tempStatSet1;
                            statsListing[tempSwapStat1] = tempStatSet2;
                            exchangeStats = true;
                        }
                    }
                    if (CheckCollisionPointRec(mousePos, dexBox) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        if (!midStatsEx)
                        {
                            tempStatSet1 = statsListing[1];
                            tempSwapStat1 = 1;
                            midStatsEx = true;
                        }
                        else 
                        {
                            tempStatSet2 = statsListing[1];
                            statsListing[1] = tempStatSet1;
                            statsListing[tempSwapStat1] = tempStatSet2;
                            exchangeStats = true;
                        }
                    }
                    if (CheckCollisionPointRec(mousePos, conBox) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        if (!midStatsEx)
                        {
                            tempStatSet1 = statsListing[2];
                            tempSwapStat1 = 2;
                            midStatsEx = true;
                        }
                        else 
                        {
                            tempStatSet2 = statsListing[2];
                            statsListing[2] = tempStatSet1;
                            statsListing[tempSwapStat1] = tempStatSet2;
                            exchangeStats = true;
                        }
                    }
                    if (CheckCollisionPointRec(mousePos, intBox) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        if (!midStatsEx)
                        {
                            tempStatSet1 = statsListing[3];
                            tempSwapStat1 = 3;
                            midStatsEx = true;
                        }
                        else 
                        {
                            tempStatSet2 = statsListing[3];
                            statsListing[3] = tempStatSet1;
                            statsListing[tempSwapStat1] = tempStatSet2;
                            exchangeStats = true;
                        }
                    }
                    if (CheckCollisionPointRec(mousePos, wisBox) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        if (!midStatsEx)
                        {
                            tempStatSet1 = statsListing[4];
                            tempSwapStat1 = 4;
                            midStatsEx = true;
                        }
                        else 
                        {
                            tempStatSet2 = statsListing[4];
                            statsListing[4] = tempStatSet1;
                            statsListing[tempSwapStat1] = tempStatSet2;
                            exchangeStats = true;
                        }
                    }
                    if (CheckCollisionPointRec(mousePos, chaBox) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        if (!midStatsEx)
                        {
                            tempStatSet1 = statsListing[5];
                            tempSwapStat1 = 5;
                            midStatsEx = true;
                        }
                        else 
                        {
                            tempStatSet2 = statsListing[5];
                            statsListing[5] = tempStatSet1;
                            statsListing[tempSwapStat1] = tempStatSet2;
                            exchangeStats = true;
                        }
                    }
                }
                if (exchangeStats && rollHD == 0) rollHD = 1;

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
                    
                    //rolling thingy
                    DrawRectangle(rollStats.x, rollStats.y, buttonSizeWidth, buttonSizeHeight, DARKGRAY);
                    DrawText("ROLL", rollStats.x + 23, rollStats.y + 15, 20, LIGHTGRAY);

                    DrawRectangle(button.x, button.y, button.width, button.height, DARKGRAY);
                    DrawText("MY NAME:", (button.x + 3), (button.y + 10), 20, LIGHTGRAY);

                    //Draw the boxes for stats
                    DrawRectangleRec(strBox, LIGHTGRAY);
                    //sprintf(mystr, "%d", num); 
                    ///char *12  itoa ( int val, char * str, int base );

                    DrawText(TextFormat("%i", statsListing[0]), (int)strBox.x + 3, (int)strBox.y, 20, MAROON);
                    DrawRectangleRec(dexBox, LIGHTGRAY);
                    DrawText(TextFormat("%i", statsListing[1]), (int)dexBox.x + 3, (int)dexBox.y, 20, MAROON);
                    DrawRectangleRec(conBox, LIGHTGRAY);
                    DrawText(TextFormat("%i", statsListing[2]), (int)conBox.x + 3, (int)conBox.y, 20, MAROON);
                    DrawRectangleRec(intBox, LIGHTGRAY);
                    DrawText(TextFormat("%i", statsListing[3]), (int)intBox.x + 3, (int)intBox.y, 20, MAROON);
                    DrawRectangleRec(wisBox, LIGHTGRAY);
                    DrawText(TextFormat("%i", statsListing[4]), (int)wisBox.x + 3, (int)wisBox.y, 20, MAROON);
                    DrawRectangleRec(chaBox, LIGHTGRAY);
                    DrawText(TextFormat("%i", statsListing[5]), (int)chaBox.x + 3, (int)chaBox.y, 20, MAROON);

                    //exchange draw stuff
                    if (exchangeStats == false && declareStatCounts == true)
                    {
                        DrawText("CLICK A STAT TO EXCHANGE WITH ANOTHER...", 300,300,20,LIGHTGRAY);
                        if (midStatsEx)
                        {
                            DrawText("NOW CHOOSE ANOTHER...", 300,350,20,LIGHTGRAY);
                        }
                    }


                    //Draw the hit suff boxes
                    DrawRectangleRec(hdBox, LIGHTGRAY);
                    DrawRectangleRec(hpBox, LIGHTGRAY);
                    DrawText(TextFormat("%i", hitD), hpBox.x + 3, hpBox.y, 20, MAROON);



                    //Draw the text of stat naming.
                    DrawText(strgView, _x_stat, _y_strn, _text_size, WHITE);
                    DrawText(dextView, _x_stat, _y_dex, _text_size, WHITE);
                    DrawText(consView, _x_stat, _y_con, _text_size, WHITE);
                    DrawText(inteView, _x_stat, _y_int, _text_size, WHITE);
                    DrawText(wiseView, _x_stat, _y_wis, _text_size, WHITE);
                    DrawText(chamView, _x_stat, _y_cha, _text_size, WHITE);

                    //Draw the hit stuff
                    DrawText("HD", _x_hd, _y_h_es, _text_size, WHITE);
                    DrawText("HP", _x_hp, _y_h_es, _text_size, WHITE);
            }break;
        }

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
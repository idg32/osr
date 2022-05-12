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

 int statsListing[5];

bool RollDice(int amount, int type, int *statsListing)
{
    int i, k;
    for ( i = 0; i < 5; i++ )
    {
        for ( k = 0; k < 2; k++ )
        {
            amount += (rand() % 6) + 1;
            statsListing[i] = amount;
        }
        amount = 0;
    }
    printf(" D6 is is %d \n", amount);
    return false;
}

int main(void)
{
    // initialization
    //---------------------------------------------------
    char namePlayer[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;

    //stats
    //int strengthSet = 0;
    int indexStat = 0;
    // int dexteritySet = 0;
    // int constitutionSet = 0;bool RollDice(int amount, int type, int *statsListing)

    // int intelligenceSet = 0;
    // int wisdomSet = 0;
    srand(time(NULL));
    int statsListing[] = {1,1,1,1,1};

    char mystr[30];
    char mystr2[30];
    char mystr3[30];
    char mystr4[30];
    char mystr5[30];

    sprintf ( mystr,"%i", statsListing[0]);
    sprintf ( mystr2,"%i", statsListing[1]);
    sprintf ( mystr3,"%i", statsListing[2]);
    sprintf ( mystr4,"%i", statsListing[3]);
    sprintf ( mystr5,"%i", statsListing[4]);



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
        bool declareStatCounts = false;


        // dice type
            if (CheckCollisionPointRec(mousePos, rollStats) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                declareStatCounts = true;
                printf(" Intersection is %d \n", declareStatCounts);
            }
            else declareStatCounts = false;


            if (declareStatCounts == true)
            {
                 RollDice(3, 2,statsListing);
                sprintf ( mystr,"%i", statsListing[0]);
                sprintf ( mystr2,"%i", statsListing[1]);
                sprintf ( mystr3,"%i", statsListing[2]);
                sprintf ( mystr4,"%i", statsListing[3]);
                sprintf ( mystr5,"%i", statsListing[4]);
                printf("%s \n", mystr2);
                declareStatCounts = false;
            }  

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
        
            
        // buttons
        // // increase
        // DrawRectangle(bDecrease.x, bDecrease.y, bDecrease.width, bDecrease.height, WHITE);
        // DrawText("<", 85, 45, 70, BLACK);

        // // decrease
        // DrawRectangle(bIncrease.x, bIncrease.y, bIncrease.width, bIncrease.height, WHITE);
        // DrawText(">", 240, 45, 70, BLACK);
        // // d4
        // DrawRectangle(bDFour.x, bDFour.y, bDFour.width, bDFour.height, WHITE);
        // DrawText("D4", 100, 230, 80, BLACK);

        // // d6
        // DrawRectangle(bDSix.x, bDSix.y, bDSix.width, bDSix.height, WHITE);
        // DrawText("D6", 350, 230, 80, BLACK);

        // // d8
        // DrawRectangle(bDEight.x, bDEight.y, bDEight.width, bDEight.height, WHITE);
        // DrawText("D8", 600, 230, 80, BLACK);

        // // d10
        // DrawRectangle(bDTen.x, bDTen.y, bDTen.width, bDTen.height, WHITE);
        // DrawText("D10", 80, 410, 80, BLACK);

        // // d12
        // DrawRectangle(bDTwelve.x, bDTwelve.y, bDTwelve.width, bDTwelve.height, WHITE);
        // DrawText("D12", 340, 410, 80, BLACK);

        // // d20
        // DrawRectangle(bdTwenty.x, bdTwenty.y, bdTwenty.width, bdTwenty.height, WHITE);
        // DrawText("D20", 580, 410, 80, BLACK);
            
            DrawRectangle(rollStats.x, rollStats.y, buttonSizeWidth, buttonSizeHeight, DARKGRAY);

            DrawRectangle(button.x, button.y, button.width, button.height, DARKGRAY);
            DrawText("MY NAME:", (button.x + 3), (button.y + 10), 20, LIGHTGRAY);

            //Draw the boxes for stats
            DrawRectangleRec(strBox, LIGHTGRAY);
            //sprintf(mystr, "%d", num); 
            ///char *12  itoa ( int val, char * str, int base );



                sprintf ( mystr,"%i", statsListing[0]);
                sprintf ( mystr2,"%i", statsListing[1]);
                sprintf ( mystr3,"%i", statsListing[2]);
                sprintf ( mystr4,"%i", statsListing[3]);
                sprintf ( mystr5,"%i", statsListing[4]);

            DrawText(mystr, (int)strBox.x + 3, (int)strBox.y, 20, MAROON);
            DrawRectangleRec(dexBox, LIGHTGRAY);
            DrawText(mystr2, (int)dexBox.x + 3, (int)dexBox.y, 20, MAROON);
            DrawRectangleRec(conBox, LIGHTGRAY);
            DrawText(mystr3, (int)conBox.x + 3, (int)conBox.y, 20, MAROON);
            DrawRectangleRec(intBox, LIGHTGRAY);
            DrawText(mystr4, (int)intBox.x + 3, (int)intBox.y, 20, MAROON);
            DrawRectangleRec(wisBox, LIGHTGRAY);
            DrawText(mystr5, (int)wisBox.x + 3, (int)wisBox.y, 20, MAROON);


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
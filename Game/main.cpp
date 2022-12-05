#include "raylib.h"
#include "logic.h"
#include "raymath.h"
#include <ctime>
#include <cstdlib>
using namespace std;
//------------------------------------------------------------------------------------------
// Types and Structures Definition
//-----------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
//GameScreen currentScreen = LOGO;
static const int screenWidth = 1920;
static const int screenHeight = 1080;

//static GameScreen transition = UNKNOWN;

/* bool collision(int playerRadius, int aiRaidius, float* playerVector, float* aiVector) {
    if (fabs(aiVector[0] - playerVector[0]) <= playerRadius + aiRaidius && fabs(aiVector[1] - playerVector[1]) <= playerRadius + aiRaidius) {
        return true;
    }
    return false;
} */


//currentScreen = LOGO;
Font font = { 0 };
Music music = { 0 };
Sound fxScary = { 0 };

//stuff for transtion screen
static void changeScreen(int screen);     // Change to screen, no transition effect
static void transistion(int screen); // Request transition to next screen
static void updateScreen(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)
static void UpdateDrawFrame(void);          // Update and draw one frame
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Rectangle screen = {0, 0, screenWidth, screenHeight};
    InitWindow(screenWidth, screenHeight, "Zom-beez");
    GameScreen currentScreen = LOGO;
    //InitLogoScreen();
    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0; 
    int enemyframesCounter = 0;
    // Useful to count frames
    //Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------
       
    // Load texture
    int currentFrame = 0;
    int enemycurrentFrame = 0;
    //background
    float scrollingBack = 0.0f;
    Texture2D Graveyard = LoadTexture("gravesnew_1_4.png");
    if (scrollingBack <= -Graveyard.width * 2) scrollingBack = 0;
    //lolz
    Texture2D background = LoadTexture("Ending.jpeg");
    //Enemy Texture
    int enemyframesSpeed = 8;
    Texture2D enemy = LoadTexture("deadScarfy.png");
    //int framesCounter = 0;
    int framesSpeed =8;
    Texture2D hero = LoadTexture("scarfy.png");

    //dimensions of HAzmat
    Rectangle hazmatRec;
    hazmatRec.width = hero.width / 6; //because of frames
    hazmatRec.height = hero.height;
    hazmatRec.x = 0;
    hazmatRec.y = 0;
        //position of hero
    Vector2 heroPos;
    heroPos.x = screenWidth / 2 - hazmatRec.width / 2;
    heroPos.y = screenHeight / 2 - hazmatRec.height / 2;


    ////dimensions of ENEMY
    Rectangle enemyRec;
    enemyRec.width = enemy.width / 6; //because of frames
    enemyRec.height = enemy.height;
    enemyRec.x = 0;
    enemyRec.y = 0;
    //position of ENEMY
    Vector2 enemyPos;
    enemyPos.x = screenWidth / 8 - enemyRec.width / 8;
    enemyPos.y = screenHeight / 8 - enemyRec.height / 8;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //UpdateDrawFrame();
        //----------------------------------------------------------------------------------
        switch (currentScreen)
        {
        case LOGO:
        {
            // TODO: Update LOGO screen variables here!

            framesCounter++;    // Count frames

            // Wait for 2 seconds (120 frames) before jumping to TITLE screen
            if (framesCounter > 120)
            {
                //InitTitleScreen();
                currentScreen = TITLE;
            }
        } break;
        case TITLE:
        {
            // TODO: Update TITLE screen variables here!

            // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                //InitTitleScreen();
                currentScreen = GAMEPLAY;
            }
        } break;
        case GAMEPLAY:
        {
            DrawTexture(Graveyard, 0, 0, WHITE);
            //currentScreen = GAMEPLAY;
            // TODO: Update GAMEPLAY screen variables here!
            enemyframesCounter++;
            framesCounter++;
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 5) currentFrame = 0;

                hazmatRec.x = currentFrame * hero.width / 6;
            }
            if (enemyframesCounter >= (60 / enemyframesSpeed))
            {
                enemyframesCounter = 0;
                enemycurrentFrame++;

                if (enemycurrentFrame > 5) enemycurrentFrame = 0;

                enemyRec.x = enemycurrentFrame * enemy.width / 6;
            }
            DrawTextureRec(hero, hazmatRec, heroPos, WHITE);
            DrawTextureRec(enemy, enemyRec, enemyPos, WHITE);
            
            //COLLISION DETECTION
            float x[2] = { enemyPos.x, enemyPos.y };
            float y[2] = { heroPos.x, heroPos.y };
            if (collision(10, 10, x, y)) {
                currentScreen = ENDING;
            }
            //COLLISION DETECTION

            // Press enter to change to ENDING screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = ENDING;
            }
            if (IsKeyDown(KEY_D)) {
                heroPos.x += 4.0f;
                heroPos.x += 4.0f;
                hero.width = abs(hero.width);
            }
            if (IsKeyDown(KEY_A)) {
                heroPos.x -= 4.0f;
                if (hero.width > 0) {
                    hero.width *= -1;
                }
            }
            if (IsKeyDown(KEY_W)) heroPos.y -= 4.0f;
            if (IsKeyDown(KEY_S)) heroPos.y += 4.0f;

            //  BeginDrawing();

            srand(time(0));
            int iRand = (rand() % 11) + 1;
          
            int towardsPlayer = (rand() % 2);
            float aiSpeed = 4.5f;


            if (towardsPlayer == 0) {
                if (enemyPos.x <= heroPos.x) {
                    enemyPos.x += aiSpeed;
                    enemy.width = abs(enemy.width);
                }

                else {
                    enemyPos.x -= aiSpeed;
                    if (enemy.width > 0) {
                        enemy.width *= -1;
                    }
                }
                if (iRand == 2 || iRand == 8 || iRand == 12 && enemyPos.y <= heroPos.y)
                    enemyPos.y -= aiSpeed;
                else if (iRand == 9 || iRand == 10 || iRand == 0 && enemyPos.y <= heroPos.y)
                    enemyPos.y += aiSpeed;
            }
            else {
                if (enemyPos.y <= heroPos.y)
                    enemyPos.y += aiSpeed;
                else
                    enemyPos.y -= aiSpeed;
                if (iRand == 4 || iRand == 1 || iRand == 6 && enemyPos.x <= heroPos.x) {
                    enemyPos.x += aiSpeed;
                    enemy.width = abs(enemy.width);
                }
                else if (iRand == 11 || iRand == 5 || iRand == 3 && enemyPos.x <= heroPos.x) {
                    enemyPos.x -= aiSpeed;
                    if (enemy.width > 0) {
                        enemy.width *= -1;
                    }
                }
            }
            



            if (enemyPos.x > screenWidth) {
                enemyPos.x = screenWidth;
            }
            else if (enemyPos.x < 0) {
                enemyPos.x = 0;
            }

            if (enemyPos.y > screenHeight) {
                enemyPos.y = screenHeight;
            }
            else if (enemyPos.y < 0) {
                enemyPos.y = 0;
            }

            ClearBackground(RAYWHITE);
            //DrawTextureRec(hero, hazmatRec, heroPos, WHITE);
            //DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            //DrawCircleV(ballPosition, 50, MAROON);

            // EndDrawing();

        } break;
        case ENDING:
        {
            // TODO: Update ENDING screen variables here!
            DrawTexturePro(background,screen, screen, Vector2Zero(), 0,WHITE);
            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = TITLE;
            }
        } break;
        default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        //ClearBackground(WHITE);
        ClearBackground(GetColor(0x052c46ff));
        
       
        switch (currentScreen)
        {
        case LOGO:
        {
            // TODO: Draw LOGO screen here!
            DrawText("Loading", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

        } break;
        case TITLE:
        {
            // TODO: Draw TITLE screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("Zombz", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

        } break;
        case GAMEPLAY:
        {
            
            
            //DrawTextureRec(hero, hazmatRec, heroPos, WHITE);
        }break;
        case ENDING:
        {
            // TODO: Draw ENDING screen here!
            DrawRectangle(0, 0, screenWidth, screenHeight, RED);
            DrawText("Game OVER", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ESC	TO CLOSE", 120, 220, 20, DARKBLUE);
        }break;


        default: break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!
    UnloadTexture(hero);
    UnloadTexture(enemy);
    UnloadTexture(background);
    //ClearBackground(background);
    //UnloadTexture(background);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

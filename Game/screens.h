#ifndef SCREEN_H
#define SCREENS_H
#include "raylib.h"

typedef enum GameScreen	{UNKNOWN = -1, LOGO = 0, TITLE, GAMEPLAY, ENDING} GameScreen;

//GLobal Var
extern GameScreen currentScreen;
extern Font font;
extern Music music;
extern Sound fxScary;

void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);
	
		//TITLE SCREEN 
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);
		
		//GAMEPLAY SCREEN
void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void UnloadGameplayScreen(void);
int FinishGameplayScreen(void);

#endif // !SCREEN_H
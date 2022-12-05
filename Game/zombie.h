/*#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "raylib.h"

#define MONSTER_ANIM_FRAMES 7
#define MONSTER_ANIM_SEQ 2

class Zombie
{
	Vector2 position;
	Texture2D texture;
	Rectangle bounds;
    Rectangle frameRec;
    Color color;
    int framesCounter;
    int currentFrame;
    int currentSeq;
    int numFrames;
    bool active;
    bool selected;
    bool spooky;
}; Zombie;

void updateZombie(Zombie* zombie);
void DrawZombie(Zombie zombie, int scroll);
void UnloadZombie(Zombie zombie);



#endif // !ZOMBIE_H

*/
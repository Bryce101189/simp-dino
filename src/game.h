#ifndef _GAME_H
#define _GAME_H

#include "simp_engine/src/simp.h"

#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (720)

// Length of a single frame in milliseconds
#define FRAME_DURATION (1000 / 60)
// Y position of the floor
#define FLOOR_POSITION (-240)

extern Simp_Window* window;
extern Simp_Font* font;

void Game_Start(void);
void Game_End(void);

#endif // _GAME_H

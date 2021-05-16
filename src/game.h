#ifndef _GAME_H
#define _GAME_H

#include "simp_engine/simp.h"

#define FRAME_DURATION (1000 / 60)

#define FLOOR_POSITION (-160)

extern Simp_Window* window;

void Game_Start(void);
void Game_End(void);

#endif // _GAME_H
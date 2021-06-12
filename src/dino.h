#ifndef _DINO_H
#define _DINO_H

#include "simp_engine/src/simp.h"

#define ANIM_CYCLE_RATE (6)

extern Simp_Sprite* dino;

bool Dino_Init(void);
void Dino_Update(void);
void Dino_Destroy(void);

#endif // _DINO_H

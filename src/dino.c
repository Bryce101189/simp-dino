#include <stdio.h>

#include "simp_engine/src/simp.h"

#include "dino.h"
#include "game.h"

Simp_Sprite* dino = NULL;

static float speed = 0.0;
static int walkCycle = 0;

const static float GRAVITY = 1;
const static float HIGH_GRAVITY = 4;
const static float JUMP_FORCE = 23;

bool Dino_Init(void) {
    dino = Simp_CreateSpriteFromImage("resources/images/Dino.png");

    if(dino == NULL) {
        puts(Simp_GetError());
        return false;
    }

    dino->position.x = -350;
    dino->position.y = FLOOR_POSITION;

    dino->src_rect.width = 88;

    return true;
}

void Dino_Update(void) {
    const bool grounded = dino->position.y == FLOOR_POSITION;
    const bool crouching = grounded && Simp_GetKey(SIMP_KEY_DOWN);

    if(grounded) {
        speed = 0;
        ++walkCycle;
        
        if((Simp_GetKey(SIMP_KEY_UP) || Simp_GetKey(SIMP_KEY_SPACE)) && !Simp_GetKey(SIMP_KEY_DOWN)) {
            speed = JUMP_FORCE;
        }
    } else {
        walkCycle = 0;

        if(Simp_GetKey(SIMP_KEY_DOWN)) {
            speed -= HIGH_GRAVITY;
        } else {
            speed -= GRAVITY;
        }
    }

    // Move sprite
    dino->position.y += speed;

    // Avoid going below the floor
    if(dino->position.y < FLOOR_POSITION) {
        dino->position.y = FLOOR_POSITION;
    }

    // Select animation frame
    const int frame = (walkCycle % (ANIM_CYCLE_RATE * 2)) / ANIM_CYCLE_RATE;

    if(grounded) {
        if(crouching) {
            dino->src_rect.width = 118;
            dino->src_rect.x = 352 + frame * 118;
        } else {
            dino->src_rect.width = 88;
            dino->src_rect.x = 88 + frame * 88;
        }
    } else {
        dino->src_rect.width = 88;
        dino->src_rect.x = 0;
    }

    // Draw sprite
    Simp_DrawSprite(window, dino);
}

void Dino_Destroy(void) {
    if(dino != NULL) {
        Simp_DestroySprite(dino);
    }
}

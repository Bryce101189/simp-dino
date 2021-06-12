#include <stdio.h>

#include "simp_engine/src/simp.h"

#include "dino.h"
#include "game.h"

Simp_Sprite** obstacles = NULL;

Simp_Sprite* smallCacti = NULL;
Simp_Sprite* largeCacti = NULL;
Simp_Sprite* pterodactyl = NULL;

bool Obst_Init(void) {
    smallCacti = Simp_CreateSpriteFromImage("resources/images/SmallCacti.png");

    if(smallCacti == NULL) {
        puts(Simp_GetError());
        return false;
    }

    largeCacti = Simp_CreateSpriteFromImage("resources/images/LargeCacti.png");

    if(largeCacti == NULL) {
        puts(Simp_GetError());
        return false;
    }

    pterodactyl = Simp_CreateSpriteFromImage("resources/images/Pterodactyl.png");

    if(pterodactyl == NULL) {
        puts(Simp_GetError());
        return false;
    }

    return true;
}

void Obst_Update(void) {
}

void Obst_Render(void) {
    Simp_DrawSprite(window, pterodactyl);
}

void Obst_Destroy(void) {
    if(smallCacti != NULL) {
        Simp_DestroySprite(smallCacti);   
    }

    if(largeCacti != NULL) {
        Simp_DestroySprite(largeCacti);   
    }

    if(pterodactyl != NULL) {
        Simp_DestroySprite(pterodactyl);
    }
}

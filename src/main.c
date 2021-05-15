#include <stdio.h>

#include "simp_engine/simp.h"

#include "game.h"

int main(void) {
    // Initialize Simp engine
    if(!Simp_Init()) {
        puts(Simp_GetError());
        return 1;
    }

    Game_Start();
    Game_End();

    Simp_Quit();
}

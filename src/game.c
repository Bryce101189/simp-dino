#include <stdio.h>

#include "simp_engine/simp.h"

#include "dino.h"
#include "game.h"

Simp_Window* window = NULL;

void Game_Start(void) {
    // Create Simp window
    window = Simp_CreateWindow("Simp Dino", 854, 480);

    if(window == NULL) {
        puts(Simp_GetError());
        return;
    }

    if(!Dino_Init()) {
        return;
    }

    // Set clear color to white
    const Simp_Color colWhite = { 0xDF, 0xDF, 0xDF, 0xFF };
    Simp_SetClearColor(window, colWhite);

    long targetTime = Simp_GetMillisecondsElapsed();

    // Game loop
    while(!Simp_GetWindowEventStatus(window, SIMP_WINDOWEVENT_CLOSE)) {
        Simp_ClearScreen(window);
        Simp_PollInputs();

        Dino_Update();

        Simp_UpdateScreen(window);

        // Limit framerate to 60fps
        targetTime += FRAME_DURATION;
        const long elapsedTime = Simp_GetMillisecondsElapsed();
        
        if(targetTime > elapsedTime) {
            Simp_DelayMilliseconds(targetTime - elapsedTime);
        }
    }
}

void Game_End(void) {
    Dino_Destroy();
    
    if(window != NULL) {
        Simp_DestroyWindow(window);
    }
}

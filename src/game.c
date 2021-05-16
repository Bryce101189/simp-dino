#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simp_engine/simp.h"

#include "dino.h"
#include "game.h"
#include "scene.h"
#include "score.h"

Simp_Window* window = NULL;
Simp_Font* font = NULL;

void Game_Start(void) {
    srand(time(NULL));

    // Create Simp window
    window = Simp_CreateWindow("Simp Dino", WINDOW_WIDTH, WINDOW_HEIGHT);

    if(window == NULL) {
        puts(Simp_GetError());
        return;
    }

    // Load font
    font = Simp_LoadFont("resources/fonts/PressStart2P.ttf", 16);

    if(font == NULL) {
        puts(Simp_GetError());
        return ;
    }

    const Simp_Color colGray = { 0x53, 0x53, 0x53, 0xFF };
    font->color = colGray;

    // Initialize dino
    if(!Dino_Init() || !Scene_Init()) {
        return;
    }

    // Set clear color to white
    const Simp_Color colWhite = { 0xF7, 0xF7, 0xF7, 0xFF };
    Simp_SetClearColor(window, colWhite);

    long targetTime = Simp_GetMillisecondsElapsed();

    // Game loop
    while(!Simp_GetWindowEventStatus(window, SIMP_WINDOWEVENT_CLOSE)) {
        Simp_ClearScreen(window);
        Simp_PollInputs();

        // Update scene
        Scene_Update();
        Scene_Render();

        // Update dino
        Dino_Update();

        // Update score
        Score_Increment();
        Score_Update();

        // Update screen
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
    Scene_Destroy();

    if(font != NULL) {
        Simp_DestroyFont(font);
    }
    
    if(window != NULL) {
        Simp_DestroyWindow(window);
    }
}

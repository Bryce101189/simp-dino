#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simp_engine/src/simp.h"

#include "game.h"
#include "scene.h"

#define MAX_CLOUDS 16

static Simp_Sprite* floor1 = NULL;
static Simp_Sprite* floor2 = NULL;
const static float floorSpeed = 7;

static Simp_Sprite* cloud = NULL;
static Simp_Sprite** clouds = NULL;
const static float cloudSpeed = 0.9;

static int spawnCountdown = 0;

bool Scene_Init(void) {
    // Init clouds
    cloud = Simp_CreateSpriteFromImage("resources/images/Cloud.png");

    if(cloud == NULL) {
        puts(Simp_GetError());
        return false;
    }

    clouds = calloc(MAX_CLOUDS, sizeof(Simp_Sprite*));
    spawnCountdown = rand() % 100;

    // Init floors
    floor1 = Simp_CreateSpriteFromImage("resources/images/Ground.png");

    if(floor1 == NULL) {
        puts(Simp_GetError());
        return false;
    }

    // Clone sprite
    floor2 = malloc(sizeof(Simp_Sprite));
    memcpy(floor2, floor1, sizeof(Simp_Sprite));

    // Position floor
    floor1->position.y = FLOOR_POSITION - 35;
    floor2->position.y = FLOOR_POSITION - 35;

    floor1->position.x = (-WINDOW_WIDTH / 2) + (floor1->src_rect.width / 2);
    floor2->position.x = floor1->position.x + floor2->src_rect.width;

    return true;
}

void Scene_Update(void) {
    // Update clouds
    --spawnCountdown;

    if(spawnCountdown == 0) {
        // Create new cloud
        for(int i = 0; i < MAX_CLOUDS; ++i) {
            if(clouds[i] != NULL) {
                continue;
            }

            clouds[i] = malloc(sizeof(Simp_Sprite));
            memcpy(clouds[i], cloud, sizeof(Simp_Sprite));

            clouds[i]->position.x = (WINDOW_WIDTH / 2) + 50;
            clouds[i]->position.y = rand() % 300;
            break;
        }
    
        spawnCountdown = 160 + (rand() % 240);
    }

    for(int i = 0; i < MAX_CLOUDS; ++i) {
        if(clouds[i] != NULL) {
            // Move clouds
            clouds[i]->position.x -= cloudSpeed;

            // Free off-screen clouds
            if(clouds[i]->position.x < (-WINDOW_WIDTH / 2) - 50) {
                free(clouds[i]);
                clouds[i] = NULL;
            }
        }
    }

    for(int i = 0; i < MAX_CLOUDS; ++i) {
        printf("Cloud: %p\n", clouds[i]);
    }

    printf("\n");

    // Floor
    floor1->position.x -= floorSpeed;
    floor2->position.x -= floorSpeed;

    if(floor1->position.x < (-WINDOW_WIDTH / 2) - (floor1->src_rect.width / 2)) {
        floor1->position.x = floor2->position.x + floor1->src_rect.width;
    }

    if(floor2->position.x < (-WINDOW_WIDTH / 2) - (floor2->src_rect.width / 2)) {
        floor2->position.x = floor1->position.x + floor2->src_rect.width;
    }
}

void Scene_Render(void) {
    for(int i = 0; i < MAX_CLOUDS; ++i) {
        if(clouds[i] != NULL) {
            Simp_DrawSprite(window, clouds[i]);
        }
    }

    Simp_DrawSprite(window, floor1);
    Simp_DrawSprite(window, floor2);
}

void Scene_Destroy(void) {
    for(int i = 0; i < MAX_CLOUDS; ++i) {
        free(clouds[i]);
    }

    if(cloud != NULL) {
        Simp_DestroySprite(cloud);
    }

    if(floor1 != NULL) {
        Simp_DestroySprite(floor1);
    }

    if(floor2 != NULL) {
        free(floor2);
    }
}

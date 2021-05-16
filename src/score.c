#include <stdio.h>

#include "simp_engine/simp.h"

#include "game.h"
#include "score.h"

long score = 0;
long hiScore = 0;

static const Simp_Color colGray = { 0x53, 0x53, 0x53, 0xFF };
static const Simp_Color colDarkGray = { 0x3C, 0x3C, 0x3C, 0xFF };

void Score_Update(void) {
    char scoreText[32];

    sprintf(scoreText, "HI:  %ld", hiScore / 10);
    font->color = colDarkGray;
    Simp_Sprite* hiScoreSprite = Simp_CreateSpriteFromText(font, scoreText);

    hiScoreSprite->position.x = (-WINDOW_WIDTH / 2) + 8 + (hiScoreSprite->src_rect.width / 2);
    hiScoreSprite->position.y = WINDOW_HEIGHT / 2 - 24;

    sprintf(scoreText, "CUR: %ld", score / 10);
    font->color = colGray;
    Simp_Sprite* scoreSprite = Simp_CreateSpriteFromText(font, scoreText);

    scoreSprite->position.x = (-WINDOW_WIDTH / 2) + 8 + (scoreSprite->src_rect.width / 2);
    scoreSprite->position.y = WINDOW_HEIGHT / 2 - 48;

    Simp_DrawSprite(window, hiScoreSprite);
    Simp_DrawSprite(window, scoreSprite);

    Simp_DestroySprite(hiScoreSprite);
    Simp_DestroySprite(scoreSprite);
}

void Score_Increment(void) {
    ++score;

    if(score > hiScore) {
        hiScore = score;
    }
}

void Score_Reset(void) {
    score = 0;
}

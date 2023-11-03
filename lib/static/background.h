#ifndef BG_H
#define BG_H
#include <TFT_eSPI.h>
#include "color.h"
#include "background.h"
#include "screenb.h"

TFT_eSprite ceilT = TFT_eSprite(&spr);
TFT_eSprite floorT = TFT_eSprite(&spr);
uint16_t ceilColor = Color(56, 56, 56).toHex();
uint16_t floorColor = Color(113, 113, 113).toHex();

void initBG (TFT_eSprite *spr){
    ceilT.createSprite(spr->width(), spr->height() / 2);
    floorT.createSprite(spr->width(), spr->height() / 2);
}

void frameBG (TFT_eSprite *spr){
    spr->fillSprite(TFT_BLACK);
    ceilT.fillSprite(ceilColor);
    floorT.fillSprite(floorColor);
    ceilT.pushToSprite(spr, 0, 0);
    floorT.pushToSprite(spr, 0, spr->height() / 2);
}

#endif
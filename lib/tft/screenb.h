#ifndef SCREENB_H
#define SCREENB_H
#include <TFT_eSPI.h>
#include "color.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

void initScreen()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(Color{255, 128, 128}.toHex());
    spr.createSprite(tft.width(), tft.height());
}

#endif
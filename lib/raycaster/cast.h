#ifndef CAST_H
#define CAST_H

#include <Arduino.h>
#include "impact.h"
#include "player.h"
#include "map.h"

float castRay(float angle, Player *player)
{
    float c = 0;
    while (true)
    {
        int x = static_cast<int>(player->x + c * cos(angle));
        int y = static_cast<int>(player->y + c * sin(angle));

        int i = static_cast<int>(x / blockWidth);
        int j = static_cast<int>(y / blockHeight);

        if (!(i > 15 || j > 10))
        {
            if (mapV.at(j).charAt(i) != ' ')
            {
                break;
            }
        }
        miniMap.drawPixel(x, y, TFT_YELLOW);

        c += 0.2f;
    };
    return c;
}

void drawStake(uint16_t x, float h, Color c)
{
    float start = spr.height() / 2.0f - h / 2.0f;
    spr.fillRect(x, start, 1, h, c.toHex());
};

void render(Player *player, TFT_eSprite *spr)
{
    for (int i = 0; i < spr->width(); i++)
    {
        float a = player->angle + player->fov / 2.0f - player->fov * i / spr->width();
        float d = castRay(a, player);
        float h = 0;
        if (d != 0){
            h = (spr->height() / d) * 5.0f;
        } else {
            h = spr->height();
        }
        drawStake(i, h, Color(0, 255, 0));
    }
    miniMap.pushToSprite(spr, 0, 0);
}

#endif
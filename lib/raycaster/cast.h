#ifndef CAST_H
#define CAST_H

#include <Arduino.h>
#include "impact.h"
#include "player.h"
#include "map.h"
#include <string>
#include "colors.h"
#include <unordered_map>

Impact castRay(float angle, Player *player)
{
    float d = 0;
    std::string hit = " ";
    while (true)
    {
        int x = static_cast<int>(player->x + d * cos(angle));
        int y = static_cast<int>(player->y + d * sin(angle));

        int i = static_cast<int>(x / blockWidth);
        int j = static_cast<int>(y / blockHeight);

        if (!(i > 15 || j > 10))
        {
            if (mapV.at(j).at(i) != ' ')
            {
                hit = mapV.at(j).at(i);
                break;
            }
        }
        miniMap.drawPixel(x, y, TFT_YELLOW);

        d += 0.2f;
    };
    return Impact{d, colors[hit]};
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
        Impact impact = castRay(a, player);
        float h = 0;
        float correct = impact.d * cos(player->angle - a);
        if (impact.d != 0)
        {
            h = static_cast<float>(spr->height() / correct) * 5.0f;
        }
        else
        {
            h = spr->height();
        }
        drawStake(i, h, impact.color);
    }
    miniMap.pushToSprite(spr, 0, 0);
}

#endif
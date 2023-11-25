#ifndef CAST_H
#define CAST_H

#include <Arduino.h>
#include "impact.h"
#include "player.h"
#include "map.h"
#include <string>
#include "colors.h"
#include <unordered_map>

void movePlayer(Player *player, float deltaX, float deltaY)
{
    float newX = player->x + deltaX;
    float newY = player->y + deltaY;

    // Define a standard size for the player
    float playerSize = 0.8f;

    // Check the four corners of the player
    for (int corner = 0; corner < 4; corner++)
    {
        float cornerX = newX + (corner % 2 == 0 ? -playerSize : playerSize);
        float cornerY = newY + (corner < 2 ? -playerSize : playerSize);

        int i = static_cast<int>(cornerX / blockWidth);
        int j = static_cast<int>(cornerY / blockHeight);

        // Check if the proposed move would hit a wall
        if (i >= 0 && i < mapV.size() && j >= 0 && j < mapV[i].size())
        {
            char mapChar = mapV.at(j).at(i); // Get the character at the new position

            // If the character is 'g', display the victory screen
            if (mapChar == 'g')
            {
                spr.fillSprite(TFT_BLACK);                                        // Fill screen with black color
                spr.setTextColor(TFT_WHITE);                                      // Set text color to white
                spr.drawString("You Win!", spr.width() / 2, spr.height() / 2, 2); // Draw "You Win!" in the center of the screen
                spr.pushSprite(0, 0);                                             // Update the screen

                delay(2000); // Wait for 2000ms

                spr.fillSprite(TFT_BLACK); // Clear the screen

                // Here you can restart the game or do something else
                return;
            }

            // If the move would hit a wall, don't allow the move
            if (mapChar != ' ')
            {
                return;
            }
        }
    }

    // If none of the corners hit a wall, allow the move
    player->x = newX;
    player->y = newY;
}

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

        d += 0.2f; // Decrease the step size
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
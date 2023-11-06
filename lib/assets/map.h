#ifndef MAP_H
#define MAP_h
#include <Arduino.h>
#include "colors.h"
#include "color.h"
#include <TFT_eSPI.h>
#include <vector>
#include "screenb.h"
#include "player.h"
#include "cast.h"
#include <string>

std::vector<std::string> mapV;
TFT_eSprite miniMap = TFT_eSprite(&spr);
float blockWidth = 0;
float blockHeight = 0;

void initMap(Player *player)
{
    mapV.shrink_to_fit();
    mapV.push_back(std::string("+--------------+"));
    mapV.push_back(std::string("|           |  |"));
    mapV.push_back(std::string("|  +-----+  +  |"));
    mapV.push_back(std::string("|  |     |     |"));
    mapV.push_back(std::string("|  +--+  +--+  |"));
    mapV.push_back(std::string("|     |     |  |"));
    mapV.push_back(std::string("+--+  +--+  +  |"));
    mapV.push_back(std::string("|     |  |     |"));
    mapV.push_back(std::string("|  +--+  +  +**+"));
    mapV.push_back(std::string("|        |     g"));
    mapV.push_back(std::string("+-----------+**+"));
    miniMap.createSprite(spr.width() / 2.0f, spr.height() / 2.0f);
    miniMap.fillSprite(Color(113, 113, 113).toHex());
    blockWidth = static_cast<float>(miniMap.width()) / static_cast<float>(mapV.at(0).length());
    blockHeight = static_cast<float>(miniMap.height()) / static_cast<float>(mapV.size());
    miniMap.pushToSprite(&spr, 0, 0);
    player->x = blockWidth + (blockWidth / 2.0f);
    player->y = blockHeight + (blockHeight / 2.0f);
    player->angle = M_PI / 4.0f;
    player->fov = M_PI / 2.0f;
}

// Dibujar miniMapa
void loopMiniMap()
{
    miniMap.fillSprite(Color(113, 113, 113).toHex());
    for (float x = 0; x < miniMap.width(); x += blockWidth)
    {
        for (float y = 0; y < miniMap.height(); y += blockHeight)
        {
            int i = static_cast<int>(ceil(x) / blockWidth);
            int j = static_cast<int>(ceil(y) / blockHeight);

            if (!(i > mapV.at(0).length() || j > mapV.size()))
            {
                char mapChar = mapV.at(j).at(i); // Obtén el carácter del mapa

                // Usa el carácter como clave para acceder a 'colors'
                if (mapChar != ' ')
                {
                    std::string colorKey(1, mapChar); // Convierte el carácter a std::string
                    miniMap.fillRect(ceil(x), ceil(y), ceil(blockWidth), ceil(blockHeight), colors[colorKey].toHex());
                }
            }
        }
    }
    miniMap.pushToSprite(&spr, 0, 0);
}
#endif
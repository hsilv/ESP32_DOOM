#ifndef MAP_H
#define MAP_h
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <vector>
#include "screenb.h"

std::vector<String> mapV;
TFT_eSprite miniMap = TFT_eSprite(&spr);
float blockWidth = 0;
float blockHeight = 0;

void initMap()
{
    mapV.shrink_to_fit();
    mapV.push_back(String("+--+--+--+--+--+"));
    mapV.push_back(String("|           *  |"));
    mapV.push_back(String("+  +--+--+  +  +"));
    mapV.push_back(String("|  |     |     *"));
    mapV.push_back(String("+  +--+  +--+  +"));
    mapV.push_back(String("|     |     |  *"));
    mapV.push_back(String("+--+  +--+  +  +"));
    mapV.push_back(String("|     |  |     *"));
    mapV.push_back(String("+  +--+  +  +**+"));
    mapV.push_back(String("|        |     g"));
    mapV.push_back(String("+--+--+--+--+**+"));
    miniMap.createSprite(spr.width() / 1, spr.height() / 1);
    miniMap.fillSprite(TFT_RED);
    blockWidth = static_cast<float>(miniMap.width())/static_cast<float>(mapV.at(0).length());
    blockHeight = static_cast<float>(miniMap.height())/static_cast<float>(mapV.size());
    miniMap.pushToSprite(&spr, 0, 0);
}

//Dibujar miniMapa
void loopMiniMap()
{
    miniMap.fillSprite(TFT_RED);
    for (float x = 0; x < miniMap.width(); x+= blockWidth){
        for(float y = 0; y < miniMap.height(); y+= blockHeight){
            int i = static_cast<int>(ceil(x) / blockWidth);
            int j = static_cast<int>(ceil(y) / blockHeight);

            if(!(i > 15 || j > 10 )){
                if (mapV.at(j).charAt(i) != ' ')
                {
                    miniMap.fillRect(ceil(x), ceil(y), ceil(blockWidth), ceil(blockHeight), TFT_WHITE);
                }
            }
        }
    }
    miniMap.pushToSprite(&spr, 0, 0);
}
#endif
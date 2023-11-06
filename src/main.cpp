#include <Arduino.h>
#include <TFT_eSPI.h>
#include "color.h"
#include "background.h"
#include "screenb.h"
#include "player.h"
#include "cast.h"

#define VRX_PIN 35

#define VRY_PIN 34

Player player;
int valueX = 0;
int valueY = 0;
float sensibility = 0.1f;
float sensibilityPos = 0.5f;
float deathZone = 0.1f;

void setup()
{
  Serial.begin(115200);
  initScreen();
  initBG(&spr);
  initMap(&player);
}

void loop()
{
  frameBG(&spr);
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);

  float mappedX = (static_cast<float>(valueX) - 2048.0f) / 2048.0f;
  float mappedY = (static_cast<float>(valueY) - 2048.0f) / 2048.0f;

  mappedX = abs(mappedX) < deathZone ? 0.0f : mappedX;
  mappedY = abs(mappedY) < deathZone ? 0.0f : mappedY;

  if (mappedX != 0)
  {
    player.angle += mappedX * sensibility;
  }

  if (mappedY != 0){
    player.y += mappedY * sensibilityPos;
  }

  spr.drawPixel(mappedX * (spr.width() / 2.0f) + spr.width() / 2.0f, mappedY * (spr.height() / 2.0f) + spr.height() / 2.0f, TFT_WHITE);

  loopMiniMap();
  render(&player, &spr);
  spr.pushSprite(0, 0);
}
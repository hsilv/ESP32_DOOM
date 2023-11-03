#include <Arduino.h>
#include <TFT_eSPI.h>
#include "color.h"
#include "background.h"
#include "screenb.h"
#include "map.h"

#define VRX_PIN 35

#define VRY_PIN 34

int valueX = 0;
int valueY = 0;
float deathZone = 0.1f;

void setup()
{
  Serial.begin(115200);
  initScreen();
  initBG(&spr);
  initMap();
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

  spr.drawPixel(mappedX*(spr.width()/2.0f) + spr.width()/2.0f, mappedY*(spr.height()/2.0f) + spr.height()/2.0f, TFT_WHITE);

  loopMiniMap();
  spr.pushSprite(0, 0);
}
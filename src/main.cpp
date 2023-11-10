#include <Arduino.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>
#include "color.h"
#include <SD.h>
#include "background.h"
#include "screenb.h"
#include "player.h"
#include "cast.h"
#include "read.h"

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
  setupSD();
}

void loop()
{
  frameBG(&spr);
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);

  float mappedX = -(static_cast<float>(valueX) - 2048.0f) / 2048.0f;
  float mappedY = -(static_cast<float>(valueY) - 2048.0f) / 2048.0f;

  mappedX = abs(mappedX) < deathZone ? 0.0f : mappedX;
  mappedY = abs(mappedY) < deathZone ? 0.0f : mappedY;

  if (mappedX != 0)
  {
    player.angle += mappedX * sensibility;
  }

  if (mappedY != 0)
  {
    float deltaX = cos(player.angle) * mappedY * sensibilityPos;
    float deltaY = sin(player.angle) * mappedY * sensibilityPos;
    player.y += deltaY;
    player.x += deltaX;
  }

  loopMiniMap();
  render(&player, &spr);
  spr.pushSprite(0, 0);
}
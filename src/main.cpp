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
unsigned long lastTime;
unsigned long frameCount;
unsigned long fps;

void setup()
{
  Serial.begin(115200);
  initScreen();

  // Draw welcome screen
  spr.fillSprite(TFT_BLACK);                                        // Fill screen with black color
  spr.setTextColor(TFT_WHITE);                                      // Set text color to white
  spr.drawString("Bienvenido!", spr.width() / 2 - 30, spr.height() / 2 - 10, 2); // Draw "Welcome!" in the center of the screen
  spr.pushSprite(0, 0);                                             // Update the screen

  delay(2000); // Wait for 2000ms

  spr.fillSprite(TFT_BLACK); // Clear the screen

  // Continue with the rest of the setup
  initBG(&spr);
  initMap(&player);
  setupSD();
  lastTime = millis();
  frameCount = 0;
  fps = 0;
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
    movePlayer(&player, deltaX, deltaY); // Call movePlayer here
  }

  loopMiniMap();
  render(&player, &spr);

  // Calculate FPS
  frameCount++;
  if (millis() - lastTime >= 1000) // Every second
  {
    fps = frameCount;
    frameCount = 0;
    lastTime = millis();
  }

  String fpsText = "FPS: " + String(fps);
  spr.drawString(fpsText, spr.width() - 50, spr.height() - 15, 2); // Draw FPS at bottom-right corner
  spr.pushSprite(0, 0);
}
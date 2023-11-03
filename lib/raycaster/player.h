#ifndef PLAYER_H
#define PLAYER_H
#include <Arduino.h>

struct Player {
  uint16_t  x;
  uint16_t  y;
  float a;
  float fov;
};

#endif
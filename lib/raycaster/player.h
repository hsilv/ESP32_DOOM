#ifndef PLAYER_H
#define PLAYER_H
#include <Arduino.h>

struct Player {
  float x;
  float  y;
  float angle;
  float fov;
};

#endif
#include "LightController.h"
#include "RGB.h"

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow
{
private:
  LightController &controller;
  int ledCount;
  int currentOffset = 0;
  int updateState = 0;

  void show();
  void setState(int newState);
  int colorValueFor(float brightness, float fraction);
  float sinValueFor(float x, float phaseShift);
  RGB rainbowColorFor(int ledIndex);

public:
  void update();
  void clear();
  void simpleGreen();
  void rainbow();
  void waveWithOffset();

  Rainbow(LightController &controller, int ledCount);
};

#endif // RAINBOW_H
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
  int colorValueFor(float brightness, float fraction);
  float sinValueFor(float x, float phaseShift);

public:
  void update();
  void clear();
  void simpleGreen();
  void rainbow();
  void rainbowWave();
  void waveWithOffset();
  void setState(int newState);

  Rainbow(LightController &controller, int ledCount);
  RGB rainbowColorFor(int ledIndex);
};

#endif // RAINBOW_H
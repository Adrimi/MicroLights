#include "LightController.h"
#include "RGB.h"

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow
{
private:
  LightController &controller;
  int ledCount;
  int state;

  void show();
  int colorValueFor(int brightness, float fraction);
  float valueForFraction(float x, float phaseShift);

public:
  // MARK: - Declaration of light effects that Rainbow offers in public API
  void clear();
  void simpleGreen();
  void rainbow();
  void rainbowWave();
  void update();

  Rainbow(LightController &controller, int ledCount);
  RGB rainbowColorFor(int ledIndex);
};

#endif // RAINBOW_H
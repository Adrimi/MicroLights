#include "LightController.h"
#include "RGB.h"

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow
{
private:
  LightController &controller;
  int ledCount;

  void show();

public:
  // MARK: - Declaration of light effects that Rainbow offers in public API
  void clear();
  void simpleGreen();
  void rainbow();
  void rainbowWave();

  Rainbow(LightController &controller, int ledCount);
  RGB rainbowColorFor(int ledIndex);
};

#endif // RAINBOW_H
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
  RGB rainbowColorFor(int ledIndex);

public:
  // MARK: - Declaration of light effects that Rainbow offers in public API
  void clear();
  void simpleGreen();
  void rainbow();
  void rainbowWave();

  Rainbow(LightController &controller, int ledCount);
};

#endif // RAINBOW_H
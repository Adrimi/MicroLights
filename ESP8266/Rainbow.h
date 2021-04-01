#include "LightController.h"

#ifndef RAINBOW_H
#define RAINBOW_H

struct RGB
{
  uint8 r, g, b;
};

class Rainbow
{
private:
  LightController *controller;
  int ledNumber;

  void show();
  RGB rainbowColorFor(int ledIndex);

public:
  void clear();
  void simpleGreen();
  void rainbow();
  void rainbowWave();

  Rainbow(LightController *controller);
  ~Rainbow();
};

#endif // RAINBOW_H
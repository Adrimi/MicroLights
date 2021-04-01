#include "LightController.h"

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow
{
private:
  LightController &controller;

  void show();
  RGB rainbowColorFor(int ledIndex);

public:
  // MARK: - Declaration of light effects that Rainbow offers in public API
  void clear();
  void simpleGreen();
  void rainbow();
  void rainbowWave();

  Rainbow(LightController &controller);
  ~Rainbow();
};

#endif // RAINBOW_H
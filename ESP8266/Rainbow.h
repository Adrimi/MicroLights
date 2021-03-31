#include "Adafruit_NeoPixel.h"

#ifndef RAINBOW_H
#define RAINBOW_H

struct RGB
{
  uint8 r, g, b;
};

class Rainbow
{
private:
  Adafruit_NeoPixel pixels;
  int ledNumber;

  void show();
  RGB rainbowColorFor(int ledIndex);

public:
  void clear();
  void simpleGreen();
  void rainbow();
  void rainbowWave();

  Rainbow(int _ledNumber, int pin);
  ~Rainbow();
};

#endif // RAINBOW_H
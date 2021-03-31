#include "Adafruit_NeoPixel.h"

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow
{
private:
  Adafruit_NeoPixel pixels;
  int ledNumber;
  void show();

public:
  void clear();
  void simpleGreen();

  Rainbow(int _ledNumber, int pin);
  ~Rainbow();
};

#endif // RAINBOW_H
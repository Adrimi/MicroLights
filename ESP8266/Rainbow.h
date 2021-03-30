#include <Adafruit_NeoPixel.h>

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow
{
private:
  Adafruit_NeoPixel pixels;
  int ledNumber;

public:
  void clear();
  void show();
  void wave();

  Rainbow(int pin, int ledNumber);
};

#endif // RAINBOW_H
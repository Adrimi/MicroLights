#include "Adafruit_NeoPixel.h"

#ifndef NEOPIXELLIGHTCONTROLLER_H
#define NEOPIXELLIGHTCONTROLLER_H

class NeopixelLightController : public LightController
{
private:
  Adafruit_NeoPixel *pixels;

public:
  NeopixelLightController(Adafruit_NeoPixel *pixels);
};

#endif // NEOPIXELLIGHTCONTROLLER_H

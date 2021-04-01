#include "Adafruit_NeoPixel.h"
#include "LightController.h"

#ifndef NEOPIXELLIGHTCONTROLLER_H
#define NEOPIXELLIGHTCONTROLLER_H

class NeopixelLightController : public LightController
{
private:
  Adafruit_NeoPixel pixels;

public:
  virtual void clear();
  virtual void show();
  virtual void setColor(int index, RGB color);
  virtual void setBrightness(int level);

  NeopixelLightController(Adafruit_NeoPixel pixels);
};

#endif // NEOPIXELLIGHTCONTROLLER_H

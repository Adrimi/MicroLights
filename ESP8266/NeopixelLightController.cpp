#include "RGB.h"
#include "NeopixelLightController.h"
#include <Adafruit_NeoPixel.h>

NeopixelLightController::NeopixelLightController(Adafruit_NeoPixel pixels, int ledNumber) : pixels(pixels), ledNumber(ledNumber)
{
  pixels.begin();
}

void NeopixelLightController::clear()
{
  pixels.clear();
}

void NeopixelLightController::show()
{
  pixels.show();
}

void NeopixelLightController::setColor(int index, RGB color)
{
  pixels.setColor(index, color.r, color.g, color.b);
}

void NeopixelLightController::setBrightness(int level)
{
  pixels.setBrightness(level);
}
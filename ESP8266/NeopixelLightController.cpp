#include "RGB.h"
#include "NeopixelLightController.h"
#include <Adafruit_NeoPixel.h>

NeopixelLightController::NeopixelLightController(Adafruit_NeoPixel &pixels) : pixels(pixels)
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
  pixels.setPixelColor(index, color.g, color.r, color.b);
}

void NeopixelLightController::setBrightness(int level)
{
  pixels.setBrightness(level);
}
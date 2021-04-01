#include "NeopixelLightController.h"

NeopixelLightController::NeopixelLightController(Adafruit_NeoPixel pixels) : pixels(pixels)
{
  pixels.begin();
}

void NeopixelLightController::clear() {}
void NeopixelLightController::show() {}
void NeopixelLightController::setColor(int index, RGB color) {}
void NeopixelLightController::setBrightness(int level) {}
#include "RGB.h"
#include "NeopixelLightController.h"
#include <Adafruit_NeoPixel.h>

NeopixelLightController::NeopixelLightController(Adafruit_NeoPixel pixels) : pixels(pixels)
{
  Serial.println("initialization");
  pixels.begin();
}

void NeopixelLightController::clear()
{
  Serial.println("clear command");
  pixels.clear();
}

void NeopixelLightController::show()
{
  Serial.println("show command");
  pixels.show();
}

void NeopixelLightController::setColor(int index, RGB color)
{
  Serial.println("setColor commmand | " + (String)index + " : " + (String)color.r + ", " + (String)color.g + ", " + (String)color.b + ".");
  pixels.setPixelColor(index, color.r, color.g, color.b);
}

void NeopixelLightController::setBrightness(int level)
{
  Serial.println("set brightness command");
  pixels.setBrightness(level);
}
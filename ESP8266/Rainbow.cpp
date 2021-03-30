#include "Rainbow.h"
#include <Adafruit_NeoPixel.h>

Rainbow::Rainbow(int pin, int _ledNumber)
{
  pixels = Adafruit_NeoPixel(ledNumber, pin, NEO_RGB + NEO_KHZ800);
  ledNumber = _ledNumber;
}

void Rainbow::clear()
{
  Serial.println("clear effect");
  pixels.begin();
  pixels.clear();
}

void Rainbow::show()
{
  Serial.println("show effect");
  pixels.show();
}

void Rainbow::wave()
{
  Serial.println("wave effect - test 2");
  for (int i = 0; i < ledNumber; i++)
  {
    pixels.setPixelColor(i, 255, 0, 0);
  }
  pixels.setBrightness(255);
  show();
}
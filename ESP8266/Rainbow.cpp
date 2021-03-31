#include "Rainbow.h"
#include "Adafruit_NeoPixel.h"

Rainbow::Rainbow(int _ledNumber, int pin)
{
  pixels = Adafruit_NeoPixel(_ledNumber, pin, NEO_RGB + NEO_KHZ800);
  ledNumber = _ledNumber;
  pixels.begin();
}

Rainbow::~Rainbow()
{
  pixels = NULL;
  ledNumber = NULL;
}

void Rainbow::clear()
{
  Serial.println("clear effect");
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
#include "Rainbow.h"
#include "Adafruit_NeoPixel.h"
#include <math.h>

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

// MARK: - PRIVATE API

void Rainbow::show()
{
  pixels.show();
}

RGB Rainbow::rainbowColorFor(int ledIndex)
{
  float fraction = (float)ledIndex / (float)ledNumber;
  RGB colors;

  colors.r = round(255 * fraction);
  colors.g = round(255 * fmodf((fraction + (1 / 3)), 1));
  colors.b = round(255 * (1 - (fmodf((fraction + 2 / 3), 1) - 1 / 2)));

  return colors;
}

// MARK: - PUBLIC API

void Rainbow::clear()
{
  pixels.clear();
  show();
}

void Rainbow::simpleGreen()
{
  for (int i = 0; i < ledNumber; i++)
  {
    pixels.setPixelColor(i, 255, 0, 0);
  }
  pixels.setBrightness(255);
  show();
}

void Rainbow::rainbow()
{
  for (int i = 0; i < ledNumber; i++)
  {
    RGB colors = rainbowColorFor(i);
    pixels.setPixelColor(i, colors.r, colors.g, colors.b);
  }
  pixels.setBrightness(255);
  show();
}

void Rainbow::rainbowWave()
{
}
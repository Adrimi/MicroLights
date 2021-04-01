#include "Rainbow.h"
#include "Adafruit_NeoPixel.h"
#include "LightController.h"
#include <math.h>

Rainbow::Rainbow(LightController *_controller, int _ledNumber, int pin)
{
  controller = _controller;
  ledNumber = _ledNumber;
  pixels.begin();
}

Rainbow::~Rainbow()
{
  controller = NULL;
  ledNumber = NULL;
}

// MARK: - PRIVATE API

void Rainbow::show()
{
  controller->show();
}

RGB Rainbow::rainbowColorFor(int ledIndex)
{
  float fraction = (float)ledIndex / (float)ledNumber;
  float brightness = 255;
  float multiplier = 6;
  RGB colors;

  colors.r = round(brightness * fraction * multiplier);
  colors.g = round(brightness * fmodf((fraction + 0.3333), (float)1));
  colors.b = round(brightness * (1 - (fmodf((fraction + 0.6667), (float)1) - 0.5)) * multiplier);

  return colors;
}

// MARK: - PUBLIC API

void Rainbow::clear()
{
  controller->.clear();
  show();
}

void Rainbow::simpleGreen()
{
  for (int i = 0; i < ledNumber; i++)
  {
    controller->.setPixelColor(i, 255, 0, 0);
  }
  controller->.setBrightness(255);
  show();
}

void Rainbow::rainbow()
{
  for (int i = 0; i < ledNumber; i++)
  {
    RGB colors = rainbowColorFor(i);
    controller->.setPixelColor(i, colors.r, colors.g, colors.b);
  }
  controller->.setBrightness(255);
  show();
}

void Rainbow::rainbowWave()
{
}
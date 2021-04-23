#include "Rainbow.h"
#include "RGB.h"
#include <math.h>
#include <Arduino.h>

Rainbow::Rainbow(LightController &controller, int ledCount) : controller(controller), ledCount(ledCount) {}

// MARK: - PRIVATE API

void Rainbow::show()
{
  controller.show();
}

RGB Rainbow::rainbowColorFor(int ledIndex)
{
  float fraction = (float)ledIndex / (float)ledCount;
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
  controller.clear();
  show();
}

void Rainbow::simpleGreen()
{
  for (int i = 0; i < ledCount; i++)
  {
    RGB colors = {
        .r = 0,
        .g = 255,
        .b = 0};
    controller.setColor(i, colors);
  }
  controller.setBrightness(255);
  show();
}

void Rainbow::rainbow()
{
  // for (int i = 0; i < ledNumber; i++)
  // {
  //   RGB colors = rainbowColorFor(i);
  //   controller->.setPixelColor(i, colors.r, colors.g, colors.b);
  // }
  // controller->.setBrightness(255);
  // show();
}

void Rainbow::rainbowWave()
{
}
#include "Rainbow.h"
#include "RGB.h"
#include <math.h>
#include <Arduino.h>

#define PI 3.14
#define WAVE_STATE 3

Rainbow::Rainbow(LightController &controller, int ledCount) : controller(controller), ledCount(ledCount)
{
  state = 0;
}

// MARK: - PRIVATE API

void Rainbow::show()
{
  controller.show();
}

float Rainbow::valueForFraction(float x, float phaseShift)
{
  return 0.5 * (1 + sin((2 * PI * x) - phaseShift));
}

int Rainbow::colorValueFor(int brightness, float fraction)
{
  return round((float)brightness * fraction);
}

RGB Rainbow::rainbowColorFor(int ledIndex)
{
  float fraction = (float)ledIndex / (float)ledCount;
  float brightness = 255;
  RGB colors;

  colors.r = colorValueFor(brightness, valueForFraction(fraction, 0));
  colors.g = colorValueFor(brightness, valueForFraction(fraction, (2 * PI) / 3));
  colors.b = colorValueFor(brightness, valueForFraction(fraction, (4 * PI) / 3));

  return colors;
}

// MARK: - PUBLIC API

void Rainbow::update()
{
  Serial.println((String)state);
  if (state == WAVE_STATE)
  {
    rainbowWave();
  }
}

void Rainbow::clear()
{
  state = 0;
  controller.clear();
  show();
}

void Rainbow::simpleGreen()
{
  state = 1;
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
  state = 2;
  for (int i = 0; i < ledCount; i++)
  {
    controller.setColor(i, rainbowColorFor(i));
  }
  controller.setBrightness(255);
  show();
}

void Rainbow::rainbowWave()
{
  state = WAVE_STATE;

  for (int i = 0; i < ledCount; i++)
  {
    for (int j = 0; j < ledCount; j++)
    {
      controller.setColor(j, rainbowColorFor((j + i) % ledCount));
    }
    controller.setBrightness(255);
    show();
  }
}
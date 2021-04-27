#include "Rainbow.h"
#include "RGB.h"
#include <math.h>
#include <Arduino.h>

#define PI 3.14
#define WAVE_STATE 3

Rainbow::Rainbow(LightController &controller, int ledCount) : controller(controller), ledCount(ledCount) {}

// MARK: - PRIVATE API

void Rainbow::show()
{
  controller.show();
}

float Rainbow::sinValueFor(float x, float phaseShift)
{
  return 0.5 * (1 + sin((2 * PI * x) - phaseShift));
}

int Rainbow::colorValueFor(float brightness, float fraction)
{
  return round(brightness * fraction);
}

RGB Rainbow::rainbowColorFor(int ledIndex)
{
  float fraction = (float)ledIndex / (float)ledCount;
  float brightness = 255;
  RGB colors;

  colors.r = colorValueFor(brightness, sinValueFor(fraction, 0));
  colors.g = colorValueFor(brightness, sinValueFor(fraction, (2 * PI) / 3));
  colors.b = colorValueFor(brightness, sinValueFor(fraction, (4 * PI) / 3));

  return colors;
}

void Rainbow::setState(int newState)
{
  if (updateState != newState)
  {
    updateState = newState;
  }
}

// MARK: - PUBLIC API

void Rainbow::update()
{
  if (updateState == WAVE_STATE)
  {
    if (currentOffset >= ledCount - 1)
    {
      currentOffset = 0;
    }
    else
    {
      currentOffset++;
    }
    waveWithOffset();
  }
}

void Rainbow::clear()
{
  setState(0);
  controller.clear();
  show();
}

void Rainbow::simpleGreen()
{
  setState(1);
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
  setState(2);
  for (int i = 0; i < ledCount; i++)
  {
    controller.setColor(i, rainbowColorFor(i));
  }
  controller.setBrightness(255);
  show();
}

void Rainbow::waveWithOffset()
{
  setState(WAVE_STATE);
  for (int j = 0; j < ledCount; j++)
  {
    controller.setColor(j, rainbowColorFor((j + currentOffset) % ledCount));
  }
  controller.setBrightness(255);
  show();
}

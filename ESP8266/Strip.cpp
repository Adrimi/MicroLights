#include <Adafruit_NeoPixel.h>
#include "Strip.h"

Strip::Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype)
{
  effect = -1;
  effects = toteffects;
  Reset();
}

void Strip::Reset()
{
  effStep = 0;
  effect = (effect + 1) % effects;
  effStart = millis();
}

uint8_t Strip::strip0_loop0_eff0()
{
  // Strip ID: 0 - Effect: Rainbow - LEDS: 60
  // Steps: 60 - Delay: 20
  // Colors: 3 (255.0.0, 0.255.0, 0.0.255)
  // Options: rainbowlen=60, toLeft=true,
  if (millis() - effStart < 20 * (effStep))
    return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for (uint16_t j = 0; j < 60; j++)
  {
    ind = effStep + j * 1;
    switch ((int)((ind % 60) / 20))
    {
    case 0:
      factor1 = 1.0 - ((float)(ind % 60 - 0 * 20) / 20);
      factor2 = (float)((int)(ind - 0) % 60) / 20;
      strip.setPixelColor(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
      break;
    case 1:
      factor1 = 1.0 - ((float)(ind % 60 - 1 * 20) / 20);
      factor2 = (float)((int)(ind - 20) % 60) / 20;
      strip.setPixelColor(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
      break;
    case 2:
      factor1 = 1.0 - ((float)(ind % 60 - 2 * 20) / 20);
      factor2 = (float)((int)(ind - 40) % 60) / 20;
      strip.setPixelColor(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
      break;
    }
  }
  if (effStep >= 60)
  {
    Reset();
    return 0x03;
  }
  else
    effStep++;
  return 0x01;
}

Loop::Loop(uint8_t totchilds, bool timebased, uint16_t tottime)
{
  currentTime = 0;
  currentChild = 0;
  childs = totchilds;
  timeBased = timebased;
  cycles = tottime;
}

uint8_t Loop::strip0_loop0()
{
  uint8_t ret = 0x00;
  switch (currentChild)
  {
  case 0:
    ret = strip0_loop0_eff0();
    break;
  }
  if (ret & 0x02)
  {
    ret &= 0xfd;
    if (currentChild + 1 >= childs)
    {
      currentChild = 0;
      if (++currentTime >= cycles)
      {
        currentTime = 0;
        ret |= 0x02;
      }
    }
    else
    {
      currentChild++;
    }
  };
  return ret;
}

#include "Rainbow.h"

#ifndef RAINBOWANIMATIONADAPTER_H
#define RAINBOWANIMATIONADAPTER_H

class RainbowAnimationAdapter
{
private:
  Rainbow *_rainbow;

public:
  unsigned long previousTime = 0;
  unsigned int FPS = 20;

  RainbowAnimationAdapter(Rainbow *rainbow) : _rainbow(rainbow) {}

  void setFPS(unsigned int newFPS)
  {
    if (newFPS != 0)
    {
      FPS = newFPS;
    }
  }

  void updateAnimations(unsigned long currentTime)
  {
    if (currentTime - previousTime >= 1000 / FPS)
    {
      previousTime = currentTime;
      _rainbow->update();
    }
  }

  // RAINBOW METHODS MAPPER
  void clear() { _rainbow->clear(); }
  void simpleGreen() { _rainbow->simpleGreen(); }
  void rainbow() { _rainbow->rainbow(); }
  void waveWithOffset() { _rainbow->waveWithOffset(); }
};

#endif // RAINBOWANIMATIONADAPTER_H

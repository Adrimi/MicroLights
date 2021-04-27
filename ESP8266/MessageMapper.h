#include "RainbowAnimationAdapter.h"

#ifndef MESSAGEMAPPER_H
#define MESSAGEMAPPER_H

class MessageMapper
{
public:
  static void mapToRainbow(const char *data, RainbowAnimationAdapter *adapter)
  {
    int config;
    unsigned int setting;
    if (sscanf(data, "%d:%d$", &config, &setting) == 2)
    {
      Serial.println("Decoded value: " + (String)config);
      if (config == 0)
      {
        adapter->clear();
      }
      else if (config == 1)
      {
        adapter->simpleGreen();
      }
      else if (config == 2)
      {
        adapter->rainbow();
      }
      else if (config == 3)
      {
        adapter->setFPS(setting);
        adapter->waveWithOffset();
      }
    }
  }
};

#endif // MESSAGEMAPPER_H
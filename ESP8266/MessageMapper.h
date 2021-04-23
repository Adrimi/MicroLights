#include "Rainbow.h"

#ifndef MESSAGEMAPPER_H
#define MESSAGEMAPPER_H

class MessageMapper
{
public:
  static void mapToRainbow(const char *data, Rainbow rainbow)
  {
    int config;
    if (sscanf(data, "%d$", &config) == 1)
    {
      Serial.println("Decoded value: " + (String)config);
      if (config == 0)
      {
        rainbow.clear();
      }
      else if (config == 1)
      {
        rainbow.simpleGreen();
      }
      else if (config == 2)
      {
        rainbow.rainbow();
      }
      else if (config == 3)
      {
        rainbow.rainbowWave();
      }
    }
  }
};

#endif // MESSAGEMAPPER_H
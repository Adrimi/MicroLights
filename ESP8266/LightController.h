#include "RGB.h"

#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

class LightController
{
public:
  virtual void clear() = 0;
  virtual void show() = 0;
  virtual void setColor(int index, RGB color) = 0;
  virtual void setBrightness(int level) = 0;
};

#endif // LIGHTCONTROLLER_H

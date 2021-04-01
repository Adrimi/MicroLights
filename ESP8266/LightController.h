#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

struct RGB
{
  uint8 r, g, b;
};

class LightController
{
  virtual void show();
  virtual void setColor(int index, RGB color);
  virtual void setBrightness(uint8 level);
};

#endif // LIGHTCONTROLLER_H

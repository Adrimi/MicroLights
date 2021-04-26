#include <iostream>
#include "Rainbow.h"
#include "LightController.h"
#include "RGB.h"

class Stub : public LightController
{
public:
  void clear(){};
  void show(){};
  void setColor(int index, RGB color)
  {
    std::cout << index << " | " << color.r << " " << color.g << " " << color.b << std::endl;
  };
  void setBrightness(int level){};
};

int main()
{
  int ledNumber = 60;
  Stub s = Stub();
  Rainbow r = Rainbow(s, ledNumber);
  for (int i = 0; i < ledNumber; i++)
  {
    RGB rainbowColors = r.rainbowColorFor(i);
    s.setColor(i, rainbowColors);
  }
  return 0;
}

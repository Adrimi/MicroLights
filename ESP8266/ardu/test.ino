/*

NeoPixel LEDs

modified on 7 May 2019
by Saeed Hosseini @ Electropeak
https://electropeak.com/learn/

*/

#include <Adafruit_NeoPixel.h>

#define PIN 4
#define NUMPIXELS 60

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void NeoFade(int FadeSpeed)
{
  int fspeed;
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 165, 242, 243);
  }
  for (int j = 255; j > 0; j = j - 2)
  {
    pixels.setBrightness(j);
    pixels.show();
    delay(FadeSpeed);
  }
}

void setup()
{
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop()
{
  NeoFade(100);
}
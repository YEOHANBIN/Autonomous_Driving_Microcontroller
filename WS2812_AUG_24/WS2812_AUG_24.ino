#include <NeoPixelBus.h>
unsigned int colorSaturation = 128;

const uint16_t PixelCount = 4; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);
RgbColor orange(255, 204, 0);

void setup() {
  // put your setup code here, to run once:
  strip.Begin();
  //strip.Show();
}

void loop() {
  // put your main code here, to run repeatedly:
  // colorSaturation = 10;
  strip.SetPixelColor(0, red);
  strip.SetPixelColor(1, red);
  strip.SetPixelColor(2, white);
  strip.SetPixelColor(3, white);
  strip.Show();
  delay(1000);

  strip.SetPixelColor(1, orange);
  strip.SetPiXelColor(3, orange);
  strip.Show();
  delay(500);

  strip.SetPixelColor(1, black);
  strip.SetPiXelColor(3, black);
  strip.Show();
  delay(500);
}

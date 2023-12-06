#include <NeoPixelBus.h>

#define colorSaturation 128
#define Trigger 7
#define Echo 8

const uint16_t PixelCount = 4;
const uint8_t PixelPin = 2;

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor white(colorSaturation);
RgbColor black(0);

void setup() {
  strip.Begin();
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
}

unsigned int time_dis;
float distance;

void loop() {
  digitalWrite(Trigger, LOW);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  time_dis = pulseIn(Echo, HIGH);
  distance = 17.0*time_dis/100;

  if(distance < 50.0){
    strip.SetPixelColor(0, red);
    strip.SetPixelColor(1, red);
    strip.SetPixelColor(2, white);
    strip.SetPixelColor(3, white);
    strip.Show();
  }
  else{
    strip.SetPixelColor(0, black);
    strip.SetPixelColor(1, black);
    strip.SetPixelColor(2, black);
    strip.SetPixelColor(3, black);
    strip.Show();
  }
}

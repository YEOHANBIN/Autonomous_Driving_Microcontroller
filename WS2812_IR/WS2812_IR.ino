#include <NeoPixelBus.h>

#define colorSaturation 128
#define Right_IR 37
#define Left_IR 35
#define Right_M_IR 38
#define Left_M_IR 34

const uint16_t PixelCount = 4;
const uint8_t PixelPin = 2;

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);
RgbColor orange(255, 204, 0);

unsigned int R_value, L_value, R_M_value, L_M_value;

void setup() {
  strip.Begin();
  Serial.begin(9600);
  pinMode(Right_IR, INPUT);
  pinMode(Left_IR, INPUT);
  pinMode(Right_M_IR, INPUT);
  pinMode(Left_M_IR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  R_value = analogRead(Right_IR);
  L_value = analogRead(Left_IR);
  R_M_value = analogRead(Right_M_IR);
  L_M_value = analogRead(Left_M_IR);

  Serial.print("LEFT = ");
  Serial.print(L_value);
  Serial.print("          LEFT_M = ");
  Serial.print(L_M_value);
  Serial.print("          RIGIHT_M = ");
  Serial.print(R_M_value);
  Serial.print("          RIGHT = ");
  Serial.println(R_value);
  delay(330);

  if(L_value>300 && L_M_value>300){
    strip.SetPixelColor(0, black);
    strip.SetPixelColor(1, orange);
    strip.SetPixelColor(2, black);
    strip.SetPixelColor(3, orange);
    strip.Show();
  }
  else if(R_value>300 && R_M_value>300){
    strip.SetPixelColor(0, orange);
    strip.SetPixelColor(1, black);
    strip.SetPixelColor(2, orange);
    strip.SetPixelColor(3, black);
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

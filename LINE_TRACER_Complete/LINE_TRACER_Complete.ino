#include "iFMotors_LINE_TRACER.h"

const uint16_t PixelCount = 4;
const uint8_t PixelPin = 2;

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

void iFMotors::init(){
    // including this does not change anything
    pinMode(LEFT_F, OUTPUT);
    pinMode(LEFT_R, OUTPUT);
    pinMode(RIGHT_F, OUTPUT);
    pinMode(RIGHT_R, OUTPUT);
    pinMode(25, INPUT_PULLDOWN);
    pinMode(14, INPUT_PULLDOWN);
    pinMode(13, INPUT_PULLDOWN);
    pinMode(15, INPUT_PULLDOWN);


    ledcSetup(LEFT_F_CH, FREQUENCY, _nPWMResBit);
    ledcSetup(LEFT_R_CH, FREQUENCY, _nPWMResBit);
    ledcSetup(RIGHT_F_CH, FREQUENCY, _nPWMResBit);                
    ledcSetup(RIGHT_R_CH, FREQUENCY, _nPWMResBit);

    ledcAttachPin(LEFT_F, LEFT_F_CH);                  
    ledcAttachPin(LEFT_R, LEFT_R_CH);
    ledcAttachPin(RIGHT_F, RIGHT_F_CH);   
    ledcAttachPin(RIGHT_R, RIGHT_R_CH);   

    ledcWrite(LEFT_F_CH, 0 );
    ledcWrite(LEFT_R_CH, 0 );  
    ledcWrite(RIGHT_F_CH, 0 );
    ledcWrite(RIGHT_R_CH, 0 );

    LT_LW_MS = TURNING_MIN_SPEED;
    LT_RW_MS = TURNING_MIN_SPEED;
    RT_LW_MS = TURNING_MIN_SPEED;
    RT_RW_MS = TURNING_MIN_SPEED;

    ui32MAX_FORWARD_SPEED = MAX_FORWARD_SPEED;
    ui32MIN_FORWARD_SPEED = MIN_FORWARD_SPEED;
    LW_FS = MIN_FORWARD_SPEED;
    RW_FS = MIN_FORWARD_SPEED;
    LW_BS = MIN_BACK_SPEED;
    RW_BS = MIN_BACK_SPEED;
}

//motor 동작 함수(좌우, 전후, 속도(~1023))
void iFMotors::pwmWrite(int wheel, int direct, uint32_t value)
{
    if( direct == BACKWARD ){
        if( wheel == WHEEL_LEFT ){
            ledcWrite(LEFT_R_CH, 0 ); 
            ledcWrite(LEFT_F_CH, value );
        }
        else{
            ledcWrite(RIGHT_R_CH, 0 );       
            ledcWrite(RIGHT_F_CH, value );     
        }
    }
    else{
        if( wheel == WHEEL_LEFT ){
            ledcWrite(LEFT_F_CH, 0 );            
            ledcWrite(LEFT_R_CH, value ); 
        }
        else{
            ledcWrite(RIGHT_F_CH, 0 ); 
            ledcWrite(RIGHT_R_CH, value );  
        }
    }
}


void iFMotors::motorStop()
{
    pwmWrite(WHEEL_LEFT, FORWARD, 0);
    pwmWrite(WHEEL_RIGHT, FORWARD, 0);
    pwmWrite(WHEEL_LEFT, BACKWARD, 0);
    pwmWrite(WHEEL_RIGHT, BACKWARD, 0);            
}

void iFMotors::motorGo(){
  pwmWrite(WHEEL_RIGHT, FORWARD, 880);
  pwmWrite(WHEEL_LEFT, FORWARD, 770);
  }

void iFMotors::motorBack(){
  ifMotor.pwmWrite(WHEEL_RIGHT, BACKWARD, 800);
  pwmWrite(WHEEL_LEFT, BACKWARD, 800);
}
          
void iFMotors::motorLeftTurn()
{
    //// this slowly increases speed
    if (LT_LW_MS < TURNING_LM_MAX_SPEED) LT_LW_MS += MOTOR_SPEED_STEP;
    else LT_LW_MS = TURNING_MIN_SPEED;

    if (LT_RW_MS < TURNING_RM_MAX_SPEED) LT_RW_MS += MOTOR_SPEED_STEP;
    else LT_RW_MS = TURNING_MIN_SPEED;
    //// this slowly increases speed
    
    pwmWrite(WHEEL_LEFT, FORWARD, 0);
    pwmWrite(WHEEL_RIGHT, FORWARD, LT_RW_MS);
}

void iFMotors::motorRightTurn()
{
    //// this slowly increases speed
    if (RT_LW_MS < TURNING_LM_MAX_SPEED) RT_LW_MS += MOTOR_SPEED_STEP;
    else RT_LW_MS = TURNING_MIN_SPEED;

    if (RT_RW_MS < TURNING_RM_MAX_SPEED) RT_RW_MS += MOTOR_SPEED_STEP;
    else RT_RW_MS = TURNING_MIN_SPEED;
    //// this slowly increases speed

    pwmWrite(WHEEL_RIGHT, FORWARD, 0);
    pwmWrite(WHEEL_LEFT, FORWARD, RT_LW_MS);
}

void iFMotors::reset_ltrt_ms()
{
    LT_LW_MS = TURNING_MIN_SPEED;
    LT_RW_MS = TURNING_MIN_SPEED;
    RT_LW_MS = TURNING_MIN_SPEED;
    RT_RW_MS = TURNING_MIN_SPEED;
}

void iFMotors::reset_max_forwardSpeed()
{
    ui32MAX_FORWARD_SPEED = MAX_FORWARD_SPEED;
}

iFMotors      ifMotor;

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);
RgbColor orange(255, 204, 0);

void setup() {
  // put your setup code here, to run once:
  ifMotor.init();
  strip.Begin();
  Serial.begin(9600);                       //1초에 9600bit 전송
  pinMode(Right_IR, INPUT);
  pinMode(Left_IR, INPUT);
  pinMode(Right_M_IR, INPUT);
  pinMode(Left_M_IR, INPUT);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);

}

unsigned int R_value, L_value, R_M_value, L_M_value, time_dis;
float distance;

void loop() {
  // put your main code here, to run repeatedly:
  R_value = analogRead(Right_IR);
  L_value = analogRead(Left_IR);
  R_M_value = analogRead(Right_M_IR);
  L_M_value = analogRead(Left_M_IR);

  digitalWrite(Trigger, LOW);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);            //센서 spec 상, 최소 10s단위로 전송
  digitalWrite(Trigger, LOW);

  time_dis = pulseIn(Echo, HIGH);
  distance = 17.0*time_dis/100;

  strip.SetPixelColor(0, red);
  strip.SetPixelColor(1, red);
  strip.SetPixelColor(2, white);
  strip.SetPixelColor(3, white);
  strip.Show();

  if (distance < 50.0) ifMotor.motorStop();
  else{
    if((R_value < 150)&&(L_value > 1000)) {
      ifMotor.pwmWrite(WHEEL_RIGHT, BACKWARD, 500);
      ifMotor.pwmWrite(WHEEL_LEFT, FORWARD, 700);
      strip.SetPixelColor(0, orange);
      strip.SetPixelColor(1, black);
      strip.SetPixelColor(2, orange);
      strip.SetPixelColor(3, black);
      strip.Show();
      }
    else if((R_value > 1000)&&(L_value < 150)) {
      ifMotor.pwmWrite(WHEEL_RIGHT, FORWARD, 700);
      ifMotor.pwmWrite(WHEEL_LEFT, BACKWARD, 500);
      strip.SetPixelColor(0, black);
      strip.SetPixelColor(1, orange);
      strip.SetPixelColor(2, black);
      strip.SetPixelColor(3, orange);
      strip.Show();
      }
    else if((R_value > 2000)&&(L_value > 2000)&&(R_M_value > 1500)&&(L_M_value > 1500)){
      ifMotor.pwmWrite(WHEEL_RIGHT, BACKWARD, 800);
      ifMotor.pwmWrite(WHEEL_LEFT, BACKWARD, 800);
      strip.SetPixelColor(0, red);
      strip.SetPixelColor(1, red);
      strip.SetPixelColor(2, black);
      strip.SetPixelColor(3, black);
      strip.Show();
      }
    else{
      ifMotor.pwmWrite(WHEEL_RIGHT, FORWARD, 880);
      ifMotor.pwmWrite(WHEEL_LEFT, FORWARD, 770);
      }
    }
}

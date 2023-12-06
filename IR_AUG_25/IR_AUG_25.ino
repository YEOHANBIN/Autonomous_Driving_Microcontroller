#define Right_IR 37
#define Left_IR 35
#define Right_M_IR 38
#define Left_M_IR 34

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                       //1초에 9600bit 전송
  pinMode(Right_IR, INPUT);
  pinMode(Left_IR, INPUT);
  pinMode(Right_M_IR, INPUT);
  pinMode(Left_M_IR, INPUT);

}

unsigned int R_value, L_value, R_M_value, L_M_value;

void loop() {
  // put your main code here, to run repeatedly:
  R_value = analogRead(Right_IR);
  L_value = analogRead(Left_IR);
  R_M_value = analogRead(Right_M_IR);
  L_M_value = analogRead(Left_M_IR);

  //Serial.write(R_value);
  Serial.print("LEFT = ");
  Serial.print(L_value);
  Serial.print("          LEFT_M = ");
  Serial.print(L_M_value);
  Serial.print("          RIGIHT_M = ");
  Serial.print(R_M_value);
  Serial.print("          RIGHT = ");
  Serial.println(R_value);
  delay(330);
}

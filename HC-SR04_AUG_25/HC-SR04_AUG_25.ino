#define Trigger 7
#define Echo 8

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);

}

unsigned int time_dis;
float distance;

void loop() {
  digitalWrite(Trigger, LOW);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);            //센서 spec 상, 최소 10s단위로 전송
  digitalWrite(Trigger, LOW);

  time_dis = pulseIn(Echo, HIGH);
  distance = 17.0*time_dis/100;
  Serial.println(distance);
  delay(330);
}

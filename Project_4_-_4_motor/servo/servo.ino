#include <Servo.h>
int pinServo = 3;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(pinServo);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i <= 180; i = i + 20)
  {
    servo.write(i);
    delay(1000);
  }
}

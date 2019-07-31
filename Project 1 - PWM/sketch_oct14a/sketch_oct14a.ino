int ledPin = 10;
int switchPin = 8;
int motorPin = 5;
boolean reading = LOW;
boolean previous = LOW;
boolean isPush = LOW;
boolean ledOn = false;
int ledLevel = 0;

#include<Servo.h>

Servo servo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  servo.attach(motorPin);
  servo.write(0);
  delay(1000);
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(switchPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}

void loop() {
  //Текущее состояние кнопки
  reading = debounce(previous);
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);
  //Serial.println(lastButton);
  if(isPush == HIGH)
  {
    if (ledLevel > 255){
      ledLevel = 0;
    }
    ledLevel += 1;
    //Serial.println(ledLevel);
    delay(20);
    analogWrite(ledPin, ledLevel);
  }
  //Проверяет состояние кнопки. Если кнопка нажата один раз, то включаем светодиод, если еще раз нажата, то отключаем и т.д.
    if (reading == HIGH && previous == LOW){
      isPush == LOW ? isPush = HIGH : isPush = LOW;
    } 
    //Прошлое состояние кнопки
    previous = reading;
}

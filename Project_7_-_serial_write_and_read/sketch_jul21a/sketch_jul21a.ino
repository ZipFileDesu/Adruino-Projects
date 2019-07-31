int pinLed = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    int val = Serial.read() - '0';
    Serial.println(val);
    if (val >= 0) {
      analogWrite(pinLed, 25.5 * val);
    }
  }
}

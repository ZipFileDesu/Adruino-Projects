unsigned long last_time;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - last_time > 1000) {
     last_time = millis();
     Serial.println(last_time);
  }
}

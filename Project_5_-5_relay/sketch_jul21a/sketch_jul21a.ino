int relayPin = 5;
int ledPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(relayPin);
  val = map(val, 0, 1023, 0, 255);
  val = constrain(val, 0, 255);
  Serial.println(val);
  analogWrite(ledPin, val);
}
